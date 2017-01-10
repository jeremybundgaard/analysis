#include <climits>
#include <vector>
#include "TROOT.h"
#include "TRint.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TF1.h"
#include "TCutG.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TPaletteAxis.h"
#include "TPaveText.h"
#include "TObjArray.h"
#include "TMath.h"
#include "TGraph.h"
#include "TPad.h"
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
#include <ostream>
#include <sstream>

void pidCut_zCut(int preamp,const char* treeFile,const char* cuts="&&1") {

	int nStdDev=9;
	int minStdDev=3;
	double dEnergy=0;
	double random_dEnergy=0;
	double dLength=0;
	double random_dLength=0;
	double MeV_per_ADC_bin=0;
	double ADC_per_MeV=0;
	char charBuff[123];
	int xBuffer = 5;
	double tcutStep=0.1; /*MeV*/
	int zCut=0;

	char polarCuts[567]="&&((-0.15>direction.CosTheta()&&direction.CosTheta()>-0.85)||(0.15<direction.CosTheta()&&direction.CosTheta()<0.85))";
	// char polarCuts[567]="&&(1.7453>direction.Theta()||1.396>direction.Theta())";
	// char polarCuts[567]="&&1";
	// char digitCut[567]="&&nDigits>60";
	char digitCut[567]="&&1";
	char treeCut[567];
	if(preamp==1){
		zCut=100;
		dEnergy=0;
		random_dEnergy=0;
		dLength=0.1;
		random_dLength=0;
		MeV_per_ADC_bin=0.005184745763*10; //*10 for a rebinning 
		ADC_per_MeV=1180/6.118;
		sprintf(treeCut,
			"run>100001856&&run!=100001870 %s %s %s",polarCuts,digitCut,cuts);
	}
	if(preamp==2){
		zCut=40;
		dEnergy=0;
		random_dEnergy=0;
		dLength=0.1;
		random_dLength=0;
		MeV_per_ADC_bin=0.004219310345*10;//*10 for a rebinning 
		ADC_per_MeV=1450/6.118;
		sprintf(treeCut,
			"!(-1<direction.Phi()&&direction.Phi()<0) %s %s %s",polarCuts,digitCut,cuts);
	}
	TFile* noMaskFile = new TFile(treeFile);
	TTree* noMaskTracks = (TTree*)noMaskFile->Get("tracks");
	TH2D * noMaskLvEn = new TH2D("noMaskLvEn","noMaskLvEn",4000,0,40000/(double)ADC_per_MeV,1000,0,10);
	TH2D * noMaskLvEn_zCut_alphas = new TH2D("noMaskLvEn_zCut_alphas","noMaskLvEn_zCut_alphas",4000,0,40000/(double)ADC_per_MeV,1000,0,10);
	noMaskLvEn->GetXaxis()->SetRangeUser(0,10);
	noMaskLvEn->GetYaxis()->SetRangeUser(0,10);
	noMaskLvEn->GetXaxis()->SetTitle("Track Energy [MeV]");
	noMaskLvEn->GetXaxis()->CenterTitle();
	noMaskLvEn->GetYaxis()->SetTitle("Track Length [cm]");
	noMaskLvEn->GetYaxis()->CenterTitle();
	sprintf(charBuff,"length:adc*%f>>noMaskLvEn",1/(double)ADC_per_MeV);
	noMaskTracks->Draw(charBuff,treeCut,"colz");

	TH2D * noMaskLvADC = new TH2D("noMaskLvADC","noMaskLvADC",4000,0,40000,1000,0,10);
	TH2D * noMaskLvADC_zCut_alphas = new TH2D("noMaskLvADC_zCut_alphas","noMaskLvADC_zCut_alphas",4000,0,40000,1000,0,10);
	noMaskLvADC->GetXaxis()->SetRangeUser(0,4000);
	noMaskLvADC->GetYaxis()->SetRangeUser(0,10);
	noMaskLvADC->GetXaxis()->SetTitle("Track Energy [ADC]");
	noMaskLvADC->GetXaxis()->CenterTitle();
	noMaskLvADC->GetYaxis()->SetTitle("Track Length [cm]");
	noMaskLvADC->GetYaxis()->CenterTitle();
	noMaskTracks->Draw("length:adc>>noMaskLvADC",treeCut,"colz");
	sprintf(charBuff,"$cft/pid/pidCut_zCut%d.root",preamp);
	TFile* outfile = new TFile(charBuff,"recreate");
	noMaskLvEn->Write();

	TCanvas *c1 = new TCanvas("c1","c1",1000,700);
	char c1PlotName[234];
	c1->SetGridy(1);
	c1->SetGridx(1);
	// gStyle->SetOptStat(0);
	gStyle->SetOptFit(1);
	gStyle->SetPalette(71);
	gStyle->SetNumberContours(99);
	gStyle->SetLegendBorderSize(0);
	sprintf(charBuff,"noMaskLvEn_above_zCut%04d",zCut);
	TH2D * noMaskLvEn_above_zCut = new TH2D(charBuff,charBuff,4000,0,40000/(double)ADC_per_MeV,1000,0,10);
	noMaskLvEn_above_zCut->GetXaxis()->SetTitle("Track Energy [MeV]");
	noMaskLvEn_above_zCut->GetXaxis()->CenterTitle();
	noMaskLvEn_above_zCut->GetYaxis()->SetTitle("Track Length [cm]");
	noMaskLvEn_above_zCut->GetYaxis()->CenterTitle();
	sprintf(charBuff,"noMaskLvEn_below_zCut%04d",zCut);
	TH2D * noMaskLvEn_below_zCut = new TH2D(charBuff,charBuff,4000,0,40000/(double)ADC_per_MeV,1000,0,10);
	noMaskLvEn_below_zCut->GetXaxis()->SetTitle("Track Energy [MeV]");
	noMaskLvEn_below_zCut->GetXaxis()->CenterTitle();
	noMaskLvEn_below_zCut->GetYaxis()->SetTitle("Track Length [cm]");
	noMaskLvEn_below_zCut->GetYaxis()->CenterTitle();
	for (int energyBin = 0; energyBin < 4000; ++energyBin){
		for (int lengthBin = 0; lengthBin < 1000; ++lengthBin){
			noMaskLvEn_below_zCut->SetBinContent(energyBin,lengthBin,0);
			noMaskLvEn_above_zCut->SetBinContent(energyBin,lengthBin,0);
			int counts=noMaskLvEn->GetBinContent(energyBin,lengthBin);
			if (counts<=zCut){noMaskLvEn_below_zCut->SetBinContent(energyBin,lengthBin,counts);}
			else{noMaskLvEn_above_zCut->SetBinContent(energyBin,lengthBin,counts);}
		}
	}

	///////////////////////// creating alpha zCut TCutG /////////////////////////////
	printf("\n\n/////////////////////// creating alpha zCut TCutG ///////////////////\n\n");
	ofstream alphaPrimitive;
	noMaskLvEn_above_zCut->GetXaxis()->SetRangeUser(0,15);
	noMaskLvEn_above_zCut->GetYaxis()->SetRangeUser(0,5);
	TH1D* yProj = noMaskLvEn_above_zCut->ProjectionY("yProj",0,1000);
	yProj->Write();
	yProj->Draw();
	c1->SetLogy(1);
	c1->SaveAs("yProj.png");
	c1->SetLogy(0);
	sprintf(charBuff,"alphaCut_zCut%03d_energy",zCut);
	TCutG* alphaCut_zCut_energy = new TCutG(charBuff,10);
	alphaCut_zCut_energy->SetVarX("adc");
	alphaCut_zCut_energy->SetVarY("length");
	alphaCut_zCut_energy->SetLineColor(kGreen);
	alphaCut_zCut_energy->SetLineWidth(1);
	alphaCut_zCut_energy->SetFillColorAlpha(kGreen,0.15);
	double alpha_maxCutLength=yProj->FindLastBinAbove(0)*0.01;
	TF1* f_alphaCut_long_low_energy = new TF1("f_alphaCut_long_low_energy","[1]*x+[0]",0,12);
	f_alphaCut_long_low_energy->SetParameter(0,2);
	f_alphaCut_long_low_energy->SetParameter(1,7/(double)12);
	f_alphaCut_long_low_energy->Write();
  	TF1* frag_energy_lengthline = new TF1("frag_energy_lengthline","[1]*x+[0]",0,100);
	frag_energy_lengthline->SetLineWidth(1);
	frag_energy_lengthline->SetParameter(0,1.1);
	frag_energy_lengthline->SetParameter(1,0.04);
	TCutG* alphaCut_long_low_energy	= new TCutG("alphaCut_long_low_energy",3);
	alphaCut_long_low_energy->SetVarX("adc");
	alphaCut_long_low_energy->SetVarY("length");
	alphaCut_long_low_energy->SetLineColor(kYellow);
	alphaCut_long_low_energy->SetLineWidth(1);
	alphaCut_long_low_energy->SetFillColorAlpha(kYellow,0.15);
	alphaCut_long_low_energy->SetPoint(0,0,2);
	alphaCut_long_low_energy->SetPoint(1,0,10);
	alphaCut_long_low_energy->SetPoint(2,12,10);
	alphaCut_long_low_energy->SetPoint(3,f_alphaCut_long_low_energy->GetX(alpha_maxCutLength),alpha_maxCutLength);
	alphaCut_long_low_energy->SetPoint(4,0,2);
	ofstream alphaCut_long_low_energy_primitive;
	sprintf(charBuff,"alphaCut_long_low_energy.C");
	alphaCut_long_low_energy_primitive.open(charBuff);
	alphaCut_long_low_energy->SavePrimitive(alphaCut_long_low_energy_primitive);
	alphaCut_long_low_energy->Write();
	TCutG* alphaCut_long_energy	= new TCutG("alphaCut_long_energy",3);
	alphaCut_long_energy->SetVarX("adc");
	alphaCut_long_energy->SetVarY("length");
	alphaCut_long_energy->SetLineColor(kCyan);
	alphaCut_long_energy->SetLineWidth(1);
	alphaCut_long_energy->SetFillColorAlpha(kCyan,0.15);
	alphaCut_long_energy->SetPoint(0,12,10);
	alphaCut_long_energy->SetPoint(1,f_alphaCut_long_low_energy->GetX(alpha_maxCutLength),alpha_maxCutLength);
	alphaCut_long_energy->SetPoint(2,15,alpha_maxCutLength);
	alphaCut_long_energy->SetPoint(3,15,10);
	alphaCut_long_energy->SetPoint(4,12,10);
	alphaCut_long_energy->Write();
	TCutG* long_high_energy	= new TCutG("long_high_energy",3);
	long_high_energy->SetVarX("adc");
	long_high_energy->SetVarY("length");
	long_high_energy->SetLineColor(kBlue);
	long_high_energy->SetLineWidth(1);
	long_high_energy->SetFillColorAlpha(kBlue,0.15);
	long_high_energy->SetPoint(0,15,frag_energy_lengthline->Eval(15));
	long_high_energy->SetPoint(1,30,frag_energy_lengthline->Eval(30));
	long_high_energy->SetPoint(2,71,3.15);
	long_high_energy->SetPoint(3,200,3.65);
	long_high_energy->SetPoint(4,200,10);
	long_high_energy->SetPoint(5,15,10);
	long_high_energy->SetPoint(6,15,frag_energy_lengthline->Eval(15));
	long_high_energy->Write();
	sprintf(charBuff,"alphaCut_short_higher_energy");
	TCutG* alphaCut_short_higher_energy = new TCutG(charBuff,4);
	alphaCut_short_higher_energy->SetVarX("adc");
	alphaCut_short_higher_energy->SetVarY("length");
	alphaCut_short_higher_energy->SetLineColor(kOrange+7);
	alphaCut_short_higher_energy->SetLineWidth(1);
	alphaCut_short_higher_energy->SetFillColorAlpha(kOrange+7,0.15);
	int alphaCut_short_higher_energy_pointNum=0;
	alphaCut_short_higher_energy->SetPoint(alphaCut_short_higher_energy_pointNum,15,frag_energy_lengthline->Eval(15));alphaCut_short_higher_energy_pointNum++;
	alphaCut_short_higher_energy->SetPoint(alphaCut_short_higher_energy_pointNum,15,alpha_maxCutLength);alphaCut_short_higher_energy_pointNum++;
	sprintf(charBuff,"fragCut_energy");
	TCutG* fragCut_energy = new TCutG(charBuff,4);
	fragCut_energy->SetVarX("adc");
	fragCut_energy->SetVarY("length");
	fragCut_energy->SetLineColor(kViolet);
	fragCut_energy->SetLineWidth(3);
	fragCut_energy->SetFillColorAlpha(kViolet,0.15);
	int frag_energy_pointNum=0;
	fragCut_energy->SetPoint(frag_energy_pointNum,15,frag_energy_lengthline->Eval(15));frag_energy_pointNum++;
	sprintf(charBuff,"alphaCut_short_low_energy");
	TCutG* alphaCut_short_low_energy= new TCutG(charBuff,4);
	alphaCut_short_low_energy->SetVarX("adc");
	alphaCut_short_low_energy->SetVarY("length");
	alphaCut_short_low_energy->SetLineColor(kRed);
	alphaCut_short_low_energy->SetLineWidth(1);
	alphaCut_short_low_energy->SetFillColorAlpha(kRed,0.15);
	int short_low_energy_pointNum=1;
	sprintf(charBuff,"alphaCut_zCut%03d_adc",zCut);
	TCutG* alphaCut_zCut_adc = new TCutG(charBuff,10);
	alphaCut_zCut_adc->SetVarX("adc");
	alphaCut_zCut_adc->SetVarY("length");
	alphaCut_zCut_adc->SetLineColor(kGreen);
	alphaCut_zCut_adc->SetLineWidth(1);
	alphaCut_zCut_adc->SetFillColorAlpha(kGreen,0.15);
	TCutG* alphaCut_long_low_adc	= new TCutG("alphaCut_long_low_adc",3);
	alphaCut_long_low_adc->SetVarX("adc");
	alphaCut_long_low_adc->SetVarY("length");
	alphaCut_long_low_adc->SetLineColor(kYellow);
	alphaCut_long_low_adc->SetLineWidth(1);
	alphaCut_long_low_adc->SetFillColorAlpha(kYellow,0.15);
	alphaCut_long_low_adc->SetPoint(0,ADC_per_MeV*0,2);
	alphaCut_long_low_adc->SetPoint(1,ADC_per_MeV*0,10);
	alphaCut_long_low_adc->SetPoint(2,ADC_per_MeV*12,10);
	alphaCut_long_low_adc->SetPoint(3,ADC_per_MeV*f_alphaCut_long_low_energy->GetX(alpha_maxCutLength),alpha_maxCutLength);
	alphaCut_long_low_adc->SetPoint(4,ADC_per_MeV*0,2);
	ofstream alphaCut_long_low_adc_primitive;
	sprintf(charBuff,"alphaCut_long_low_adc.C");
	alphaCut_long_low_adc_primitive.open(charBuff);
	alphaCut_long_low_adc->SavePrimitive(alphaCut_long_low_adc_primitive);
	alphaCut_long_low_adc->Write();
	TCutG* alphaCut_long_adc	= new TCutG("alphaCut_long_adc",3);
	alphaCut_long_adc->SetVarX("adc");
	alphaCut_long_adc->SetVarY("length");
	alphaCut_long_adc->SetLineColor(kCyan);
	alphaCut_long_adc->SetLineWidth(1);
	alphaCut_long_adc->SetFillColorAlpha(kCyan,0.15);
	alphaCut_long_adc->SetPoint(0,ADC_per_MeV*12,10);
	alphaCut_long_adc->SetPoint(1,ADC_per_MeV*f_alphaCut_long_low_energy->GetX(alpha_maxCutLength),alpha_maxCutLength);
	alphaCut_long_adc->SetPoint(2,ADC_per_MeV*15,alpha_maxCutLength);
	alphaCut_long_adc->SetPoint(3,ADC_per_MeV*15,10);
	alphaCut_long_adc->SetPoint(4,ADC_per_MeV*12,10);
	alphaCut_long_adc->Write();
	TCutG* long_high_adc	= new TCutG("long_high_adc",3);
	long_high_adc->SetVarX("adc");
	long_high_adc->SetVarY("length");
	long_high_adc->SetLineColor(kBlue);
	long_high_adc->SetLineWidth(1);
	long_high_adc->SetFillColorAlpha(kBlue,0.15);
	long_high_adc->SetPoint(0,ADC_per_MeV*15,frag_energy_lengthline->Eval(15));
	long_high_adc->SetPoint(1,ADC_per_MeV*30,frag_energy_lengthline->Eval(30));
	long_high_adc->SetPoint(2,ADC_per_MeV*71,3.15);
	long_high_adc->SetPoint(3,ADC_per_MeV*200,3.65);
	long_high_adc->SetPoint(4,ADC_per_MeV*200,10);
	long_high_adc->SetPoint(5,ADC_per_MeV*15,10);
	long_high_adc->SetPoint(6,ADC_per_MeV*15,frag_energy_lengthline->Eval(15));
	long_high_adc->Write();
	sprintf(charBuff,"alphaCut_short_higher_adc");
	TCutG* alphaCut_short_higher_adc = new TCutG(charBuff,4);
	alphaCut_short_higher_adc->SetVarX("adc");
	alphaCut_short_higher_adc->SetVarY("length");
	alphaCut_short_higher_adc->SetLineColor(kOrange+7);
	alphaCut_short_higher_adc->SetLineWidth(1);
	alphaCut_short_higher_adc->SetFillColorAlpha(kOrange+7,0.15);
	int alphaCut_short_higher_adc_pointNum=0;
	alphaCut_short_higher_adc->SetPoint(alphaCut_short_higher_adc_pointNum,15*ADC_per_MeV,frag_energy_lengthline->Eval(15));alphaCut_short_higher_adc_pointNum++;
	alphaCut_short_higher_adc->SetPoint(alphaCut_short_higher_adc_pointNum,15*ADC_per_MeV,alpha_maxCutLength);alphaCut_short_higher_adc_pointNum++;
	sprintf(charBuff,"fragCut_adc");
	TCutG* fragCut_adc = new TCutG(charBuff,4);
	fragCut_adc->SetVarX("adc");
	fragCut_adc->SetVarY("length");
	fragCut_adc->SetLineColor(kViolet);
	fragCut_adc->SetLineWidth(3);
	fragCut_adc->SetFillColorAlpha(kViolet,0.15);
	int frag_adc_pointNum=0;
	fragCut_adc->SetPoint(frag_adc_pointNum,15*ADC_per_MeV,frag_energy_lengthline->Eval(15));frag_adc_pointNum++;
	sprintf(charBuff,"alphaCut_short_low_adc");
	TCutG* alphaCut_short_low_adc= new TCutG(charBuff,4);
	alphaCut_short_low_adc->SetVarX("adc");
	alphaCut_short_low_adc->SetVarY("length");
	alphaCut_short_low_adc->SetLineColor(kRed);
	alphaCut_short_low_adc->SetLineWidth(1);
	alphaCut_short_low_adc->SetFillColorAlpha(kRed,0.15);
	int short_low_adc_pointNum=1;
	int zCut_pointNum=0;
	int midpoint_length=(yProj->FindFirstBinAbove(0)+yProj->FindLastBinAbove(0))/2*0.01;
	//////////////////  low energy side of zCut //////////////////
	printf("//////////////////  low energy side of zCut //////////////////\n\n");
	for (int lengthBin = yProj->FindFirstBinAbove(0); lengthBin <= yProj->FindLastBinAbove(0); ++lengthBin ){
		TH1D *px = noMaskLvEn_above_zCut->ProjectionX("px", lengthBin, lengthBin);
		double length1=(lengthBin-1)*0.01+random_dLength;
		double length2=lengthBin*0.01+random_dLength;
		double energy=(px->FindFirstBinAbove(0)-1)*MeV_per_ADC_bin;
		energy=energy-dEnergy+random_dEnergy;
		int adc = energy*ADC_per_MeV;
		alphaCut_zCut_energy->SetPoint(zCut_pointNum,energy,length1);
		alphaCut_zCut_adc->SetPoint(zCut_pointNum,adc,length1);
		zCut_pointNum++;
		alphaCut_zCut_energy->SetPoint(zCut_pointNum,energy,length2);
		alphaCut_zCut_adc->SetPoint(zCut_pointNum,adc,length2);
		zCut_pointNum++;
		alphaCut_short_low_energy->SetPoint(short_low_energy_pointNum,energy,length1);short_low_energy_pointNum++;
		alphaCut_short_low_adc->SetPoint(short_low_adc_pointNum,adc,length1);short_low_adc_pointNum++;
		alphaCut_short_low_energy->SetPoint(short_low_energy_pointNum,energy,length2);short_low_energy_pointNum++;
		alphaCut_short_low_adc->SetPoint(short_low_adc_pointNum,adc,length2);short_low_adc_pointNum++;
	}
	//////////////////  high energy side of zCut //////////////////
	printf("//////////////////  high energy side of zCut //////////////////\n\n");
	bool fragCut_switch=0;
	double last_length2=0;
	double last_length1=0;
	for (int lengthBin = yProj->FindLastBinAbove(0); lengthBin >= yProj->FindFirstBinAbove(0); --lengthBin ){
		TH1D *px = noMaskLvEn_above_zCut->ProjectionX("px", lengthBin, lengthBin);
		double length1=(lengthBin-1)*0.01+random_dLength;
		double length2=lengthBin*0.01+random_dLength;
		last_length2=length2;
		last_length1=length1;
		double energy=px->FindLastBinAbove(0)*MeV_per_ADC_bin;
		energy=energy+dEnergy+random_dEnergy;
		int adc = energy*ADC_per_MeV;
		alphaCut_zCut_energy->SetPoint(zCut_pointNum,energy,length2);
		alphaCut_zCut_adc->SetPoint(zCut_pointNum,adc,length2);
		zCut_pointNum++;
		alphaCut_zCut_energy->SetPoint(zCut_pointNum,energy,length1);
		alphaCut_zCut_adc->SetPoint(zCut_pointNum,adc,length1);
		zCut_pointNum++;
		if (length2>1){
			alphaCut_short_higher_energy->SetPoint(alphaCut_short_higher_energy_pointNum,energy,length2);alphaCut_short_higher_energy_pointNum++;
			alphaCut_short_higher_adc->SetPoint(alphaCut_short_higher_adc_pointNum,adc,length2);alphaCut_short_higher_adc_pointNum++;
			alphaCut_short_higher_energy->SetPoint(alphaCut_short_higher_energy_pointNum,energy,length1);alphaCut_short_higher_energy_pointNum++;
			alphaCut_short_higher_adc->SetPoint(alphaCut_short_higher_adc_pointNum,adc,length1);alphaCut_short_higher_adc_pointNum++;
			fragCut_energy->SetPoint(frag_energy_pointNum,energy,length2);
			fragCut_adc->SetPoint(frag_adc_pointNum,adc,length2);
			fragCut_energy->SetPoint(frag_energy_pointNum,energy,length1);
			fragCut_adc->SetPoint(frag_adc_pointNum,adc,length1);
		}
		else{
			if (fragCut_switch==0)
			{
				frag_energy_pointNum++;
				frag_adc_pointNum++;
				fragCut_switch=1;
			}
			printf("last_length2%f\n",last_length2);
			fragCut_energy->SetPoint(frag_energy_pointNum,energy,length2);frag_energy_pointNum++;
			fragCut_adc->SetPoint(frag_adc_pointNum,adc,length2);frag_adc_pointNum++;
			fragCut_energy->SetPoint(frag_energy_pointNum,energy,length1);frag_energy_pointNum++;
			fragCut_adc->SetPoint(frag_adc_pointNum,adc,length1);frag_adc_pointNum++;
		}		
	}
	TH1D *px = noMaskLvEn_above_zCut->ProjectionX("px",yProj->FindFirstBinAbove(0),yProj->FindFirstBinAbove(0));
	alphaCut_zCut_energy->SetPoint(zCut_pointNum,(px->FindFirstBinAbove(0)-1)*MeV_per_ADC_bin,(yProj->FindFirstBinAbove(0)-1)*0.01);
	alphaCut_zCut_energy->Write();
	alphaCut_zCut_adc->SetPoint(zCut_pointNum,(px->FindFirstBinAbove(0)-1)*MeV_per_ADC_bin*ADC_per_MeV,(yProj->FindFirstBinAbove(0)-1)*0.01);zCut_pointNum++;
	alphaCut_zCut_adc->Write();
	sprintf(charBuff,"alphaCut_zCut%d.C",zCut);
	alphaPrimitive.open(charBuff);
	alphaCut_zCut_energy->SavePrimitive(alphaPrimitive);
	alphaCut_short_low_energy->SetPoint(short_low_energy_pointNum,f_alphaCut_long_low_energy->GetX(alpha_maxCutLength),alpha_maxCutLength);short_low_energy_pointNum++;
	alphaCut_short_low_energy->SetPoint(short_low_energy_pointNum,0,2);short_low_energy_pointNum++;
	alphaCut_short_low_energy->SetPoint(0,0,last_length2);
	alphaCut_short_low_energy->Write();
	alphaCut_short_low_adc->SetPoint(short_low_adc_pointNum,ADC_per_MeV*f_alphaCut_long_low_energy->GetX(alpha_maxCutLength),alpha_maxCutLength);short_low_adc_pointNum++;
	alphaCut_short_low_adc->SetPoint(short_low_adc_pointNum,0,2);short_low_adc_pointNum++;
	alphaCut_short_low_adc->SetPoint(0,0,last_length2);
	alphaCut_short_low_adc->Write();
	alphaCut_short_higher_energy->SetPoint(alphaCut_short_higher_energy_pointNum,15,frag_energy_lengthline->Eval(15));alphaCut_short_higher_energy_pointNum++;
	alphaCut_short_higher_energy->Write();
	alphaCut_short_higher_adc->SetPoint(alphaCut_short_higher_adc_pointNum,ADC_per_MeV*15,frag_energy_lengthline->Eval(15));alphaCut_short_higher_adc_pointNum++;
	alphaCut_short_higher_adc->Write();
	fragCut_energy->SetPoint(frag_energy_pointNum,0,last_length1);frag_energy_pointNum++;
	fragCut_energy->SetPoint(frag_energy_pointNum,0,0);frag_energy_pointNum++;
	fragCut_energy->SetPoint(frag_energy_pointNum,200,0);frag_energy_pointNum++;
	fragCut_energy->SetPoint(frag_energy_pointNum,200,3.65);frag_energy_pointNum++;
	fragCut_energy->SetPoint(frag_energy_pointNum,71,3.15);frag_energy_pointNum++;
	fragCut_energy->SetPoint(frag_energy_pointNum,30,frag_energy_lengthline->Eval(30));frag_energy_pointNum++;
	fragCut_energy->SetPoint(frag_energy_pointNum,15,frag_energy_lengthline->Eval(15));frag_energy_pointNum++;
	sprintf(charBuff,"fragCut_energy.C");
	ofstream fragPrimitive;
	fragPrimitive.open(charBuff);
	fragCut_energy->SavePrimitive(fragPrimitive);
	fragCut_energy->Write();
	fragCut_adc->SetPoint(frag_adc_pointNum,0,last_length1);frag_adc_pointNum++;
	fragCut_adc->SetPoint(frag_adc_pointNum,0,0);frag_adc_pointNum++;
	fragCut_adc->SetPoint(frag_adc_pointNum,ADC_per_MeV*200,0);frag_adc_pointNum++;
	fragCut_adc->SetPoint(frag_adc_pointNum,ADC_per_MeV*200,3.65);frag_adc_pointNum++;
	fragCut_adc->SetPoint(frag_adc_pointNum,ADC_per_MeV*71,3.15);frag_adc_pointNum++;
	fragCut_adc->SetPoint(frag_adc_pointNum,ADC_per_MeV*30,frag_energy_lengthline->Eval(30));frag_adc_pointNum++;
	fragCut_adc->SetPoint(frag_adc_pointNum,ADC_per_MeV*15,frag_energy_lengthline->Eval(15));frag_adc_pointNum++;
	sprintf(charBuff,"fragCut_adc.C");
	fragPrimitive.open(charBuff);
	fragCut_adc->SavePrimitive(fragPrimitive);
	fragCut_adc->Write();
	noMaskLvEn_above_zCut->GetXaxis()->SetRangeUser(0,15);
	noMaskLvEn_above_zCut->GetYaxis()->SetRangeUser(0,5);
	c1->SetLogz(1);
	noMaskLvEn_above_zCut->SetStats(kFALSE);
	noMaskLvEn_above_zCut->Draw("colz");
	alphaCut_zCut_energy->Draw("same");
	alphaCut_zCut_energy->Draw("same f");
	sprintf(charBuff,"noMaskLvEn_above_zCut%03d.png",zCut);
	c1->SaveAs(charBuff);
	noMaskLvEn_below_zCut->Write();
	noMaskLvEn_above_zCut->Write();
	outfile->Close();

	////////////////////////  plotting color pid cuts  ////////////////////
	printf("\n\n////////////////////////  plotting color pid cuts  ////////////////////\n\n");
	/////////////  draw color cuts ////////////
	noMaskLvEn->GetXaxis()->SetRangeUser(0,20);
	noMaskLvEn->GetYaxis()->SetRangeUser(0,10);
	noMaskLvEn->Draw("colz");
	alphaCut_zCut_energy->Draw("same f");
	alphaCut_zCut_energy->Draw("same");
	alphaCut_short_low_energy->Draw("same f");
	alphaCut_short_low_energy->Draw("same");
	alphaCut_short_higher_energy->Draw("same f");
	alphaCut_short_higher_energy->Draw("same");
	alphaCut_long_low_energy->Draw("same f");
	alphaCut_long_low_energy->Draw("same");
	alphaCut_long_energy->Draw("same f");
	alphaCut_long_energy->Draw("same");
	long_high_energy->Draw("same");
	long_high_energy->Draw("same f");
	fragCut_energy->Draw("same f");
	fragCut_energy->Draw("same");
	c1->SetLogx(1);
	c1->SetLogz(1);
	sprintf(charBuff,"alphaCut_below_zCut_full_logxz_energy.png");
	c1->SaveAs(charBuff);
	sprintf(charBuff,"alphaCut_below_zCut_full_energy.png");
	c1->SaveAs(charBuff);
	c1->SetLogx(0);
	noMaskLvADC->Draw("colz");
	alphaCut_zCut_adc->Draw("same");
	alphaCut_zCut_adc->Draw("same f");
	alphaCut_short_low_adc->Draw("same f");
	alphaCut_short_low_adc->Draw("same");
	alphaCut_short_higher_adc->Draw("same f");
	alphaCut_short_higher_adc->Draw("same");
	alphaCut_long_low_adc->Draw("same f");
	alphaCut_long_low_adc->Draw("same");
	alphaCut_long_adc->Draw("same f");
	alphaCut_long_adc->Draw("same");
	long_high_adc->Draw("same");
	long_high_adc->Draw("same f");
	fragCut_adc->Draw("same f");
	fragCut_adc->Draw("same");
	sprintf(charBuff,"alphaCut_below_zCut_full_logxz_adc.png");
	c1->SaveAs(charBuff);
	sprintf(charBuff,"alphaCut_below_zCut_full_adc.png");
	c1->SaveAs(charBuff);

	// ///////////////////  plotting zCut scans  ////////////////////
	// printf("\n\n/////////////////// plotting zCut scans //////////////////\n\n");
	// TLatex text;
	// text.SetTextAlign(13);
	// text.SetTextSize(0.025);
	// text.SetTextFont(42);
	// c1->SetLogx(1);
	// TH2D* noMaskLvEn_not_frags = new (TH2D*)noMaskLvEn->Clone("noMaskLvEn_not_frags");
	// for (int z = 0; z <= 110; z+=2){
	// 	for (int energyBin = 0; energyBin < 4000; ++energyBin){
	// 		for (int lengthBin = 0; lengthBin < 1000; ++lengthBin){
	// 			noMaskLvEn_below_zCut->SetBinContent(energyBin,lengthBin,0);
	// 			noMaskLvEn_above_zCut->SetBinContent(energyBin,lengthBin,0);
	// 			int counts=noMaskLvEn_not_frags->GetBinContent(energyBin,lengthBin);
	// 			if (counts < z){noMaskLvEn_below_zCut->SetBinContent(energyBin,lengthBin,counts);}
	// 			else{noMaskLvEn_above_zCut->SetBinContent(energyBin,lengthBin,counts);}
	// 		}
	// 	}
	// 	c1->cd();
	// 	c1->SetLogz(0);
	// 	c1->SetLogx(0);
	// 	noMaskLvEn_below_zCut->GetXaxis()->SetRangeUser(0.4,10);
	// 	sprintf(charBuff,"noMaskLvEn_below_zCut%03d",z);
	// 	noMaskLvEn_below_zCut->SetTitle(charBuff);
	// 	noMaskLvEn_below_zCut->SetStats(kFALSE);
	// 	noMaskLvEn_below_zCut->Draw("colz");
	// 	sprintf(charBuff,"number_above_zCut%d: %d",z,(int)noMaskLvEn_above_zCut->Integral());
	// 	text.DrawTextNDC(0.15,0.89,charBuff);
	// 	sprintf(charBuff,"number_below_zCut%d: %d",z,(int)noMaskLvEn_below_zCut->Integral());
	// 	text.DrawTextNDC(0.15,0.86,charBuff);
	// 	sprintf(charBuff,"%% #alpha tracks: %1.3f",noMaskLvEn_below_zCut->Integral()/(double)noMaskLvEn_not_frags->Integral()*100);
	// 	text.DrawTextNDC(0.15,0.81,charBuff);
	// 	TLegend *zCutLegend = new TLegend(0.35,0.15,0.55,0.12);
	// 	zCutLegend->SetTextFont(42);
	// 	zCutLegend->SetTextSize(0.03);
	// 	zCutLegend->SetFillColorAlpha(kWhite,0.2);
	// 	zCutLegend->AddEntry(alphaCut_zCut_energy,">99%% alphas inside");
	// 	zCutLegend->Draw();
	// 	TPad *inset_pad0 = new TPad ("inset_pad0", "inset_pad0",0.55,0.55,0.9,0.9);
	// 	inset_pad0->SetPhi(35);
	// 	inset_pad0->SetTheta(70);
	// 	inset_pad0->Draw();
	// 	inset_pad0->cd();
	// 	inset_pad0->SetLogz(1);
	// 	inset_pad0->SetLogx(0);
	// 	noMaskLvEn_above_zCut->GetXaxis()->SetRangeUser(0.4,10);
	// 	noMaskLvEn_above_zCut->GetYaxis()->SetRangeUser(0,6);
	// 	sprintf(charBuff,"noMaskLvEn_above_zCut%d",z);
	// 	noMaskLvEn_above_zCut->SetTitle(charBuff);
	// 	sprintf(charBuff,"noMaskLvEn_alphas_zCut%03d.png",z);
	// 	noMaskLvEn_above_zCut->Draw("surf2");
	// 	c1->cd();
	// 	c1->SaveAs(charBuff);
	// 	delete inset_pad0;
	// }
	// c1->SetLogx(1);
	// for (int z = 0; z <= 150; z+=2){
	// 	zCut=z;
	// 	for (int energyBin = 0; energyBin < 4000; ++energyBin){
	// 		for (int lengthBin = 0; lengthBin < 1000; ++lengthBin){
	// 			noMaskLvEn_below_zCut->SetBinContent(energyBin,lengthBin,0);
	// 			noMaskLvEn_above_zCut->SetBinContent(energyBin,lengthBin,0);
	// 			int counts=noMaskLvEn->GetBinContent(energyBin,lengthBin);
	// 			if (counts<zCut){noMaskLvEn_below_zCut->SetBinContent(energyBin,lengthBin,counts);}
	// 			else{noMaskLvEn_above_zCut->SetBinContent(energyBin,lengthBin,counts);}
	// 		}
	// 	}
	// 	c1->cd();
	// 	c1->SetLogz(0);
	// 	noMaskLvEn_below_zCut->GetXaxis()->SetRangeUser(0.4,200);
	// 	sprintf(charBuff,"noMaskLvEn_below_zCut%d",zCut);
	// 	noMaskLvEn_below_zCut->SetTitle(charBuff);
	// 	noMaskLvEn_below_zCut->SetStats(kFALSE);
	// 	noMaskLvEn_below_zCut->Draw("colz");
	// 	sprintf(charBuff,"number_above_zCut%d: %d",zCut,(int)noMaskLvEn_above_zCut->Integral());
	// 	text.DrawTextNDC(0.15,0.89,charBuff);
	// 	sprintf(charBuff,"number_below_zCut%d: %d",zCut,(int)noMaskLvEn_below_zCut->Integral());
	// 	text.DrawTextNDC(0.15,0.86,charBuff);
	// 	sprintf(charBuff,"%% #all tracks: %1.3f",noMaskLvEn_below_zCut->Integral()/(double)noMaskLvEn->Integral()*100);
	// 	text.DrawTextNDC(0.15,0.81,charBuff);
	// 	TPad *inset_pad0 = new TPad ("inset_pad0", "inset_pad0",0.55,0.55,0.9,0.9);
	// 	inset_pad0->Draw();
	// 	inset_pad0->cd();
	// 	inset_pad0->SetLogz(1);
	// 	inset_pad0->SetLogx(1);
	// 	noMaskLvEn_above_zCut->GetXaxis()->SetRangeUser(0.4,200);
	// 	noMaskLvEn_above_zCut->GetYaxis()->SetRangeUser(0,6);
	// 	sprintf(charBuff,"noMaskLvEn_above_zCut%d",zCut);
	// 	noMaskLvEn_above_zCut->SetTitle(charBuff);
	// 	sprintf(charBuff,"noMaskLvEn_all_zCut%03d.png",zCut);
	// 	noMaskLvEn_above_zCut->Draw("surf2");
	// 	c1->cd();
	// 	c1->SaveAs(charBuff);
	// 	delete inset_pad0;
	// }

}
