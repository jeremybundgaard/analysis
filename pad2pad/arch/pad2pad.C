// NIFFTE Libraries
#include "NiffteRootIO.h"
#include "NiffteDataBucket.h"
#include "NiffteEventHandle.h"
#include "NiffteEventHandle.h"
#include "NiffteTPCTrack.h"
#include "NiffteTPCDigit.h"
#include "NiffteTPCADCSignal.h"
#include "NiffteMCParticle.h"
#include "NiffteMCHit.h"
#include "NiffteGeometryMap.h"
#include "NiffteAnalysisManager.h"
#include "AnaHistoList.h"
#include "AnaH1D.h"
#include "AnaH2D.h"
#include "AnaH2PadPlane.h"
#include "AnaH1DR.h"
#include "AnaH2DR.h"
#include "MsgLog.h"

// ROOT libraries
#include "TROOT.h"
#include "TRint.h"
#include "TObjArray.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include "TH2Poly.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TPaletteAxis.h"
#include "TGraph.h"
#include "TFile.h"
#include "TCutG.h"

// C++ libraries
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <numeric>
#include <climits>
#include <vector>

TObjArray *sigArray;
TObjArray *digArray;
TObjArray *trkArray;

NiffteGeometryMap* ngm = NiffteGeometryMap::Instance("v2_03");

