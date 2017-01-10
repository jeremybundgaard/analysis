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
#include "TImage.h"
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

void intensityVsRadius(const char* infile = "infile-list.txt", const char* outfile="Analysis-RunXXX.root", int nevt = -1) {

	//Niffte Analysis------------------------------
	std::string geo("v2_03");
	std::string ofile(outfile);
	NiffteAnalysisManager aMgr(infile,ofile,geo);
            
	//__Define some histograms___________________________________________  
	AnaH1D* intens_vs_rad = new AnaH1D("intens_vs_rad","intensity vs radius",1000,0,6);

	//Open file list -----------------------------------------
	if(nevt == -1)
		nevt = INT_MAX;

	int n = 0, nSkip = 0, SparseFactor = 0;
	int sample=0,trig=0;
	int totNumEvents=0;
	double xdig=0,ydig=0,rad=0;

	aMgr.Execute(nevt,nSkip,SparseFactor);
	TPCResult_t status;
	while (true){

		status = aMgr.NextEvent();
		if (status != kTPCSuccess && status != kTPCNewRun ) break;

		const NiffteTPCADCSignal* currsig = aMgr.GetSignal(0);
		currsig->GetSampleAndTrigger(0,sample,trig);
		if (trig != 5) continue;
	    if(n%1000==0){
  	      cout <<"#### Event " << aMgr.EventNumber() << " ###" << endl;
		  totNumEvents+=1000;
	    }

	    //Digits______________________________________________
		for(int iDig = 0; iDig < aMgr.NDigits(); iDig++){
			const NiffteTPCDigit* currdig = aMgr.GetDigit(iDig);
			xdig = 0;
			ydig = 0;
			ngm->MapVolRowColtoXY(currdig->Volume(),currdig->PadRow(),currdig->Column(),xdig,ydig);
			rad=std::sqrt(std::pow(xdig,2)+std::pow(ydig,2));
			intens_vs_rad->Fill(rad,currdig->ADC());
		}
		//--Digits---------------------------------------*/


		++n;
	}


	std::cout<<"wrote ~"<<totNumEvents<<" events"<<std::endl;

	TCanvas *c1 = new TCanvas("c1","c1",2000,1400);
	TImage *img = TImage::Create();
	c1->SetLogy();
	intens_vs_rad->Draw();
	img->FromPad(c1);
	img->WriteImage("intens_vs_rad.png");



	aMgr.Terminate();
	//fRootIO->Close();
	gROOT->SetStyle("Plain");
	gApplication->Terminate();
}
