#include <climits>
#include <vector>
#include "TROOT.h"
#include "TRint.h"
#include "MsgLog.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TF1.h"
#include "TCut.h"
#include "TCutG.h"
#include "TGaxis.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TGaxis.h"
#include "TChain.h"
#include "TTree.h"
#include "TPaletteAxis.h"
#include "TPaveText.h"
#include "TObjArray.h"
#include "TMath.h"
#include "TLine.h"
#include "TMarker.h"
#include "TLegend.h"
#include "TLatex.h"

#include "NiffteGeometryMap.h"
#include "NifftePlotUtilities.h"

#include <math.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>


void nDigitDependence(const int preamp) {

char cftFileName[345];
char noMaskFileName[345];

TCutG *fragCut = new TCutG("fragCut",8);
fragCut->SetLineColor(kViolet);
fragCut->SetLineWidth(3);
if (preamp==1)
{
	sprintf(cftFileName,"$cftrees/cfCFT.1stPreamp.trees.1865.73.83.root");
	sprintf(noMaskFileName,"$cftrees/cfNoMask.1stPreamp.trees.1850-56.66-72.74-82.root");
	fragCut->SetPoint(0,2,0.856419);
	fragCut->SetPoint(1,15,1.5);
	fragCut->SetPoint(2,35,2.5);
	fragCut->SetPoint(3,60,3.25);
	fragCut->SetPoint(4,140,3.5);
	fragCut->SetPoint(5,140,1.25);
	fragCut->SetPoint(6,1,0);
	fragCut->SetPoint(7,1,0.434625);
	fragCut->SetPoint(8,1.2,0.496664);
	fragCut->SetPoint(9,1.4,0.56915);
	fragCut->SetPoint(10,1.6,0.652886);
	fragCut->SetPoint(11,1.8,0.748508);
	fragCut->SetPoint(12,2,0.856419);
}
else if (preamp==2)
{
	sprintf(cftFileName,"$cftrees/cfCFT.2ndPreamp.trees.2068-9.root");
	sprintf(noMaskFileName,"$cftrees/cfNoMask.2ndPreamp.trees.2057-61.root");
	fragCut->SetPoint(0,2,0.700327);
	fragCut->SetPoint(1,15,1.5);
	fragCut->SetPoint(2,35,2.5);
	fragCut->SetPoint(3,60,3.25);
	fragCut->SetPoint(4,140,3.5);
	fragCut->SetPoint(5,140,1.25);
	fragCut->SetPoint(6,1,0);
	fragCut->SetPoint(7,1,0.295582);
	fragCut->SetPoint(8,1.2,0.363805);
	fragCut->SetPoint(9,1.4,0.438273);
	fragCut->SetPoint(10,1.6,0.519138);
	fragCut->SetPoint(11,1.8,0.606485);
	fragCut->SetPoint(12,2,0.700327);
}

TFile* cftFile = new TFile(cftFileName);
TFile* noMaskFile = new TFile(noMaskFileName);

TTree* noMaskTracks = (TTree*)noMaskFile->Get("tracks");
TTree* cftTracks = (TTree*)cftFile->Get("tracks");

TH2D * noMaskLvEn = new TH2D("noMaskLvEn","",40000,0,168.6,1000,0,10);
TH2D * cftLvEn = new TH2D("cftLvEn","",40000,0,168.6,1000,0,10);

TCanvas *c1 = new TCanvas("c1","c1",1000,700);
gStyle->SetOptStat(0);

char charContainer[234];
std::stringstream nDigCut;
double origin=0;

//// polar loop
int minDig=0;
int maxDig=0;
int startDigStep=2;
int lastDigStep=150;
int digStepSize=2;

for (int nDig = startDigStep; nDig <= lastDigStep; nDig+=digStepSize){

	minDig=0;
	maxDig=nDig+2;

	nDigCut.str("");
    nDigCut<< minDig << " < nDigits && nDigits < "<< maxDig <<" && fitType==10 && trackNo==1";
	std::cout << nDigCut.str().c_str() << std::endl;


	cftLvEn->GetXaxis()->SetTitle("Track Energy [MeV]");
	cftLvEn->GetXaxis()->CenterTitle();
	cftLvEn->GetYaxis()->SetTitle("Track Length [cm]");
	cftLvEn->GetYaxis()->CenterTitle();
	cftLvEn->SetTitle(nDigCut.str().c_str());
	cftTracks->Draw("length:adc*168.6/40000>>cftLvEn",nDigCut.str().c_str());

	noMaskLvEn->GetXaxis()->SetTitle("Track Energy [MeV]");
	noMaskLvEn->GetXaxis()->CenterTitle();
	noMaskLvEn->GetYaxis()->SetTitle("Track Length [cm]");
	noMaskLvEn->GetYaxis()->CenterTitle();
	noMaskLvEn->SetTitle(nDigCut.str().c_str());
	noMaskTracks->Draw("length:adc*168.6/40000>>noMaskLvEn",nDigCut.str().c_str());

	// ///////////////////////////////////////////////////////////////////
	// ///////////////////////  Plot lenght VS ADC ///////////////////////
	// ///////////////////////////////////////////////////////////////////
	c1->cd();
	c1->SetGridy(0);
	c1->SetGridx(0);
	c1->SetLogy(0);
	c1->SetLogx(1);
	cftLvEn->GetXaxis()->SetRangeUser(0.01,150);
	cftLvEn->GetYaxis()->SetRangeUser(0,10);
	cftLvEn->Draw("colz");
	sprintf(charContainer,"cftLvEn.full.log.minDig%0.3d.maxDig%0.3d.png",minDig,maxDig);
	c1->SaveAs(charContainer,"recreate");
	cftLvEn->GetYaxis()->SetRangeUser(0,2);
	sprintf(charContainer,"cftLvEn.full.log.zoom.minDig%0.3d.maxDig%0.3d.png",minDig,maxDig);
	c1->SaveAs(charContainer,"recreate");

	c1->cd();
	c1->SetLogx(0);
	cftLvEn->GetXaxis()->SetRangeUser(0.01,150);
	cftLvEn->GetYaxis()->SetRangeUser(0,2);
	cftLvEn->Draw("Colz");
	fragCut->Draw("same");
	sprintf(charContainer,"cftLvEn.full.minDig%0.3d.maxDig%0.3d.png",minDig,maxDig);
	c1->SaveAs(charContainer,"recreate");

	c1->cd();
	c1->SetLogx(0);
	cftLvEn->GetXaxis()->SetRangeUser(0.01,6);
	cftLvEn->Draw("Colz");
	fragCut->Draw("same");
	sprintf(charContainer,"cftLvEn.lowEn.minDig%0.3d.maxDig%0.3d.png",minDig,maxDig);
	c1->SaveAs(charContainer,"recreate");

	c1->cd();
	c1->SetLogx(1);
	noMaskLvEn->GetXaxis()->SetRangeUser(0.01,150);
	noMaskLvEn->GetYaxis()->SetRangeUser(0,10);
	noMaskLvEn->Draw("colz");
	sprintf(charContainer,"noMaskLvEn.full.log.minDig%0.3d.maxDig%0.3d.png",minDig,maxDig);
	c1->SaveAs(charContainer,"recreate");
	noMaskLvEn->GetYaxis()->SetRangeUser(0,2);
	sprintf(charContainer,"noMaskLvEn.full.log.zoom.minDig%0.3d.maxDig%0.3d.png",minDig,maxDig);
	c1->SaveAs(charContainer,"recreate");

	c1->cd();
	c1->SetLogx(0);
	noMaskLvEn->GetXaxis()->SetRangeUser(0.01,150);
	noMaskLvEn->GetYaxis()->SetRangeUser(0,2);
	noMaskLvEn->Draw("Colz");
	// fragCut->Draw("same");
	sprintf(charContainer,"noMaskLvEn.full.minDig%0.3d.maxDig%0.3d.png",minDig,maxDig);
	c1->SaveAs(charContainer,"recreate");

	c1->cd();
	c1->SetLogx(0);
	noMaskLvEn->GetXaxis()->SetRangeUser(0.01,6);
	noMaskLvEn->Draw("Colz");
	fragCut->Draw("same");
	sprintf(charContainer,"noMaskLvEn.lowEn.minDig%0.3d.maxDig%0.3d.png",minDig,maxDig);
	c1->SaveAs(charContainer,"recreate");

	}
}
