#include "TRint.h"
#include "TROOT.h"
#include "TH1.h"
#include "TH2.h"
#include "TTree.h"
#include "TCut.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TMath.h"

#include <iomanip>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>


void compDiffRuns(const char* runType, const char* treeFileName) {


std::vector<int> runNum;
char runCut[123];
char bestCut[123];
char azCut[123];
char plotName[123];
char histName[123];


if ( !(strcmp(runType,"cfCFT1")))
{
	std::cout<<runType<<'\t'<<treeFileName<<endl;
	runNum.push_back(1865);
	runNum.push_back(1873);
	runNum.push_back(1883);

}
else if ( !(strcmp(runType,"cfCFT2")))
{
	std::cout<<runType<<'\t'<<treeFileName<<endl;

	// sprintf(azCut,"direction.Phi() < 2.2 && !(-1 < direction.Phi() && direction.Phi() < 0)");
	runNum.push_back(2068);
	runNum.push_back(2069);
}
else if ( !(strcmp(runType,"cfNoMask1")))
{
	std::cout<<runType<<'\t'<<treeFileName<<endl;

	runNum.push_back(1850);
	runNum.push_back(1851);
	runNum.push_back(1852);
	runNum.push_back(1853);
	runNum.push_back(1854);
	runNum.push_back(1855);
	runNum.push_back(1856);
	runNum.push_back(1866);
	runNum.push_back(1867);
	runNum.push_back(1868);
	runNum.push_back(1869);
	runNum.push_back(1870);
	runNum.push_back(1871);
	runNum.push_back(1872);
	runNum.push_back(1872);
	runNum.push_back(1874);
	runNum.push_back(1875);
	runNum.push_back(1876);
	runNum.push_back(1877);
	runNum.push_back(1878);
	runNum.push_back(1879);
	runNum.push_back(1880);
	runNum.push_back(1881);
	runNum.push_back(1882);

}
else if ( !(strcmp(runType,"cfNoMask2")))
{
	std::cout<<runType<<'\t'<<treeFileName<<endl;
	
	sprintf(azCut,"direction.Phi() < 2.2 && !(-1 < direction.Phi() && direction.Phi() < 0)");
	runNum.push_back(2057);
	runNum.push_back(2058);
	runNum.push_back(2059);
	runNum.push_back(2060);
	runNum.push_back(2061);
}


TFile* treeFile = new TFile(treeFileName);
TTree* tracks = (TTree*)treeFile->Get("tracks");

TCanvas *c1 = new TCanvas("c1","c1",1000,700);
gStyle->SetOptStat(0);


for (std::vector<int>::iterator runNumIter = runNum.begin(); runNumIter != runNum.end(); ++runNumIter)
{

	sprintf(bestCut,"bestFit && %s",runCut);

	cout<<runCut<<endl;

	c1->SetLogx(0);
	c1->SetLogy(0);
	c1->SetLogz(0);

	c1->SetLogz(1);

	TH2D* lVsEn = new TH2D("lVsEn","lVsEn",40000,0,168.6,1000,0,10);
	lVsEn->GetXaxis()->SetTitle("MeV");
	lVsEn->GetYaxis()->SetTitle("cm");
	sprintf(histName,"lVsEn{%s}",runCut);
	lVsEn->SetTitle(histName);
	tracks->Draw("length:adc*168.6/40000>>lVsEn",runCut,"colz");
	lVsEn->GetZaxis()->SetRangeUser(1,lVsEn->GetMaximum());
	lVsEn->Draw("Colz");
	sprintf(plotName,"%s.lVsEn.run%d.png",runType,*runNumIter);
	c1->SaveAs(plotName);
	sprintf(histName,"lVsEn{%s}",bestCut);
	cout<<bestCut<<endl;
	lVsEn->SetTitle(histName);
	tracks->Draw("length:adc*168.6/40000>>lVsEn",bestCut,"colz");
	sprintf(plotName,"%s.lVsEn.bestFit.run%d.png",runType,*runNumIter);
	c1->SaveAs(plotName);
	sprintf(plotName,"%s.lVsEn.bestFit.logx.run%d.png",runType,*runNumIter);
	c1->SetLogx(1);
	tracks->Draw("length:adc*168.6/40000>>lVsEn",bestCut,"colz");
	c1->SaveAs(plotName);
	c1->SetLogx(0);
	delete lVsEn;

	c1->SetLogy(1);	

	TH2D* enVsAz = new TH2D("enVsAz","enVsAz",2000,-3.15,3.15,40000,0,168.6); 
	enVsAz->GetXaxis()->SetTitle("adc");
	enVsAz->GetYaxis()->SetTitle("cm");
	sprintf(histName,"enVsAz{%s}",runCut);
	enVsAz->SetTitle(histName);
	enVsAz->GetYaxis()->SetRangeUser(0.1,170);
	tracks->Draw("adc*168.6/40000:direction.Phi()>>enVsAz",runCut,"colz");
	enVsAz->GetZaxis()->SetRangeUser(1,enVsAz->GetMaximum());
	enVsAz->Draw("Colz");
	sprintf(plotName,"%s.enVsAz.run%d.png",runType,*runNumIter);
	c1->SaveAs(plotName);
	sprintf(histName,"enVsAz{%s}",bestCut);
	enVsAz->SetTitle(histName);
	tracks->Draw("adc*168.6/40000:direction.Phi()>>enVsAz",bestCut,"colz");
	sprintf(plotName,"%s.enVsAz.bestFit.run%d.png",runType,*runNumIter);
	c1->SaveAs(plotName);
	delete enVsAz;

	TH2D* enVsPolar = new TH2D("enVsPolar","enVsPolar",1000,0,3.15,40000,0,168.6);
	enVsPolar->GetXaxis()->SetTitle("MeV");
	enVsPolar->GetYaxis()->SetTitle("#theta");
	sprintf(histName,"enVsPolar{%s}",runCut);
	enVsPolar->SetTitle(histName);
	enVsPolar->GetYaxis()->SetRangeUser(0.1,170);
	tracks->Draw("adc*168.6/40000:direction.Theta()>>enVsPolar",runCut,"colz");
	enVsPolar->GetZaxis()->SetRangeUser(1,enVsPolar->GetMaximum());
	enVsPolar->Draw("Colz");
	sprintf(plotName,"%s.enVsPolar.run%d.png",runType,*runNumIter);
	c1->SaveAs(plotName);
	sprintf(histName,"enVsPolar{%s}",bestCut);
	enVsPolar->SetTitle(histName);
	tracks->Draw("adc*168.6/40000:direction.Theta()>>enVsPolar",bestCut,"colz");
	sprintf(plotName,"%s.enVsPolar.bestFit.run%d.png",runType,*runNumIter);
	c1->SaveAs(plotName);
	delete enVsPolar;

	TH2D* enVsCosPolar = new TH2D("enVsCosPolar","enVsCosPolar",1000,-1,1,40000,0,168.6);
	enVsCosPolar->GetXaxis()->SetTitle("MeV");
	enVsCosPolar->GetYaxis()->SetTitle("cos(#theta)");
	sprintf(histName,"enVsCosPolar{%s}",runCut);
	enVsCosPolar->SetTitle(histName);
	enVsCosPolar->GetYaxis()->SetRangeUser(0.1,170);	
	tracks->Draw("adc*168.6/40000:direction.CosTheta()>>enVsCosPolar",runCut,"colz");
	enVsCosPolar->GetZaxis()->SetRangeUser(1,enVsCosPolar->GetMaximum());
	enVsCosPolar->Draw("Colz");
	sprintf(plotName,"%s.enVsCosPolar.run%d.png",runType,*runNumIter);
	c1->SaveAs(plotName);
	sprintf(histName,"enVsCosPolar{%s}",bestCut);
	enVsCosPolar->SetTitle(histName);
	tracks->Draw("adc*168.6/40000:direction.CosTheta()>>enVsCosPolar",bestCut,"colz");
	sprintf(plotName,"%s.enVsCosPolar.bestFit.run%d.png",runType,*runNumIter);
	c1->SaveAs(plotName);
	delete enVsCosPolar;


	c1->SetLogy(0);

	TH2D* xyStart = new TH2D("xyStart","xyStart",1000,-7,7,1000,-7,7);
	xyStart->GetXaxis()->SetTitle("cm");
	xyStart->GetYaxis()->SetTitle("cm");
	sprintf(histName,"xyStart{%s}",runCut);
	xyStart->SetTitle(histName);
	tracks->Draw("start.x():start.y()>>xyStart",runCut,"colz");
	xyStart->GetZaxis()->SetRangeUser(1,xyStart->GetMaximum());
	xyStart->Draw("Colz");
	sprintf(plotName,"%s.xyStart.run%d.png",runType,*runNumIter);
	c1->SaveAs(plotName);
	sprintf(histName,"xyStart{%s}",bestCut);
	xyStart->SetTitle(histName);
	tracks->Draw("start.x():start.y()>>xyStart",bestCut,"colz");
	sprintf(plotName,"%s.xyStart.bestFit.run%d.png",runType,*runNumIter);
	c1->SaveAs(plotName);
	delete xyStart;

	TH2D* xyEnd = new TH2D("xyEnd","xyEnd",1000,-7,7,1000,-7,7);
	xyEnd->GetXaxis()->SetTitle("cm");
	xyEnd->GetYaxis()->SetTitle("cm");
	sprintf(histName,"xyEnd{%s}",runCut);
	xyEnd->SetTitle(histName);
	tracks->Draw("end.x():end.y()>>xyEnd",runCut,"colz");
	xyEnd->GetZaxis()->SetRangeUser(1,xyEnd->GetMaximum());
	xyEnd->Draw("Colz");
	sprintf(plotName,"%s.xyEnd.run%d.png",runType,*runNumIter);
	c1->SaveAs(plotName);
	sprintf(histName,"xyEnd{%s}",bestCut);
	xyEnd->SetTitle(histName);
	tracks->Draw("end.x():end.y()>>xyEnd",bestCut,"colz");
	sprintf(plotName,"%s.xyEnd.bestFit.run%d.png",runType,*runNumIter);
	c1->SaveAs(plotName);
	delete xyEnd;

	c1->SetLogz(0);

	c1->SetLogy(1);

	// TH1D* en = new TH1D("en","en",4000,0,168.6);
	// en->GetXaxis()->SetTitle("MeV");
	// tracks->Draw("energy*168.6/40000>>en",runCut,"");
	// sprintf(plotName,"%s.en.run%d.png",runType,*runNumIter);
	// c1->SaveAs(plotName);
	// tracks->Draw("energy*168.6/40000>>en",bestCut,"");
	// sprintf(plotName,"%s.en.bestFit.run%d.png",runType,*runNumIter);
	// c1->SaveAs(plotName);
	// delete en;

	// TH1D* adc = new TH1D("adc","adc",50000,0,50000);
	// adc->GetXaxis()->SetTitle("adc");
	// tracks->Draw("adc>>adc",runCut,"");
	// sprintf(plotName,"%s.adc.run%d.png",runType,*runNumIter);
	// c1->SaveAs(plotName);
	// tracks->Draw("adc>>adc",bestCut,"");
	// sprintf(plotName,"%s.adc.bestFit.run%d.png",runType,*runNumIter);
	// c1->SaveAs(plotName);
	// delete adc;

	// TH1D* length = new TH1D("length","length",1000,0,10);
	// length->GetXaxis()->SetTitle("cm");
	// tracks->Draw("length>>length",runCut,"");
	// sprintf(plotName,"%s.length.run%d.png",runType,*runNumIter);
	// c1->SaveAs(plotName);
	// tracks->Draw("length>>length",bestCut,"");
	// sprintf(plotName,"%s.length.bestFit.run%d.png",runType,*runNumIter);
	// c1->SaveAs(plotName);
	// delete length;

	// TH1D* digCharge = new TH1D("digCharge","digCharge",50000,0,50000);
	// digCharge->GetXaxis()->SetTitle("adcPerDig");
	// tracks->Draw("digitCharge>>digCharge",runCut,"");
	// sprintf(plotName,"%s.digCharge.run%d.png",runType,*runNumIter);
	// c1->SaveAs(plotName);
	// tracks->Draw("digitCharge>>digCharge",bestCut,"");
	// sprintf(plotName,"%s.digCharge.bestFit.run%d.png",runType,*runNumIter);
	// c1->SaveAs(plotName);
	// c1->SetLogy(0);
	// delete digCharge;

	// TH1D* az = new TH1D("az","az",2000,-3.15,3.15);
	// en->GetXaxis()->SetTitle("#phi");
	// tracks->Draw("direction.Phi()>>az",runCut,"");
	// sprintf(plotName,"%s.az.run%d.png",runType,*runNumIter);
	// c1->SaveAs(plotName);
	// tracks->Draw("direction.Phi()>>az",bestCut,"");
	// sprintf(plotName,"%s.az.bestFit.run%d.png",runType,*runNumIter);
	// c1->SaveAs(plotName);
	// delete az;

	// TH1D* cosPolar = new TH1D("cosPolar","cosPolar",1000,-1,1);
	// en->GetXaxis()->SetTitle("cos(#theta)");
	// tracks->Draw("direction.CosTheta()>>cosPolar",runCut,"");
	// sprintf(plotName,"%s.cosPolar.run%d.png",runType,*runNumIter);
	// c1->SaveAs(plotName);
	// tracks->Draw("direction.CosTheta()>>cosPolar",bestCut,"");
	// sprintf(plotName,"%s.cosPolar.bestFit.run%d.png",runType,*runNumIter);
	// c1->SaveAs(plotName);
	// delete cosPolar;

	// TH1D* polar = new TH1D("polar","polar",1000,0,3.15);
	// polar->GetXaxis()->SetTitle("#theta");
	// tracks->Draw("direction.Theta()>>polar",runCut,"");
	// sprintf(plotName,"%s.polar.run%d.png",runType,*runNumIter);
	// c1->SaveAs(plotName);
	// tracks->Draw("direction.Theta()>>polar",bestCut,"");
	// sprintf(plotName,"%s.polar.bestFit.run%d.png",runType,*runNumIter);
	// c1->SaveAs(plotName);
	// delete polar;



}

}