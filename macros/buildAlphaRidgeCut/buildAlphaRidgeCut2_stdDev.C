#include "THStack.h"
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

void pidCuts_stdDev() {

	TFile* noMaskFile = new TFile("$trees/cf252.noMask2.trees.root");
	// TFile* noMaskFile = new TFile("$trees/cf252.noMask2.nEv500000.trees.root");
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
	gStyle->SetOptStat(0);
	gStyle->SetPalette(kRainBow);
	gStyle->SetNumberContours(999);

	// noMaskTracks->Draw("length:adc*168.6/40000>>noMaskLvEn","!(-1<direction.Phi()&&direction.Phi()<0)&&((-0.1>direction.CosTheta()&&direction.CosTheta()>-0.9)||(0.1<direction.CosTheta()&&direction.CosTheta()<0.9))&&run>100001856&&run!=100001870&&nDigits>60","colz");
	noMaskTracks->Draw("length:adc*168.6/40000>>noMaskLvEn","!(-1<direction.Phi()&&direction.Phi()<0)&&((-0.05>direction.CosTheta()&&direction.CosTheta()>-0.95)||(0.05<direction.CosTheta()&&direction.CosTheta()<0.95))&&run>100001856&&run!=100001870&&nDigits>60","colz");
	// noMaskTracks->Draw("length:adc*168.6/40000>>noMaskLvEn","!(-1<direction.Phi()&&direction.Phi()<0)&&run>100001856&&run!=100001870&&nDigits>60","colz");


	int nStdDev=10;
	int minStdDev=2;
	int fitBins=50;
	double enCal=168.6/4000;
	char dumChar[123];
	int xBuffer = 5;
	double tcutStep=0.01;


	//////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////// defining alpha cut points ///////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////
	printf("\n\n /////////////////////// define alpha cut points /////////////////// \n\n");

	Double_t energyCutPoint_alphas_plusStdDev[nStdDev][fitBins];
	Double_t lenghtCutPoint_alphas_plusStdDev[fitBins];
	Double_t energyCutPoint_alphas_minusStdDev[nStdDev][fitBins];
	Double_t lenghtCutPoint_alphas_minusStdDev[fitBins];
	int arrayPos=0;
	for (int lengthBin = 150; lengthBin < 400; lengthBin+=5){
		TH1D *px = noMaskLvEn->ProjectionX("px", lengthBin, lengthBin);
		px->GetXaxis()->SetRangeUser(0,8);
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

		lenghtCutPoint_alphas_plusStdDev[arrayPos] = lengthBin/(double)100;
		lenghtCutPoint_alphas_minusStdDev[arrayPos] = lengthBin/(double)100;
		for (int i = 0; i < nStdDev; ++i)
		{
			energyCutPoint_alphas_plusStdDev[i][arrayPos] = px_avg->GetMean()+i*px_avg->GetStdDev();
			energyCutPoint_alphas_minusStdDev[i][arrayPos] = px_avg->GetMean()-i*px_avg->GetStdDev();
			TLine *Line_plusStdDev = new TLine(
				energyCutPoint_alphas_plusStdDev[i][arrayPos],0,
				energyCutPoint_alphas_plusStdDev[i][arrayPos],10-i);
			Line_plusStdDev->SetLineColor(i);
			Line_plusStdDev->Draw("same");
			TLine *Line_minusStdDev = new TLine(
				energyCutPoint_alphas_minusStdDev[i][arrayPos],0,
				energyCutPoint_alphas_minusStdDev[i][arrayPos],10-i);
			Line_minusStdDev->SetLineColor(i);
			Line_minusStdDev->Draw("same");
		}
		sprintf(dumChar,"AlphaBand_proj.lengthBin%d.png",lengthBin);
		c1->SetLogy(1);
		c1->SaveAs(dumChar);
		c1->SetLogy(0);
		arrayPos++;		
	}

	/////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////  fitting alpha cut points  /////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////
	printf("\n\n ///////////////////////  fit alpha cut points  /////////////////// \n\n");
	TGraph *alphaGraph_plusStdDev[nStdDev];
	TF1 *alphaFit_plusStdDev[nStdDev];
	TGraph *alphaGraph_minusStdDev[nStdDev];
	TF1 *alphaFit_minusStdDev[nStdDev];
	for (int i = 0; i < nStdDev; ++i)
	{
		alphaGraph_plusStdDev[i] = new TGraph((sizeof(energyCutPoint_alphas_plusStdDev[0])/sizeof(Double_t)),energyCutPoint_alphas_plusStdDev[i],lenghtCutPoint_alphas_plusStdDev);
		sprintf(dumChar,"alphaFit_plus_%dstdDev",i);
		alphaFit_plusStdDev[i]=new TF1(dumChar,"[3]+[2]*TMath::Exp([1]*x+[0])",1,10);
		alphaFit_plusStdDev[i]->SetLineColor(i);
		alphaFit_plusStdDev[i]->SetLineWidth(1);
		alphaGraph_plusStdDev[i]->Fit(alphaFit_plusStdDev[i]);

		alphaGraph_minusStdDev[i]=new TGraph((sizeof(energyCutPoint_alphas_minusStdDev[0])/sizeof(Double_t)),energyCutPoint_alphas_minusStdDev[i],lenghtCutPoint_alphas_minusStdDev);
		sprintf(dumChar,"alphaFit_minus_%dstdDev",i);
		alphaFit_minusStdDev[i]=new TF1(dumChar,"[3]+[2]*TMath::Exp([1]*x+[0])",1,10);
		alphaFit_minusStdDev[i]->SetLineColor(i);
		alphaFit_minusStdDev[i]->SetLineWidth(1);
		alphaGraph_minusStdDev[i]->Fit(alphaFit_minusStdDev[i]);
	}

	////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////  drawing alpha cut points /////////////////////////
	////////////////////////////////////////////////////////////////////////////////////
	printf("\n\n /////////////////////// drawing alpha cut points /////////////////// \n\n");
	noMaskLvEn->GetXaxis()->SetRangeUser(0,8);
	noMaskLvEn->GetYaxis()->SetRangeUser(0.5,5);
	gStyle->SetPalette(kGreyScale);
	noMaskLvEn->Draw("colz");
	noMaskLvEn->Draw("colz");
	c1->SetLogz(1);
	arrayPos=0;
	for (int lengthBin = 150; lengthBin < 400; lengthBin+=5){
		for (int i = 0; i < nStdDev; ++i)
		{
			double length=lengthBin/(double)100;
			double energy_plus=energyCutPoint_alphas_plusStdDev[i][arrayPos];
			double energy_minus=energyCutPoint_alphas_minusStdDev[i][arrayPos];

			TLine *Line_plusStdDev = new TLine(
				energy_plus,length-0.02,
				energy_plus,length+0.02);
			Line_plusStdDev->SetLineColor(i);
			Line_plusStdDev->SetLineWidth(4);
			Line_plusStdDev->Draw();

			TLine *Line_minusStdDev = new TLine(
				energy_minus,length+0.02,
				energy_minus,length-0.02);
			Line_minusStdDev->SetLineColor(i);
			Line_minusStdDev->SetLineWidth(4);
			Line_minusStdDev->Draw();
			alphaFit_plusStdDev[i]->Draw("same");
			alphaFit_minusStdDev[i]->Draw("same");

		}
		sprintf(dumChar,"noMaskLvEn_cutPoints.y%d.png",lengthBin);
		c1->SaveAs(dumChar);
		arrayPos++;		
	}
	gStyle->SetPalette(kRainBow);

	/////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////  creating alpha TCutC ////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////
	printf("\n\n /////////////////////// creating alpha TCutG /////////////////// \n\n");
	noMaskLvEn->GetXaxis()->SetRangeUser(0,15);
	noMaskLvEn->GetYaxis()->SetRangeUser(0,10);
	TCutG *alphaCut2[nStdDev];
	for (int i = minStdDev; i < nStdDev; ++i)
	{
		sprintf(dumChar,"alphaCut2_%dstdDev",i);
		TCutG* alphaCut2_tmp= new TCutG(dumChar,10);
		alphaCut2_tmp->SetVarX("adc");
		alphaCut2_tmp->SetVarY("length");
		alphaCut2_tmp->SetLineColor(kGreen);
		alphaCut2_tmp->SetLineWidth(2);
		alphaCut2_tmp->SetFillColorAlpha(kGreen,0.25);

		int pointNum=0;
		alphaCut2_tmp->SetPoint(pointNum,0.5,alphaFit_minusStdDev[i]->Eval(0.5));pointNum++;
		for (double energy = 0.5; energy < 12; energy+=tcutStep){
			if(alphaFit_plusStdDev[i]->Eval(energy) > 7)continue;
			alphaCut2_tmp->SetPoint(pointNum,energy,alphaFit_plusStdDev[i]->Eval(energy));pointNum++;
		}
		for (double energy = 8.5; energy > 0.5; energy-=tcutStep){
			if(alphaFit_minusStdDev[i]->Eval(energy) > 7)continue;
			alphaCut2_tmp->SetPoint(pointNum,energy,alphaFit_minusStdDev[i]->Eval(energy));pointNum++;
		}
		alphaCut2[i] = alphaCut2_tmp;

		// noMaskLvEn->Draw("Colz");
		// alphaCut2[i]->Draw("same f");
		// sprintf(dumChar,"tcutg_noMaskLvEn_stdDev%d.png",i);
		// c1->SaveAs(dumChar);
	}

	///////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////  creating noMaskLvEn_alphas ////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////
	printf("\n\n /////////////////////// creating noMaskLvEn_alphas /////////////////// \n\n");
	TH2D* noMaskLvEn_alphas[nStdDev];
	TH2D* noMaskLvEn_frags[nStdDev];
	int counts=0;
	for (int i = minStdDev; i < nStdDev; ++i){
		sprintf(dumChar,"noMaskLvEn_alphas_%dstdDev",i);
		TH2D* noMaskLvEn_alphas_tmp = (TH2D*)noMaskLvEn->Clone(dumChar);
		sprintf(dumChar,"noMaskLvEn_frags_%dstdDev",i);
		TH2D* noMaskLvEn_frags_tmp = (TH2D*)noMaskLvEn->Clone(dumChar);
		for (int energyBin = 0; energyBin < 4000; ++energyBin){
			for (int lengthBin = 0; lengthBin < 1000; ++lengthBin){
				double energy=energyBin*enCal;
				double length=lengthBin/(double)100;
				counts=noMaskLvEn->GetBinContent(energyBin,lengthBin);
				noMaskLvEn_alphas_tmp->SetBinContent(energyBin,lengthBin,0);
				noMaskLvEn_frags_tmp->SetBinContent(energyBin,lengthBin,0);
				if (alphaCut2[i]->IsInside(energy,length))
					noMaskLvEn_alphas_tmp->SetBinContent(energyBin,lengthBin,counts);
				if (!(alphaCut2[i]->IsInside(energy,length))&&length<1.7&&energy>3)
					noMaskLvEn_frags_tmp->SetBinContent(energyBin,lengthBin,counts);
				noMaskLvEn_alphas[i]=noMaskLvEn_alphas_tmp;
				noMaskLvEn_frags[i]=noMaskLvEn_frags_tmp;
			}
		}
		// noMaskLvEn_alphas[i]->Draw("colz");
		// alphaCut2[i]->Draw("same f");
		// sprintf(dumChar,"noMaskLvEn_alphas_stdDev%d.png",i);
		// c1->SaveAs(dumChar);

		// noMaskLvEn_frags[i]->Draw("colz");
		// alphaCut2[i]->Draw("same f");
		// sprintf(dumChar,"noMaskLvEn_frags_stdDev%d.png",i);
		// c1->SaveAs(dumChar);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////// creating noMaskLvEn_alphas_meanShifted //////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////
	printf("\n\n /////////////////////// creating noMaskLvEn_alphas_meanShifted /////////////////// \n\n");
	c1->SetLogz(1);c1->Update();
	TH2D* noMaskLvEn_alphas_meanShifted[nStdDev];
	TH1D* lengthProj_alphas_meanShifted[nStdDev];
	int meanShift[700];
	for (int i = minStdDev; i < nStdDev; ++i)
	{
		sprintf(dumChar,"noMaskLvEn_alphas_meanShifted_tmp_stdDev%d",i);
		TH2D* noMaskLvEn_alphas_meanShifted_tmp = new TH2D(dumChar,"",700,0,7,200,-100*enCal,100*enCal);
		for (int lengthBin = 0; lengthBin < 700; ++lengthBin)
		{
			c1->SetLogz(0);
			c1->SetLogy(0);
			sprintf(dumChar,"px_ybin%d",lengthBin);
			TH1D *px = noMaskLvEn_alphas[i]->ProjectionX(dumChar,lengthBin,lengthBin);
			// px->Draw();
			// sprintf(dumChar,"px_noMaskLvEn_alphas_stdDev%d_lengthbin%d.png",i,lengthBin);
			// c1->SaveAs(dumChar);
			// px->SetMaximum(1000);
			if (i==minStdDev)
				meanShift[lengthBin]=px->FindBin(px->GetMean());

			int alphaStartBin=px->FindBin(alphaFit_minusStdDev[i]->GetX(lengthBin/(double)100));
			int alphaStopBin=px->FindBin(alphaFit_plusStdDev[i]->GetX(lengthBin/(double)100));
			int alphaShift = (alphaStartBin+alphaStopBin)/2;
			for (int i = alphaStartBin; i < alphaStopBin; ++i)
				noMaskLvEn_alphas_meanShifted_tmp->SetBinContent(lengthBin,i+100-meanShift[lengthBin],px->GetBinContent(i));
				if (i==alphaStartBin||i==alphaStartBin)
					noMaskLvEn_alphas_meanShifted_tmp->SetBinContent(lengthBin,i,3000);


		}
		noMaskLvEn_alphas_meanShifted[i]=noMaskLvEn_alphas_meanShifted_tmp;
		TH1D* lengthProj_alphas_meanShifted_tmp = noMaskLvEn_alphas_meanShifted[i]->ProjectionX("lengthProj_alphas_meanShifted");


		lengthProj_alphas_meanShifted[i] = lengthProj_alphas_meanShifted_tmp;
		c1->SetLogy(1);c1->Update();
		lengthProj_alphas_meanShifted[i]->Draw();
		lengthProj_alphas_meanShifted[i]->GetXaxis()->SetRangeUser(0,7);
		lengthProj_alphas_meanShifted[i]->GetXaxis()->SetTitle("length [cm]");		
		sprintf(dumChar,"lengthProj_alphas_meanShifted_stdDev%d.png",i);
		c1->SaveAs(dumChar);
		c1->SetLogy(0);c1->Update();

		c1->SetLogz(1);c1->Update();
		noMaskLvEn_alphas_meanShifted[i]->Draw("colz");
		noMaskLvEn_alphas_meanShifted[i]->GetXaxis()->SetRangeUser(0,7);
		noMaskLvEn_alphas_meanShifted[i]->GetXaxis()->SetTitle("length [cm]");
		noMaskLvEn_alphas_meanShifted[i]->GetYaxis()->SetRangeUser(-80,80);
		noMaskLvEn_alphas_meanShifted[i]->GetYaxis()->SetTitle("mean shifted energy [MeV]");
		sprintf(dumChar,"noMaskLvEn_alphas_meanShifted_stdDev%d.png",i);
		c1->SaveAs(dumChar);
		c1->SetLogz(0);c1->Update();
	}

	////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////  creating frag TCutG ////////////////////////////
	////////////////////////////////////////////////////////////////////////////////
	printf("\n\n /////////////////////// creating frag TCutG /////////////////// \n\n");
	TCutG *fragCut2[nStdDev];
	TF1* frag_lengthline = new TF1("frag_lengthline","[1]*x+[0]");
	frag_lengthline->SetParameter(0,1.1357142857);
	frag_lengthline->SetParameter(1,0.01428571429);
	for (int i = minStdDev; i < nStdDev; ++i)
	{
		sprintf(dumChar,"fragCut_%dstdDev",i);
		TCutG *fragCut2_tmp = new TCutG(dumChar,4);
		fragCut2_tmp->SetVarX("adc");
		fragCut2_tmp->SetVarY("length");
		fragCut2_tmp->SetLineColor(kViolet);
		fragCut2_tmp->SetLineWidth(2);
		fragCut2_tmp->SetFillColorAlpha(kViolet,0.15);

		int pointNum=0;
		fragCut2_tmp->SetPoint(pointNum,150,0.05);pointNum++;
		fragCut2_tmp->SetPoint(pointNum,1.6,0.05);pointNum++;
		double lastEnergy=0;
		for (double energy = 1.6; energy < 4; energy+=tcutStep){

			if (alphaFit_plusStdDev[i]->Eval(energy)>frag_lengthline->Eval(energy))continue;
			fragCut2_tmp->SetPoint(pointNum,energy,alphaFit_plusStdDev[i]->Eval(energy));pointNum++;
			lastEnergy=energy;
		}
		fragCut2_tmp->SetPoint(pointNum,lastEnergy,frag_lengthline->Eval(lastEnergy));pointNum++;
		fragCut2_tmp->SetPoint(pointNum,15,2.35);pointNum++;
		fragCut2_tmp->SetPoint(pointNum,71,3.15);pointNum++;
		fragCut2_tmp->SetPoint(pointNum,150,3.65);pointNum++;
		fragCut2_tmp->SetPoint(pointNum,150,0.05);pointNum++;
		fragCut2[i] = fragCut2_tmp;
	}

	///////////////////////////////////////////////////////////////////////////
	////////////////////////////////  plotting TCutGs  ////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	printf("\n\n /////////////////////// plots TCutGs /////////////////// \n\n");
	c1->SetLogz(1);
	for (int i = minStdDev; i < nStdDev; ++i)
	{
		noMaskLvEn->GetXaxis()->SetRangeUser(0,15);
		noMaskLvEn->GetYaxis()->SetRangeUser(0,8);
		noMaskLvEn->Draw("Colz");
		fragCut2[i]->Draw("same f");
		fragCut2[i]->Draw("same");
		alphaCut2[i]->Draw("same f");
		alphaCut2[i]->Draw("same");
		sprintf(dumChar,"bothCuts_noMaskLvEn_stdDev%d.png",i);
		c1->SaveAs(dumChar);

		noMaskLvEn->GetXaxis()->SetRangeUser(0.5,5);
		noMaskLvEn->GetYaxis()->SetRangeUser(0.5,2);
		c1->SetLogz(0);c1->Update();
		sprintf(dumChar,"bothCuts_noMaskLvEn_linearZoom_stdDev%d.png",i);
		c1->SaveAs(dumChar);
		c1->SetLogz(1);c1->Update();

		noMaskLvEn->GetXaxis()->SetRangeUser(0.4,180);
		noMaskLvEn->GetYaxis()->SetRangeUser(0,8);
		noMaskLvEn->Draw("Colz");
		c1->SetLogx(1);c1->Update();
		fragCut2[i]->Draw("same f");
		fragCut2[i]->Draw("same");
		alphaCut2[i]->Draw("same f");
		alphaCut2[i]->Draw("same");
		sprintf(dumChar,"bothCuts_noMaskLvEn_logEnergy_stdDev%d.png",i);
		c1->SaveAs(dumChar);
		c1->SetLogx(0);c1->Update();
	}

	TFile* outfile = new TFile("$cft/buildAlphaRidgeCut/pidCuts_2.root","recreate");
	outfile->cd();
	for (int i = minStdDev; i < nStdDev; ++i)
	{
		alphaCut2[i]->Write();
		fragCut2[i]->Write();
		alphaFit_plusStdDev[i]->Write();
		noMaskLvEn_alphas[i]->Write();
		noMaskLvEn_frags[i]->Write();
		noMaskLvEn_alphas_meanShifted[i]->Write();
	}

	outfile->Close();
}
