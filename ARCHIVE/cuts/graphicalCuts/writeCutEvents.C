//
// A simple test macro for loading Niffte
// code into ROOT and running it
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

void writeCutEvents(const char* infile = "infile-list.txt", const char* outfile="Analysis-RunXXX.root", int nevt = -1) {

//Niffte Analysis------------------------------
std::string geo("v2_03");
std::string ofile(outfile);
NiffteAnalysisManager aMgr(infile,ofile,geo);

aMgr.AddEventOutputFile("adc1700cm3.root");
aMgr.AddEventOutputFile("adc2100cm6.root");
aMgr.AddEventOutputFile("adc1000cm2.root");
aMgr.AddEventOutputFile("adc300cm2.root");
aMgr.AddEventOutputFile("fissionLowEn.root");
aMgr.AddEventOutputFile("alphaHighStats.root");
aMgr.Initialize();
int cutFlag[6]={};

TFile *cutFile = new TFile("alphaInvestigation.rootCuts");
TCutG* adc1700cm3 = (TCutG*)cutFile->Get("adc1700cm3");
TCutG* adc2100cm6 = (TCutG*)cutFile->Get("adc2100cm6");
TCutG* adc1000cm2 = (TCutG*)cutFile->Get("adc1000cm2");
TCutG* adc300cm2 = (TCutG*)cutFile->Get("adc300cm2");
TCutG* fissionLowEn = (TCutG*)cutFile->Get("fissionLowEn");
TCutG* alphaHighStats = (TCutG*)cutFile->Get("alphaHighStats");

//__Define some histograms___________________________________________  
AnaH1D* hNumTrk = new AnaH1D("hNumTrk","# of Tracks per Evt",10,0,10);
AnaH1D* hAzimuth = new AnaH1D("hAzimuth","Azimuthal Angles",361,-180.5,180.5);
AnaH1D* hPolar = new AnaH1D("hPolar","Track Polar Angles",200,-1,1);
AnaH1D* hTotalADC = new AnaH1D("hTotalADC","Total ADC",100000,0,100000);
AnaH1D* hAlphaADC = new AnaH1D("hAlphaADC","ALpha ADC",200,1000,3000);
AnaH2D* hLengthvsADC = new AnaH2D("LengthvsADC","Track Length vs. ADC",40000,0,40000,1000,0.0,10.0);
AnaH2D* hStartXY = new AnaH2D("hStartXY","X-Y start position of track",1000,-10,10,1000,-10,10);
AnaH1D* hStartZ = new AnaH1D("hStartZ","Z start position of track",1000,-10,10);
AnaH2D* hADCvsPolar = new AnaH2D("hADCvsPolar","ADC vs Cos(Polar)",200,-1,1,20000,0,20000);
AnaH2D* hTrkLvsPolar = new AnaH2D("hTrkLvsPolar","Track L vs Cos(Polar)",200,-1,1,100,0,10);
AnaH2PadPlane *hdigADCvol0 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol0"," ",0);
AnaH2PadPlane *hdigADCvol1 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol1"," ",1);

//Open file list -----------------------------------------
if(nevt == -1)
	nevt = INT_MAX;

int nSkip = 0, SparseFactor = 0;
int iTrk = 0;
int Fit = 0;
int sample=0,trig=0;
int totNumEvents=0;
int volume=0;
double trkADC = 0;
double trkL = 0;
double xStart = 0;
double yStart = 0;
double zStart = 0;
double xdig = 0, ydig = 0;

aMgr.Execute(nevt,nSkip,SparseFactor);
TPCResult_t status;
while (true){

	status = aMgr.NextEvent();
	if (status != kTPCSuccess && status != kTPCNewRun ) break;

	const NiffteTPCADCSignal* currsig = aMgr.GetSignal(0);
	currsig->GetSampleAndTrigger(0,sample,trig);
	if (trig != 5) continue;
	hNumTrk->Fill(aMgr.NTracks());

    if(aMgr.EventNumber()%1000==0){
	      std::cout <<"#### Event " << aMgr.EventNumber() << " ###" << std::endl;
	  totNumEvents+=1000;
    }

	cutFlag[0] = 0;
	cutFlag[1] = 0;
	cutFlag[2] = 0;
	cutFlag[3] = 0;
	cutFlag[4] = 0;
	cutFlag[5] = 0;
	for(iTrk = 0; iTrk < aMgr.NTracks(); iTrk++){
		const NiffteTPCTrack* currtrk = aMgr.GetTrack(iTrk);
		Fit = 0;
		for(int fc = 0; fc < currtrk->FitCount(); fc++){
			if(currtrk->Fitted(fc) == kFitKalmanSmooth)
				Fit = fc;
		}
		NiffteTPCTrackFit *currfit = currtrk->GetTrackFit(Fit);
		trkADC = currtrk->TotalADC();
		// std::cout << "trkADC = " << trkADC << std::endl;
		trkL = currfit->Length();
		xStart = currtrk->TrackStartPoint(0,Fit);
		yStart = currtrk->TrackStartPoint(1,Fit);
		zStart = currtrk->TrackStartPoint(2,Fit);		
		TVector3 direction(currtrk->TrackDirection(0,Fit),currtrk->TrackDirection(1,Fit),currtrk->TrackDirection(2,Fit));

		// fill histograms
		hAzimuth->Fill(direction.Phi()*TMath::RadToDeg());
		hPolar->Fill(cos(direction.Theta()));
		hLengthvsADC->Fill(trkADC,trkL);
		hTotalADC->Fill(trkADC);
		hAlphaADC->Fill(trkADC);
		hStartXY->Fill(xStart,yStart);
		hStartZ->Fill(zStart);
		hADCvsPolar->Fill(cos(direction.Theta()),trkADC);
		hTrkLvsPolar->Fill(cos(direction.Theta()),trkL);

		if(adc1700cm3->IsInside(trkADC,trkL)){cutFlag[0]++;}
		if(adc2100cm6->IsInside(trkADC,trkL)){cutFlag[1]++;}
		if(adc1000cm2->IsInside(trkADC,trkL)){cutFlag[2]++;}
		if(adc300cm2->IsInside(trkADC,trkL)){cutFlag[3]++;}
		if(fissionLowEn->IsInside(trkADC,trkL)){cutFlag[4]++;}
		if(alphaHighStats->IsInside(trkADC,trkL)){cutFlag[5]++;}

	}

    //Digits______________________________________________
	for(int iDig = 0; iDig < aMgr.NDigits(); iDig++){
		const NiffteTPCDigit* currdig = aMgr.GetDigit(iDig);
		xdig = 0;
		ydig = 0;
		ngm->MapVolRowColtoXY(currdig->Volume(),currdig->PadRow(),currdig->Column(),xdig,ydig);
		volume=currdig->Volume();
		if (volume==1)
			hdigADCvol1->Fill(xdig,ydig,currdig->ADC());
		else
			hdigADCvol1->Fill(xdig,ydig,0);
		if (volume==0)
			hdigADCvol0->Fill(xdig,ydig,currdig->ADC());
		else
			hdigADCvol0->Fill(xdig,ydig,0);
	}

	if(cutFlag[0]){aMgr.SaveEvent(0);}
	if(cutFlag[1]){aMgr.SaveEvent(1);}
	if(cutFlag[2]){aMgr.SaveEvent(2);}
	if(cutFlag[3]){aMgr.SaveEvent(3);}
	if(cutFlag[4]){aMgr.SaveEvent(4);}
	if(cutFlag[5]){aMgr.SaveEvent(5);}

}

std::cout<<"wrote ~"<<totNumEvents<<" events"<<std::endl;
aMgr.Terminate();
//fRootIO->Close();
gROOT->SetStyle("Plain");
gApplication->Terminate();
}
