#include "TRint.h"
#include "TROOT.h"
#include "TTree.h"
#include "TFile.h"
#include "TH2D.h"

#include <stdio.h>
#include "fragCut_lVsADC.C"

int fragCount(const char* treeFileName){

	TCutG* fragCutADC;
	fragCutADC = fragCut_lVsADC(1,150,0);

	TFile* trackFile = new TFile(treeFileName);
	TTree* tracks = (TTree*)trackFile->Get("tracks");
	TH2D* lVsEn = new TH2D("lVsEn","lVsEn",4000,0,40000,1000,0,10);
	TH2D* lVsEn_fragCut = new TH2D("lVsEn_fragCut","lVsEn_fragCut",4000,0,40000,1000,0,10);
	tracks->Draw("length:adc>>lVsEn_fragCut","fragCutADC");

	lVsEn->GetXaxis()->SetTitle("Track Energy [ADC]");
	lVsEn->GetXaxis()->CenterTitle();
	lVsEn->GetYaxis()->SetTitle("Track Length [cm]");
	lVsEn->GetYaxis()->CenterTitle();

	lVsEn_fragCut->GetXaxis()->SetTitle("Track Energy [ADC]");
	lVsEn_fragCut->GetXaxis()->CenterTitle();
	lVsEn_fragCut->GetYaxis()->SetTitle("Track Length [cm]");
	lVsEn_fragCut->GetYaxis()->CenterTitle();

	int fragCount = lVsEn_fragCut->Integral();

	UInt_t runNumber;
	tracks->SetBranchAddress("run",&runNumber);
	tracks->GetEntry(0);

	TCanvas *c1 = new TCanvas("c1","c1",1000,700);
	gStyle->SetOptStat(1);
	c1->SetLogz();

	char fragChar[234];
	sprintf(fragChar,"# frags: %d",fragCount);
	TText *t = new TText(0.5,0.5,fragChar);
	t->SetTextAlign(22);
	t->SetTextColor(kRed+2);
	t->SetTextFont(43);
	t->SetTextSize(40);

	char plotname[56];
	c1->SetLogz(0);
	lVsEn_fragCut->Draw();
	// sprintf(plotname,"%d.lVsEn.png",runNumber);
	// c1->SaveAs(plotname);
	t->DrawTextNDC(0.5,0.5,fragChar);
	fragCutADC->Draw("same");
	sprintf(plotname,"%d.lVsEn_fragCut.png",runNumber);
	c1->SaveAs(plotname);

	// lVsEn_fragCut->GetXaxis()->SetRangeUser(0,2000);	
	// lVsEn_fragCut->Draw("colz");
	// fragCutADC->Draw("same");
	// sprintf(plotname,"%d.lVsEn_fragCut.zoom.png",runNumber);
	// c1->SaveAs(plotname);

	delete trackFile;
	return fragCount;

}
