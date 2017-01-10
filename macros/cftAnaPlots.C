#include "THStack.h"
#include <climits>
#include <vector>
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

#include <math.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>

void cftAnaPlots(const int preamp, const char* actinide, const char* pidFileName="", const char* noMaskFileName="", const char* cftFileName="", const char* otherTreeCuts="1", const char* driftVel="", const char* addGuide="") {

TCanvas *c1 = new TCanvas("c1","c1",1000,700);
char c1PlotName[234];
gStyle->SetOptStat(0);
gStyle->SetPalette(71);
gStyle->SetNumberContours(999);
gStyle->SetLegendBorderSize(0);
char buffChar[345];

double MeV_per_ADC=0;
double ADC_per_MeV=0;
double dEnergy = 0.1;
double isoTopicCalib=0.9186;
double pi=4*atan(1);
double deg2rad = pi/(double)180;

char noMaskCut[234];
char cftCut[234];
char noMaskRunCut[234];
char cftRunCut[234];
char azCut[234];
char noMaskDigitFileName[234];
char cftDigitFileName[234];
char pidFile_char[345];

if (preamp==1)
{
	ADC_per_MeV=1180/6.118;
	MeV_per_ADC=6.118/1180;
	if (!(strcmp(actinide,"cf252"))){}
	sprintf(noMaskRunCut,"run>100001856");
	sprintf(noMaskCut," %s",noMaskRunCut);
}
else if (preamp==2)
{
	ADC_per_MeV=1450/6.118;
	MeV_per_ADC=6.118/1450;
	if (!(strcmp(actinide,"cf252"))){
		sprintf(azCut,"!(-1<direction.Phi()&&direction.Phi()<0)");
	}
	if ( !(strcmp(actinide,"cm244"))){
		sprintf(azCut,"direction.Phi()<2.2");
	}
	sprintf(noMaskCut,"%s",azCut);
	sprintf(cftCut,"%s",azCut);
}


////////////////////// initialize cuts from pid file ///////////////////////////////////
printf("////////////////////// initialize cuts from pid file:%s ///////////////////////////////////\n",pidFileName);
/////////  create TCutG chars ///////////
char fragCut_adc_char[345];
char fragCut_unlikely_adc_char[345];
char alphaCut_adc_char[345];
char alpha_short_high_adc_char[345];
char alpha_short_low_adc_char[345];
char above_zCut_adc_char[345];
sprintf(fragCut_unlikely_adc_char,"fragCut_unlikely_adc");
sprintf(fragCut_adc_char,"fragCut_adc");
sprintf(alphaCut_adc_char,"alphaCut_adc");
sprintf(alpha_short_high_adc_char,"alphaCut_short_higher_adc");
sprintf(alpha_short_low_adc_char,"alphaCut_short_low_adc");
sprintf(above_zCut_adc_char,"alphaCut_zCut_adc");
char fragCut_energy_char[345];
char fragCut_unlikely_energy_char[345];
char alphaCut_energy_char[345];
char alpha_short_high_energy_char[345];
char alpha_short_low_energy_char[345];
char above_zCut_energy_char[345];
sprintf(fragCut_unlikely_energy_char,"fragCut_unlikely_energy");
sprintf(fragCut_energy_char,"fragCut_energy");
sprintf(alphaCut_energy_char,"alphaCut_energy");
sprintf(alpha_short_high_energy_char,"alphaCut_short_higher_energy");
sprintf(alpha_short_low_energy_char,"alphaCut_short_low_energy");
sprintf(above_zCut_energy_char,"alphaCut_zCut_energy");
// fragCut_adc is crucial for invoking this cut in ->Draw()
TFile* pidFile = new TFile(pidFileName);
// TCutG* fragCut_adc = (TCutG*)pidFile->Get(fragCut_adc_char);
// fragCut_adc->SetName("fragCut_adc");
// fragCut_adc->SetLineColor(kViolet);
// fragCut_adc->SetLineWidth(1);
// fragCut_adc->SetFillColorAlpha(kViolet,0.3);
// TCutG* fragCut_unlikely_adc = (TCutG*)pidFile->Get(fragCut_unlikely_adc_char);
// fragCut_unlikely_adc->SetName("fragCut_unlikely_adc");
// fragCut_unlikely_adc->SetLineColor(kViolet-9);
// fragCut_unlikely_adc->SetLineWidth(1);
// fragCut_unlikely_adc->SetFillColorAlpha(kViolet-9,0.3);
// TCutG* alphaCut_above_zCut_adc = (TCutG*)pidFile->Get(above_zCut_adc_char);
// alphaCut_above_zCut_adc->SetName("alphaCut_above_zCut_adc");
// alphaCut_above_zCut_adc->SetLineColor(kSpring);
// alphaCut_above_zCut_adc->SetLineWidth(2);
// alphaCut_above_zCut_adc->SetFillColorAlpha(kSpring,0.3);
// TCutG* alphaCut_long_low_adc = (TCutG*)pidFile->Get("alphaCut_long_low_adc");
// alphaCut_long_low_adc->SetName("alphaCut_long_low_adc");
// alphaCut_long_low_adc->SetLineColor(kYellow);
// alphaCut_long_low_adc->SetLineWidth(1);
// alphaCut_long_low_adc->SetFillColorAlpha(kYellow,0.3);
// TCutG* alphaCut_long_adc = (TCutG*)pidFile->Get("alphaCut_long_adc");
// alphaCut_long_adc->SetName("alphaCut_long_adc");
// alphaCut_long_adc->SetLineColor(kCyan);
// alphaCut_long_adc->SetLineWidth(1);
// alphaCut_long_adc->SetFillColorAlpha(kCyan,0.3);
// TCutG* long_high_adc = (TCutG*)pidFile->Get("long_high_adc");
// long_high_adc->SetName("long_high_adc");
// long_high_adc->SetLineColor(kBlue);
// long_high_adc->SetLineWidth(1);
// long_high_adc->SetFillColorAlpha(kBlue,0.3);
// TCutG* alphaCut_short_higher_adc = (TCutG*)pidFile->Get(alpha_short_high_adc_char);
// alphaCut_short_higher_adc->SetName("alphaCut_short_higher_adc");
// alphaCut_short_higher_adc->SetLineColor(kOrange+7);
// alphaCut_short_higher_adc->SetLineWidth(1);
// alphaCut_short_higher_adc->SetFillColorAlpha(kOrange+7,0.3);
// TCutG* alphaCut_short_low_adc = (TCutG*)pidFile->Get(alpha_short_low_adc_char);
// alphaCut_short_low_adc->SetName("alphaCut_short_low_adc");
// alphaCut_short_low_adc->SetLineColor(kRed);
// alphaCut_short_low_adc->SetLineWidth(1);
// alphaCut_short_low_adc->SetFillColorAlpha(kRed,0.3);
// // fragCut_energy is crucial for invoking this cut in ->Draw()
// TCutG* fragCut_energy = (TCutG*)pidFile->Get(fragCut_energy_char);
// fragCut_energy->SetName("fragCut_energy");
// fragCut_energy->SetLineColor(kViolet);
// fragCut_energy->SetLineWidth(1);
// fragCut_energy->SetFillColorAlpha(kViolet,0.3);
// TCutG* fragCut_unlikely_energy = (TCutG*)pidFile->Get(fragCut_unlikely_energy_char);
// fragCut_unlikely_energy->SetName("fragCut_unlikely_energy");
// fragCut_unlikely_energy->SetLineColor(kViolet-9);
// fragCut_unlikely_energy->SetLineWidth(1);
// fragCut_unlikely_energy->SetFillColorAlpha(kViolet-9,0.3);
// TCutG* alphaCut_above_zCut_energy = (TCutG*)pidFile->Get(above_zCut_energy_char);
// alphaCut_above_zCut_energy->SetName("above_zCut_energy");
// alphaCut_above_zCut_energy->SetLineColor(kSpring);
// alphaCut_above_zCut_energy->SetLineWidth(2);
// alphaCut_above_zCut_energy->SetFillColorAlpha(kSpring,0.3);
// TCutG* alphaCut_long_low_energy = (TCutG*)pidFile->Get("alphaCut_long_low_energy");
// alphaCut_long_low_energy->SetName("alphaCut_long_low_energy");
// alphaCut_long_low_energy->SetLineColor(kYellow);
// alphaCut_long_low_energy->SetLineWidth(1);
// alphaCut_long_low_energy->SetFillColorAlpha(kYellow,0.3);
// TCutG* alphaCut_long_energy = (TCutG*)pidFile->Get("alphaCut_long_energy");
// alphaCut_long_energy->SetName("alphaCut_long_energy");
// alphaCut_long_energy->SetLineColor(kCyan);
// alphaCut_long_energy->SetLineWidth(1);
// alphaCut_long_energy->SetFillColorAlpha(kCyan,0.3);
// TCutG* long_high_energy = (TCutG*)pidFile->Get("long_high_energy");
// long_high_energy->SetName("long_high_energy");
// long_high_energy->SetLineColor(kBlue);
// long_high_energy->SetLineWidth(1);
// long_high_energy->SetFillColorAlpha(kBlue,0.3);
// TCutG* alphaCut_short_higher_energy = (TCutG*)pidFile->Get(alpha_short_high_energy_char);
// alphaCut_short_higher_energy->SetName("alphaCut_short_higher_energy");
// alphaCut_short_higher_energy->SetLineColor(kOrange+7);
// alphaCut_short_higher_energy->SetLineWidth(1);
// alphaCut_short_higher_energy->SetFillColorAlpha(kOrange+7,0.3);
// TCutG* alphaCut_short_low_energy = (TCutG*)pidFile->Get(alpha_short_low_energy_char);
// alphaCut_short_low_energy->SetName("alphaCut_short_low_energy");
// alphaCut_short_low_energy->SetLineColor(kRed);
// alphaCut_short_low_energy->SetLineWidth(1);
// alphaCut_short_low_energy->SetFillColorAlpha(kRed,0.3);
// char noMaskFragCut[234];sprintf(noMaskFragCut,"fragCut_adc");
// printf("noMaskFragCut: %s\n",noMaskFragCut);
// char noMaskFragUnlikelyCut_char[234];sprintf(noMaskFragUnlikelyCut_char,"fragCut_unlikely_adc");
// printf("noMaskFragUnlikelyCut_char: %s\n",noMaskFragUnlikelyCut_char);
// char noMaskAlphaCut_above_zCut_adc_char[234];sprintf(noMaskAlphaCut_above_zCut_adc_char,"alphaCut_above_zCut_adc");
// char noMaskAlphaCut_long_char[234];sprintf(noMaskAlphaCut_long_char,"alphaCut_long_adc");
// char noMaskAlphaCut_long_low_char[234];sprintf(noMaskAlphaCut_long_low_char,"alphaCut_long_low_adc");
// char noMaskAlphaCut_long_high_adc_char[234];sprintf(noMaskAlphaCut_long_high_adc_char,"long_high_adc");
// char noMaskAlphaCut_short_higher_adc_char[234];sprintf(noMaskAlphaCut_short_higher_adc_char,"alphaCut_short_higher_adc");
// char noMaskAlphaCut_alphaCut_short_low_adc_char[234];sprintf(noMaskAlphaCut_alphaCut_short_low_adc_char,"alphaCut_short_low_adc");
// char cftFragCut[234];sprintf(cftFragCut,"fragCut_adc");
// char cftFragUnlikelyCut_char[234];sprintf(cftFragUnlikelyCut_char,"fragCut_unlikely_adc");
// char cftAlphaCut_above_zCut_adc_char[234];sprintf(cftAlphaCut_above_zCut_adc_char,"alphaCut_above_zCut_adc");
// char cftAlphaCut_long_char[234];sprintf(cftAlphaCut_long_char,"alphaCut_long_adc");
// char cftAlphaCut_long_low_char[234];sprintf(cftAlphaCut_long_low_char,"alphaCut_long_low_adc");
// char cftAlphaCut_long_high_adc_char[234];sprintf(cftAlphaCut_long_high_adc_char,"long_high_adc");
// char cftAlphaCut_short_higher_adc_char[234];sprintf(cftAlphaCut_short_higher_adc_char,"alphaCut_short_higher_adc");
// char cftAlphaCut_alphaCut_short_low_adc_char[234];sprintf(cftAlphaCut_alphaCut_short_low_adc_char,"alphaCut_short_low_adc");

// // ////////////////////// draw noMask digit/tracks trees ///////////////////////////////////
// // printf("////////////////////// draw noMask digit/tracks trees ///////////////////////////////////\n");
// // sprintf(noMaskDigitFileName,"/p/lscratche/jerbundg/data/thesisData/trees/digTrkTreeDir/noMask%d.driftVel%s_trk_dig.2k.trees.root",preamp,driftVel);
// // TFile* noMaskDigitFile = new TFile(noMaskDigitFileName);
// // TTree* noMaskDigits = (TTree*)noMaskDigitFile->Get("tracks");
// // printf("drawing digits in noMaskLvADC cut \n");
// // noMaskDigits->Draw("dig_x:dig_y:dig_z:dig_adc",noMaskCut);
// // c1->SaveAs("noMaskLvADC.png");
// // c1->SaveAs("noMaskLvADC.C");
// // printf("drawing digits in noMaskLvADCAlphas cut \n");
// // noMaskDigits->Draw("dig_x:dig_y:dig_z:dig_adc",noMaskAlphaCut_above_zCut_adc_char);
// // c1->SaveAs("noMaskLvADCAlphas.png");
// // c1->SaveAs("noMaskLvADCAlphas.C");
// // printf("drawing digits in noMaskLvADCFrags cut \n");
// // noMaskDigits->Draw("dig_x:dig_y:dig_z:dig_adc",noMaskFragCut);
// // c1->SaveAs("noMaskLvADCFrags.png");
// // c1->SaveAs("noMaskLvADCFrags.C");
// // printf("drawing digits in noMaskLvADCFragsUnlikely cut \n");
// // noMaskDigits->Draw("dig_x:dig_y:dig_z:dig_adc",noMaskFragUnlikelyCut_char);
// // c1->SaveAs("noMaskLvADCFragsUnlikely.png");
// // c1->SaveAs("noMaskLvADCFragsUnlikely.C");
// // printf("drawing digits in noMaskLvADCAlphas_long cut \n");
// // noMaskDigits->Draw("dig_x:dig_y:dig_z:dig_adc",noMaskAlphaCut_long_char);
// // c1->SaveAs("noMaskLvADCAlphas_long.png");
// // c1->SaveAs("noMaskLvADCAlphas_long.C");
// // printf("drawing digits in noMaskLvADCAlphas_long_low cut \n");
// // noMaskDigits->Draw("dig_x:dig_y:dig_z:dig_adc",noMaskAlphaCut_long_low_char);
// // c1->SaveAs("noMaskLvADCAlphas_long_low.png");
// // c1->SaveAs("noMaskLvADCAlphas_long_low.C");
// // printf("drawing digits in noMaskLvADCAlphas_long_high cut \n");
// // noMaskDigits->Draw("dig_x:dig_y:dig_z:dig_adc",noMaskAlphaCut_long_high_adc_char);
// // c1->SaveAs("noMaskLvADCAlphas_long_high.png");
// // c1->SaveAs("noMaskLvADCAlphas_long_high.C");
// // printf("drawing digits in noMaskLvADCAlphas_short_higher cut \n");
// // noMaskDigits->Draw("dig_x:dig_y:dig_z:dig_adc",noMaskAlphaCut_short_higher_adc_char);
// // c1->SaveAs("noMaskLvADCAlphas_short_higher.png");
// // c1->SaveAs("noMaskLvADCAlphas_short_higher.C");
// // printf("drawing digits in noMaskLvADCAlphas_alphaCut_short_low cut \n");
// // noMaskDigits->Draw("dig_x:dig_y:dig_z:dig_adc",noMaskAlphaCut_alphaCut_short_low_adc_char);
// // c1->SaveAs("noMaskLvADCAlphas_alphaCut_short_low.png");
// // c1->SaveAs("noMaskLvADCAlphas_alphaCut_short_low.C");
//
// printf("noMaskCut = %s\n",noMaskCut);
// printf("cftCut = %s\n",cftCut);
// ////////////////////// get track trees ///////////////////////////////////
// printf("////////////////////// get track trees ///////////////////////////////////\n");
// TFile* cftFile = new TFile(cftFileName);
// TTree* cftTracks_orig = (TTree*)cftFile->Get("tracks");
// TFile* noMaskFile = new TFile(noMaskFileName);
// TTree* noMaskTracks_orig = (TTree*)noMaskFile->Get("tracks");
// TFile* dummy = new TFile("deleteme.root","create");
// dummy->cd();
// TTree* cftTracks = (TTree*)cftTracks_orig->CopyTree(cftCut);
// TTree* noMaskTracks = (TTree*)noMaskTracks_orig->CopyTree(noMaskCut);
//
// ///////////////////////////////////////////////////////////////////
// //////////////  build theta inset to guide the eye ////////////////
// ///////////////////////////////////////////////////////////////////
// TH1D* getThetaRange = new TH1D("getThetaRange","getThetaRange",500,0,pi);
// noMaskTracks->Draw("direction.Theta()>>getThetaRange");
// double radThetaMin=getThetaRange->GetBinCenter(getThetaRange->FindFirstBinAbove(0));
// double radThetaMax=getThetaRange->GetBinCenter(getThetaRange->FindLastBinAbove(0));
// double origin=0.5;
// TLine *lMin = new TLine(origin,origin,0.5*TMath::Cos(radThetaMin)+origin,0.5*TMath::Sin(radThetaMin)+origin);
// lMin->SetLineColor(3);
// lMin->SetLineWidth(2);
// TLine *lMax = new TLine(origin,origin,0.5*TMath::Cos(radThetaMax)+origin,0.5*TMath::Sin(radThetaMax)+origin);
// lMax->SetLineColor(3);
// lMax->SetLineWidth(2);
// TLine *lcath = new TLine(origin,origin,origin,2*origin);
// lcath->SetLineColor(2);
// TLine *lano = new TLine(0,origin,1,origin);
// lano->SetLineColor(kBlack);
// TMarker *m = new TMarker();
// m->SetMarkerStyle(20);
// m->SetMarkerColor(kBlue);
// TLatex *t0deg = new TLatex(2*origin-0.1,origin-0.1,"#scale[2.2]{0^{o}}");
// TLatex *t90deg = new TLatex(origin-0.1,2*origin-0.1,"#scale[2.2]{90^{o}}");
// TLatex *t180deg = new TLatex(0,origin-0.1,"#scale[2.2]{180^{o}}");
// TLatex *vol1 = new TLatex(0.25,0.66,"#scale[2.2]{vol 1}");vol1->SetTextAlign(22);
// TLatex *vol0 = new TLatex(0.75,0.66,"#scale[2.2]{vol 0}");vol0->SetTextAlign(22);
// TLegend* otherTreeCuts_legend = new TLegend(0,0,1,1);
// otherTreeCuts_legend->SetTextFont(30);
// otherTreeCuts_legend->AddEntry((TObject*)0,otherTreeCuts,"");
// TCanvas* smallCanvas = new TCanvas("smallCanvas","smallCanvas",200,200);
// if ( !(strcmp(addGuide,"polar")) ){
// 	m->DrawMarker(origin,origin);
// 	lMin->Draw();
// 	lMax->Draw();
// 	lcath->Draw();
// 	lano->Draw();
// 	t0deg->Draw("same");
// 	// t90deg->Draw("same");
// 	t180deg->Draw("same");
// 	vol0->Draw("same");
// 	vol1->Draw("same");
// }
// if ( !(strcmp(addGuide,"nDigits")) ){
// 	otherTreeCuts_legend->Draw();
// }
// smallCanvas->SaveAs("scanGuide.png");
// c1->cd();
//
//
// ////////////////////// create PID bin histograms ///////////////////////////////////
// printf("////////////////////// create PID bin histograms ///////////////////////////////////\n");
// TH2D* noMaskLvADC = new TH2D("noMaskLvADC","noMaskLvADC",40000,0,40000,1000,0,10);
// TH2D* noMaskLvADCFrags = (TH2D*)noMaskLvADC->Clone("noMaskLvADCFrags");
// TH2D* noMaskLvADCFragsUnlikely = (TH2D*)noMaskLvADC->Clone("noMaskLvADCFragsUnlikely");
// TH2D* noMaskLvADCAlphas = (TH2D*)noMaskLvADC->Clone("noMaskLvADCAlphas");
// TH2D* noMaskLvADCAlphas_long = (TH2D*)noMaskLvADC->Clone("noMaskLvADCAlphas_long");
// TH2D* noMaskLvADCAlphas_long_low = (TH2D*)noMaskLvADC->Clone("noMaskLvADCAlphas_long_low");
// TH2D* noMaskLvADCAlphas_long_high = (TH2D*)noMaskLvADC->Clone("noMaskLvADCAlphas_long_high");
// TH2D* noMaskLvADCAlphas_short_higher = (TH2D*)noMaskLvADC->Clone("noMaskLvADCAlphas_short_higher");
// TH2D* noMaskLvADCAlphas_alphaCut_short_low = (TH2D*)noMaskLvADC->Clone("noMaskLvADCAlphas_alphaCut_short_low");
// TH2D* noMaskLvADC_checkMutualExclusivity = (TH2D*)noMaskLvADC->Clone("noMaskLvADC_checkMutualExclusivity");
// TH2D* cftLvADC = new TH2D("cftLvADC","cftLvADC",40000,0,40000,1000,0,10);
// TH2D* cftLvADCFrags = (TH2D*)cftLvADC->Clone("cftLvADCFrags");
// TH2D* cftLvADCFragsUnlikely = (TH2D*)cftLvADC->Clone("cftLvADCFragsUnlikely");
// TH2D* cftLvADCAlphas = (TH2D*)cftLvADC->Clone("cftLvADCAlphas");
// TH2D* cftLvADCAlphas_long = (TH2D*)cftLvADC->Clone("cftLvADCAlphas_long");
// TH2D* cftLvADCAlphas_long_low = (TH2D*)cftLvADC->Clone("cftLvADCAlphas_long_low");
// TH2D* cftLvADCAlphas_long_high = (TH2D*)cftLvADC->Clone("cftLvADCAlphas_long_high");
// TH2D* cftLvADCAlphas_short_higher = (TH2D*)cftLvADC->Clone("cftLvADCAlphas_short_higher");
// TH2D* cftLvADCAlphas_alphaCut_short_low = (TH2D*)cftLvADC->Clone("cftLvADCAlphas_alphaCut_short_low");
//
// ////////////////////// fill noMask PID histograms ///////////////////////////////////
// printf("////////////////////// fill noMask PID histograms ///////////////////////////////////\n");
// char noMask_mutualExclusivityCheckChar[567];
// sprintf(noMask_mutualExclusivityCheckChar,"%s||%s||%s||%s||%s||%s||%s||%s",
// noMaskAlphaCut_above_zCut_adc_char,
// noMaskFragCut,
// noMaskFragUnlikelyCut_char,
// noMaskAlphaCut_long_char,
// noMaskAlphaCut_long_low_char,
// noMaskAlphaCut_long_high_adc_char,
// noMaskAlphaCut_short_higher_adc_char,
// noMaskAlphaCut_alphaCut_short_low_adc_char);
// printf("noMask_mutualExclusivityCheckChar:%s\n",noMask_mutualExclusivityCheckChar);
// noMaskTracks->Draw("length:adc>>noMaskLvADC_checkMutualExclusivity",noMask_mutualExclusivityCheckChar);
// int noMaskLvADC_checkMutualExclusivity_integral = noMaskLvADC_checkMutualExclusivity->Integral();
// printf("filled %d noMaskLvADC_checkMutualExclusivity from track tree\n",noMaskLvADC_checkMutualExclusivity_integral);
// noMaskTracks->Draw("length:adc>>noMaskLvADC",noMaskCut);
// int noMaskLvADC_integral = noMaskLvADC->Integral();
// printf("filled %d noMaskLvADC from track tree\n",noMaskLvADC_integral);
// noMaskTracks->Draw("length:adc>>noMaskLvADCAlphas",noMaskAlphaCut_above_zCut_adc_char);
// int noMaskLvADCAlphas_integral = noMaskLvADCAlphas->Integral();
// printf("filled %d noMaskLvADCAlphas from track tree\n",noMaskLvADCAlphas_integral);
// noMaskTracks->Draw("length:adc>>noMaskLvADCFrags",noMaskFragCut);
// int noMaskLvADCFrags_integral = noMaskLvADCFrags->Integral();
// printf("filled %d noMaskLvADCFrags from track tree\n",noMaskLvADCFrags_integral);
// noMaskTracks->Draw("length:adc>>noMaskLvADCFragsUnlikely",noMaskFragUnlikelyCut_char);
// int noMaskLvADCFragsUnlikely_integral = noMaskLvADCFragsUnlikely->Integral();
// printf("filled %d noMaskLvADCFragsUnlikely from track tree\n",noMaskLvADCFragsUnlikely_integral);
// noMaskTracks->Draw("length:adc>>noMaskLvADCAlphas_long",noMaskAlphaCut_long_char);
// int noMaskLvADCAlphas_long_integral = noMaskLvADCAlphas_long->Integral();
// printf("filled %d noMaskLvADCAlphas_long from track tree\n",noMaskLvADCAlphas_long_integral);
// noMaskTracks->Draw("length:adc>>noMaskLvADCAlphas_long_low",noMaskAlphaCut_long_low_char);
// int noMaskLvADCAlphas_long_low_integral = noMaskLvADCAlphas_long_low->Integral();
// printf("filled %d noMaskLvADCAlphas_long_low from track tree\n",noMaskLvADCAlphas_long_low_integral);
// noMaskTracks->Draw("length:adc>>noMaskLvADCAlphas_long_high",noMaskAlphaCut_long_high_adc_char);
// int noMaskLvADCAlphas_long_high_integral = noMaskLvADCAlphas_long_high->Integral();
// printf("filled %d noMaskLvADCAlphas_long_high from track tree\n",noMaskLvADCAlphas_long_high_integral);
// noMaskTracks->Draw("length:adc>>noMaskLvADCAlphas_short_higher",noMaskAlphaCut_short_higher_adc_char);
// int noMaskLvADCAlphas_short_higher_integral = noMaskLvADCAlphas_short_higher->Integral();
// printf("filled %d noMaskLvADCAlphas_short_higher from track tree\n",noMaskLvADCAlphas_short_higher_integral);
// noMaskTracks->Draw("length:adc>>noMaskLvADCAlphas_alphaCut_short_low",noMaskAlphaCut_alphaCut_short_low_adc_char);
// int noMaskLvADCAlphas_alphaCut_short_low_integral = noMaskLvADCAlphas_alphaCut_short_low->Integral();
// ////////////////////// verify PID bins are mutually exclusive ///////////////////////////////////
// printf("////////////////////// verify PID bins are mutually exclusive ///////////////////////////////////\n");
// printf("filled %d noMaskLvADCAlphas_alphaCut_short_low from track tree\n",noMaskLvADCAlphas_alphaCut_short_low_integral);
// printf("noMaskLvADC_integral - all TCutG integrals :%d\n",
// noMaskLvADC_integral
// -noMaskLvADCAlphas_integral
// -noMaskLvADCFrags_integral
// -noMaskLvADCFragsUnlikely_integral
// -noMaskLvADCAlphas_long_integral
// -noMaskLvADCAlphas_long_low_integral
// -noMaskLvADCAlphas_long_high_integral
// -noMaskLvADCAlphas_short_higher_integral
// -noMaskLvADCAlphas_alphaCut_short_low_integral
// );
// printf("noMaskLvADC_integral - noMaskLvADC_checkMutualExclusivity_integral :%d\n",
// noMaskLvADC_integral - noMaskLvADC_checkMutualExclusivity_integral);
//
// ////////////////////// fill cft PID histograms ///////////////////////////////////
// printf("////////////////////// fill cft PID histograms ///////////////////////////////////\n");
// cftTracks->Draw("length:adc>>cftLvADC",cftCut);
// cftTracks->Draw("length:adc>>cftLvADCAlphas",cftAlphaCut_above_zCut_adc_char);
// cftTracks->Draw("length:adc>>cftLvADCFrags",cftFragCut);
// cftTracks->Draw("length:adc>>cftLvADCFragsUnlikely",cftFragUnlikelyCut_char);
// cftTracks->Draw("length:adc>>cftLvADCAlphas_long",cftAlphaCut_long_char);
// cftTracks->Draw("length:adc>>cftLvADCAlphas_long_low",cftAlphaCut_long_low_char);
// cftTracks->Draw("length:adc>>cftLvADCAlphas_long_high",cftAlphaCut_long_high_adc_char);
// cftTracks->Draw("length:adc>>cftLvADCAlphas_short_higher",cftAlphaCut_short_higher_adc_char);
// cftTracks->Draw("length:adc>>cftLvADCAlphas_alphaCut_short_low",cftAlphaCut_alphaCut_short_low_adc_char);
//
// ////////////////////// create noMaskLvEn  ///////////////////////////////////
// printf("////////////////////// create noMaskLvEn  ///////////////////////////////////\n");
// TH2D* noMaskLvEn = new TH2D("noMaskLvEn","noMaskLvEn",40000,0,40000*MeV_per_ADC,1000,0,10);
// noMaskLvEn->GetXaxis()->SetTitle("Track Energy [MeV]");
// noMaskLvEn->GetXaxis()->CenterTitle();
// noMaskLvEn->GetYaxis()->SetTitle("Track Length [cm]");
// noMaskLvEn->GetYaxis()->CenterTitle();
// TH2D* noMaskLvEnFrags = (TH2D*)noMaskLvEn->Clone("noMaskLvEnFrags");
// noMaskLvEnFrags->SetTitle("noMaskLvEnFrags");
// TH2D* noMaskLvEnFragsUnlikely = (TH2D*)noMaskLvEn->Clone("noMaskLvEnFragsUnlikely");
// noMaskLvEnFragsUnlikely->SetTitle("noMaskLvEnFragsUnlikely");
// TH2D* noMaskLvEnAlphas = (TH2D*)noMaskLvEn->Clone("noMaskLvEnAlphas");
// noMaskLvEnAlphas->SetTitle("noMaskLvEnAlphas");
// TH2D* noMaskLvEnAlphas_long = (TH2D*)noMaskLvEn->Clone("noMaskLvEnAlphas_long");
// noMaskLvEnAlphas_long->SetTitle("noMaskLvEnAlphas_long");
// TH2D* noMaskLvEnAlphas_long_low = (TH2D*)noMaskLvEn->Clone("noMaskLvEnAlphas_long_low");
// noMaskLvEnAlphas_long_low->SetTitle("noMaskLvEnAlphas_long_low");
// TH2D* noMaskLvEnAlphas_long_high = (TH2D*)noMaskLvEn->Clone("noMaskLvEnAlphas_long_high");
// noMaskLvEnAlphas_long_high->SetTitle("noMaskLvEnAlphas_long_high");
// TH2D* noMaskLvEnAlphas_short_higher = (TH2D*)noMaskLvEn->Clone("noMaskLvEnAlphas_short_higher");
// noMaskLvEnAlphas_short_higher->SetTitle("noMaskLvEnAlphas_short_higher");
// TH2D* noMaskLvEnAlphas_alphaCut_short_low = (TH2D*)noMaskLvEn->Clone("noMaskLvEnAlphas_alphaCut_short_low");
// noMaskLvEnAlphas_alphaCut_short_low->SetTitle("noMaskLvEnAlphas_alphaCut_short_low");
// ////////////////////// create cftLvEn  ///////////////////////////////////
// printf("////////////////////// create cftLvEn  ///////////////////////////////////\n");
// TH2D* cftLvEn = new TH2D("cftLvEn","cftLvEn",40000,0,40000*MeV_per_ADC,1000,0,10);
// cftLvEn->GetXaxis()->SetTitle("Track Energy [MeV]");
// cftLvEn->GetXaxis()->CenterTitle();
// cftLvEn->GetYaxis()->SetTitle("Track Length [cm]");
// cftLvEn->GetYaxis()->CenterTitle();
// TH2D* cftLvEnFrags = (TH2D*)cftLvEn->Clone("cftLvEnFrags");
// cftLvEnFrags->SetTitle("cftLvEnFrags");
// TH2D* cftLvEnFragsUnlikely = (TH2D*)cftLvEn->Clone("cftLvEnFragsUnlikely");
// cftLvEnFragsUnlikely->SetTitle("cftLvEnFragsUnlikely");
// TH2D* cftLvEnAlphas = (TH2D*)cftLvEn->Clone("cftLvEnAlphas");
// cftLvEnAlphas->SetTitle("cftLvEnAlphas");
// TH2D* cftLvEnAlphas_long = (TH2D*)cftLvEn->Clone("cftLvEnAlphas_long");
// cftLvEnAlphas_long->SetTitle("cftLvEnAlphas_long");
// TH2D* cftLvEnAlphas_long_low = (TH2D*)cftLvEn->Clone("cftLvEnAlphas_long_low");
// cftLvEnAlphas_long_low->SetTitle("cftLvEnAlphas_long_low");
// TH2D* cftLvEnAlphas_long_high = (TH2D*)cftLvEn->Clone("cftLvEnAlphas_long_high");
// cftLvEnAlphas_long_high->SetTitle("cftLvEnAlphas_long_high");
// TH2D* cftLvEnAlphas_short_higher = (TH2D*)cftLvEn->Clone("cftLvEnAlphas_short_higher");
// cftLvEnAlphas_short_higher->SetTitle("cftLvEnAlphas_short_higher");
// TH2D* cftLvEnAlphas_alphaCut_short_low = (TH2D*)cftLvEn->Clone("cftLvEnAlphas_alphaCut_short_low");
// cftLvEnAlphas_alphaCut_short_low->SetTitle("cftLvEnAlphas_alphaCut_short_low");
// for (int adcBin = 0; adcBin < 40000; ++adcBin)
// {
// 	if (adcBin%10000==0)printf("adcBin:%d\n",adcBin);
// 	for (int lengthBin = 0; lengthBin < 1000; ++lengthBin)
// 	{
// 		noMaskLvEn->SetBinContent(adcBin,lengthBin,noMaskLvADC->GetBinContent(adcBin,lengthBin));
// 		noMaskLvEnFrags->SetBinContent(adcBin,lengthBin,noMaskLvADCFrags->GetBinContent(adcBin,lengthBin));
// 		noMaskLvEnFragsUnlikely->SetBinContent(adcBin,lengthBin,noMaskLvADCFragsUnlikely->GetBinContent(adcBin,lengthBin));
// 		noMaskLvEnAlphas->SetBinContent(adcBin,lengthBin,noMaskLvADCAlphas->GetBinContent(adcBin,lengthBin));
// 		noMaskLvEnAlphas_long->SetBinContent(adcBin,lengthBin,noMaskLvADCAlphas_long->GetBinContent(adcBin,lengthBin));
// 		noMaskLvEnAlphas_long_low->SetBinContent(adcBin,lengthBin,noMaskLvADCAlphas_long_low->GetBinContent(adcBin,lengthBin));
// 		noMaskLvEnAlphas_long_high->SetBinContent(adcBin,lengthBin,noMaskLvADCAlphas_long_high->GetBinContent(adcBin,lengthBin));
// 		noMaskLvEnAlphas_short_higher->SetBinContent(adcBin,lengthBin,noMaskLvADCAlphas_short_higher->GetBinContent(adcBin,lengthBin));
// 		noMaskLvEnAlphas_alphaCut_short_low->SetBinContent(adcBin,lengthBin,noMaskLvADCAlphas_alphaCut_short_low->GetBinContent(adcBin,lengthBin));
// 		cftLvEn->SetBinContent(adcBin,lengthBin,cftLvADC->GetBinContent(adcBin,lengthBin));
// 		cftLvEnFrags->SetBinContent(adcBin,lengthBin,cftLvADCFrags->GetBinContent(adcBin,lengthBin));
// 		cftLvEnFragsUnlikely->SetBinContent(adcBin,lengthBin,cftLvADCFragsUnlikely->GetBinContent(adcBin,lengthBin));
// 		cftLvEnAlphas->SetBinContent(adcBin,lengthBin,cftLvADCAlphas->GetBinContent(adcBin,lengthBin));
// 		cftLvEnAlphas_long->SetBinContent(adcBin,lengthBin,cftLvADCAlphas_long->GetBinContent(adcBin,lengthBin));
// 		cftLvEnAlphas_long_low->SetBinContent(adcBin,lengthBin,cftLvADCAlphas_long_low->GetBinContent(adcBin,lengthBin));
// 		cftLvEnAlphas_long_high->SetBinContent(adcBin,lengthBin,cftLvADCAlphas_long_high->GetBinContent(adcBin,lengthBin));
// 		cftLvEnAlphas_short_higher->SetBinContent(adcBin,lengthBin,cftLvADCAlphas_short_higher->GetBinContent(adcBin,lengthBin));
// 		cftLvEnAlphas_alphaCut_short_low->SetBinContent(adcBin,lengthBin,cftLvADCAlphas_alphaCut_short_low->GetBinContent(adcBin,lengthBin));
// 	}
// }
//
// ////////////////////// noMask fill color coded length-ADC containers ///////////////////////////////////
// printf("////////////////////// noMask fill color coded length-ADC containers ///////////////////////////////////\n");
// c1->SetGridy(1);
// c1->SetGridx(1);
// c1->SetLogz(0);
// c1->SetLogy(0);
// noMaskLvEnAlphas_long->GetXaxis()->SetRangeUser(0.4,15);
// // noMaskLvEnAlphas_long->Draw("colz");
// // alphaCut_long_energy->Draw("same f");
// // c1->SaveAs("noMaskLvEnAlphas_long.png");
// noMaskLvEnAlphas_long_low->GetXaxis()->SetRangeUser(0.4,15);
// // noMaskLvEnAlphas_long_low->Draw("colz");
// // alphaCut_long_low_energy->Draw("same f");
// // c1->SaveAs("noMaskLvEnAlphas_long_low.png");
// noMaskLvEnAlphas_long_high->GetXaxis()->SetRangeUser(0.4,15);
// // noMaskLvEnAlphas_long_high->Draw("colz");
// // long_high_energy->Draw("same f");
// // c1->SaveAs("noMaskLvEnAlphas_long_high.png");
// noMaskLvEnAlphas_short_higher->GetXaxis()->SetRangeUser(0.4,15);
// // noMaskLvEnAlphas_short_higher->Draw("colz");
// // alphaCut_short_higher_energy->Draw("same f");
// // c1->SaveAs("noMaskLvEnAlphas_short_higher.png");
// noMaskLvEnAlphas_alphaCut_short_low->GetXaxis()->SetRangeUser(0.4,15);
// // noMaskLvEnAlphas_alphaCut_short_low->Draw("colz");
// // alphaCut_short_low_energy->Draw("same f");
// // c1->SaveAs("noMaskLvEnAlphas_alphaCut_short_low.png");
// noMaskLvEnAlphas->GetXaxis()->SetRangeUser(0.4,15);
// // noMaskLvEnAlphas->Draw("colz");
// // alphaCut_above_zCut_energy->Draw("same f");
// alphaCut_above_zCut_energy->Draw("same");
// // c1->SaveAs("noMaskLvEnAlphas.png");
// noMaskLvEnFrags->GetXaxis()->SetRangeUser(0.4,15);
// // noMaskLvEnFrags->Draw("colz");
// // fragCut_energy->Draw("same f");
// // c1->SaveAs("noMaskLvEnFrags.png");
// noMaskLvEnFragsUnlikely->GetXaxis()->SetRangeUser(0.4,15);
// // noMaskLvEnFragsUnlikely->Draw("colz");
// // fragCut_unlikely_energy->Draw("same f");
// // c1->SaveAs("noMaskLvEnFragsUnlikely.png");
// ////////////////////// cft fill color coded length-ADC containers ///////////////////////////////////
// printf("////////////////////// cft fill color coded length-ADC containers ///////////////////////////////////\n");
// cftLvEnAlphas_long->GetXaxis()->SetRangeUser(0.4,15);
// // cftLvEnAlphas_long->Draw("colz");
// // alphaCut_long_energy->Draw("same f");
// // c1->SaveAs("cftLvEnAlphas_long.png");
// cftLvEnAlphas_long_low->GetXaxis()->SetRangeUser(0.4,15);
// // cftLvEnAlphas_long_low->Draw("colz");
// // alphaCut_long_low_energy->Draw("same f");
// // c1->SaveAs("cftLvEnAlphas_long_low.png");
// cftLvEnAlphas_long_high->GetXaxis()->SetRangeUser(0.4,15);
// // cftLvEnAlphas_long_high->Draw("colz");
// // long_high_energy->Draw("same f");
// // c1->SaveAs("cftLvEnAlphas_long_high.png");
// cftLvEnAlphas_short_higher->GetXaxis()->SetRangeUser(0.4,15);
// // cftLvEnAlphas_short_higher->Draw("colz");
// // alphaCut_short_higher_energy->Draw("same f");
// // c1->SaveAs("cftLvEnAlphas_short_higher.png");
// cftLvEnAlphas_alphaCut_short_low->GetXaxis()->SetRangeUser(0.4,15);
// // cftLvEnAlphas_alphaCut_short_low->Draw("colz");
// // alphaCut_short_low_energy->Draw("same f");
// // c1->SaveAs("cftLvEnAlphas_alphaCut_short_low.png");
// cftLvEnAlphas->GetXaxis()->SetRangeUser(0.4,15);
// // cftLvEnAlphas->Draw("colz");
// // alphaCut_above_zCut_energy->Draw("same f");
// alphaCut_above_zCut_energy->Draw("same");
// // c1->SaveAs("cftLvEnAlphas.png");
// cftLvEnFrags->GetXaxis()->SetRangeUser(0.4,15);
// // cftLvEnFrags->Draw("colz");
// // fragCut_energy->Draw("same f");
// // c1->SaveAs("cftLvEnFrags.png");
// cftLvEnFragsUnlikely->GetXaxis()->SetRangeUser(0.4,15);
// // cftLvEnFragsUnlikely->Draw("colz");
// // fragCut_unlikely_energy->Draw("same f");
// // c1->SaveAs("cftLvEnFragsUnlikely.png");
//
// ////////////////////// noMask create energy projection of color coded length-energy containers ///////////////
// printf("////////////////////// noMask create energy projection of color coded length-energy containers ///////////////\n");
// TH1D* noMaskADC = noMaskLvADC->ProjectionX("noMaskADC",0,40000);
// TH1D* noMaskFragsADC = noMaskLvADCFrags->ProjectionX("noMaskFragsADC",0,40000);
// TH1D* noMaskFragsUnlikeyADC = noMaskLvADCFrags->ProjectionX("noMaskFragsUnlikeyADC",0,40000);
// TH1D* noMaskAlphasADC = noMaskLvADCAlphas->ProjectionX("noMaskAlphasADC",0,40000);
// TH1D* noMaskAlphasADC_long = noMaskLvADCAlphas_long->ProjectionX("noMaskAlphasADC_long",0,40000);
// TH1D* noMaskAlphasADC_long_low = noMaskLvADCAlphas_long_low->ProjectionX("noMaskAlphasADC_long_low",0,40000);
// TH1D* noMaskAlphasADC_long_high = noMaskLvADCAlphas_long_high->ProjectionX("noMaskAlphasADC_long_high",0,40000);
// TH1D* noMaskAlphasADC_short_higher = noMaskLvADCAlphas_short_higher->ProjectionX("noMaskAlphasADC_short_higher",0,40000);
// TH1D* noMaskAlphasADC_alphaCut_short_low = noMaskLvADCAlphas_alphaCut_short_low->ProjectionX("noMaskAlphasADC_alphaCut_short_low",0,40000);
// c1->SetLogy(0);
// TH1D* noMaskEn = new TH1D("noMaskEn","noMaskEn",40000,0,40000*MeV_per_ADC);
// noMaskLvEn->GetXaxis()->SetRangeUser(0.4,160);
// noMaskEn = noMaskLvEn->ProjectionX("noMaskEn");
// noMaskEn->SetTitle("noMaskLvEn energy projection");
// noMaskEn->GetXaxis()->SetTitle("Track Energy [MeV]");
// noMaskEn->Draw();
// // c1->SaveAs("noMaskEn.png");
// TH1D* noMaskFragsEn = new TH1D("noMaskFragsEn","noMaskFragsEn",40000,0,40000*MeV_per_ADC);
// noMaskLvEnFrags->GetXaxis()->SetRangeUser(0.4,160);
// noMaskFragsEn = noMaskLvEnFrags->ProjectionX("noMaskFragsEn");
// noMaskFragsEn->SetTitle("noMaskFragsEn");
// noMaskFragsEn->SetLineColor(kViolet);
// noMaskFragsEn->SetLineWidth((Width_t)0.01);
// noMaskFragsEn->SetFillColorAlpha(kViolet,0.9);
// noMaskFragsEn->GetXaxis()->SetTitle("Track Energy [MeV]");
// noMaskFragsEn->Draw();
// // c1->SaveAs("noMaskFragsEn.png");
// TH1D* noMaskFragsUnlikelyEn = new TH1D("noMaskFragsUnlikelyEn","noMaskFragsUnlikelyEn",40000,0,40000*MeV_per_ADC);
// noMaskLvEnFrags->GetXaxis()->SetRangeUser(0.4,160);
// noMaskFragsUnlikelyEn = noMaskLvEnFragsUnlikely->ProjectionX("noMaskFragsUnlikelyEn");
// noMaskFragsUnlikelyEn->SetTitle("noMaskFragsUnlikelyEn");
// noMaskFragsUnlikelyEn->SetLineColor(kViolet-9);
// noMaskFragsUnlikelyEn->SetLineWidth((Width_t)0.01);
// noMaskFragsUnlikelyEn->SetFillColorAlpha(kViolet-9,0.9);
// noMaskFragsUnlikelyEn->GetXaxis()->SetTitle("Track Energy [MeV]");
// noMaskFragsUnlikelyEn->Draw();
// // c1->SaveAs("noMaskFragsUnlikelyEn.png");
// TH1D* noMaskAlphasEn = new TH1D("noMaskAlphasEn","noMaskAlphasEn",40000,0,40000*MeV_per_ADC);
// noMaskLvEnAlphas->GetXaxis()->SetRangeUser(0.4,160);
// noMaskAlphasEn = noMaskLvEnAlphas->ProjectionX("noMaskAlphasEn");
// noMaskAlphasEn->SetTitle("noMaskAlphasEn");
// noMaskAlphasEn->SetLineColor(kSpring);
// noMaskAlphasEn->SetLineWidth((Width_t)0.01);
// noMaskAlphasEn->SetFillColorAlpha(kSpring,0.9);
// noMaskAlphasEn->GetXaxis()->SetTitle("Track Energy [MeV]");
// noMaskAlphasEn->Draw();
// // c1->SaveAs("noMaskAlphasEn.png");
// TH1D* noMaskAlphasEn_long = new TH1D("noMaskAlphasEn_long","noMaskAlphasEn_long",40000,0,40000*MeV_per_ADC);
// noMaskLvEnAlphas_long->GetXaxis()->SetRangeUser(0.4,160);
// noMaskAlphasEn_long = noMaskLvEnAlphas_long->ProjectionX("noMaskAlphasEn_long");
// noMaskAlphasEn_long->SetTitle("noMaskAlphasEn_long");
// noMaskAlphasEn_long->SetLineColor(kCyan);
// noMaskAlphasEn_long->SetLineWidth((Width_t)0.01);
// noMaskAlphasEn_long->SetFillColorAlpha(kCyan,0.9);
// noMaskAlphasEn_long->GetXaxis()->SetTitle("Track Energy [MeV]");
// noMaskAlphasEn_long->Draw();
// // c1->SaveAs("noMaskAlphasEn_long.png");
// TH1D* noMaskAlphasEn_long_low = new TH1D("noMaskAlphasEn_long_low","noMaskAlphasEn_long_low",40000,0,40000*MeV_per_ADC);
// noMaskLvEnAlphas_long_low->GetXaxis()->SetRangeUser(0.4,160);
// noMaskAlphasEn_long_low = noMaskLvEnAlphas_long_low->ProjectionX("noMaskAlphasEn_long_low");
// noMaskAlphasEn_long_low->SetTitle("noMaskAlphasEn_long_low");
// noMaskAlphasEn_long_low->SetLineColor(kYellow);
// noMaskAlphasEn_long_low->SetLineWidth((Width_t)0.01);
// noMaskAlphasEn_long_low->SetFillColorAlpha(kYellow,0.9);
// noMaskAlphasEn_long_low->GetXaxis()->SetTitle("Track Energy [MeV]");
// noMaskAlphasEn_long_low->Draw();
// // c1->SaveAs("noMaskAlphasEn_long_low.png");
// TH1D* noMaskAlphasEn_long_high = new TH1D("noMaskAlphasEn_long_high","noMaskAlphasEn_long_high",40000,0,40000*MeV_per_ADC);
// noMaskLvEnAlphas_long_high->GetXaxis()->SetRangeUser(0.4,160);
// noMaskAlphasEn_long_high = noMaskLvEnAlphas_long_high->ProjectionX("noMaskAlphasEn_long_high");
// noMaskAlphasEn_long_high->SetTitle("noMaskAlphasEn_long_high");
// noMaskAlphasEn_long_high->SetLineColor(kBlue);
// noMaskAlphasEn_long_high->SetLineWidth((Width_t)0.01);
// noMaskAlphasEn_long_high->SetFillColorAlpha(kBlue,0.9);
// noMaskAlphasEn_long_high->GetXaxis()->SetTitle("Track Energy [MeV]");
// noMaskAlphasEn_long_high->Draw();
// // c1->SaveAs("noMaskAlphasEn_long_high.png");
// TH1D* noMaskAlphasEn_short_higher = new TH1D("noMaskAlphasEn_short_higher","noMaskAlphasEn_short_higher",40000,0,40000*MeV_per_ADC);
// noMaskLvEnAlphas_short_higher->GetXaxis()->SetRangeUser(0.4,160);
// noMaskAlphasEn_short_higher = noMaskLvEnAlphas_short_higher->ProjectionX("noMaskAlphasEn_short_higher");
// noMaskAlphasEn_short_higher->SetTitle("noMaskAlphasEn_short_higher");
// noMaskAlphasEn_short_higher->SetLineColor(kOrange+7);
// noMaskAlphasEn_short_higher->SetLineWidth((Width_t)0.01);
// noMaskAlphasEn_short_higher->SetFillColorAlpha(kOrange+7,0.9);
// noMaskAlphasEn_short_higher->GetXaxis()->SetTitle("Track Energy [MeV]");
// noMaskAlphasEn_short_higher->Draw();
// // c1->SaveAs("noMaskAlphasEn_short_higher.png");
// TH1D* noMaskAlphasEn_alphaCut_short_low = new TH1D("noMaskAlphasEn_alphaCut_short_low","noMaskAlphasEn_alphaCut_short_low",40000,0,40000*MeV_per_ADC);
// noMaskLvEnAlphas_alphaCut_short_low->GetXaxis()->SetRangeUser(0.4,160);
// noMaskAlphasEn_alphaCut_short_low = noMaskLvEnAlphas_alphaCut_short_low->ProjectionX("noMaskAlphasEn_alphaCut_short_low");
// noMaskAlphasEn_alphaCut_short_low->SetTitle("noMaskAlphasEn_alphaCut_short_low");
// noMaskAlphasEn_alphaCut_short_low->SetLineColor(kRed);
// noMaskAlphasEn_alphaCut_short_low->SetLineWidth((Width_t)0.1);
// noMaskAlphasEn_alphaCut_short_low->SetFillColorAlpha(kRed,0.9);
// noMaskAlphasEn_alphaCut_short_low->GetXaxis()->SetTitle("Track Energy [MeV]");
// noMaskAlphasEn_alphaCut_short_low->Draw();
// // c1->SaveAs("noMaskAlphasEn_alphaCut_short_low.png");
// ////////////////////// cft create ADC projection of color coded length-ADC containers ///////////////
// printf("////////////////////// cft create ADC projection of color coded length-ADC containers ///////////////\n");
// TH1D* cftADC = cftLvADC->ProjectionX("cftADC",0,40000);
// TH1D* cftFragsADC = cftLvADCFrags->ProjectionX("cftFragsADC",0,40000);
// TH1D* cftFragsUnlikeyADC = cftLvADCFrags->ProjectionX("cftFragsUnlikeyADC",0,40000);
// TH1D* cftAlphasADC = cftLvADCAlphas->ProjectionX("cftAlphasADC",0,40000);
// TH1D* cftAlphasADC_long = cftLvADCAlphas_long->ProjectionX("cftAlphasADC_long",0,40000);
// TH1D* cftAlphasADC_long_low = cftLvADCAlphas_long_low->ProjectionX("cftAlphasADC_long_low",0,40000);
// TH1D* cftAlphasADC_long_high = cftLvADCAlphas_long_high->ProjectionX("cftAlphasADC_long_high",0,40000);
// TH1D* cftAlphasADC_short_higher = cftLvADCAlphas_short_higher->ProjectionX("cftAlphasADC_short_higher",0,40000);
// TH1D* cftAlphasADC_alphaCut_short_low = cftLvADCAlphas_alphaCut_short_low->ProjectionX("cftAlphasADC_alphaCut_short_low",0,40000);
// c1->SetLogy(0);
// TH1D* cftEn = new TH1D("cftEn","cftEn",40000,0,40000*MeV_per_ADC);
// cftLvEn->GetXaxis()->SetRangeUser(0.4,160);
// cftEn = cftLvEn->ProjectionX("cftEn");
// cftEn->SetTitle("cftLvEn energy projection");
// cftEn->GetXaxis()->SetTitle("Track Energy [MeV]");
// cftEn->Draw();
// // c1->SaveAs("cftEn.png");
// TH1D* cftFragsEn = new TH1D("cftFragsEn","cftFragsEn",40000,0,40000*MeV_per_ADC);
// cftLvEnFrags->GetXaxis()->SetRangeUser(0.4,160);
// cftFragsEn = cftLvEnFrags->ProjectionX("cftFragsEn");
// cftFragsEn->SetTitle("cftFragsEn");
// cftFragsEn->SetLineColor(kViolet);
// cftFragsEn->SetLineWidth((Width_t)0.01);
// cftFragsEn->SetFillColorAlpha(kViolet,0.9);
// cftFragsEn->GetXaxis()->SetTitle("Track Energy [MeV]");
// cftFragsEn->Draw();
// // c1->SaveAs("cftFragsEn.png");
// TH1D* cftFragsUnlikelyEn = new TH1D("cftFragsUnlikelyEn","cftFragsUnlikelyEn",40000,0,40000*MeV_per_ADC);
// cftLvEnFrags->GetXaxis()->SetRangeUser(0.4,160);
// cftFragsUnlikelyEn = cftLvEnFragsUnlikely->ProjectionX("cftFragsUnlikelyEn");
// cftFragsUnlikelyEn->SetTitle("cftFragsUnlikelyEn");
// cftFragsUnlikelyEn->SetLineColor(kViolet-9);
// cftFragsUnlikelyEn->SetLineWidth((Width_t)0.01);
// cftFragsUnlikelyEn->SetFillColorAlpha(kViolet-9,0.9);
// cftFragsUnlikelyEn->GetXaxis()->SetTitle("Track Energy [MeV]");
// cftFragsUnlikelyEn->Draw();
// // c1->SaveAs("cftFragsUnlikelyEn.png");
// TH1D* cftAlphasEn = new TH1D("cftAlphasEn","cftAlphasEn",40000,0,40000*MeV_per_ADC);
// cftLvEnAlphas->GetXaxis()->SetRangeUser(0.4,160);
// cftAlphasEn = cftLvEnAlphas->ProjectionX("cftAlphasEn");
// cftAlphasEn->SetTitle("cftAlphasEn");
// cftAlphasEn->SetLineColor(kSpring);
// cftAlphasEn->SetLineWidth((Width_t)0.01);
// cftAlphasEn->SetFillColorAlpha(kSpring,0.9);
// cftAlphasEn->GetXaxis()->SetTitle("Track Energy [MeV]");
// cftAlphasEn->Draw();
// // c1->SaveAs("cftAlphasEn.png");
// TH1D* cftAlphasEn_long = new TH1D("cftAlphasEn_long","cftAlphasEn_long",40000,0,40000*MeV_per_ADC);
// cftLvEnAlphas_long->GetXaxis()->SetRangeUser(0.4,160);
// cftAlphasEn_long = cftLvEnAlphas_long->ProjectionX("cftAlphasEn_long");
// cftAlphasEn_long->SetTitle("cftAlphasEn_long");
// cftAlphasEn_long->SetLineColor(kCyan);
// cftAlphasEn_long->SetLineWidth((Width_t)0.01);
// cftAlphasEn_long->SetFillColorAlpha(kCyan,0.9);
// cftAlphasEn_long->GetXaxis()->SetTitle("Track Energy [MeV]");
// cftAlphasEn_long->Draw();
// // c1->SaveAs("cftAlphasEn_long.png");
// TH1D* cftAlphasEn_long_low = new TH1D("cftAlphasEn_long_low","cftAlphasEn_long_low",40000,0,40000*MeV_per_ADC);
// cftLvEnAlphas_long_low->GetXaxis()->SetRangeUser(0.4,160);
// cftAlphasEn_long_low = cftLvEnAlphas_long_low->ProjectionX("cftAlphasEn_long_low");
// cftAlphasEn_long_low->SetTitle("cftAlphasEn_long_low");
// cftAlphasEn_long_low->SetLineColor(kYellow);
// cftAlphasEn_long_low->SetLineWidth((Width_t)0.01);
// cftAlphasEn_long_low->SetFillColorAlpha(kYellow,0.9);
// cftAlphasEn_long_low->GetXaxis()->SetTitle("Track Energy [MeV]");
// cftAlphasEn_long_low->Draw();
// // c1->SaveAs("cftAlphasEn_long_low.png");
// TH1D* cftAlphasEn_long_high = new TH1D("cftAlphasEn_long_high","cftAlphasEn_long_high",40000,0,40000*MeV_per_ADC);
// cftLvEnAlphas_long_high->GetXaxis()->SetRangeUser(0.4,160);
// cftAlphasEn_long_high = cftLvEnAlphas_long_high->ProjectionX("cftAlphasEn_long_high");
// cftAlphasEn_long_high->SetTitle("cftAlphasEn_long_high");
// cftAlphasEn_long_high->SetLineColor(kBlue);
// cftAlphasEn_long_high->SetLineWidth((Width_t)0.01);
// cftAlphasEn_long_high->SetFillColorAlpha(kBlue,0.9);
// cftAlphasEn_long_high->GetXaxis()->SetTitle("Track Energy [MeV]");
// cftAlphasEn_long_high->Draw();
// // c1->SaveAs("cftAlphasEn_long_high.png");
// TH1D* cftAlphasEn_short_higher = new TH1D("cftAlphasEn_short_higher","cftAlphasEn_short_higher",40000,0,40000*MeV_per_ADC);
// cftLvEnAlphas_short_higher->GetXaxis()->SetRangeUser(0.4,160);
// cftAlphasEn_short_higher = cftLvEnAlphas_short_higher->ProjectionX("cftAlphasEn_short_higher");
// cftAlphasEn_short_higher->SetTitle("cftAlphasEn_short_higher");
// cftAlphasEn_short_higher->SetLineColor(kOrange+7);
// cftAlphasEn_short_higher->SetLineWidth((Width_t)0.01);
// cftAlphasEn_short_higher->SetFillColorAlpha(kOrange+7,0.9);
// cftAlphasEn_short_higher->GetXaxis()->SetTitle("Track Energy [MeV]");
// cftAlphasEn_short_higher->Draw();
// // c1->SaveAs("cftAlphasEn_short_higher.png");
// TH1D* cftAlphasEn_alphaCut_short_low = new TH1D("cftAlphasEn_alphaCut_short_low","cftAlphasEn_alphaCut_short_low",40000,0,40000*MeV_per_ADC);
// cftLvEnAlphas_alphaCut_short_low->GetXaxis()->SetRangeUser(0.4,160);
// cftAlphasEn_alphaCut_short_low = cftLvEnAlphas_alphaCut_short_low->ProjectionX("cftAlphasEn_alphaCut_short_low");
// cftAlphasEn_alphaCut_short_low->SetTitle("cftAlphasEn_alphaCut_short_low");
// cftAlphasEn_alphaCut_short_low->SetLineColor(kRed);
// cftAlphasEn_alphaCut_short_low->SetLineWidth((Width_t)0.1);
// cftAlphasEn_alphaCut_short_low->SetFillColorAlpha(kRed,0.9);
// cftAlphasEn_alphaCut_short_low->GetXaxis()->SetTitle("Track Energy [MeV]");
// cftAlphasEn_alphaCut_short_low->Draw();
// // c1->SaveAs("cftAlphasEn_alphaCut_short_low.png");
//
// ////////////////////// fill length-energy & plots color cuts ///////////////////////////////////
// printf("////////////////////// noMask fill length-energy & plots color cuts ///////////////////////////////////\n");
// c1->cd();
// noMaskEn->GetXaxis()->SetRangeUser(0.4,160);
// c1->SetLogx(1);c1->SetLogy(1);
// noMaskEn->SetMinimum(0.5);
// noMaskEn->Draw();
// c1->SaveAs("noMaskEn.fullEn.logx.png");
// noMaskEn->GetXaxis()->SetRangeUser(0.4,15);
// c1->SetLogx(0);c1->SetLogy(1);
// noMaskEn->Draw();
// c1->SaveAs("noMaskEn.lowEn.png");
// noMaskLvEn->GetXaxis()->SetRangeUser(0.4,160);
// c1->SetLogx(1);c1->SetLogy(0);
// noMaskLvEn->Draw("colz");
// c1->SaveAs("noMaskLvEn.fullEn.logx.png");
// alphaCut_long_energy->Draw("same f");
// alphaCut_long_low_energy->Draw("same f");
// long_high_energy->Draw("same f");
// alphaCut_short_higher_energy->Draw("same f");
// alphaCut_short_low_energy->Draw("same f");
// fragCut_energy->Draw("same f");
// fragCut_unlikely_energy->Draw("same f");
// alphaCut_above_zCut_energy->Draw("same f");
// // alphaCut_above_zCut_energy->Draw("same");
// c1->SaveAs("noMaskLvEn.cuts.fullEn.logx.png");
// noMaskLvEn->GetXaxis()->SetRangeUser(0.4,15);
// c1->SetLogx(0);c1->SetLogy(0);
// noMaskLvEn->Draw("colz");
// c1->SaveAs("noMaskLvEn.lowEn.png");
// alphaCut_long_energy->Draw("same f");
// alphaCut_long_low_energy->Draw("same f");
// long_high_energy->Draw("same f");
// alphaCut_short_higher_energy->Draw("same f");
// alphaCut_short_low_energy->Draw("same f");
// fragCut_energy->Draw("same f");
// fragCut_unlikely_energy->Draw("same f");
// alphaCut_above_zCut_energy->Draw("same f");
// // alphaCut_above_zCut_energy->Draw("same");
// c1->SaveAs("noMaskLvEn.cuts.lowEn.png");
// printf("////////////////////// cft fill length-energy & plots color cuts ///////////////////////////////////\n");
// cftEn->GetXaxis()->SetRangeUser(0.4,160);
// c1->SetLogx(1);c1->SetLogy(1);
// cftEn->SetMinimum(0.5);
// cftEn->Draw();
// c1->SaveAs("cftEn.fullEn.logx.png");
// cftEn->GetXaxis()->SetRangeUser(0.4,15);
// c1->SetLogx(0);c1->SetLogy(1);
// cftEn->Draw();
// c1->SaveAs("cftEn.lowEn.png");
// cftLvEn->GetXaxis()->SetRangeUser(0.4,160);
// c1->SetLogx(1);c1->SetLogy(0);
// cftLvEn->Draw("colz");
// c1->SaveAs("cftLvEn.fullEn.logx.png");
// alphaCut_long_energy->Draw("same f");
// alphaCut_long_low_energy->Draw("same f");
// long_high_energy->Draw("same f");
// alphaCut_short_higher_energy->Draw("same f");
// alphaCut_short_low_energy->Draw("same f");
// fragCut_energy->Draw("same f");
// fragCut_unlikely_energy->Draw("same f");
// alphaCut_above_zCut_energy->Draw("same f");
// // alphaCut_above_zCut_energy->Draw("same");
// c1->SaveAs("cftLvEn.cuts.fullEn.logx.png");
// cftLvEn->GetXaxis()->SetRangeUser(0.4,15);
// c1->SetLogx(0);c1->SetLogy(0);
// cftLvEn->Draw("colz");
// c1->SaveAs("cftLvEn.lowEn.png");
// alphaCut_long_energy->Draw("same f");
// alphaCut_long_low_energy->Draw("same f");
// long_high_energy->Draw("same f");
// alphaCut_short_higher_energy->Draw("same f");
// alphaCut_short_low_energy->Draw("same f");
// fragCut_energy->Draw("same f");
// fragCut_unlikely_energy->Draw("same f");
// alphaCut_above_zCut_energy->Draw("same f");
// // alphaCut_above_zCut_energy->Draw("same");
// c1->SaveAs("cftLvEn.cuts.lowEn.png");
//
// //////////////  count frags ////////////////
// printf("\n//////////////  count frags ////////////////\n\n");
// int minNormEnergy=12;
// double fragNormalization = noMaskFragsADC->Integral(minNormEnergy*ADC_per_MeV,40000)/(double)cftFragsADC->Integral(minNormEnergy*ADC_per_MeV,40000);
// cftEn->Scale(fragNormalization);
// cftAlphasEn->Scale(fragNormalization);
// cftFragsEn->Scale(fragNormalization);
// TH1D* cftEfficiency = (TH1D*)cftFragsEn->Clone("cftEfficiency");
// cftEfficiency->SetLineColor(kMagenta);
// cftEfficiency->SetLineWidth(1);
// cftEfficiency->SetFillColorAlpha(kMagenta,0);
// cftEfficiency->SetTitle("cftEfficiency = cft / noMask");
// cftEfficiency->Divide(noMaskFragsEn);
// int noMaskIntegral=noMaskADC->Integral();
// printf("noMaskIntegral: %d\n",noMaskIntegral);
// int noMaskFragIntegral=noMaskFragsADC->Integral();
// printf("noMaskFragIntegral: %d\n",noMaskFragIntegral);
// int noMaskAlphaIntegral=noMaskAlphasADC->Integral();
// printf("noMaskAlphaIntegral: %d\n",noMaskAlphaIntegral);
// int noMaskNotFragIntegral=noMaskIntegral-noMaskFragIntegral;
// printf("noMaskNotFragIntegral: %d\n",noMaskNotFragIntegral);
// double noMaskFragsEn_percent_integral=noMaskFragsEn->Integral()/(double)noMaskIntegral*100;
// printf("noMaskFragsEn_percent_integral: %.4f\n",noMaskFragsEn_percent_integral);
// double noMaskFragsUnlikelyEn_percent_integral=noMaskFragsUnlikelyEn->Integral()/(double)noMaskIntegral*100;
// printf("noMaskFragsUnlikelyEn_percent_integral: %.4f\n",noMaskFragsUnlikelyEn_percent_integral);
// double noMaskAlphasEn_percent_integral=noMaskAlphasEn->Integral()/(double)noMaskIntegral*100;
// printf("noMaskAlphasEn_percent_integral: %.4f\n",noMaskAlphasEn_percent_integral);
// double noMaskAlphasEn_long_percent_integral=noMaskAlphasEn_long->Integral()/(double)noMaskIntegral*100;
// printf("noMaskAlphasEn_long_percent_integral: %.4f\n",noMaskAlphasEn_long_percent_integral);
// double noMaskAlphasEn_long_low_percent_integral=noMaskAlphasEn_long_low->Integral()/(double)noMaskIntegral*100;
// printf("noMaskAlphasEn_long_low_percent_integral: %.4f\n",noMaskAlphasEn_long_low_percent_integral);
// double noMaskAlphasEn_long_high_percent_integral=noMaskAlphasEn_long_high->Integral()/(double)noMaskIntegral*100;
// printf("noMaskAlphasEn_long_high_percent_integral: %.4f\n",noMaskAlphasEn_long_high_percent_integral);
// double noMaskAlphasEn_short_higher_percent_integral=noMaskAlphasEn_short_higher->Integral()/(double)noMaskIntegral*100;
// printf("noMaskAlphasEn_short_higher_percent_integral: %.4f\n",noMaskAlphasEn_short_higher_percent_integral);
// double noMaskAlphasEn_alphaCut_short_low_percent_integral=noMaskAlphasEn_alphaCut_short_low->Integral()/(double)noMaskIntegral*100;
// printf("noMaskAlphasEn_alphaCut_short_low_percent_integral: %.4f\n",noMaskAlphasEn_alphaCut_short_low_percent_integral);
// int cftIntegral=cftADC->Integral();
// printf("cftIntegral: %d\n",cftIntegral);
// int cftFragIntegral=cftFragsADC->Integral();
// printf("cftFragIntegral: %d\n",cftFragIntegral);
// int cftAlphaIntegral=cftAlphasADC->Integral();
// printf("cftAlphaIntegral: %d\n",cftAlphaIntegral);
// int cftNotFragIntegral=cftIntegral-cftFragIntegral;
// printf("cftNotFragIntegral: %d\n",cftNotFragIntegral);
// double cftFragsEn_percent_integral=cftFragsADC->Integral()/(double)cftIntegral*100;
// printf("cftFragsEn_percent_integral: %.4f\n",cftFragsEn_percent_integral);
// double cftFragsUnlikelyEn_percent_integral=cftFragsUnlikelyEn->Integral()/(double)cftIntegral*100;
// printf("cftFragsUnlikelyEn_percent_integral: %.4f\n",cftFragsUnlikelyEn_percent_integral);
// double cftAlphasEn_percent_integral=cftAlphasADC->Integral()/(double)cftIntegral*100;
// printf("cftAlphasEn_percent_integral: %.4f\n",cftAlphasEn_percent_integral);
// double cftAlphasEn_long_percent_integral=cftAlphasADC_long->Integral()/(double)cftIntegral*100;
// printf("cftAlphasEn_long_percent_integral: %.4f\n",cftAlphasEn_long_percent_integral);
// double cftAlphasEn_long_low_percent_integral=cftAlphasADC_long_low->Integral()/(double)cftIntegral*100;
// printf("cftAlphasEn_long_low_percent_integral: %.4f\n",cftAlphasEn_long_low_percent_integral);
// double cftAlphasEn_long_high_percent_integral=cftAlphasADC_long_high->Integral()/(double)cftIntegral*100;
// printf("cftAlphasEn_long_high_percent_integral: %.4f\n",cftAlphasEn_long_high_percent_integral);
// double cftAlphasEn_short_higher_percent_integral=cftAlphasADC_short_higher->Integral()/(double)cftIntegral*100;
// printf("cftAlphasEn_short_higher_percent_integral: %.4f\n",cftAlphasEn_short_higher_percent_integral);
// double cftAlphasEn_alphaCut_short_low_percent_integral=cftAlphasADC_alphaCut_short_low->Integral()/(double)cftIntegral*100;
// printf("cftAlphasEn_alphaCut_short_low_percent_integral: %.4f\n",cftAlphasEn_alphaCut_short_low_percent_integral);
// printf("cftFragIntegral: %d\n",cftFragIntegral);
// printf("cftAlphaIntegral: %d\n",cftAlphaIntegral);
// printf("noMaskFragIntegral: %d\n",noMaskFragIntegral);
// printf("noMaskAlphaIntegral: %d\n",noMaskAlphaIntegral);
// printf("fragNormalization: %f\n",fragNormalization);
// double noMask_aSF_ratio=2*noMaskAlphaIntegral/(double)noMaskFragIntegral*isoTopicCalib;
// double cft_aSF_ratio=2*cftAlphaIntegral/(double)cftFragIntegral*isoTopicCalib;
// char noMaskFragChar[234],cftFragChar[234],
// 	noMaskAlphaChar[234],cftAlphaChar[234],
// 	noMask_aSF_ratioChar[234],cft_aSF_ratioChar[234],
// 	nFragRejectedChar[234],nAlphasRejectedChar[234],
// 	noMaskFragsEn_percent_char[234],
// 	noMaskFragsUnlikelyEn_percent_char[234],
// 	noMaskAlphasEn_percent_char[234],
// 	noMaskAlphasEn_long_percent_char[234],
// 	noMaskAlphasEn_long_low_percent_char[234],
// 	noMaskAlphasEn_long_high_percent_char[234],
// 	noMaskAlphasEn_short_higher_percent_char[234],
// 	noMaskAlphasEn_alphaCut_short_low_percent_char[234],
// 	cftFragsEn_percent_char[234],
// 	cftFragsUnlikelyEn_percent_char[234],
// 	cftAlphasEn_percent_char[234],
// 	cftAlphasEn_long_percent_char[234],
// 	cftAlphasEn_long_low_percent_char[234],
// 	cftAlphasEn_long_high_percent_char[234],
// 	cftAlphasEn_short_higher_percent_char[234],
// 	cftAlphasEn_alphaCut_short_low_percent_char[234];
// sprintf(nFragRejectedChar,"nFragRejected = %.3f%%",100*TMath::Abs(1-cftFragsEn->Integral()/(double)noMaskFragsEn->Integral()));
// sprintf(nAlphasRejectedChar,"nAlphasRejected = %.3f%%",100*TMath::Abs(1-cftAlphasEn->Integral()/(double)noMaskAlphasEn->Integral()));
// sprintf(cft_aSF_ratioChar,"cft_aSF_ratio = %.3f",cft_aSF_ratio);
// sprintf(noMask_aSF_ratioChar,"noMask_aSF_ratio = %.3f",noMask_aSF_ratio);
// sprintf(cftAlphaChar,"cft alphas = %d",cftAlphaIntegral);
// sprintf(noMaskAlphaChar,"noMask alphas = %d",noMaskAlphaIntegral);
// sprintf(cftFragChar,"cft frags = %d",cftFragIntegral);
// sprintf(noMaskFragChar,"noMask frags = %d",noMaskFragIntegral);
// sprintf(noMaskFragsEn_percent_char,"%.3f%%",noMaskFragsEn_percent_integral);
// sprintf(noMaskFragsUnlikelyEn_percent_char,"%.3f%%",noMaskFragsUnlikelyEn_percent_integral);
// sprintf(noMaskAlphasEn_percent_char,"%.3f%%",noMaskAlphasEn_percent_integral);
// sprintf(noMaskAlphasEn_long_percent_char,"%.3f%%",noMaskAlphasEn_long_percent_integral);
// sprintf(noMaskAlphasEn_long_low_percent_char,"%.3f%%",noMaskAlphasEn_long_low_percent_integral);
// sprintf(noMaskAlphasEn_long_high_percent_char,"%.3f%%",noMaskAlphasEn_long_high_percent_integral);
// sprintf(noMaskAlphasEn_short_higher_percent_char,"%.3f%%",noMaskAlphasEn_short_higher_percent_integral);
// sprintf(noMaskAlphasEn_alphaCut_short_low_percent_char,"%.3f%%",noMaskAlphasEn_alphaCut_short_low_percent_integral);
// sprintf(cftFragsEn_percent_char,"%.3f%%",cftFragsEn_percent_integral);
// sprintf(cftFragsUnlikelyEn_percent_char,"%.3f%%",cftFragsUnlikelyEn_percent_integral);
// sprintf(cftAlphasEn_percent_char,"%.3f%%",cftAlphasEn_percent_integral);
// sprintf(cftAlphasEn_long_percent_char,"%.3f%%",cftAlphasEn_long_percent_integral);
// sprintf(cftAlphasEn_long_low_percent_char,"%.3f%%",cftAlphasEn_long_low_percent_integral);
// sprintf(cftAlphasEn_long_high_percent_char,"%.3f%%",cftAlphasEn_long_high_percent_integral);
// sprintf(cftAlphasEn_short_higher_percent_char,"%.3f%%",cftAlphasEn_short_higher_percent_integral);
// sprintf(cftAlphasEn_alphaCut_short_low_percent_char,"%.3f%%",cftAlphasEn_alphaCut_short_low_percent_integral);
// printf("nFragRejectedChar: %s\n",nFragRejectedChar);
// printf("nAlphasRejectedChar: %s\n",nAlphasRejectedChar);
// printf("cft_aSF_ratioChar: %s\n",cft_aSF_ratioChar);
// printf("noMask_aSF_ratioChar: %s\n",noMask_aSF_ratioChar);
// printf("cftAlphaChar: %s\n",cftAlphaChar);
// printf("noMaskAlphaChar: %s\n",noMaskAlphaChar);
// printf("cftFragChar: %s\n",cftFragChar);
// printf("noMaskFragChar: %s\n",noMaskFragChar);
// TText fragCountText;
// fragCountText.SetTextAlign(13);
// fragCountText.SetTextSize(0.025);
// fragCountText.SetTextFont(42);
//
// /////////////////////////////// noMask create colorcoded ADC projection stack ///////////////////////////////////
// printf("////////////////////// noMask create colorcoded ADC projection stack ///////////////////////////////////\n");
// double stack_leg_x_start;
// if (preamp==1) {stack_leg_x_start = 0;}
// if (preamp==2) {stack_leg_x_start=0.75;}
// double stack_leg_x_stop = stack_leg_x_start+0.15;
// TLegend* noMask_pidCuts_stack_legend = new TLegend(stack_leg_x_start,0.65,stack_leg_x_stop,0.89);
// noMask_pidCuts_stack_legend->SetTextFont(42);
// noMask_pidCuts_stack_legend->SetTextSize(0.03);
// noMask_pidCuts_stack_legend->AddEntry(noMaskAlphasEn,noMaskAlphasEn_percent_char,"f");
// noMask_pidCuts_stack_legend->AddEntry(noMaskFragsEn,noMaskFragsEn_percent_char,"f");
// noMask_pidCuts_stack_legend->AddEntry(noMaskFragsUnlikelyEn,noMaskFragsUnlikelyEn_percent_char,"f");
// noMask_pidCuts_stack_legend->AddEntry(noMaskAlphasEn_alphaCut_short_low,noMaskAlphasEn_alphaCut_short_low_percent_char,"f");
// noMask_pidCuts_stack_legend->AddEntry(noMaskAlphasEn_short_higher,noMaskAlphasEn_short_higher_percent_char,"f");
// noMask_pidCuts_stack_legend->AddEntry(noMaskAlphasEn_long,noMaskAlphasEn_long_percent_char,"f");
// noMask_pidCuts_stack_legend->AddEntry(noMaskAlphasEn_long_low,noMaskAlphasEn_long_low_percent_char,"f");
// noMask_pidCuts_stack_legend->AddEntry(noMaskAlphasEn_long_high,noMaskAlphasEn_long_high_percent_char,"f");
// THStack* noMask_pidCuts_En_Stack = new THStack("noMask_pidCuts_En_Stack","");
// noMask_pidCuts_En_Stack->Add(noMaskFragsEn);
// noMask_pidCuts_En_Stack->Add(noMaskFragsUnlikelyEn);
// noMask_pidCuts_En_Stack->Add(noMaskAlphasEn);
// noMask_pidCuts_En_Stack->Add(noMaskAlphasEn_long);
// noMask_pidCuts_En_Stack->Add(noMaskAlphasEn_long_low);
// noMask_pidCuts_En_Stack->Add(noMaskAlphasEn_long_high);
// noMask_pidCuts_En_Stack->Add(noMaskAlphasEn_short_higher);
// noMask_pidCuts_En_Stack->Add(noMaskAlphasEn_alphaCut_short_low);
// noMask_pidCuts_En_Stack->SetMinimum(0.5);
// noMask_pidCuts_En_Stack->Draw();
// c1->SetLogx(0);c1->SetLogy(1);
// noMask_pidCuts_En_Stack->GetXaxis()->SetTitle("Track Energy [MeV]");
// noMask_pidCuts_En_Stack->GetXaxis()->CenterTitle();
// noMask_pidCuts_En_Stack->GetXaxis()->SetRangeUser(0.4,15);
// noMask_pidCuts_En_Stack->SetTitle("noMask_pidCuts_En_Stack_logy");
// noMask_pidCuts_stack_legend->Draw();
//
// c1->SaveAs("noMask_pidCuts_En_Stack_logy_lowEn.png");
// c1->SetLogx(1);
// noMask_pidCuts_En_Stack->SetTitle("noMask_pidCuts_En_Stack_logxy");
// noMask_pidCuts_En_Stack->Draw();
// noMask_pidCuts_En_Stack->GetXaxis()->SetRangeUser(0.4,160);
// noMask_pidCuts_stack_legend->Draw();
// c1->Update();
// c1->SaveAs("noMask_pidCuts_En_Stack_logxy_fullEn.png");
// /////////////////////////////// cft create colorcoded ADC projection stack ///////////////////////////////////
// printf("////////////////////// cft create colorcoded ADC projection stack ///////////////////////////////////\n");
// TLegend* cft_pidCuts_stack_legend = new TLegend(stack_leg_x_start,0.65,stack_leg_x_stop,0.89);
// cft_pidCuts_stack_legend->SetTextFont(42);
// cft_pidCuts_stack_legend->SetTextSize(0.03);
// cft_pidCuts_stack_legend->AddEntry(cftAlphasEn,cftAlphasEn_percent_char,"f");
// cft_pidCuts_stack_legend->AddEntry(cftFragsEn,cftFragsEn_percent_char,"f");
// cft_pidCuts_stack_legend->AddEntry(cftFragsUnlikelyEn,cftFragsUnlikelyEn_percent_char,"f");
// cft_pidCuts_stack_legend->AddEntry(cftAlphasEn_alphaCut_short_low,cftAlphasEn_alphaCut_short_low_percent_char,"f");
// cft_pidCuts_stack_legend->AddEntry(cftAlphasEn_short_higher,cftAlphasEn_short_higher_percent_char,"f");
// cft_pidCuts_stack_legend->AddEntry(cftAlphasEn_long,cftAlphasEn_long_percent_char,"f");
// cft_pidCuts_stack_legend->AddEntry(cftAlphasEn_long_low,cftAlphasEn_long_low_percent_char,"f");
// cft_pidCuts_stack_legend->AddEntry(cftAlphasEn_long_high,cftAlphasEn_long_high_percent_char,"f");
// THStack* cft_pidCuts_En_Stack = new THStack("cft_pidCuts_En_Stack","");
// cft_pidCuts_En_Stack->Add(cftFragsEn);
// cft_pidCuts_En_Stack->Add(cftFragsUnlikelyEn);
// cft_pidCuts_En_Stack->Add(cftAlphasEn);
// cft_pidCuts_En_Stack->Add(cftAlphasEn_long);
// cft_pidCuts_En_Stack->Add(cftAlphasEn_long_low);
// cft_pidCuts_En_Stack->Add(cftAlphasEn_long_high);
// cft_pidCuts_En_Stack->Add(cftAlphasEn_short_higher);
// cft_pidCuts_En_Stack->Add(cftAlphasEn_alphaCut_short_low);
// cft_pidCuts_En_Stack->SetMinimum(0.5);
// cft_pidCuts_En_Stack->Draw();
// c1->SetLogx(0);c1->SetLogy(1);
// cft_pidCuts_En_Stack->GetXaxis()->SetTitle("Track Energy [MeV]");
// cft_pidCuts_En_Stack->GetXaxis()->CenterTitle();
// cft_pidCuts_En_Stack->GetXaxis()->SetRangeUser(0.4,15);
// cft_pidCuts_En_Stack->SetTitle("cft_pidCuts_En_Stack_logy");
// cft_pidCuts_stack_legend->Draw();
// c1->SaveAs("cft_pidCuts_En_Stack_logy_lowEn.png");
// c1->SetLogx(0);
// c1->SetLogx(1);
// cft_pidCuts_En_Stack->SetTitle("cft_pidCuts_En_Stack_logxy");
// cft_pidCuts_En_Stack->Draw();
// cft_pidCuts_En_Stack->GetXaxis()->SetRangeUser(0.4,160);
// cft_pidCuts_stack_legend->Draw();
// c1->Update();
// c1->SaveAs("cft_pidCuts_En_Stack_logxy_fullEn.png");
//
// //////////////////// cft vs noMask stacks comparison /////////////
// printf("\n//////////////////// noMask stacks comparison /////////////\n\n");
// TLegend* noMaskEnStack_legend = new TLegend(0.55,0.75,0.9,0.89);
// noMaskEnStack_legend->SetTextFont(42);
// noMaskEnStack_legend->SetTextSize(0.03);
// noMaskEnStack_legend->AddEntry((TObject*)0,noMask_aSF_ratioChar,"");
// noMaskEnStack_legend->AddEntry((TObject*)0,noMaskFragChar,"");
// noMaskEnStack_legend->AddEntry((TObject*)0,noMaskAlphaChar,"");
// THStack* noMaskEnStack = new THStack("noMaskEnStack","");
// c1->SetGridy(0);c1->SetGridx(0);
// noMaskFragsEn->SetFillColorAlpha(kViolet,0.9);
// noMaskFragsEn->SetLineColor(kViolet);
// noMaskAlphasEn->SetFillColorAlpha(kSpring,0.9);
// noMaskAlphasEn->SetLineColor(kSpring);
// noMaskEnStack->Add(noMaskFragsEn);
// noMaskEnStack->Add(noMaskAlphasEn);
// noMaskEnStack->Draw();
// c1->SetGridy(0);c1->SetGridx(1);
// c1->SetLogx(0);c1->SetLogy(1);
// noMaskEnStack->SetMinimum(0.5);
// noMaskEnStack->GetXaxis()->SetRangeUser(0.4,15);
// noMaskEnStack->SetTitle("noMaskLvEn_stack energy projection");
// noMaskEnStack->GetXaxis()->SetTitle("Track Energy [MeV]");
// noMaskEnStack->GetXaxis()->CenterTitle();
// c1->Update();
// sprintf(c1PlotName,"%s.preamp%d.noMaskEn.lowEn.logy.png",actinide,preamp);
// c1->SaveAs(c1PlotName,"recreate");
// noMaskEnStack->GetXaxis()->SetRangeUser(0.4,160);
// c1->SetLogx(1);c1->SetLogy(1);
// c1->Update();
// sprintf(c1PlotName,"%s.preamp%d.noMaskEn.fullEn.logxy.png",actinide,preamp);
// c1->SaveAs(c1PlotName,"recreate");
// printf("\n//////////////////// cft stacks comparison /////////////\n\n");
// THStack* cftEnStack = new THStack("cftEnStack","");
// c1->SetGridy(0);c1->SetGridx(0);
// cftFragsEn->SetFillColorAlpha(kViolet,0.9);
// cftFragsEn->SetLineColor(kViolet);
// cftAlphasEn->SetFillColorAlpha(kSpring,0.9);
// cftAlphasEn->SetLineColor(kSpring);
// cftEnStack->Add(cftFragsEn);
// cftEnStack->Add(cftAlphasEn);
// cftEnStack->Draw();
// c1->SetGridy(0);c1->SetGridx(1);
// c1->SetLogx(0);c1->SetLogy(1);
// cftEnStack->SetMinimum(0.5);
// cftEnStack->GetXaxis()->SetRangeUser(0.4,15);
// cftEnStack->SetTitle("cftLvEn_stack energy projection");
// cftEnStack->GetXaxis()->SetTitle("Track Energy [MeV]");
// cftEnStack->GetXaxis()->CenterTitle();
// c1->Update();
// sprintf(c1PlotName,"%s.preamp%d.cftEn.lowEn.logy.png",actinide,preamp);
// c1->SaveAs(c1PlotName,"recreate");
// cftEnStack->GetXaxis()->SetRangeUser(0.4,160);
// c1->SetLogx(1);c1->SetLogy(1);
// c1->Update();
// sprintf(c1PlotName,"%s.preamp%d.cftEn.fullEn.logxy.png",actinide,preamp);
// c1->SaveAs(c1PlotName,"recreate");
//
// ///////////////////////  length energy plots  ////////////////////
// printf("\n/////////////////////// noMask lenght VS Energy ////////////////////\n\n");
// fragCut_energy->SetFillColorAlpha(kViolet,0.2);
// alphaCut_above_zCut_energy->SetFillColorAlpha(kSpring,0.2);
// c1->SetLogx(0);c1->SetLogy(0);
// noMaskLvEn->GetXaxis()->SetRangeUser(0.4,15);
// noMaskLvEn->SetTitle("noMaskLvEn");
// noMaskLvEn->Draw("colz");
// fragCut_energy->Draw("same");
// fragCut_energy->Draw("same f");
// alphaCut_above_zCut_energy->Draw("same f");
// alphaCut_above_zCut_energy->Draw("same");
// c1->SetLogx(0);
// noMaskEnStack_legend->Draw();
// c1->SaveAs("noMaskCuts.asf.lowEn.png");
// c1->SetLogx(1);
// noMaskLvEn->GetXaxis()->SetRangeUser(0.4,160);
// fragCut_energy->Draw("same");
// fragCut_energy->Draw("same f");
// alphaCut_above_zCut_energy->Draw("same f");
// alphaCut_above_zCut_energy->Draw("same");
// c1->SaveAs("noMaskCuts.asf.fullEn.logxy.png");
// printf("\n///////////////////////  cft lenght VS Energy ////////////////////\n\n");
// fragCut_energy->SetFillColorAlpha(kViolet,0.2);
// alphaCut_above_zCut_energy->SetFillColorAlpha(kSpring,0.2);
// c1->SetLogx(0);c1->SetLogy(0);
// cftLvEn->GetXaxis()->SetRangeUser(0.4,15);
// cftLvEn->SetTitle("cftLvEn");
// cftLvEn->Draw("colz");
// fragCut_energy->Draw("same");
// fragCut_energy->Draw("same f");
// alphaCut_above_zCut_energy->Draw("same f");
// alphaCut_above_zCut_energy->Draw("same");
// c1->SetLogx(0);
// TLegend* cftEnStack_legend = new TLegend(0.55,0.75,0.9,0.89);
// cftEnStack_legend->SetTextFont(42);
// cftEnStack_legend->SetTextSize(0.03);
// cftEnStack_legend->AddEntry((TObject*)0,cftFragChar,"");
// cftEnStack_legend->AddEntry((TObject*)0,cftAlphaChar,"");
// cftEnStack_legend->AddEntry((TObject*)0,nAlphasRejectedChar,"");
// cftEnStack_legend->AddEntry((TObject*)0,nFragRejectedChar,"");
// cftEnStack_legend->Draw();
// c1->SaveAs("cftCuts.asf.lowEn.png");
// c1->SetLogx(1);
// cftLvEn->GetXaxis()->SetRangeUser(0.4,160);
// fragCut_energy->Draw("same");
// fragCut_energy->Draw("same f");
// alphaCut_above_zCut_energy->Draw("same f");
// alphaCut_above_zCut_energy->Draw("same");
// cftEnStack_legend->Draw();
// c1->SaveAs("cftCuts.asf.fullEn.logxy.png");
//
// /////////////////////// efficiency ////////////////////
// printf("\n/////////////////////// efficiency ////////////////////\n\n");
// noMaskFragsEn->SetLineColor(kRed);
// noMaskFragsEn->SetLineWidth(1);
// noMaskFragsEn->SetFillColorAlpha(kViolet,0);
// cftFragsEn->SetLineColor(kBlue);
// cftFragsEn->SetLineWidth(1);
// cftFragsEn->SetFillColorAlpha(kViolet,0);
// TLegend* legend1=new TLegend(0.4,0.75,0.9,0.89);
// legend1->SetTextFont(42);
// legend1->SetTextSize(0.03);
// legend1->AddEntry(cftFragsEn,"CFT");
// legend1->AddEntry(noMaskFragsEn,"noMask");
// // for plotting the scaled region
// TH1D* cftFragsEnScaleRegion = (TH1D*)cftFragsEn->Clone();
// for (int i = 0; i < minNormEnergy*ADC_per_MeV; ++i) cftFragsEnScaleRegion->SetBinContent(i,0);
// cftFragsEnScaleRegion->SetFillColorAlpha(kBlue,0.2);
// cftFragsEnScaleRegion->SetLineColor(kBlue);
// cftFragsEnScaleRegion->GetXaxis()->SetRangeUser(0.4,160);
// noMaskFragsEn->GetYaxis()->SetRangeUser(0.001,10*noMaskFragsEn->GetMaximum());
// noMaskFragsEn->GetXaxis()->SetRangeUser(0.4,160);
// cftFragsEn->GetYaxis()->SetRangeUser(0.001,10*noMaskFragsEn->GetMaximum());
// cftFragsEn->GetXaxis()->SetRangeUser(0.4,160);
// cftEfficiency->GetYaxis()->SetRangeUser(0.001,10*noMaskFragsEn->GetMaximum());legend1->AddEntry(cftEfficiency,"CFT/noMask");
// c1->SetLogx(1);c1->SetLogy(1);
// noMaskFragsEn->Draw();
// cftFragsEn->Draw("same");
// legend1->Draw("same");
// fragCountText.DrawTextNDC(0.7,0.78,nFragRejectedChar);
// fragCountText.DrawTextNDC(0.7,0.83,noMaskFragChar);
// fragCountText.DrawTextNDC(0.7,0.88,cftFragChar);
// cftFragsEnScaleRegion->Draw("same");
// cftEfficiency->Draw("same");
// sprintf(c1PlotName,"%s.preamp%d.bothFragsCut.fullEn.logxy.png",actinide,preamp);
// c1->SaveAs(c1PlotName,"recreate");
// c1->SetLogx(0);c1->SetLogy(1);
// sprintf(c1PlotName,"%s.preamp%d.bothFragsCut.fullEn.logy.png",actinide,preamp);
// c1->SaveAs(c1PlotName,"recreate");
// cftFragsEnScaleRegion->GetXaxis()->SetRangeUser(0.4,15);
// noMaskFragsEn->GetXaxis()->SetRangeUser(0.4,15);
// cftFragsEn->GetXaxis()->SetRangeUser(0.4,15);
// c1->Update();
// sprintf(c1PlotName,"%s.preamp%d.bothFragsCut.lowEn.logy.png",actinide,preamp);
// c1->SaveAs(c1PlotName,"recreate");
//
// noMaskFragsEn->SetLineColor(kViolet);
// noMaskFragsUnlikelyEn->SetLineColor(kViolet);
// noMaskAlphasEn->SetLineColor(kSpring);
// noMaskAlphasEn_long->SetLineColor(kCyan);
// noMaskAlphasEn_long_low->SetLineColor(kYellow);
// noMaskAlphasEn_long_high->SetLineColor(kBlue);
// noMaskAlphasEn_short_higher->SetLineColor(kOrange+7);
// noMaskAlphasEn_alphaCut_short_low->SetLineColor(kRed);
// cftFragsEn->SetLineColor(kViolet);
// cftFragsUnlikelyEn->SetLineColor(kViolet);
// cftAlphasEn->SetLineColor(kSpring);
// cftAlphasEn_long->SetLineColor(kCyan);
// cftAlphasEn_long_low->SetLineColor(kYellow);
// cftAlphasEn_long_high->SetLineColor(kBlue);
// cftAlphasEn_short_higher->SetLineColor(kOrange+7);
// cftAlphasEn_alphaCut_short_low->SetLineColor(kRed);
//
// ////////////////////// create polar histograms ///////////////////////////////////
// printf("////////////////////// create polar histograms ///////////////////////////////////\n");
// TH1D* noMaskCosTheta = new TH1D("noMaskCosTheta","noMaskCosTheta",500,-1,1);
// TH1D* noMaskCosThetaFrags = (TH1D*)noMaskCosTheta->Clone("noMaskCosThetaFrags");
// noMaskCosThetaFrags->SetLineColor(kViolet);
// noMaskCosThetaFrags->SetLineWidth((Width_t)0.01);
// noMaskCosThetaFrags->SetFillColorAlpha(kViolet,0.9);
// TH1D* noMaskCosThetaFragsUnlikely = (TH1D*)noMaskCosTheta->Clone("noMaskCosThetaFragsUnlikely");
// noMaskCosThetaFragsUnlikely->SetLineColor(kViolet-9);
// noMaskCosThetaFragsUnlikely->SetLineWidth((Width_t)0.01);
// noMaskCosThetaFragsUnlikely->SetFillColorAlpha(kViolet-9,0.9);
// TH1D* noMaskCosThetaAlphas = (TH1D*)noMaskCosTheta->Clone("noMaskCosThetaAlphas");
// noMaskCosThetaAlphas->SetLineColor(kSpring);
// noMaskCosThetaAlphas->SetLineWidth((Width_t)0.01);
// noMaskCosThetaAlphas->SetFillColorAlpha(kSpring,0.9);
// TH1D* noMaskCosThetaAlphas_long = (TH1D*)noMaskCosTheta->Clone("noMaskCosThetaAlphas_long");
// noMaskCosThetaAlphas_long->SetLineColor(kCyan);
// noMaskCosThetaAlphas_long->SetLineWidth((Width_t)0.01);
// noMaskCosThetaAlphas_long->SetFillColorAlpha(kCyan,0.9);
// TH1D* noMaskCosThetaAlphas_long_low = (TH1D*)noMaskCosTheta->Clone("noMaskCosThetaAlphas_long_low");
// noMaskCosThetaAlphas_long_low->SetLineColor(kYellow);
// noMaskCosThetaAlphas_long_low->SetLineWidth((Width_t)0.01);
// noMaskCosThetaAlphas_long_low->SetFillColorAlpha(kYellow,0.9);
// TH1D* noMaskCosThetaAlphas_long_high = (TH1D*)noMaskCosTheta->Clone("noMaskCosThetaAlphas_long_high");
// noMaskCosThetaAlphas_long_high->SetLineColor(kBlue);
// noMaskCosThetaAlphas_long_high->SetLineWidth((Width_t)0.01);
// noMaskCosThetaAlphas_long_high->SetFillColorAlpha(kBlue,0.9);
// TH1D* noMaskCosThetaAlphas_short_higher = (TH1D*)noMaskCosTheta->Clone("noMaskCosThetaAlphas_short_higher");
// noMaskCosThetaAlphas_short_higher->SetLineColor(kOrange+7);
// noMaskCosThetaAlphas_short_higher->SetLineWidth((Width_t)0.01);
// noMaskCosThetaAlphas_short_higher->SetFillColorAlpha(kOrange+7,0.9);
// TH1D* noMaskCosThetaAlphas_alphaCut_short_low = (TH1D*)noMaskCosTheta->Clone("noMaskCosThetaAlphas_alphaCut_short_low");
// noMaskCosThetaAlphas_alphaCut_short_low->SetLineColor(kRed);
// noMaskCosThetaAlphas_alphaCut_short_low->SetLineWidth((Width_t)0.01);
// noMaskCosThetaAlphas_alphaCut_short_low->SetFillColorAlpha(kRed,0.9);
// TH1D* cftCosTheta = new TH1D("cftCosTheta","cftCosTheta",500,-1,1);
// TH1D* cftCosThetaFrags = (TH1D*)cftCosTheta->Clone("cftCosThetaFrags");
// cftCosThetaFrags->SetLineColor(kViolet);
// cftCosThetaFrags->SetLineWidth((Width_t)0.01);
// cftCosThetaFrags->SetFillColorAlpha(kViolet,0.9);
// TH1D* cftCosThetaFragsUnlikely = (TH1D*)cftCosTheta->Clone("cftCosThetaFragsUnlikely");
// cftCosThetaFragsUnlikely->SetLineColor(kViolet-9);
// cftCosThetaFragsUnlikely->SetLineWidth((Width_t)0.01);
// cftCosThetaFragsUnlikely->SetFillColorAlpha(kViolet-9,0.9);
// TH1D* cftCosThetaAlphas = (TH1D*)cftCosTheta->Clone("cftCosThetaAlphas");
// cftCosThetaAlphas->SetLineColor(kSpring);
// cftCosThetaAlphas->SetLineWidth((Width_t)0.01);
// cftCosThetaAlphas->SetFillColorAlpha(kSpring,0.9);
// TH1D* cftCosThetaAlphas_long = (TH1D*)cftCosTheta->Clone("cftCosThetaAlphas_long");
// cftCosThetaAlphas_long->SetLineColor(kCyan);
// cftCosThetaAlphas_long->SetLineWidth((Width_t)0.01);
// cftCosThetaAlphas_long->SetFillColorAlpha(kCyan,0.9);
// TH1D* cftCosThetaAlphas_long_low = (TH1D*)cftCosTheta->Clone("cftCosThetaAlphas_long_low");
// cftCosThetaAlphas_long_low->SetLineColor(kYellow);
// cftCosThetaAlphas_long_low->SetLineWidth((Width_t)0.01);
// cftCosThetaAlphas_long_low->SetFillColorAlpha(kYellow,0.9);
// TH1D* cftCosThetaAlphas_long_high = (TH1D*)cftCosTheta->Clone("cftCosThetaAlphas_long_high");
// cftCosThetaAlphas_long_high->SetLineColor(kBlue);
// cftCosThetaAlphas_long_high->SetLineWidth((Width_t)0.01);
// cftCosThetaAlphas_long_high->SetFillColorAlpha(kBlue,0.9);
// TH1D* cftCosThetaAlphas_short_higher = (TH1D*)cftCosTheta->Clone("cftCosThetaAlphas_short_higher");
// cftCosThetaAlphas_short_higher->SetLineColor(kOrange+7);
// cftCosThetaAlphas_short_higher->SetLineWidth((Width_t)0.01);
// cftCosThetaAlphas_short_higher->SetFillColorAlpha(kOrange+7,0.9);
// TH1D* cftCosThetaAlphas_alphaCut_short_low = (TH1D*)cftCosTheta->Clone("cftCosThetaAlphas_alphaCut_short_low");
// cftCosThetaAlphas_alphaCut_short_low->SetLineColor(kRed);
// cftCosThetaAlphas_alphaCut_short_low->SetLineWidth((Width_t)0.01);
// cftCosThetaAlphas_alphaCut_short_low->SetFillColorAlpha(kRed,0.9);
//
// ////////////////////// fill polar histograms ///////////////////////////////////
// printf("////////////////////// fill polar histograms ///////////////////////////////////\n");
// noMaskTracks->Draw("direction.CosTheta()>>noMaskCosTheta",noMaskCut);
// noMaskTracks->Draw("direction.CosTheta()>>noMaskCosThetaAlphas",noMaskAlphaCut_above_zCut_adc_char);
// noMaskTracks->Draw("direction.CosTheta()>>noMaskCosThetaFrags",noMaskFragCut);
// noMaskTracks->Draw("direction.CosTheta()>>noMaskCosThetaFragsUnlikely",noMaskFragUnlikelyCut_char);
// noMaskTracks->Draw("direction.CosTheta()>>noMaskCosThetaAlphas_long",noMaskAlphaCut_long_char);
// noMaskTracks->Draw("direction.CosTheta()>>noMaskCosThetaAlphas_long_low",noMaskAlphaCut_long_low_char);
// noMaskTracks->Draw("direction.CosTheta()>>noMaskCosThetaAlphas_long_high",noMaskAlphaCut_long_high_adc_char);
// noMaskTracks->Draw("direction.CosTheta()>>noMaskCosThetaAlphas_short_higher",noMaskAlphaCut_short_higher_adc_char);
// noMaskTracks->Draw("direction.CosTheta()>>noMaskCosThetaAlphas_alphaCut_short_low",noMaskAlphaCut_alphaCut_short_low_adc_char);
// cftTracks->Draw("direction.CosTheta()>>cftCosTheta",cftCut);
// cftTracks->Draw("direction.CosTheta()>>cftCosThetaAlphas",cftAlphaCut_above_zCut_adc_char);
// cftTracks->Draw("direction.CosTheta()>>cftCosThetaFrags",cftFragCut);
// cftTracks->Draw("direction.CosTheta()>>cftCosThetaFragsUnlikely",cftFragUnlikelyCut_char);
// cftTracks->Draw("direction.CosTheta()>>cftCosThetaAlphas_long",cftAlphaCut_long_char);
// cftTracks->Draw("direction.CosTheta()>>cftCosThetaAlphas_long_low",cftAlphaCut_long_low_char);
// cftTracks->Draw("direction.CosTheta()>>cftCosThetaAlphas_long_high",cftAlphaCut_long_high_adc_char);
// cftTracks->Draw("direction.CosTheta()>>cftCosThetaAlphas_short_higher",cftAlphaCut_short_higher_adc_char);
// cftTracks->Draw("direction.CosTheta()>>cftCosThetaAlphas_alphaCut_short_low",cftAlphaCut_alphaCut_short_low_adc_char);
//
// /////////////////////////////// colorcoded polar projection stack ///////////////////////////////////
// printf("////////////////////// colorcoded polar projection stack ///////////////////////////////////\n");
// c1->SetLogx(0);c1->SetLogy(0);
// TLegend* noMask_cosTheta_stack_legend = new TLegend(stack_leg_x_start,0.65,stack_leg_x_stop,0.89);
// noMask_cosTheta_stack_legend->SetTextFont(42);
// noMask_cosTheta_stack_legend->SetTextSize(0.03);
// noMask_cosTheta_stack_legend->AddEntry(noMaskCosThetaAlphas_alphaCut_short_low,noMaskAlphasEn_alphaCut_short_low_percent_char,"f");
// noMask_cosTheta_stack_legend->AddEntry(noMaskCosThetaAlphas_short_higher,noMaskAlphasEn_short_higher_percent_char,"f");
// noMask_cosTheta_stack_legend->AddEntry(noMaskCosThetaAlphas_long,noMaskAlphasEn_long_percent_char,"f");
// noMask_cosTheta_stack_legend->AddEntry(noMaskCosThetaAlphas_long_low,noMaskAlphasEn_long_low_percent_char,"f");
// noMask_cosTheta_stack_legend->AddEntry(noMaskCosThetaAlphas_long_high,noMaskAlphasEn_long_high_percent_char,"f");
// noMask_cosTheta_stack_legend->AddEntry(noMaskCosThetaFragsUnlikely,noMaskFragsUnlikelyEn_percent_char,"f");
// THStack* noMask_cosTheta_Stack = new THStack("noMask_cosTheta_Stack","");
// noMask_cosTheta_Stack->Add(noMaskCosThetaAlphas_long);
// noMask_cosTheta_Stack->Add(noMaskCosThetaAlphas_long_low);
// noMask_cosTheta_Stack->Add(noMaskCosThetaAlphas_long_high);
// noMask_cosTheta_Stack->Add(noMaskCosThetaAlphas_short_higher);
// noMask_cosTheta_Stack->Add(noMaskCosThetaAlphas_alphaCut_short_low);
// noMask_cosTheta_Stack->Add(noMaskCosThetaFragsUnlikely);
// noMask_cosTheta_Stack->Draw();
// c1->SetGridx();c1->SetGridy();
// noMask_cosTheta_Stack->GetXaxis()->SetTitle("cos #theta");
// noMask_cosTheta_Stack->SetTitle("noMask_NOalpha_NOfrag_cosTheta_Stack");
// noMask_cosTheta_stack_legend->Draw();
// c1->Update();
// c1->SaveAs("noMask_NOalpha_NOfrag_cosTheta_Stack.png");
// noMask_cosTheta_stack_legend->AddEntry(noMaskCosThetaAlphas,noMaskAlphasEn_percent_char,"f");
// noMask_cosTheta_stack_legend->AddEntry(noMaskCosThetaFrags,noMaskFragsEn_percent_char,"f");
// noMask_cosTheta_Stack->Add(noMaskCosThetaFrags);
// noMask_cosTheta_Stack->Add(noMaskCosThetaAlphas);
// noMask_cosTheta_Stack->Draw();
// noMask_cosTheta_Stack->SetTitle("noMask_cosTheta_Stack");
// c1->SetLogy(1);
// noMask_cosTheta_stack_legend->Draw();
// c1->Update();
// c1->SaveAs("noMask_cosTheta_Stack.png");
// c1->SetLogx(0);c1->SetLogy(0);
// TLegend* cft_cosTheta_stack_legend = new TLegend(stack_leg_x_start,0.65,stack_leg_x_stop,0.89);
// cft_cosTheta_stack_legend->SetTextFont(42);
// cft_cosTheta_stack_legend->SetTextSize(0.03);
// cft_cosTheta_stack_legend->AddEntry(cftCosThetaAlphas_alphaCut_short_low,cftAlphasEn_alphaCut_short_low_percent_char,"f");
// cft_cosTheta_stack_legend->AddEntry(cftCosThetaAlphas_short_higher,cftAlphasEn_short_higher_percent_char,"f");
// cft_cosTheta_stack_legend->AddEntry(cftCosThetaAlphas_long,cftAlphasEn_long_percent_char,"f");
// cft_cosTheta_stack_legend->AddEntry(cftCosThetaAlphas_long_low,cftAlphasEn_long_low_percent_char,"f");
// cft_cosTheta_stack_legend->AddEntry(cftCosThetaAlphas_long_high,cftAlphasEn_long_high_percent_char,"f");
// cft_cosTheta_stack_legend->AddEntry(cftCosThetaFragsUnlikely,cftFragsUnlikelyEn_percent_char,"f");
// THStack* cft_cosTheta_Stack = new THStack("cft_cosTheta_Stack","");
// cft_cosTheta_Stack->Add(cftCosThetaAlphas_long);
// cft_cosTheta_Stack->Add(cftCosThetaAlphas_long_low);
// cft_cosTheta_Stack->Add(cftCosThetaAlphas_long_high);
// cft_cosTheta_Stack->Add(cftCosThetaAlphas_short_higher);
// cft_cosTheta_Stack->Add(cftCosThetaAlphas_alphaCut_short_low);
// cft_cosTheta_Stack->Add(cftCosThetaFragsUnlikely);
// cft_cosTheta_Stack->Draw();
// c1->SetGridx();c1->SetGridy();
// cft_cosTheta_Stack->SetTitle("cft_NOalpha_NOfrag_cosTheta_Stack");
// cft_cosTheta_stack_legend->Draw();
// cft_cosTheta_Stack->GetXaxis()->SetTitle("cos #theta");
// c1->Update();
// c1->SaveAs("cft_NOalpha_NOfrag_cosTheta_Stack.png");
// cft_cosTheta_stack_legend->AddEntry(cftCosThetaAlphas,cftAlphasEn_percent_char,"f");
// cft_cosTheta_stack_legend->AddEntry(cftCosThetaFrags,cftFragsEn_percent_char,"f");
// cft_cosTheta_Stack->Add(cftCosThetaFrags);
// cft_cosTheta_Stack->Add(cftCosThetaAlphas);
// cft_cosTheta_Stack->Draw();
// c1->SetLogy(1);
// cft_cosTheta_stack_legend->Draw();
// cft_cosTheta_Stack->SetTitle("cft_cosTheta_Stack");
// c1->Update();
// c1->SaveAs("cft_cosTheta_Stack.png");
//
//
// // ///////////////////////  write histograms ////////////////////
// // printf("\n/////////////////////// write histograms ////////////////////\n\n");
// // TFile* theseHists = new TFile("cftAnaPlots.root","create");
// // ///////////////////////  write TCutG ///////////////////
// // fragCut_adc->Write();
// // alphaCut_above_zCut_adc->Write();
// // alphaCut_long_low_adc->Write();
// // alphaCut_long_adc->Write();
// // long_high_adc->Write();
// // alphaCut_short_higher_adc->Write();
// // alphaCut_short_low_adc->Write();
// // fragCut_energy->Write();
// // alphaCut_above_zCut_energy->Write();
// // alphaCut_long_low_energy->Write();
// // alphaCut_long_energy->Write();
// // long_high_energy->Write();
// // alphaCut_short_higher_energy->Write();
// // alphaCut_short_low_energy->Write();
// // ///////////////////////  write TH2D ////////////////////
// // noMaskLvADC->Write();
// // noMaskLvADCFrags->Write();
// // noMaskLvADCFragsUnlikely->Write();
// // noMaskLvADCAlphas->Write();
// // noMaskLvADCAlphas_long->Write();
// // noMaskLvADCAlphas_long_low->Write();
// // noMaskLvADCAlphas_long_high->Write();
// // noMaskLvADCAlphas_short_higher->Write();
// // noMaskLvADCAlphas_alphaCut_short_low->Write();
// // cftLvADC->Write();
// // cftLvADCFrags->Write();
// // cftLvADCFragsUnlikely->Write();
// // cftLvADCAlphas->Write();
// // cftLvADCAlphas_long->Write();
// // cftLvADCAlphas_long_low->Write();
// // cftLvADCAlphas_long_high->Write();
// // cftLvADCAlphas_short_higher->Write();
// // cftLvADCAlphas_alphaCut_short_low->Write();
// // noMaskLvEn->Write();
// // noMaskLvEnFrags->Write();
// // noMaskLvEnFragsUnlikely->Write();
// // noMaskLvEnAlphas->Write();
// // noMaskLvEnAlphas_long->Write();
// // noMaskLvEnAlphas_long_low->Write();
// // noMaskLvEnAlphas_long_high->Write();
// // noMaskLvEnAlphas_short_higher->Write();
// // noMaskLvEnAlphas_alphaCut_short_low->Write();
// // cftLvEn->Write();
// // cftLvEnFrags->Write();
// // cftLvEnFragsUnlikely->Write();
// // cftLvEnAlphas->Write();
// // cftLvEnAlphas_long->Write();
// // cftLvEnAlphas_long_low->Write();
// // cftLvEnAlphas_long_high->Write();
// // cftLvEnAlphas_short_higher->Write();
// // cftLvEnAlphas_alphaCut_short_low->Write();
// // ///////////////////////  write TH1D ////////////////////
// // noMaskADC->Write();
// // noMaskFragsADC->Write();
// // noMaskFragsUnlikeyADC->Write();
// // noMaskAlphasADC->Write();
// // noMaskAlphasADC_long->Write();
// // noMaskAlphasADC_long_low->Write();
// // noMaskAlphasADC_long_high->Write();
// // noMaskAlphasADC_short_higher->Write();
// // noMaskAlphasADC_alphaCut_short_low->Write();
// // cftADC->Write();
// // cftFragsADC->Write();
// // cftFragsUnlikeyADC->Write();
// // cftAlphasADC->Write();
// // cftAlphasADC_long->Write();
// // cftAlphasADC_long_low->Write();
// // cftAlphasADC_long_high->Write();
// // cftAlphasADC_short_higher->Write();
// // cftAlphasADC_alphaCut_short_low->Write();
// // noMaskEn->Write();
// // noMaskFragsEn->Write();
// // noMaskFragsUnlikelyEn->Write();
// // noMaskAlphasEn->Write();
// // noMaskAlphasEn_long->Write();
// // noMaskAlphasEn_long_low->Write();
// // noMaskAlphasEn_long_high->Write();
// // noMaskAlphasEn_short_higher->Write();
// // noMaskAlphasEn_alphaCut_short_low->Write();
// // cftEn->Write();
// // cftFragsEn->Write();
// // cftFragsUnlikelyEn->Write();
// // cftAlphasEn->Write();
// // cftAlphasEn_long->Write();
// // cftAlphasEn_long_low->Write();
// // cftAlphasEn_long_high->Write();
// // cftAlphasEn_short_higher->Write();
// // cftAlphasEn_alphaCut_short_low->Write();
// // cftEfficiency->Write();
// // cftFragsEnScaleRegion->Write();

}
