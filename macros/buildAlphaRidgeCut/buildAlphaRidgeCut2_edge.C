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

void buildAlphaRidgeCut2_edge() {

	TFile* noMaskFile = new TFile("$trees/cf252.noMask2.nEv500000.trees.root");
	// TFile* noMaskFile = new TFile("$trees/cf252.noMask2.trees.root");
	TTree* noMaskTracks = (TTree*)noMaskFile->Get("tracks");
	TH2D * noMaskLvEn = new TH2D("noMaskLvEn","noMaskLvEn",4000,0,168.6,1000,0,10);
	TH2D * noMaskLvEn_alphas = (TH2D*)noMaskLvEn->Clone("noMaskLvEn_alphas");
	TH2D * noMaskLvEn_alphas_meanShifted = new TH2D("noMaskLvEn_alphas_meanShifted","",200,-100,100,500,0,5);
	noMaskLvEn->GetXaxis()->SetRangeUser(0,10);
	noMaskLvEn->GetYaxis()->SetRangeUser(0,10);
	noMaskLvEn->GetXaxis()->SetTitle("Track Energy [MeV]");
	noMaskLvEn->GetXaxis()->CenterTitle();
	noMaskLvEn->GetYaxis()->SetTitle("Track Length [cm]");
	noMaskLvEn->GetYaxis()->CenterTitle();

	TCanvas *c1 = new TCanvas("c1","c1",1000,700);
	char c1PlotName[234];
	gStyle->SetOptStat(0);
	gStyle->SetPalette(109);
	gStyle->SetNumberContours(999);

	noMaskTracks->Draw(
	"length:adc*168.6/40000>>noMaskLvEn",
	"!(-1<direction.Phi()&&direction.Phi()<0)&&((-0.2>direction.CosTheta()&&direction.CosTheta()>-0.8)||(0.2<direction.CosTheta()&&direction.CosTheta()<0.8))&&run>100001856&&run!=100001870&&nDigits>60",
	"colz");

	Double_t xCut_plus[50];
	Double_t yCut_plus[50];
	Double_t xCut_minus[50];
	Double_t yCut_minus[50];
	char projname[123];
	int xBuffer = 20;

	int arrayPos=0;
	for (int lbinStep = 150; lbinStep < 400; lbinStep+=5){
		TH1D *px = noMaskLvEn->ProjectionX("px", lbinStep, lbinStep);
		px->GetXaxis()->SetRangeUser(1,7);
		px->GetYaxis()->SetRangeUser(1,10);

		/* define fit points via edge finding */
		int xCut_plusBin = px->FindLastBinAbove(10)+xBuffer;
		xCut_plus[arrayPos] = px->GetBinCenter(xCut_plusBin);
		yCut_plus[arrayPos] = lbinStep/(double)100;
		int xCut_minusBin = px->FindFirstBinAbove(10)-xBuffer;
		xCut_minus[arrayPos] = px->GetBinCenter(xCut_minusBin);
		yCut_minus[arrayPos] = lbinStep/(double)100;


		std::cout << "xCut_plus , yCut_plus"<<'\t'<<xCut_plus[arrayPos] <<" , "<<yCut_plus[arrayPos] <<'\t'
				<<"arrayPos="<<arrayPos<<'\t'<<"lbinStep = "<<lbinStep<< std::endl;
		std::cout << "xCut_minus , yCut_minus"<<'\t'<<xCut_minus[arrayPos] <<" , "<<yCut_minus[arrayPos] <<'\t'
				<<"arrayPos="<<arrayPos<<'\t'<<"lbinStep = "<<lbinStep<< std::endl;
		arrayPos++;
	}

	c1->SetLogy(0);
	TGraph *g_plus = new TGraph((sizeof(xCut_plus) / sizeof(Double_t)), xCut_plus, yCut_plus);
	TF1 *fitLvEn_plus = new TF1("fitLvEn_plus","[3] + [2]*TMath::Exp( [1]*x + [0] )",1,10);
	TGraph *g_minus = new TGraph((sizeof(xCut_minus) / sizeof(Double_t)), xCut_minus, yCut_minus);
	TF1 *fitLvEn_minus = new TF1("fitLvEn_minus","[3] + [2]*TMath::Exp( [1]*x + [0] )",1,10);
	fitLvEn_plus->SetLineWidth(2);
	fitLvEn_plus->SetLineColor(kMagenta);
	g_plus->Fit(fitLvEn_plus);
	fitLvEn_minus->SetLineWidth(2);
	fitLvEn_minus->SetLineColor(kMagenta);
	g_minus->Fit(fitLvEn_minus);

	noMaskLvEn->SetTitle(fitLvEn_plus->GetTitle());
	noMaskLvEn->Draw("Colz");
	fitLvEn_plus->DrawF1(0,10,"same");
	fitLvEn_minus->DrawF1(0,10,"same");
	sprintf(projname,"alphaRidgeFit.LvEn.png");
	c1->SaveAs(projname);

	noMaskLvEn->GetXaxis()->SetRangeUser(0,10);
	noMaskLvEn->GetYaxis()->SetRangeUser(0,10);
	noMaskLvEn->Draw("Colz");
	fitLvEn_plus->DrawF1(0,10,"same");
	fitLvEn_minus->DrawF1(0,10,"same");
	sprintf(projname,"alphaRidgeFit.zoom.LvEn.png");
	c1->SaveAs(projname);
	c1->SetLogz(1);
	noMaskLvEn->Draw("Colz");
	fitLvEn_plus->DrawF1(0,10,"same");
	fitLvEn_minus->DrawF1(0,10,"same");
	sprintf(projname,"alphaRidgeFit.zoom.log.LvEn.png");
	c1->SaveAs(projname);
	noMaskLvEn->GetXaxis()->SetRangeUser(0,10);
	noMaskLvEn->GetYaxis()->SetRangeUser(0,10);

	// show projection of alpha ridge
	arrayPos=0;
	for (int lbinStep = 150; lbinStep < 400; lbinStep+=5){
		c1->SetLogz(0);
		c1->SetLogy(0);
		TH1D *px = noMaskLvEn->ProjectionX("px", lbinStep, lbinStep);
		px->SetMaximum(1000);

		TLine *startLine_plus = new TLine(
			px->GetBinCenter(px->FindLastBinAbove(10)),
			0,
			px->GetBinCenter(px->FindLastBinAbove(10)),
			10);
		startLine_plus->SetLineColor(kGreen);
		startLine_plus->SetLineWidth(3);

		TLine *startLine_minus = new TLine(
			px->GetBinCenter(px->FindFirstBinAbove(10)),
			0,
			px->GetBinCenter(px->FindFirstBinAbove(10)),
			10);
		startLine_minus->SetLineColor(kGreen);
		startLine_minus->SetLineWidth(3);

		TLine *linePlusBuffer = new TLine(
			xCut_plus[arrayPos],
			0,
			xCut_plus[arrayPos],
			10);
		linePlusBuffer->SetLineColor(kRed);
		linePlusBuffer->SetLineWidth(3);

		TLine *lineMinusBuffer = new TLine(
			xCut_minus[arrayPos],
			0,
			xCut_minus[arrayPos],
			10);
		lineMinusBuffer->SetLineColor(kRed);
		lineMinusBuffer->SetLineWidth(3);

		sprintf(projname,"projx.LvEn.ybin%d.zoom.png",lbinStep);
		px->SetTitle(projname);
		px->Draw();
		startLine_plus->Draw("same");
		linePlusBuffer->Draw("same");
		startLine_minus->Draw("same");
		lineMinusBuffer->Draw("same");
		c1->SetLogy();
		c1->SetGridx();
		c1->SetGridy();
		c1->SaveAs(projname);
		arrayPos++;
	}

	noMaskLvEn->GetXaxis()->SetRangeUser(0,10);
	noMaskLvEn->GetYaxis()->SetRangeUser(0,10);
	arrayPos=0;

	for (int lbinStep = 150; lbinStep < 400; lbinStep+=5){
		c1->SetLogz(1);
		c1->SetLogy(0);
		TH1D *px = noMaskLvEn->ProjectionX("px", lbinStep, lbinStep);

		TLine *startLine_plus = new TLine(
			px->GetBinCenter(px->FindLastBinAbove(10)),yCut_plus[arrayPos]-0.05,
			px->GetBinCenter(px->FindLastBinAbove(10)),yCut_plus[arrayPos]+0.05);
		startLine_plus->SetLineColor(kGreen);
		startLine_plus->SetLineWidth(5);

		TLine *startLine_minus = new TLine(
			px->GetBinCenter(px->FindFirstBinAbove(10)),yCut_plus[arrayPos]-0.05,
			px->GetBinCenter(px->FindFirstBinAbove(10)),yCut_plus[arrayPos]+0.05);
		startLine_minus->SetLineColor(kGreen);
		startLine_minus->SetLineWidth(5);

		TLine *linePlusBuffer = new TLine(
			xCut_plus[arrayPos],yCut_plus[arrayPos]-0.05,
			xCut_plus[arrayPos],yCut_plus[arrayPos]+0.05);
		linePlusBuffer->SetLineColor(kRed);
		linePlusBuffer->SetLineWidth(5);
		TLine *lineMinusBuffer = new TLine(
			xCut_minus[arrayPos],yCut_minus[arrayPos]-0.05,
			xCut_minus[arrayPos],yCut_minus[arrayPos]+0.05);
		lineMinusBuffer->SetLineColor(kRed);
		lineMinusBuffer->SetLineWidth(5);

		noMaskLvEn->Draw("Colz");
		fitLvEn_plus->Draw("same");
		fitLvEn_minus->Draw("same");
		startLine_plus->Draw("same");
		linePlusBuffer->Draw("same");
		startLine_minus->Draw("same");
		lineMinusBuffer->Draw("same");
		sprintf(projname,"LvEn.y%d.zoom.png",lbinStep);
		c1->SaveAs(projname);
		arrayPos++;
	}

	TCutG *alphaCut1 = new TCutG("alphaCut1",7);
	alphaCut1->SetVarX("adc");
	alphaCut1->SetVarY("length");
	alphaCut1->SetLineColor(kGreen);
	alphaCut1->SetLineWidth(3);

	alphaCut1->SetPoint(0,0.5,fitLvEn_minus->Eval(0.5));
	alphaCut1->SetPoint(1,1.0,fitLvEn_plus->Eval(1.0));
	alphaCut1->SetPoint(2,1.0,fitLvEn_plus->Eval(1.0));
	alphaCut1->SetPoint(3,1.5,fitLvEn_plus->Eval(1.5));
	alphaCut1->SetPoint(4,2.0,fitLvEn_plus->Eval(2.0));
	alphaCut1->SetPoint(5,2.5,fitLvEn_plus->Eval(2.5));
	alphaCut1->SetPoint(6,3.0,fitLvEn_plus->Eval(3.0));
	alphaCut1->SetPoint(7,3.5,fitLvEn_plus->Eval(3.5));
	alphaCut1->SetPoint(8,4.0,fitLvEn_plus->Eval(4.0));
	alphaCut1->SetPoint(9,4.5,fitLvEn_plus->Eval(4.5));
	alphaCut1->SetPoint(10,5.0,fitLvEn_plus->Eval(5.0));
	alphaCut1->SetPoint(11,5.5,fitLvEn_plus->Eval(5.5));
	alphaCut1->SetPoint(12,6.0,fitLvEn_plus->Eval(6.0));
	alphaCut1->SetPoint(13,6.5,fitLvEn_plus->Eval(6.5));
	alphaCut1->SetPoint(14,7.0,fitLvEn_plus->Eval(7.0));
	alphaCut1->SetPoint(15,7.5,fitLvEn_plus->Eval(7.5));
	alphaCut1->SetPoint(16,8.0,fitLvEn_plus->Eval(8.0));
	alphaCut1->SetPoint(17,8.5,fitLvEn_plus->Eval(8.5));
	alphaCut1->SetPoint(18,9.0,fitLvEn_plus->Eval(9.0));
	alphaCut1->SetPoint(19,9.5,fitLvEn_plus->Eval(9.5));
	alphaCut1->SetPoint(20,6.5,fitLvEn_minus->Eval(6.5));
	alphaCut1->SetPoint(21,6.0,fitLvEn_minus->Eval(6.0));
	alphaCut1->SetPoint(22,5.5,fitLvEn_minus->Eval(5.5));
	alphaCut1->SetPoint(23,5.0,fitLvEn_minus->Eval(5.0));
	alphaCut1->SetPoint(24,4.5,fitLvEn_minus->Eval(4.5));
	alphaCut1->SetPoint(25,4.0,fitLvEn_minus->Eval(4.0));
	alphaCut1->SetPoint(26,3.5,fitLvEn_minus->Eval(3.5));
	alphaCut1->SetPoint(27,3.0,fitLvEn_minus->Eval(3.0));
	alphaCut1->SetPoint(28,2.5,fitLvEn_minus->Eval(2.5));
	alphaCut1->SetPoint(29,2.0,fitLvEn_minus->Eval(2.0));
	alphaCut1->SetPoint(30,1.5,fitLvEn_minus->Eval(1.5));
	alphaCut1->SetPoint(31,1.0,fitLvEn_minus->Eval(1.0));
	alphaCut1->SetPoint(32,0.5,fitLvEn_minus->Eval(0.5));

	double enCal=168.6/4000;
	for (int adcbin = 0; adcbin < 4000; ++adcbin)
		for (int lenbin = 0; lenbin < 1000; ++lenbin)
		{
			double energy=adcbin*enCal;
			double length=lenbin/(double)100;
			if (alphaCut1->IsInside(energy,length))
				noMaskLvEn_alphas->SetBinContent(adcbin,lenbin,noMaskLvEn->GetBinContent(adcbin,lenbin));
		}


	for (int lbinStep = 0; lbinStep < 700; ++lbinStep)
	{
		c1->SetLogz(0);
		c1->SetLogy(0);
		sprintf(projname,"px_ybin%d",lbinStep);
		TH1D *px = noMaskLvEn_alphas->ProjectionX(projname,lbinStep,lbinStep);
		px->SetMaximum(1000);

		int meanShift=px->FindBin(px->GetMean());
		int alphaStartBin=px->FindBin(fitLvEn_minus->GetX(lbinStep/(double)100));
		int alphaStopBin=px->FindBin(fitLvEn_plus->GetX(lbinStep/(double)100));
		int alphaShift = (alphaStartBin+alphaStopBin)/2;
		for (int i = alphaStartBin; i < alphaStopBin; ++i)
			noMaskLvEn_alphas_meanShifted->SetBinContent(i+100-meanShift,lbinStep,px->GetBinContent(i));

	}

	TH1D* alphas_LvEn_1d = noMaskLvEn_alphas_meanShifted->ProjectionY("alphas_LvEn_1d");
	alphas_LvEn_1d->Draw();
	c1->SaveAs("alphas_LvEn_1d.png");

	c1->SetLogx(1);
	c1->SetLogz(1);
	noMaskLvEn->Draw("colz");
	c1->SaveAs("noMaskLvEn.png");

	c1->SetLogx(1);
	c1->SetLogz(1);
	noMaskLvEn_alphas->Draw("colz");
	c1->SaveAs("noMaskLvEn_alphas.png");

	c1->SetLogx(0);
	c1->SetLogz(1);
	noMaskLvEn_alphas_meanShifted->Draw("colz");
	c1->SaveAs("noMaskLvEn_alphas_meanShifted.png");


	double_t alphaRidgeFitStartY = 0.5;
	double_t alphaRidgeFitStartX = fitLvEn_plus->GetX(alphaRidgeFitStartY);
	double_t alphaRidgeFitStopY = 1.1;
	double_t alphaRidgeFitStopX = fitLvEn_plus->GetX(alphaRidgeFitStopY);


	TCutG *fragCut1 = new TCutG("fragCut1",7);
	fragCut1->SetVarX("adc");
	fragCut1->SetVarY("length");
	fragCut1->SetLineColor(kViolet);
	fragCut1->SetLineWidth(3);
	fragCut1->GetXaxis()->SetRangeUser(1,3);
	fragCut1->GetYaxis()->SetRangeUser(0,1);
	fragCut1->SetPoint(1, 15,1.95+0.4);
	fragCut1->SetPoint(2, 71,2.75+0.4);
	fragCut1->SetPoint(3, 150,3.25+0.4);
	fragCut1->SetPoint(4, 150,0.5 );
	fragCut1->SetPoint(5, alphaRidgeFitStartX,alphaRidgeFitStartY);
	fragCut1->SetPoint(6, 1.5,0.70+0.4);
	fragCut1->SetPoint(0, 1.5,0.70+0.4);

	int newCutPoint=6;
	noMaskLvEn->GetXaxis()->SetRangeUser(0,10);
	noMaskLvEn->GetYaxis()->SetRangeUser(0,10);

	for (double interpoAlphaRidge = alphaRidgeFitStartX; interpoAlphaRidge <= 2.2; interpoAlphaRidge+=0.1)
	{
		fragCut1->SetPoint(newCutPoint,interpoAlphaRidge,fitLvEn_plus->Eval(interpoAlphaRidge));
		fragCut1->SetPoint(0,interpoAlphaRidge,fitLvEn_plus->Eval(interpoAlphaRidge));
		newCutPoint++;
		noMaskLvEn->Draw("Colz");
		// fitLvEn_plus->DrawF1(alphaRidgeFitStartX-.2,alphaRidgeFitStopX+.2,"same");
		fitLvEn_plus->Draw("same");
		fragCut1->Draw("same");
		sprintf(projname,"alphaRidgeFit.zoom.log.LvEn.%0.1f.png",interpoAlphaRidge);
		c1->SetLogx(0);
		c1->SaveAs(projname);
	}


	ofstream primCutFile;
	primCutFile.open("fragCut1_primitive.C");
	fragCut1->SavePrimitive(primCutFile,"");

	TFile* outfile = new TFile("$cft/buildAlphaRidgeCut/fragCut1.root","recreate");

	noMaskLvEn->SetTitle(fitLvEn_plus->GetTitle());
	noMaskLvEn->GetXaxis()->SetRangeUser(0,10);
	noMaskLvEn->GetYaxis()->SetRangeUser(0,10);	
	noMaskLvEn->Draw("Colz");
	fitLvEn_plus->DrawF1(0,10,"same");
	fitLvEn_minus->DrawF1(0,10,"same");
	fragCut1->Draw("same");
	alphaCut1->Draw("same");
	sprintf(projname,"alphaRidgeFit.plusFragCut.LvEn.png");
	c1->SaveAs(projname);

	noMaskLvEn->GetXaxis()->SetRangeUser(0,150);
	noMaskLvEn->GetYaxis()->SetRangeUser(0,10);	
	noMaskLvEn->Draw("Colz");
	fitLvEn_plus->DrawF1(0,10,"same");
	fitLvEn_minus->DrawF1(0,10,"same");
	fragCut1->Draw("same");
	alphaCut1->Draw("same");
	sprintf(projname,"FragCut.LvEn.png");
	c1->SaveAs(projname);

	noMaskLvEn->GetXaxis()->SetRangeUser(0.4,150);
	noMaskLvEn->GetYaxis()->SetRangeUser(0,10);
	noMaskLvEn->Draw("Colz");
	fitLvEn_plus->DrawF1(0,10,"same");
	fitLvEn_minus->DrawF1(0,10,"same");
	fragCut1->Draw("same");
	alphaCut1->Draw("same");
	c1->SetLogx(1);
	sprintf(projname,"FragCut.LvEn.logx.png");
	c1->SaveAs(projname);

	std::cout<< "alphaRidgeFitStartY = "<<alphaRidgeFitStartY<<std::endl;
	std::cout<< "alphaRidgeFitStartX = "<<alphaRidgeFitStartX<<std::endl;
	std::cout<< "alphaRidgeFitStopY = "<<alphaRidgeFitStopY<<std::endl;
	std::cout<< "alphaRidgeFitStopX = "<<alphaRidgeFitStopX<<std::endl;

	outfile->cd();
	fragCut1->Write();
	alphaCut1->Write();
	fitLvEn_plus->Write();
	noMaskLvEn_alphas->Write();
	noMaskLvEn_alphas_meanShifted->Write();

	outfile->Close();
}
