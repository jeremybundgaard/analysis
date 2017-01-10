
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

void anaHistMaker(const char* infile = "infile-list.txt", const char* outfile="Analysis-RunXXX.root", int nevt = -1) {

     if (!trkArray) return;
     NiffteGeometryMap *ngm=fNgm;
     TCanvas *c1;
     if (gROOT->FindObject("BraggCanvas")) {
       c1 = (TCanvas*) gROOT->FindObject("BraggCanvas");
     } else {
       c1 = gEve->AddCanvasTab("Bragg Curves");
       c1->SetName("BraggCanvas");
     }
     c1->cd();
     
     const double kBinWidth = 0.1; // cm
     TString title = "Track specific ionization;distance along fitted track, x (cm); -dE/dx (uncalib. ADC/cm)";

     TCanvas* oldCanvas = 0;
     if (TVirtualPad::Pad() && gPad){ 
         oldCanvas = (TCanvas*) TVirtualPad::Pad();
     }

     TLegend *leg;
     if (gROOT->FindObject("dEdxLegend")) {
       leg = (TLegend*) gROOT->FindObject("dEdxLegend");
       leg->Clear();
     } else {
       leg = new TLegend(0.9,0.1,0.995,0.9);
       leg->SetName("dEdxLegend");
     }
     
     THStack* hs = 0;
     if (gROOT->FindObject("dEdxStack")) {
       hs = (THStack*) gROOT->FindObject("dEdxStack");
       // deleting the histogram deletes it from the stack so actually decraments
       //  s->GetHists()->GetSize().  Using the while loop ensures all histograms
       //  are properly deleted.  The old method failed to delete all histograms
       //  in the case where s->GetHists()->GetSize() > 1.
       if (hs->GetHists()){
           while(hs->GetHists()->GetSize()>0){
               delete hs->GetHists()->At(0);
           }
       }
       //if (hs->GetHists())
       //  for (int mmi=0; mmi<hs->GetHists()->GetSize(); mmi++) {
       //    delete hs->GetHists()->At(mmi);
       //  }
       delete hs;
     }
     hs = new THStack("dEdxStack",title);

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


     for (int i = 0; i < trkArray->GetEntries(); i++) {
       const NiffteTPCTrack* currtrk = (NiffteTPCTrack*)trkArray->At(i);
       if (currtrk->Fitted() == 0) continue;

       TVector3 startPoint(currtrk->TrackStartPoint(0),currtrk->TrackStartPoint(1),currtrk->TrackStartPoint(2));
       TVector3 endPoint(currtrk->TrackEndPoint(0),currtrk->TrackEndPoint(1),currtrk->TrackEndPoint(2));
       TVector3 direction(currtrk->TrackDirection(0),currtrk->TrackDirection(1),currtrk->TrackDirection(2));
       direction = direction.Unit();

       // Calculate effective "length" of a voxel along the track direction through the center of the voxel
       double tmin=-1;
       const double tiny = 1.0e-10;
       for (int j=0; j<8; j++) {
         // Iterate over all 8 faces of the hexagonal prism voxel.  Find points where the track direction intersects the voxel.
         double numerator = faceCenters[j][0]*faceNormals[j][0] +faceCenters[j][1]*faceNormals[j][1] + faceCenters[j][2]*faceNormals[j][2];
         double denominator = direction.X()*faceNormals[j][0] + direction.Y()*faceNormals[j][1] + direction.Z()*faceNormals[j][2];
         if (TMath::Abs(denominator) < tiny) continue; // direction is (almost) parallel to this face

         double t = numerator/denominator;
         if (t > 0.0) {
           if (tmin < 0.0) tmin=t;
           tmin = std::min(tmin,t);
         }
       }
       double length = 0.1;
       if (tmin>0) length = 2*tmin;
       TVector3 ptA = -tmin*direction;
       TVector3 ptB = tmin*direction;


       double totalADC=0;
       double xTMax = (TVector3(endPoint-startPoint)).Mag();
       xTMax += std::min(kBinWidth*3, 0.12*xTMax);
       double xTMin = 0.0 - kBinWidth*3;
       //std::cout << "track length = xTMax = " << xTMax << " cm" << std::endl;

       int nbins = std::floor((xTMax-xTMin)/kBinWidth) + 1;
       double hmax = (nbins-3)*kBinWidth;
       double hmin = -3 * kBinWidth;
       TString histName = "trk_"; histName+=i; histName+="_";

       char htitle[256];
       sprintf(htitle,"RecoTrk_%d;distance along fitted track, x (cm); -dE/dx (uncalib. ADC/cm)", i /*currtrk->ID()*/);
       if (gROOT->FindObject(histName)) gROOT->FindObject(histName)->Delete();
       TH1F* hde = new TH1F(histName,htitle,nbins,hmin,hmax);
       Int_t* diglist = currtrk->Digits();
        std::cout << " Digits: " << currtrk->Ndigits() << std::endl;
       for (int m = 0; m < currtrk->Ndigits(); m++) {
        
         //std::cout << diglist[m] << std::endl;
         //uint32_t index = (uint32_t)diglist[m];
         //ngm->VRCBFromIndex(index,vol,row,col,bkt);

         const NiffteTPCDigit* currdig = (NiffteTPCDigit*) digArray->At(diglist[m]);
         //const NiffteTPCDigit* currdig = (NiffteTPCDigit*) diglist[m];
         totalADC+=currdig->ADC();
         double x=0.0,y=0.0,z=0.0;
         ngm->MapVolRowColtoXY(currdig->Volume(), currdig->PadRow(), currdig->Column(), x, y);
         ngm->MapVolBuckettoZ(currdig->Volume(), currdig->Bucket(), z);
         TVector3 digCenter(x,y,z);

         double distance=0;

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
       leg->AddEntry(hde,hde->GetTitle(),"L");
       hde->SetLineColor(i+1);
       hs->Add(hde);

     }
     hs->Draw("nostack");
     if(hs->GetYaxis()) hs->GetYaxis()->SetTitleOffset(1.22);

     if (gPad) leg->SetFillColor(gPad->GetFillColor());
     leg->Draw();
     //gPad->Update();


}
