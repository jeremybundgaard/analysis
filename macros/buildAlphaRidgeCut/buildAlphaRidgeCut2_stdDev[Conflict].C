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

void buildAlphaRidgeCut2_stdDev() {

	// TFile* noMaskFile = new TFile("$trees/cf252.noMask2.trees.root");
	TFile* noMaskFile = new TFile("$trees/cf252.noMask2.nEv500000.trees.root");
	TTree* noMaskTracks = (TTree*)noMaskFile->Get("tracks");
	TH2D * noMaskLvEn = new TH2D("noMaskLvEn","noMaskLvEn",4000,0,168.6,1000,0,10);
	noMaskLvEn->GetXaxis()->SetRangeUser(0,10);
	noMaskLvEn->GetYaxis()->SetRangeUser(0,10);
	noMaskLvEn->GetXaxis()->SetTitle("Track Energy [MeV]");
	noMaskLvEn->GetXaxis()->CenterTitle();
	noMaskLvEn->GetYaxis()->SetTitle("Track Length [cm]");
	noMaskLvEn->GetYaxis()->CenterTitle();

	TCanvas *c1 = new TCanvas("c1","c1",1000,700);
	char c1PlotName[234];
	// gStyle->SetOptStat(0);
	gStyle->SetPalette(109);
	gStyle->SetNumberContours(999);

	// noMaskTracks->Draw(
	// "length:adc*168.6/40000>>noMaskLvEn",
	// "!(-1<direction.Phi()&&direction.Phi()<0)&&((-0.1>direction.CosTheta()&&direction.CosTheta()>-0.9)||(0.1<direction.CosTheta()&&direction.CosTheta()<0.9))&&run>100001856&&run!=100001870&&nDigits>60",
	// "colz");

	noMaskTracks->Draw(
	"length:adc*168.6/40000>>noMaskLvEn",
	"!(-1<direction.Phi()&&direction.Phi()<0)&&run>100001856&&run!=100001870&&nDigits>80",
	"colz");

	// noMaskTracks->Draw(
	// "start.x():start.y()>>h(100,-2,2,100,-2,2)",
	// "((start.x()*start.x()+start.y()*start.y())<2)&!(-1<direction.Phi()&&direction.Phi()<0)&&((-0.2>direction.CosTheta()&&direction.CosTheta()>-0.8)||(0.2<direction.CosTheta()&&direction.CosTheta()<0.8))&&run>100001856&&run!=100001870&&nDigits>60",
	// "colz");

	// noMaskTracks->Draw(
	// "adc*168.6/40000:direction.Phi()>>h(40000,170,0.5,500,-3.2,3.2)",
	// "((start.x()*start.x()+start.y()*start.y())<2)&!(-1<direction.Phi()&&direction.Phi()<0)&&((-0.2>direction.CosTheta()&&direction.CosTheta()>-0.8)||(0.2<direction.CosTheta()&&direction.CosTheta()<0.8))&&run>100001856&&run!=100001870&&nDigits>60",
	// "colz");

	int nStdDev=10;
	int fitBins=50;
	double enCal=168.6/4000;

	Double_t xCut_plusStdDev[nStdDev][fitBins];
	Double_t yCut_plusStdDev[fitBins];

	Double_t xCut_minusStdDev[nStdDev][fitBins];
	Double_t yCut_minusStdDev[fitBins];

	char dumChar[123];
	int xBuffer = 5;

	int arrayPos=0;
	for (int lbinStep = 150; lbinStep < 400; lbinStep+=5){
		TH1D *px = noMaskLvEn->ProjectionX("px", lbinStep, lbinStep);
		px->GetXaxis()->SetRangeUser(1,7);
		px->GetYaxis()->SetRangeUser(1,1000);
		TH1D* px_avg = (TH1D*)px->Clone("px_avg");
		px_avg->SetLineColor(kRed);

		int startBin = px->FindFirstBinAbove(10)-xBuffer;
		int stopBin = px->FindLastBinAbove(10)+xBuffer;
		for (int i = 0; i < px->GetNbinsX(); ++i){ 
			if( (startBin<i&&i<stopBin) ) continue;
			px_avg->SetBinContent(i,0);
		}

		px_avg->Draw();
		// px->Draw("same");

		yCut_plusStdDev[arrayPos] = lbinStep/(double)100;
		yCut_minusStdDev[arrayPos] = lbinStep/(double)100;
		for (int i = 0; i < nStdDev; ++i)
		{
			xCut_plusStdDev[i][arrayPos] = px_avg->GetMean()+i*px_avg->GetStdDev();
			xCut_minusStdDev[i][arrayPos] = px_avg->GetMean()-i*px_avg->GetStdDev();
			TLine *Line_plusStdDev = new TLine(
				xCut_plusStdDev[i][arrayPos],0,
				xCut_plusStdDev[i][arrayPos],10-i);
			Line_plusStdDev->SetLineColor(kRed+i);
			Line_plusStdDev->Draw("same");
			TLine *Line_minusStdDev = new TLine(
				xCut_minusStdDev[i][arrayPos],0,
				xCut_minusStdDev[i][arrayPos],10-i);
			Line_minusStdDev->SetLineColor(kRed+i);
			Line_minusStdDev->Draw("same");
		}
		sprintf(dumChar,"projx_avg.ybin%d.png",lbinStep);
		c1->SetLogy(1);
		c1->SaveAs(dumChar);
		arrayPos++;		
	}

	TGraph *g_plusStdDev[nStdDev];
	TF1 *fitLvEn_plusStdDev[nStdDev];
	TGraph *g_minusStdDev[nStdDev];
	TF1 *fitLvEn_minusStdDev[nStdDev];

	for (int i = 0; i < nStdDev; ++i)
	{
		g_plusStdDev[i] = new TGraph((sizeof(xCut_plusStdDev[0])/sizeof(Double_t)),xCut_plusStdDev[i],yCut_plusStdDev);
		sprintf(dumChar,"fitLvEn_plus_%dstdDev",i);
		fitLvEn_plusStdDev[i]=new TF1(dumChar,"[3]+[2]*TMath::Exp([1]*x+[0])",1,10);
		fitLvEn_plusStdDev[i]->SetLineColor(kRed+i);
		fitLvEn_plusStdDev[i]->SetLineWidth(1);
		g_plusStdDev[i]->Fit(fitLvEn_plusStdDev[i]);

		g_minusStdDev[i]=new TGraph((sizeof(xCut_minusStdDev[0])/sizeof(Double_t)),xCut_minusStdDev[i],yCut_minusStdDev);
		sprintf(dumChar,"fitLvEn_minus_%dstdDev",i);
		fitLvEn_minusStdDev[i]=new TF1(dumChar,"[3]+[2]*TMath::Exp([1]*x+[0])",1,10);
		fitLvEn_minusStdDev[i]->SetLineColor(kRed+i);
		fitLvEn_minusStdDev[i]->SetLineWidth(1);
		g_minusStdDev[i]->Fit(fitLvEn_minusStdDev[i]);
	}

	noMaskLvEn->SetTitle(fitLvEn_plusStdDev[0]->GetTitle());
	noMaskLvEn->Draw("Colz");
	c1->SetLogy(0);
	c1->SetLogz(1);
	for (int i = 0; i < nStdDev; ++i){
		fitLvEn_plusStdDev[i]->DrawF1(0,10,"same");
		fitLvEn_minusStdDev[i]->DrawF1(0,10,"same");
	}
	sprintf(dumChar,"alphaRidgeFit.LvEn.png");
	c1->SaveAs(dumChar);

	noMaskLvEn->GetXaxis()->SetRangeUser(1,7);
	noMaskLvEn->GetYaxis()->SetRangeUser(0,5);
	arrayPos=0;
	for (int lbinStep = 150; lbinStep < 400; lbinStep+=5){
		TH1D *px = noMaskLvEn->ProjectionX("px", lbinStep, lbinStep);
		px->GetXaxis()->SetRangeUser(1,7);
		px->GetYaxis()->SetRangeUser(1,1000);

		for (int i = 0; i < nStdDev; ++i)
		{
			double length=lbinStep/(double)100;
			double energy_plus=xCut_plusStdDev[i][arrayPos];
			double energy_minus=xCut_minusStdDev[i][arrayPos];

			TLine *Line_plusStdDev = new TLine(
				energy_plus,length-0.02,
				energy_plus,length+0.02);
			Line_plusStdDev->SetLineColor(kRed+i);
			Line_plusStdDev->SetLineWidth(3);
			Line_plusStdDev->Draw();

			TLine *Line_minusStdDev = new TLine(
				energy_minus,length+0.02,
				energy_minus,length-0.02);
			Line_minusStdDev->SetLineColor(kRed+i);
			Line_minusStdDev->SetLineWidth(3);
			Line_minusStdDev->Draw();

		}
		sprintf(dumChar,"noMaskLvEn_cutPoints.y%d.png",lbinStep);
		c1->SaveAs(dumChar);
		arrayPos++;		
	}

	noMaskLvEn->Draw("Colz");
	noMaskLvEn->GetXaxis()->SetRangeUser(0,10);
	noMaskLvEn->GetYaxis()->SetRangeUser(0,10);

	TCutG *alphaCut2[nStdDev];
	TCutG *fragCut2[nStdDev];

	for (int i = 1; i < nStdDev; ++i)
	{
		sprintf(dumChar,"alphaCut2_%dstdDev",i);
		TCutG* alphaCut2_tmp= new TCutG(dumChar,10);
		alphaCut2_tmp->SetVarX("adc");
		alphaCut2_tmp->SetVarY("length");
		alphaCut2_tmp->SetLineColor(kRed+i);

		int pointNum=0;
		alphaCut2_tmp->SetPoint(pointNum,0.5,fitLvEn_minusStdDev[i]->Eval(0.5));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,1.0,fitLvEn_plusStdDev[i]->Eval(1.0));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,1.1,fitLvEn_plusStdDev[i]->Eval(1.1));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,1.2,fitLvEn_plusStdDev[i]->Eval(1.2));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,1.3,fitLvEn_plusStdDev[i]->Eval(1.3));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,1.4,fitLvEn_plusStdDev[i]->Eval(1.4));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,1.5,fitLvEn_plusStdDev[i]->Eval(1.5));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,1.6,fitLvEn_plusStdDev[i]->Eval(1.6));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,1.7,fitLvEn_plusStdDev[i]->Eval(1.7));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,1.8,fitLvEn_plusStdDev[i]->Eval(1.8));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,1.9,fitLvEn_plusStdDev[i]->Eval(1.9));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,2.0,fitLvEn_plusStdDev[i]->Eval(2.0));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,2.1,fitLvEn_plusStdDev[i]->Eval(2.1));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,2.2,fitLvEn_plusStdDev[i]->Eval(2.2));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,2.3,fitLvEn_plusStdDev[i]->Eval(2.3));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,2.4,fitLvEn_plusStdDev[i]->Eval(2.4));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,2.5,fitLvEn_plusStdDev[i]->Eval(2.5));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,2.6,fitLvEn_plusStdDev[i]->Eval(2.6));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,2.7,fitLvEn_plusStdDev[i]->Eval(2.7));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,2.8,fitLvEn_plusStdDev[i]->Eval(2.8));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,2.9,fitLvEn_plusStdDev[i]->Eval(2.9));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,3.0,fitLvEn_plusStdDev[i]->Eval(3.0));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,3.5,fitLvEn_plusStdDev[i]->Eval(3.5));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,4.0,fitLvEn_plusStdDev[i]->Eval(4.0));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,4.5,fitLvEn_plusStdDev[i]->Eval(4.5));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,5.0,fitLvEn_plusStdDev[i]->Eval(5.0));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,5.5,fitLvEn_plusStdDev[i]->Eval(5.5));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,6.0,fitLvEn_plusStdDev[i]->Eval(6.0));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,6.5,fitLvEn_plusStdDev[i]->Eval(6.5));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,7.0,fitLvEn_plusStdDev[i]->Eval(7.0));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,7.5,fitLvEn_plusStdDev[i]->Eval(7.5));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,8.0,fitLvEn_plusStdDev[i]->Eval(8.0));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,8.5,fitLvEn_plusStdDev[i]->Eval(8.5));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,9.0,fitLvEn_plusStdDev[i]->Eval(9.0));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,9.5,fitLvEn_plusStdDev[i]->Eval(9.5));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,5.5,fitLvEn_minusStdDev[i]->Eval(5.5));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,5.0,fitLvEn_minusStdDev[i]->Eval(5.0));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,4.5,fitLvEn_minusStdDev[i]->Eval(4.5));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,4.0,fitLvEn_minusStdDev[i]->Eval(4.0));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,3.5,fitLvEn_minusStdDev[i]->Eval(3.5));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,3.0,fitLvEn_minusStdDev[i]->Eval(3.0));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,2.5,fitLvEn_minusStdDev[i]->Eval(2.5));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,2.0,fitLvEn_minusStdDev[i]->Eval(2.0));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,1.5,fitLvEn_minusStdDev[i]->Eval(1.5));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,1.0,fitLvEn_minusStdDev[i]->Eval(1.0));pointNum++
		alphaCut2_tmp->SetPoint(pointNum,0.5,fitLvEn_minusStdDev[i]->Eval(0.5));pointNum++

		alphaCut2[i] = alphaCut2_tmp;
		alphaCut2[i]->Draw("same");

		sprintf(dumChar,"fragCut_%dstdDev",i);
		TCutG *fragCut2_tmp = new TCutG(dumChar,4);
		fragCut2_tmp->SetVarX("adc");
		fragCut2_tmp->SetVarY("length");
		fragCut2_tmp->SetLineColor(kRed+i);

		pointNum=0;
		fragCut2_tmp->SetPoint(pointNum,150,0.5);pointNum++
		fragCut2_tmp->SetPoint(pointNum,1.0,fitLvEn_plusStdDev[i]->Eval(1.0));pointNum++
		fragCut2_tmp->SetPoint(pointNum,1.1,fitLvEn_plusStdDev[i]->Eval(1.1));pointNum++
		fragCut2_tmp->SetPoint(pointNum,1.2,fitLvEn_plusStdDev[i]->Eval(1.2));pointNum++
		fragCut2_tmp->SetPoint(pointNum,1.3,fitLvEn_plusStdDev[i]->Eval(1.3));pointNum++
		fragCut2_tmp->SetPoint(pointNum,1.4,fitLvEn_plusStdDev[i]->Eval(1.4));pointNum++
		fragCut2_tmp->SetPoint(pointNum,1.5,fitLvEn_plusStdDev[i]->Eval(1.5));pointNum++
		fragCut2_tmp->SetPoint(pointNum,1.6,fitLvEn_plusStdDev[i]->Eval(1.6));pointNum++
		fragCut2_tmp->SetPoint(pointNum,1.7,fitLvEn_plusStdDev[i]->Eval(1.7));pointNum++
		fragCut2_tmp->SetPoint(pointNum,1.8,fitLvEn_plusStdDev[i]->Eval(1.8));pointNum++
		fragCut2_tmp->SetPoint(pointNum,1.9,fitLvEn_plusStdDev[i]->Eval(1.9));pointNum++
		fragCut2_tmp->SetPoint(pointNum,2.0,fitLvEn_plusStdDev[i]->Eval(2.0));pointNum++
		fragCut2_tmp->SetPoint(pointNum,2.1,fitLvEn_plusStdDev[i]->Eval(2.1));pointNum++
		fragCut2_tmp->SetPoint(pointNum,2.2,fitLvEn_plusStdDev[i]->Eval(2.2));pointNum++
		fragCut2_tmp->SetPoint(pointNum,2.3,fitLvEn_plusStdDev[i]->Eval(2.3));pointNum++
		fragCut2_tmp->SetPoint(pointNum,2.4,fitLvEn_plusStdDev[i]->Eval(2.4));pointNum++
		fragCut2_tmp->SetPoint(pointNum,2.5,fitLvEn_plusStdDev[i]->Eval(2.5));pointNum++
		fragCut2_tmp->SetPoint(pointNum,2.6,fitLvEn_plusStdDev[i]->Eval(2.6));pointNum++
		fragCut2_tmp->SetPoint(pointNum,2.7,fitLvEn_plusStdDev[i]->Eval(2.7));pointNum++
		fragCut2_tmp->SetPoint(pointNum,2.8,fitLvEn_plusStdDev[i]->Eval(2.8));pointNum++
		fragCut2_tmp->SetPoint(pointNum,2.9,fitLvEn_plusStdDev[i]->Eval(2.9));pointNum++
		fragCut2_tmp->SetPoint(pointNum,3.0,fitLvEn_plusStdDev[i]->Eval(3.0));pointNum++
		fragCut2_tmp->SetPoint(pointNum,10,2.0);pointNum++
		fragCut2_tmp->SetPoint(pointNum,15,2.35);pointNum++
		fragCut2_tmp->SetPoint(pointNum,71,3.15);pointNum++
		fragCut2_tmp->SetPoint(pointNum,150,3.65);pointNum++
		fragCut2_tmp->SetPoint(pointNum,150,0.5);pointNum++

		fragCut2[i] = fragCut2_tmp;
		fragCut2[i]->Draw("same");
		sprintf(dumChar,"noMaskLvEn_tcutg_stdDev%d.png",i);
		c1->SaveAs(dumChar);

	}

	TH2D* noMaskLvEn_alphas[nStdDev];
	for (int i = 1; i < nStdDev; ++i){
		TH2D* noMaskLvEn_alphas_tmp = (TH2D*)noMaskLvEn->Clone("noMaskLvEn_alphas");
		for (int adcbin = 0; adcbin < 4000; ++adcbin){
			for (int lenbin = 0; lenbin < 1000; ++lenbin){
				double energy=adcbin*enCal;
				double length=lenbin/(double)100;
				if (!(alphaCut2[i]->IsInside(energy,length))){
					noMaskLvEn_alphas_tmp->SetBinContent(adcbin,lenbin,0);
				}
				noMaskLvEn_alphas[i]=noMaskLvEn_alphas_tmp;
			}
		}
		noMaskLvEn_alphas[i]->Draw("colz");
		alphaCut2[i]->Draw("same");

		sprintf(dumChar,"noMaskLvEn_alphas_stdDev%d.png",i);
		c1->SaveAs(dumChar);
	}

	TH2D* noMaskLvEn_alphas_meanShifted[nStdDev];
	TH1D* lengthProj_alphas_meanShifted[nStdDev];
	for (int i = 1; i < nStdDev; ++i)
	{
		sprintf(dumChar,"noMaskLvEn_alphas_meanShifted_tmp_stdDev%d",i);
		TH2D* noMaskLvEn_alphas_meanShifted_tmp = new TH2D(dumChar,"",500,0,5,200,-100,100);
		for (int lbinStep = 0; lbinStep < 700; ++lbinStep)
		{
			c1->SetLogz(0);
			c1->SetLogy(0);
			sprintf(dumChar,"px_ybin%d",lbinStep);
			TH1D *px = noMaskLvEn_alphas[i]->ProjectionX(dumChar,lbinStep,lbinStep);
			// px->Draw();
			// sprintf(dumChar,"px_noMaskLvEn_alphas_stdDev%d_lengthbin%d.png",i,lbinStep);
			// c1->SaveAs(dumChar);
			// px->SetMaximum(1000);

			int meanShift=px->FindBin(px->GetMean());
			int alphaStartBin=px->FindBin(fitLvEn_minusStdDev[i]->GetX(lbinStep/(double)100));
			int alphaStopBin=px->FindBin(fitLvEn_plusStdDev[i]->GetX(lbinStep/(double)100));
			int alphaShift = (alphaStartBin+alphaStopBin)/2;
			for (int i = alphaStartBin; i < alphaStopBin; ++i)
				noMaskLvEn_alphas_meanShifted_tmp->SetBinContent(lbinStep,i+100-meanShift,px->GetBinContent(i));
		}
		noMaskLvEn_alphas_meanShifted[i]=noMaskLvEn_alphas_meanShifted_tmp;
		TH1D* lengthProj_alphas_meanShifted_tmp = noMaskLvEn_alphas_meanShifted[i]->ProjectionX("lengthProj_alphas_meanShifted");

		lengthProj_alphas_meanShifted[i] = lengthProj_alphas_meanShifted_tmp;
		lengthProj_alphas_meanShifted[i]->Draw();
		c1->SetLogy(1);
		sprintf(dumChar,"lengthProj_alphas_meanShifted_stdDev%d.png",i);
		c1->SaveAs(dumChar);

		noMaskLvEn_alphas_meanShifted[i]->Draw("colz");
		c1->SetLogy(0);
		sprintf(dumChar,"noMaskLvEn_alphas_meanShifted_stdDev%d.png",i);
		c1->SaveAs(dumChar);
	}

	c1->SetLogx(1);
	c1->SetLogz(1);
	noMaskLvEn->Draw("colz");
	c1->SaveAs("noMaskLvEn.logx.png");



	TFile* outfile = new TFile("$cft/buildAlphaRidgeCut/pidCuts_2.root","recreate");
	outfile->cd();

	for (int i = 1; i < nStdDev; ++i)
	{
		alphaCut2[i]->Write();
		fragCut2[i]->Write();
		fitLvEn_plusStdDev[i]->Write();
		noMaskLvEn_alphas[i]->Write();
		noMaskLvEn_alphas_meanShifted[i]->Write();
	}

	outfile->Close();
}
