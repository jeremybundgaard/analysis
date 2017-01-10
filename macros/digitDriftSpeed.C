
#include "THStack.h"
#include <climits>
#include "TROOT.h"
#include "TRint.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TF1.h"
#include "TCut.h"
#include "TCutG.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TAxis.h"
#include "TChain.h"
#include "TTree.h"
#include "TPaletteAxis.h"
#include "TPaveText.h"
#include "TObjArray.h"
#include "TMath.h"
#include "TLine.h"
#include "TPolyLine.h"
#include "TMarker.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TStyle.h" 
#include "TText.h"
#include "TAttMarker.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TString.h"
#include "TPolyMarker3D.h"
#include "TPolyLine3D.h"

#include <math.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

void digitDriftSpeed(const char* infile, const char* outputFilePath) {

TString plotFileName = "";
plotFileName += outputFilePath;
plotFileName += "/plotFile.root";
TFile* plotFile = new TFile(plotFileName,"RECREATE");

TFile* trackFile = new TFile(infile);
TTree* tracks = (TTree*)trackFile->Get("tracks");

Double_t dig_x, dig_y, dig_z, start_x, start_y, start_z, end_x, end_y, end_z, theta;
Int_t dig_bucket, eventID;
float_t length;
tracks->SetBranchAddress("dig_x", &dig_x);
tracks->SetBranchAddress("dig_y", &dig_y);
tracks->SetBranchAddress("dig_z", &dig_z);
tracks->SetBranchAddress("dig_bucket", &dig_bucket);
tracks->SetBranchAddress("eventID", &eventID);
tracks->SetBranchAddress("start.x()", &start_x);
tracks->SetBranchAddress("start.y()", &start_y);
tracks->SetBranchAddress("start.z()", &start_z);
tracks->SetBranchAddress("end.x()", &end_x);
tracks->SetBranchAddress("end.y()", &end_y);
tracks->SetBranchAddress("end.z()", &end_z);
tracks->SetBranchAddress("direction.Theta()", &theta);
tracks->SetBranchAddress("length", &length);

Long64_t nentries = tracks->GetEntries();

// TCutG* vertexCut = new TCutG("vertexCut",4);
// vertexCut->SetVarX("start.y()");
// vertexCut->SetVarY("start.x()");
// vertexCut->SetPoint(0,-1,0);
// vertexCut->SetPoint(1,0,1);
// vertexCut->SetPoint(2,1,0);
// vertexCut->SetPoint(3,0,-1);
// vertexCut->SetPoint(4,-1,0);
// vertexCut->Write();

TCanvas *c1 = new TCanvas("c1","c1",1000,700);
// gStyle->SetOptStat(0);
TH3D *digitsPlot = new TH3D("digitsPlot","digitsPlot",200,-5,5,200,-5,5,100,0,5);
digitsPlot->GetXaxis()->SetTitle("X [cm]");
digitsPlot->GetYaxis()->SetTitle("Y [cm]");
digitsPlot->GetZaxis()->SetTitle("Z [cm]");
TCut fitCut = "fitType==5";

//Making Digit Plots
for (int i = 1; i < 5; i++){
	if(i==1){
		tracks->Draw("dig_x:dig_y:dig_z>>digitsAll",fitCut);
		c1->SaveAs("digitsAll.png");
	}
	if(i==2){
		TCut fragCut = "adc > 5000";
		fragCut = fitCut&&fragCut;
		tracks->Draw("dig_x:dig_y:dig_z>>digitsAll",fragCut);
		c1->SaveAs("digitsFrag.png");
	}
	if(i==3){
		TCut alphaCut = "adc < 5000";
		alphaCut = fitCut&&alphaCut;
		tracks->Draw("dig_x:dig_y:dig_z>>digitsAll",alphaCut);
		c1->SaveAs("digitsAlpha.png");
	}
	if(i==4){
		TCut driftVelCut = "length>3.8 && length<4.2 && direction.Theta() < 0.7";
		driftVelCut = fitCut&&driftVelCut;
		tracks->Draw("dig_x:dig_y:dig_z>>digitsDriftVel",driftVelCut,"");
		// for(Long64_t j = 0; j < nentries; j++)
		// {
		// 	tracks->GetEntry(j);
		// 	if(length > 3.7 && length < 4.2 && theta < 0.7){
		// 		TPolyLine3D *plDigits = new TPolyLine3D(2);
		// 		plDigits->SetPoint(0, start_x, start_y, start_z);
		// 		plDigits->SetPoint(0, end_x, end_y, end_z);
		// 		plDigits->Draw("Same");
		// 	}
		// }
		c1->SaveAs("digitsDriftVel.png");

	}
}
// TPolyMarker3D *pmDigits = new TPolyMarker3D(nentries);
// Int_t index = 0;
// for(Long64_t i = 0; i < nentries; i++)
// {
// 	tracks->GetEntry(i);
// 	pmDigits->SetPoint(i,dig_x,dig_y,dig_z);
// }

// //pmDigits->SetMarkerStyle(20);
// pmDigits->SetMarkerSize(5);
// pmDigits->SetMarkerColor(2);
// pmDigits->Draw();
// c1->SaveAs("polyMarkerDigitsAll.png");

// TTreeReader myReader("tracks", trackFile);
// TTreeReaderValue<Double_t> currDig_x(myReader, "dig_x");
// TTreeReaderValue<Double_t> currDig_y(myReader, "dig_y");
// TTreeReaderValue<Double_t> currDig_z(myReader, "dig_z");
// TTreeReaderValue<Int_t> currBucket(myReader, "dig_bucket");
// TTreeReaderValue<Int_t> eid(myReader,"eventID");

// Int_t counter = 0;
// while (myReader.Next())
// {
// 	counter++;
// }
// printf("Total number of events in the TTreeReader is: %d \n",counter);

plotFile->Write();

}
