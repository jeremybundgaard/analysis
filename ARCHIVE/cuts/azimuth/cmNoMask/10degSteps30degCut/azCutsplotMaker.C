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
#include "TLine.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TMath.h"
#include "TFitResult.h"
#include "TAttMarker.h"
#include "TImage.h"
#include "TGraph.h"
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
#include <string>
#include <unistd.h>

void azCutsplotMaker(const char* infile){

	TFile *inputAnaFile = new TFile(infile);
	TCanvas *c1 = new TCanvas("c1","c1",1000,700);
	// TImage *img = TImage::Create();
	char plotName[128];
	stringstream ss;
	// int sleepTime=500000;

	if(	inputAnaFile->GetListOfKeys()->Contains("hAzimuth") ){
		AnaH1D * hAzimuth = (AnaH1D*)inputAnaFile->Get("hAzimuth");
		hAzimuth->Draw();
		sprintf(plotName,"azimuth.%s.png",infile);
		c1->SaveAs(plotName);
		cout<< plotName <<endl;
	}

	if(	inputAnaFile->GetListOfKeys()->Contains("hStartZ") ){
		AnaH1D * hStartZ = (AnaH1D*)inputAnaFile->Get("hStartZ");
		hStartZ->Draw();
		sprintf(plotName,"hStartZ.%s.png",infile);
		c1->SaveAs(plotName);
		cout<< plotName <<endl;
	}	
	
	c1->SetLogy();
	
	if(	inputAnaFile->GetListOfKeys()->Contains("hPolar") ){
		AnaH1D * hPolar = (AnaH1D*)inputAnaFile->Get("hPolar");
		hPolar->Draw();
		sprintf(plotName,"hPolar.%s.png",infile);
		c1->SaveAs(plotName);
		cout<< plotName <<endl;
	}	

	if(	inputAnaFile->GetListOfKeys()->Contains("hTotalADC") ){
		AnaH1D * hTotalADC = (AnaH1D*)inputAnaFile->Get("hTotalADC");
		hTotalADC->Draw();
		sprintf(plotName,"hTotalADC.%s.png",infile);
		c1->SaveAs(plotName);
		cout<< plotName <<endl;


		c1->SetLogy(1);
		hTotalADC->GetXaxis()->SetRange(0,3000);
		hTotalADC->SetAxisRange(1, 20000, "y");
		hTotalADC->SetTitle("total ADC [alphas]");
		hTotalADC->Draw();
		TLine *line = new TLine(1324,0,1324,20000);
		line->Draw("SAME");
		c1->Update();
		sprintf(plotName,"alphaTotalADC.%s.png",infile);
		c1->SaveAs(plotName);
		cout<< plotName <<endl;		

	}	
	
	if(	inputAnaFile->GetListOfKeys()->Contains("hNumTrk") ){
		AnaH1D * hNumTrk = (AnaH1D*)inputAnaFile->Get("hNumTrk");
		hNumTrk->Draw();
		sprintf(plotName,"hNumTrk.%s.png",infile);
		c1->SaveAs(plotName);
		cout<< plotName <<endl;
	}	
	
	c1->SetLogz(1);
	c1->SetLogy(0);
	
	if(	inputAnaFile->GetListOfKeys()->Contains("LengthvsADC") ){
		AnaH2D * LengthvsADC = (AnaH2D*)inputAnaFile->Get("LengthvsADC");
		LengthvsADC->Draw("Colz");
		sprintf(plotName,"LengthvsADC.%s.png",infile);
		c1->SaveAs(plotName);
		cout<< plotName <<endl;

		LengthvsADC->GetXaxis()->SetRange(0,4500);
		LengthvsADC->SetTitle("length vs ADC [alphas]");
		LengthvsADC->Draw("Colz");
		c1->Update();
		sprintf(plotName,"alphaLengthvsADC.%s.png",infile);
		c1->SaveAs(plotName);

	}	
	
	
	if(	inputAnaFile->GetListOfKeys()->Contains("hADCvsPolar") ){
		AnaH2D * hADCvsPolar = (AnaH2D*)inputAnaFile->Get("hADCvsPolar");
		hADCvsPolar->Draw("update");hADCvsPolar->Draw("Colz");
		sprintf(plotName,"ADCvsPolar.%s.png",infile);
		c1->SaveAs(plotName);
		cout<< plotName <<endl;
	
		hADCvsPolar->GetYaxis()->SetRange(0,4000);
		hADCvsPolar->SetTitle("ADC vs cos(polar) [alphas]");
		hADCvsPolar->Draw("update");hADCvsPolar->Draw("Colz");
		sprintf(plotName,"alphaADCvsPolar.%s.png",infile);
		c1->SaveAs(plotName);
		cout<< plotName <<endl;
	
	}
	
	if(	inputAnaFile->GetListOfKeys()->Contains("hStartXY") ){
		AnaH2D * hStartXY = (AnaH2D*)inputAnaFile->Get("hStartXY");
		hStartXY->GetXaxis()->SetRange(150,850);
		hStartXY->GetYaxis()->SetRange(150,850);
		hStartXY->Draw("update");hStartXY->Draw("Colz");
		sprintf(plotName,"startXY.%s.png",infile);
		c1->SaveAs(plotName);
		cout<< plotName <<endl;

	}
	if(	inputAnaFile->GetListOfKeys()->Contains("hTrkLvsPolar") ){
		AnaH2D * hTrkLvsPolar = (AnaH2D*)inputAnaFile->Get("hTrkLvsPolar");
		hTrkLvsPolar->Draw("update");hTrkLvsPolar->Draw("Colz");
		sprintf(plotName,"trkLvsPolar.%s.png",infile);
		c1->SaveAs(plotName);
		cout<< plotName <<endl;

	}
	
	if(	inputAnaFile->GetListOfKeys()->Contains("hdigADCvol0") ){
		TH2Poly * hdigADCvol0 = (TH2Poly*)inputAnaFile->Get("hdigADCvol0");
		hdigADCvol0->Draw("update");hdigADCvol0->Draw("Colz");
		sprintf(plotName,"digADCvol0.%s.png",infile);
		c1->SaveAs(plotName);
		cout<< plotName <<endl;

	}
	
	if(	inputAnaFile->GetListOfKeys()->Contains("hdigADCvol1") ){
		TH2Poly * hdigADCvol1 = (TH2Poly*)inputAnaFile->Get("hdigADCvol1");
		hdigADCvol1->Draw("update");hdigADCvol1->Draw("Colz");
		sprintf(plotName,"digADCvol1.%s.png",infile);
		c1->SaveAs(plotName);
		cout<< plotName <<endl;

	}

	c1->Close();

}
