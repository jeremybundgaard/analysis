// ROOT Libraries
#include "TF1.h"
#include "TH2.h"
#include "TH1.h"
#include "TH2Poly.h"
#include "AnaHistoList.h"
#include "AnaH1D.h"
#include "AnaH2D.h"
#include "AnaH2PadPlane.h"
#include "AnaH1DR.h"
#include "AnaH2DR.h"
#include "TFile.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TMath.h"
#include "TFitResult.h"
#include "TAttMarker.h"
#include "TGraph.h"
#include "TImage.h"
#include "TCutG.h"


// NIFFTE Libraries
#include "NiffteGeometryMap.h"
#include "NiffteTPCADCSignal.h"
#include "NiffteRootIO.h"
#include "NiffteTPCDetectorConstruction.h"

// c++ Libraries
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <time.h>
#include <string>
#include <stdlib.h>
#include <sstream>


void displayCutsOnLvsADC(const char* infile, const char* alphaCutFileName, bool outputPlots){

	TFile *inputAnaFile = new TFile(infile);
	// AnaH1D * hAlphaADC = (AnaH1D*)inputAnaFile->Get("hAlphaADC");
	// AnaH1D * hAzimuth = (AnaH1D*)inputAnaFile->Get("hAzimuth");
	// AnaH1D * hFissionPolar = (AnaH1D*)inputAnaFile->Get("hFissionPolar");
	// AnaH1D * hNumTrk = (AnaH1D*)inputAnaFile->Get("hNumTrk");
	// AnaH1D * hPolar = (AnaH1D*)inputAnaFile->Get("hPolar");
	// AnaH1D * hStartZ = (AnaH1D*)inputAnaFile->Get("hStartZ");
	// AnaH1D * hTotalADC = (AnaH1D*)inputAnaFile->Get("hTotalADC");
	AnaH2D * LengthvsADC = (AnaH2D*)inputAnaFile->Get("LengthvsADC");
	// AnaH2D * hADCvsPolar = (AnaH2D*)inputAnaFile->Get("hADCvsPolar");
	// AnaH2D * hFissionTrkLvsPolar = (AnaH2D*)inputAnaFile->Get("hFissionTrkLvsPolar");
	// AnaH2D * hStartXY = (AnaH2D*)inputAnaFile->Get("hStartXY");
	// AnaH2D * hTrkLvsPolar = (AnaH2D*)inputAnaFile->Get("hTrkLvsPolar");
	// TH2Poly * hdigADC = (TH2Poly*)inputAnaFile->Get("hdigADC");

	  
	TFile *cutFile = new TFile(alphaCutFileName);
	TCutG* adc1700cm3 = (TCutG*)cutFile->Get("adc1700cm3");
	TCutG* adc2100cm6 = (TCutG*)cutFile->Get("adc2100cm6");
	TCutG* adc1000cm2 = (TCutG*)cutFile->Get("adc1000cm2");
	TCutG* adc300cm2 = (TCutG*)cutFile->Get("adc300cm2");
	TCutG* fissionLowEn = (TCutG*)cutFile->Get("fissionLowEn");
	TCutG* alphaHighStats = (TCutG*)cutFile->Get("alphaHighStats");
	cutFile->Close();
	delete cutFile;
	
	
	if (outputPlots){
		TCanvas *c1 = new TCanvas("c1","c1",1000,700);
		TGraph *g = (TGraph*)c1->GetPrimitive("Graph");
		TImage *img = TImage::Create();
	    LengthvsADC->GetXaxis()->SetRange(0,4000);
	    int nbinsY = LengthvsADC->GetNbinsY();
	    LengthvsADC->GetXaxis()->SetTitle("ADC");
	    LengthvsADC->GetXaxis()->CenterTitle();
	    LengthvsADC->GetYaxis()->SetTitle("cm");
	    LengthvsADC->GetYaxis()->CenterTitle();
	    gStyle->SetOptStat(1);
		LengthvsADC->SetTitle(infile);
	    c1->SetLogz();
		LengthvsADC->Draw("Colz");c1->Update();
		adc1700cm3->Draw("same");       c1->Update();
		adc2100cm6->Draw("same");       c1->Update();
		adc1000cm2->Draw("same");       c1->Update();
		adc300cm2->Draw("same");        c1->Update();
		fissionLowEn->Draw("same");     c1->Update();
		alphaHighStats->Draw("same");   c1->Update();		
		char plotName[128];
		sprintf(plotName,"graphCuts.%s.png",infile);
		c1->SaveAs(plotName);

	  
		// ss << "hdigADC."<< infile << ".png";
		// plotName = ss.str().c_str(); 	
		// ss.str(std::string());
		// hdigADC->Draw("same");hdigADC->Draw("Colz");
		// c1->Print(plotName);
		// 	
		// ss << "kTrkLvsPolar."<< infile << ".png";
		// plotName = ss.str().c_str(); 	
		// ss.str(std::string());
		// hTrkLvsPolar->Draw("same"); hTrkLvsPolar->Draw("Colz");
		// c1->Print(plotName);
		// 	
		// ss <<"hPolar."<< infile << ".png";
		// plotName = ss.str().c_str(); 	
		// ss.str(std::string());
		// hPolar->Draw("same");hPolar->Draw();
		// c1->Print(plotName);
		// 	
		// ss <<"ADCvsPolar."<< infile << ".png";
		// plotName = ss.str().c_str(); 	
		// ss.str(std::string());
		// 	    hADCvsPolar->Draw("same");hADCvsPolar->Draw("Colz");
		// 	    c1->Print(plotName);
		// 	  
		// ss << "hFissionTrkLvsPolar."<< infile << ".png";
		// plotName = ss.str().c_str(); 	
		// ss.str(std::string());
		// 	    hFissionTrkLvsPolar->Draw("Colz");
		// 	    c1->Print(plotName);
		// 	
		// ss << "hFissionPolar." << infile << ".png";
		// plotName = ss.str().c_str(); 	
		// ss.str(std::string());
		// 	    hFissionPolar->Draw();
		// 	    c1->Print(plotName);
	
	    c1->Close();
	}
	
}

	