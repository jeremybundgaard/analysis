#include <climits>
#include <vector>
#include "TROOT.h"
#include "TRint.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TCutG.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TMath.h"
#include "TLine.h"
#include "TMarker.h"
#include "TLegend.h"
#include "TStyle.h"

#include <math.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>

void buildAlphaRidgeCut2ndPreampHK() {

TFile* noMaskFile = new TFile("$trees/cf252.noMask2.trees.root");
TTree* noMaskTracks = (TTree*)noMaskFile->Get("tracks");
TH2D * noMaskLvEn = new TH2D("noMaskLvEn","",40000,0,168.6,1000,0,10);
noMaskLvEn->GetXaxis()->SetRangeUser(1,7);
noMaskLvEn->GetYaxis()->SetRangeUser(0,6);
noMaskLvEn->GetXaxis()->SetTitle("Track Energy [MeV]");
noMaskLvEn->GetXaxis()->CenterTitle();
noMaskLvEn->GetYaxis()->SetTitle("Track Length [cm]");
noMaskLvEn->GetYaxis()->CenterTitle();
TCanvas *c1 = new TCanvas("c1","c1",1000,700);
gStyle->SetOptStat(0);

noMaskTracks->Draw("length:adc*168.6/40000>>noMaskLvEn","fitType==5 && direction.Phi() < 2.2 && !(-1 < direction.Phi() && direction.Phi() < 0)","colz");
Double_t xCut[29];
Double_t yCut[29];
char projname[123];
int xBuffer = 111;

int arrayPos=0;
for (int lbinStep = 150; lbinStep < 300; lbinStep+=5){
	TH1D *px = noMaskLvEn->ProjectionX("px", lbinStep, lbinStep);
	px->GetXaxis()->SetRangeUser(1,7);
	px->GetYaxis()->SetRangeUser(1,300);
	int xCutBin = px->FindLastBinAbove(10)+xBuffer;
	xCut[arrayPos] = px->GetBinCenter(xCutBin);
	yCut[arrayPos] = lbinStep/(double)100;
	std::cout << "xCut , yCut"<<'\t'<<xCut[arrayPos] <<" , "<<yCut[arrayPos] <<'\t'
			<<"arrayPos="<<arrayPos<<'\t'<<"lbinStep = "<<lbinStep<< std::endl;
	arrayPos++;
}

c1->SetLogy(0);
TGraph *g = new TGraph((sizeof(xCut) / sizeof(Double_t)), xCut, yCut);
TF1 *fitLvsEn = new TF1("f", "[4] + [3]*TMath::Exp( [2]*x*x + [1]*x + [0] )",1,xCut[29 - 1]);

fitLvsEn->SetLineWidth(3);
fitLvsEn->SetLineColor(kRed);
g->Fit(fitLvsEn);
noMaskLvEn->SetTitle(fitLvsEn->GetTitle());
noMaskLvEn->Draw("Colz");
fitLvsEn->DrawF1(1,xCut[29 - 1],"same");
sprintf(projname,"alphaRidgeFit.LvEn.png");
c1->SaveAs(projname);

noMaskLvEn->GetXaxis()->SetRangeUser(xCut[0]-2,xCut[0]+2);
noMaskLvEn->GetYaxis()->SetRangeUser(yCut[0]-2,yCut[0]+2);
noMaskLvEn->Draw("Colz");
fitLvsEn->DrawF1(1,xCut[29 - 1],"same");
sprintf(projname,"alphaRidgeFit.zoom.LvEn.png");
c1->SaveAs(projname);
c1->SetLogz(1);
noMaskLvEn->Draw("Colz");
fitLvsEn->DrawF1(1,xCut[29 - 1],"same");
sprintf(projname,"alphaRidgeFit.zoom.log.LvEn.png");
c1->SaveAs(projname);
noMaskLvEn->GetXaxis()->SetRangeUser(0,7);
noMaskLvEn->GetYaxis()->SetRangeUser(0,6);

// show projection of alpha ridge
arrayPos=0;
for (int lbinStep = 150; lbinStep < 300; lbinStep+=5){
	c1->SetLogz(0);
	c1->SetLogy(0);
	TH1D *px = noMaskLvEn->ProjectionX("px", lbinStep, lbinStep);
	int xCutBin = px->FindLastBinAbove(10)+xBuffer;
	xCut[arrayPos] = px->GetBinCenter(xCutBin);
	yCut[arrayPos] = lbinStep/(double)100;
	std::cout << "xCut , yCut"<<'\t'<<xCut[arrayPos] <<" , "<<yCut[arrayPos] << std::endl;
	TLine *startLine = new TLine(px->GetBinCenter(px->FindLastBinAbove(10)),0,px->GetBinCenter(px->FindLastBinAbove(10)),px->GetBinContent(px->FindLastBinAbove(10)));
	startLine->SetLineColor(kGreen);
	startLine->SetLineWidth(3);
	TLine *linePlusBuffer = new TLine(xCut[arrayPos],0,xCut[arrayPos],px->GetBinContent(px->FindLastBinAbove(10)));
	linePlusBuffer->SetLineColor(kRed);
	linePlusBuffer->SetLineWidth(3);
	sprintf(projname,"projx.LvEn.ybin%d.zoom.png",lbinStep);
	px->SetTitle(projname);
	px->Draw();
	startLine->Draw("same");
	linePlusBuffer->Draw("same");
	c1->SetLogy();
	c1->SetGridx();
	c1->SetGridy();
	c1->SaveAs(projname);
	arrayPos++;
}


noMaskLvEn->GetYaxis()->SetRangeUser(0,5);
noMaskLvEn->SetTitle("LvEn [No Trigger]");
arrayPos=0;
for (int lbinStep = 150; lbinStep < 300; lbinStep+=5){
	c1->SetLogz(1);
	c1->SetLogy(0);
	TH1D *px = noMaskLvEn->ProjectionX("px", lbinStep, lbinStep);
	int xCutBin = px->FindLastBinAbove(10)+xBuffer;
	xCut[arrayPos] = px->GetBinCenter(xCutBin);
	yCut[arrayPos] = lbinStep/(double)100;
	std::cout << "xCut , yCut"<<'\t'<<xCut[arrayPos] <<" , "<<yCut[arrayPos] << std::endl;
	TLine *startLine = new TLine(px->GetBinCenter(px->FindLastBinAbove(10)),yCut[arrayPos]-0.05,px->GetBinCenter(px->FindLastBinAbove(10)),yCut[arrayPos]+0.05);
	startLine->SetLineColor(kGreen);
	startLine->SetLineWidth(5);
	TLine *linePlusBuffer = new TLine(xCut[arrayPos],yCut[arrayPos]-0.05,xCut[arrayPos],yCut[arrayPos]+0.05);
	linePlusBuffer->SetLineColor(kRed);
	linePlusBuffer->SetLineWidth(5);
	noMaskLvEn->Draw("Colz");
	startLine->Draw("same");
	linePlusBuffer->Draw("same");
	sprintf(projname,"LvEn.y%d.zoom.png",lbinStep);
	c1->SaveAs(projname);
	arrayPos++;
}

double_t alphaRidgeFitStartY = 0.5;
double_t alphaRidgeFitStartX = fitLvsEn->GetX(alphaRidgeFitStartY);
double_t alphaRidgeFitStopY = 1;
double_t alphaRidgeFitStopX = fitLvsEn->GetX(alphaRidgeFitStopY);


TCutG *fragCutSimple = new TCutG("fragCutSimple",8);
fragCutSimple->SetLineColor(kViolet);
fragCutSimple->SetLineWidth(3);
fragCutSimple->GetXaxis()->SetRangeUser(1,3);
fragCutSimple->GetYaxis()->SetRangeUser(0,1);
fragCutSimple->SetPoint(1, 15,1.95+0.4);
fragCutSimple->SetPoint(2, 71,2.75+0.4);
fragCutSimple->SetPoint(3, 150,3.25+0.4);
fragCutSimple->SetPoint(4, 150,1.25+0.4);
fragCutSimple->SetPoint(5, alphaRidgeFitStartX,alphaRidgeFitStartY);
fragCutSimple->SetPoint(6, 1.5,0.70+0.4);
fragCutSimple->SetPoint(0, 1.5,0.70+0.4);


int newCutPoint=7;
noMaskLvEn->GetXaxis()->SetRangeUser(alphaRidgeFitStartX-1,alphaRidgeFitStopX+1);
noMaskLvEn->GetYaxis()->SetRangeUser(alphaRidgeFitStartY-1,alphaRidgeFitStopY+1);

for (double interpoAlphaRidge = alphaRidgeFitStartX; interpoAlphaRidge <= alphaRidgeFitStopX; interpoAlphaRidge+=0.1)
{
	fragCutSimple->SetPoint(newCutPoint,interpoAlphaRidge,fitLvsEn->Eval(interpoAlphaRidge));
	fragCutSimple->SetPoint(0,interpoAlphaRidge,fitLvsEn->Eval(interpoAlphaRidge));
	newCutPoint++;
	noMaskLvEn->Draw("Colz");
	fitLvsEn->DrawF1(alphaRidgeFitStartX-.2,alphaRidgeFitStopX+.2,"same");
	fragCutSimple->Draw("same");
	sprintf(projname,"alphaRidgeFit.zoom.log.LvEn.%0.1f.png",interpoAlphaRidge);
	c1->SaveAs(projname);
}

ofstream cutfile;
cutfile.open("alphaRidgeCut2ndPreamp.C");
fragCutSimple->SavePrimitive(cutfile,"");

noMaskLvEn->SetTitle(fitLvsEn->GetTitle());
noMaskLvEn->GetXaxis()->SetRangeUser(1,7);
noMaskLvEn->GetYaxis()->SetRangeUser(0,6);	
noMaskLvEn->Draw("Colz");
fitLvsEn->DrawF1(1,xCut[29 - 1],"same");
fragCutSimple->Draw("same");
sprintf(projname,"alphaRidgeFit.plusFragCut.LvEn.png");
c1->SaveAs(projname);

noMaskLvEn->GetXaxis()->SetRangeUser(1,50);
noMaskLvEn->GetYaxis()->SetRangeUser(0,6);	
noMaskLvEn->Draw("Colz");
fitLvsEn->DrawF1(1,xCut[29 - 1],"same");
fragCutSimple->Draw("same");
sprintf(projname,"FragCut.LvEn.png");
c1->SaveAs(projname);

std::cout<< "alphaRidgeFitStartY = "<<alphaRidgeFitStartY<<std::endl;
std::cout<< "alphaRidgeFitStartX = "<<alphaRidgeFitStartX<<std::endl;
std::cout<< "alphaRidgeFitStopY = "<<alphaRidgeFitStopY<<std::endl;
std::cout<< "alphaRidgeFitStopX = "<<alphaRidgeFitStopX<<std::endl;


}
