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
#include "TTree.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TMath.h"
#include "TFitResult.h"
#include "TAttMarker.h"
#include "TGraph.h"
#include "TImage.h"
#include "TCutG.h"
#include "TCut.h"
#include "TLegend.h"
#include "TLatex.h"


// NIFFTE Libraries
#include "NiffteGeometryMap.h"
#include "NiffteTPCADCSignal.h"
#include "NiffteRootIO.h"
#include "NiffteTPCDetectorConstruction.h"

// c++ Libraries
#include <cmath>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <time.h>
#include <string>
#include <stdlib.h>
#include <sstream>


void stepThruFragCut(const char* cftFile,const char* noMaskFile){

TFile * cftFileHandle = new TFile(cftFile);
TFile * noMaskFileHandle = new TFile(noMaskFile);
TH1D * cftLengthvsADC = (TH1D*)cftFileHandle->Get("LengthvsADC");
TH1D * noMaskLengthvsADC = (TH1D*)noMaskFileHandle->Get("LengthvsADC");

TH2D * cftLvsEn = new TH2D("cftLvsEn","Track Length vs. Energy",40000,0,191,1000,0.0,10.0);
TH2D * noMaskLvsEn = new TH2D("noMaskLvsEn","Track Length vs. Energy",40000,0,191,1000,0.0,10.0);
for (int adcbin = 0; adcbin < 40000; ++adcbin){
 	for (int lbin = 0; lbin < 1000; ++lbin){
	 	cftLvsEn->SetBinContent(adcbin,lbin,cftLengthvsADC->GetBinContent(adcbin,lbin));
	 	noMaskLvsEn->SetBinContent(adcbin,lbin,noMaskLengthvsADC->GetBinContent(adcbin,lbin));
 	}
}

TCutG *fragCut = new TCutG("fragCut",10);
fragCut->SetLineColor(2);
fragCut->SetLineWidth(3);
fragCut->SetPoint(0,  0,1.45);
fragCut->SetPoint(1, 15,2.25);
fragCut->SetPoint(2, 35,2.70);
fragCut->SetPoint(3, 71,3.50);
fragCut->SetPoint(4,143,4.00);
fragCut->SetPoint(5,143,3.00);
fragCut->SetPoint(6, 95,1.75);
fragCut->SetPoint(7, 71,1.50);
fragCut->SetPoint(8,  0,0.75);
fragCut->SetPoint(9,  0,1.45);

// TCutG *fragCut = new TCutG("fragCut",18);
// fragCut->SetLineColor(2);
// fragCut->SetLineWidth(3);
// fragCut->SetPoint(0,1.277,0.75);
// fragCut->SetPoint(1,1.750,0.85);
// fragCut->SetPoint(2,2.003,0.95);
// fragCut->SetPoint(3,2.251,1.05);
// fragCut->SetPoint(4,2.480,1.15);
// fragCut->SetPoint(5,2.652,1.25);
// fragCut->SetPoint(6,2.872,1.35);
// fragCut->SetPoint(7,3.010,1.45);
// fragCut->SetPoint(8,3.163,1.55);
// fragCut->SetPoint(9,3.287,1.65);
// fragCut->SetPoint(10, 15,2.25);
// fragCut->SetPoint(11, 35,2.70);
// fragCut->SetPoint(12, 71,3.50);
// fragCut->SetPoint(13,143,4.00);
// fragCut->SetPoint(14,143,3.00);
// fragCut->SetPoint(15, 95,1.75);
// fragCut->SetPoint(16, 71,1.50);
// fragCut->SetPoint(17,1.277,0.75);

cftLvsEn->SetName("cftLvsEn");
cftLvsEn->GetXaxis()->SetTitle("Track Energy [MeV]");
cftLvsEn->GetXaxis()->CenterTitle();
cftLvsEn->GetYaxis()->SetTitle("Track Length [cm]");
cftLvsEn->GetYaxis()->CenterTitle();

cftLvsEn->SetTitle("Cf-252 [Fission Trigger]");
TH1D * cftFrags = cftLvsEn->ProjectionX("cftFrags",0,40000,"[fragCut]");
cftFrags->GetXaxis()->SetTitle("MeV");
cftFrags->GetXaxis()->CenterTitle();
cftFrags->GetYaxis()->SetTitle("counts");
cftFrags->GetYaxis()->CenterTitle();
cftFrags->SetTitle("fragCut [Fission Trigger]");
cftFrags->SetLineColor(9);
cftFrags->SetLineWidth(2);

noMaskLvsEn->SetName("noMaskLvsEn");
noMaskLvsEn->GetXaxis()->SetTitle("Track Energy [MeV]");
noMaskLvsEn->GetXaxis()->CenterTitle();
noMaskLvsEn->GetYaxis()->SetTitle("Track Length [cm]");
noMaskLvsEn->GetYaxis()->CenterTitle();
noMaskLvsEn->SetTitle("Cf-252 [No Trigger]");
TH1D * noMaskFrags = noMaskLvsEn->ProjectionX("noMaskFrags",0,40000,"[fragCut]");

noMaskFrags->GetXaxis()->SetTitle("MeV");
noMaskFrags->GetXaxis()->CenterTitle();
noMaskFrags->GetYaxis()->SetTitle("counts");
noMaskFrags->GetYaxis()->CenterTitle();
noMaskFrags->SetTitle("fragCut [No Trigger]");
noMaskFrags->SetLineColor(2);
noMaskFrags->SetLineWidth(2);

// char projname[123];
// for (int lbinStep = 75; lbinStep <= 165; lbinStep+=10){

// 	TH1D *px = noMaskLvsEn->ProjectionX("px", lbinStep, lbinStep);
// 	double xCut = px->GetBinCenter(px->FindLastBinAbove(10)+50);
// 	double yCut = lbinStep/(double)10;
// 	std::cout << "xCut "<<xCut <<'\t'<<"yCut "<<yCut << std::endl;

// 	// px->Draw();
// 	// c1->SetLogy();
// 	// c1->SetGridx();
// 	// c1->SetGridy();
// 	// sprintf(projname,"projx.LvEn.yi%d.yf%d.png",lbinStep,lbinStep);
// 	// c1->SaveAs(projname);
// }


TFile f("cft_vs_noMask.root","recreate");
cftFrags->Write();
noMaskFrags->Write();
cftLvsEn->Write();
noMaskLvsEn->Write();
fragCut->Write();
double scaleCFT = noMaskFrags->Integral(5000,40000)/cftFrags->Integral(5000,40000);
TH1D* scaledCftFrags = (TH1D*)cftFrags->Clone("scaledCftFrags");
scaledCftFrags->Scale(scaleCFT);
scaledCftFrags->Write();

//////////////////////////////////////////
//////////  length vs En plots ///////////
//////////////////////////////////////////
TCanvas *c1 = new TCanvas("c1","c1",1000,700);
gStyle->SetOptStat(0);

// lenght VS ADC
c1->SetLogz(1);
cftLvsEn->GetXaxis()->SetRange(0,30000);
cftLvsEn->Draw("Colz");
c1->SaveAs("LvEn.full.cft.png","recreate");
fragCut->Draw("same");
c1->SaveAs("LvEn.full.cft.plusCut.png","recreate");
cftLvsEn->GetXaxis()->SetRange(200,2500);
cftLvsEn->Draw("Colz");
c1->SaveAs("LvEn.lowEn.cft.png","recreate");
fragCut->Draw("same");
c1->SaveAs("LvEn.lowEn.cft.plusCut.png","recreate");
cftLvsEn->GetXaxis()->SetRange(200,2500);
c1->SaveAs("LvEn.lowEn.cft.png","recreate");
cftLvsEn->GetXaxis()->SetRange(200,1500);
c1->Update();
c1->SaveAs("LvEn.lowEn.cft.plusCut.zoom.png","recreate");

noMaskLvsEn->GetXaxis()->SetRange(0,30000);
noMaskLvsEn->Draw("Colz");
c1->SaveAs("LvEn.full.noMask.png","recreate");
fragCut->Draw("same");
c1->SaveAs("LvEn.full.noMask.plusCut.png","recreate");
noMaskLvsEn->GetXaxis()->SetRange(200,2500);
noMaskLvsEn->Draw("Colz");
c1->SaveAs("LvEn.lowEn.noMask.png","recreate");
fragCut->Draw("same");
c1->SaveAs("LvEn.lowEn.noMask.plusCut.png","recreate");
noMaskLvsEn->GetXaxis()->SetRange(200,1500);
c1->Update();
c1->SaveAs("LvEn.lowEn.noMask.plusCut.zoom.png","recreate");


//////////////////////////////////////////
//////////////  rebinning ////////////////
//////////////////////////////////////////
int rebinInt=5;
TH1D* cftFragsRebin = (TH1D*)scaledCftFrags->Clone("cftFragsRebin");
cftFragsRebin->Rebin(rebinInt);
cftFragsRebin->Write();
TH1D* noMaskFragsRebin = (TH1D*)noMaskFrags->Clone("noMaskFragsRebin");
noMaskFragsRebin->Rebin(rebinInt);
noMaskFragsRebin->Write();

TH1D* cftEfficiency = (TH1D*)cftFragsRebin->Clone("cftEfficiency");
cftEfficiency->SetTitle("cftEfficiency = cft / noMask");
cftEfficiency->Divide(noMaskFragsRebin);
cftEfficiency->Write();


//fragment cut
c1->SetGridx(1);
c1->SetGridy(1);
c1->SetLogx(1);
c1->SetLogy(1);
cftFragsRebin->GetXaxis()->SetRange(noMaskFragsRebin->FindFirstBinAbove(0),30000/rebinInt);
cftFragsRebin->SetMaximum(noMaskFragsRebin->GetMaximum()*1.1);
cftFragsRebin->Draw("HIST P9 L");
char charContainer[128];
sprintf(charContainer,"frags.full.cft.%s.png",cftFile);
c1->SaveAs(charContainer,"recreate");
noMaskFragsRebin->GetXaxis()->SetRange(noMaskFragsRebin->FindFirstBinAbove(0),30000/rebinInt);
noMaskFragsRebin->SetMaximum(noMaskFragsRebin->GetMaximum());
noMaskFragsRebin->Draw("HIST P9 L");
sprintf(charContainer,"frags.full.noMask.%s.png",noMaskFile);
c1->SaveAs(charContainer,"recreate");

TLegend *legend1=new TLegend(0.5,0.15,0.78,0.35);
legend1->SetTextFont(42);
legend1->SetTextSize(0.03);
legend1->SetFillColor(kWhite);
legend1->AddEntry(noMaskFragsRebin,"No Trigger");
legend1->AddEntry(cftFragsRebin,"Fission Trigger");


// cft & noMask fragment same plot
noMaskFragsRebin->GetXaxis()->SetRange(noMaskFragsRebin->FindFirstBinAbove(0),30000/rebinInt);
cftFragsRebin->GetXaxis()->SetRange(noMaskFragsRebin->FindFirstBinAbove(0),30000/rebinInt);
c1->SetLogx(1);
c1->SetLogy(1);
noMaskFragsRebin->Draw("HIST P9 L");
noMaskFragsRebin->SetTitle("fragCut [Tirgger vs No Trigger]");
cftFragsRebin->Draw("same HIST P9 L");
legend1->Draw("same");
sprintf(charContainer,"bothFragsCut.withFits.%s.png",noMaskFile);
c1->SaveAs(charContainer,"recreate");
c1->SetLogx(0);
noMaskFragsRebin->SetMinimum(1);
noMaskFragsRebin->GetXaxis()->SetRange(noMaskFragsRebin->FindFirstBinAbove(0),2500/rebinInt);
cftFragsRebin->GetXaxis()->SetRange(noMaskFragsRebin->FindFirstBinAbove(0),2500/rebinInt);
cftFragsRebin->Draw("same HIST P9 L");
sprintf(charContainer,"lowEn.plusCFT.%s.png",noMaskFile);
c1->SaveAs(charContainer,"recreate");

TLegend *legendCFTefficiency=new TLegend(0.6,0.15,0.88,0.35);
legendCFTefficiency->SetTextFont(42);
legendCFTefficiency->SetTextSize(0.03);
legendCFTefficiency->SetFillColor(kWhite);
legendCFTefficiency->AddEntry(noMaskFragsRebin,"No Trigger");
legendCFTefficiency->AddEntry(cftFragsRebin,"Fission Trigger");
legendCFTefficiency->AddEntry(cftEfficiency,"CFT Efficiency");

// cft efficiency -> noMask / cft fragments
c1->SetLogx(0);
c1->SetLogy(0);
cftEfficiency->GetXaxis()->SetRange(noMaskFragsRebin->FindFirstBinAbove(0),2500/rebinInt);
cftEfficiency->SetLineColor(6);
cftEfficiency->Draw("HIST P9 L");
sprintf(charContainer,"cftEfficiency.%s.png",noMaskFile);
c1->SaveAs(charContainer,"recreate");
noMaskFragsRebin->SetMinimum(0.001);
noMaskFragsRebin->Draw("HIST P9 L");
cftFragsRebin->Draw("same HIST P9 L");
cftEfficiency->Draw("same HIST P9 L");
legendCFTefficiency->Draw("same HIST P9 L");
sprintf(charContainer,"cftEfficiencyWithFrags.%s.png",noMaskFile);
c1->SaveAs(charContainer,"recreate");

c1->SetLogy(1);
cftEfficiency->GetXaxis()->SetRange(noMaskFragsRebin->FindFirstBinAbove(0),2500/rebinInt);
cftEfficiency->SetLineColor(6);
cftEfficiency->Draw("HIST P9 L");
sprintf(charContainer,"cftEfficiency.log.%s.png",noMaskFile);
c1->SaveAs(charContainer,"recreate");
noMaskFragsRebin->SetMinimum(0.001);
noMaskFragsRebin->Draw("HIST P9 L");
cftFragsRebin->Draw("same HIST P9 L");
cftEfficiency->Draw("same HIST P9 L");
legendCFTefficiency->Draw("same HIST P9 L");
sprintf(charContainer,"cftEfficiencyWithFrags.log.%s.png",noMaskFile);
c1->SaveAs(charContainer,"recreate");

}