void pad2pad(const char* infile = "infile-list.txt", const char* outfile="Analysis-RunXXX.root", int nevt = -1) {

//Niffte Analysis------------------------------
std::string geo("v2_03");
std::string ofile(outfile);
NiffteAnalysisManager aMgr(infile,ofile,geo);

//Open file list -----------------------------------------
if(nevt == -1)
	nevt = INT_MAX;

int nSkip = 0, SparseFactor = 0;
int iTrk = 0;
int Fit = 0;
int sample=0,trig=0;
int totNumEvents=0;
int volume=0;
int nbins = 0;
double trkADC = 0;
double trkL = 0;
double xStart = 0;
double yStart = 0;
double zStart = 0;
double x = 0, y = 0, z = 0, distance = 0;
double tmin=-1;
const double tiny = 1.0e-10;
const double kBinWidth = 0.1; // cm
double numerator = 0,denominator = 0;
double t = 0, length = 0, totalADC = 0, xTMax = 0, xTMin = 0, hmax = 0, hmin = 0;
char htitle[256];
TString histName = "trk_"; 

// Constants for HexagonXY voxels
const double rt3over2=std::sqrt(3.0)/2.0;
const double a = ngm->GetA();
const double h = ngm->GetDriftDistance()/ngm->GetNBuckets();
const double faceCenters[8][3] = {
  {0, 0, -h/2}, {0, a, 0}, {a*rt3over2, a/2, 0}, {a*rt3over2, -a/2, 0},
  {0, -a, 0}, {-a*rt3over2, -a/2, 0}, {-a*rt3over2, a/2, 0}, {0, 0, h/2}
};
const double faceNormals[8][3] = {
  {0, 0, -1}, {0, 1, 0}, {rt3over2, 0.5, 0}, {rt3over2, -0.5, 0},
  {0, -1, 0}, {-rt3over2, -0.5, 0}, {-rt3over2, 0.5, 0}, {0, 0, 1}
};

aMgr.Execute(nevt,nSkip,SparseFactor);
TPCResult_t status;
while (true){

	status = aMgr.NextEvent();
	if (status != kTPCSuccess && status != kTPCNewRun ) break;

	const NiffteTPCADCSignal* currsig = aMgr.GetSignal(0);
	currsig->GetSampleAndTrigger(0,sample,trig);
	if (trig != 5) continue;

  if(aMgr.EventNumber()%1000==0){
      cout <<"#### Event " << aMgr.EventNumber() << " ###" << endl; totNumEvents+=1000;
  }

	for(iTrk = 0; iTrk < aMgr.NTracks(); iTrk++){
		const NiffteTPCTrack* currtrk = aMgr.GetTrack(iTrk);
		Fit = 0;
		for(int fc = 0; fc < currtrk->FitCount(); fc++){
			if(currtrk->Fitted(fc) == kFitKalmanSmooth)
				Fit = fc;
		}

		NiffteTPCTrackFit *currfit = currtrk->GetTrackFit(Fit);
		trkADC = currtrk->TotalADC();
		trkL = currfit->Length();
    TVector3 startPoint(currtrk->TrackStartPoint(0),currtrk->TrackStartPoint(1),currtrk->TrackStartPoint(2));
    TVector3 endPoint(currtrk->TrackEndPoint(0),currtrk->TrackEndPoint(1),currtrk->TrackEndPoint(2));
		TVector3 direction(currtrk->TrackDirection(0,Fit),currtrk->TrackDirection(1,Fit),currtrk->TrackDirection(2,Fit));
    direction = direction.Unit();
    

   // Calculate effective "length" of a voxel along the track direction through the center of the voxel
    tmin=-1;
    for (int j=0; j<8; j++) {
      // Iterate over all 8 faces of the hexagonal prism voxel.  Find points where the track direction intersects the voxel.
      numerator = faceCenters[j][0]*faceNormals[j][0] +faceCenters[j][1]*faceNormals[j][1] + faceCenters[j][2]*faceNormals[j][2];
      denominator = direction.X()*faceNormals[j][0] + direction.Y()*faceNormals[j][1] + direction.Z()*faceNormals[j][2];
      if (TMath::Abs(denominator) < tiny) continue; // direction is (almost) parallel to this face
      t = numerator/denominator;
      if (t > 0.0) {
      if (tmin < 0.0) tmin=t;
        tmin = std::min(tmin,t);
      }
    }

    length = 0.1;
    if (tmin>0) length = 2*tmin;
    TVector3 ptA = -tmin*direction;
    TVector3 ptB = tmin*direction;
    totalADC=0;
    xTMax = (TVector3(endPoint-startPoint)).Mag();
    xTMax += std::min(kBinWidth*3, 0.12*xTMax);
    xTMin = 0.0 - kBinWidth*3;
    //std::cout << "track length = xTMax = " << xTMax << " cm" << std::endl;

    nbins = std::floor((xTMax-xTMin)/kBinWidth) + 1;
    hmax = (nbins-3)*kBinWidth;
    hmin = -3 * kBinWidth;
    histName+=iTrk; histName+="_";

    sprintf(htitle,"RecoTrk_%d;distance along fitted track, x (cm); -dE/dx (uncalib. ADC/cm)", iTrk /*currtrk->ID()*/);
    TH1F* hde = new TH1F(histName,htitle,nbins,hmin,hmax);
    Int_t* diglist = currtrk->Digits();
    std::cout << " Digits: " << currtrk->Ndigits() << std::endl;
    for (int m = 0; m < currtrk->Ndigits(); m++) {

      const NiffteTPCDigit* currdig = (NiffteTPCDigit*) digArray->At(diglist[m]);
      //const NiffteTPCDigit* currdig = (NiffteTPCDigit*) diglist[m];
      totalADC+=currdig->ADC();
      x=0.0,y=0.0,z=0.0;
      ngm->MapVolRowColtoXY(currdig->Volume(), currdig->PadRow(), currdig->Column(), x, y);
      ngm->MapVolBuckettoZ(currdig->Volume(), currdig->Bucket(), z);
      TVector3 digCenter(x,y,z);
      distance=0;

      // New method: assume uniform energy deposition within a voxel
      int nS = int(13 * length/double(kBinWidth));
      TVector3 point;
      for (int k=0; k<nS; k++) {
        point = digCenter + ptA + direction*(length*double(k)/double(nS-1));
        distance = direction.Dot(point - startPoint);
        //hde->Fill(distance, (1.0e-8)*currdig->ADC()/(double(nS)*kBinWidth)); // ADC/angstrom
        hde->Fill(distance,currdig->ADC()/(double(nS)*kBinWidth)); // ADC/centimeter
      }

		}
	}

}

std::cout<<"wrote ~"<<totNumEvents<<" events"<<std::endl;
aMgr.Terminate();

system("./cleanup.sh");

gApplication->Terminate();

}
