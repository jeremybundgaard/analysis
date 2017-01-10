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

void rotateToExpoBasis() {


	TFile* noMaskFile = new TFile("$trees/cf252.noMask2.nEv500000.trees.root");
	TTree* noMaskTracks = (TTree*)noMaskFile->Get("tracks");
	TH2D * noMaskLvEn = new TH2D("noMaskLvEn","noMaskLvEn",4000,0,168.6,1000,0,10);
	
	noMaskLvEn->GetXaxis()->SetRangeUser(0,10);
	noMaskLvEn->GetYaxis()->SetRangeUser(0,10);
	noMaskLvEn->GetXaxis()->SetTitle("Track Energy [MeV]");
	noMaskLvEn->GetXaxis()->CenterTitle();
	noMaskLvEn->GetYaxis()->SetTitle("Track Length [cm]");
	noMaskLvEn->GetYaxis()->CenterTitle();
	TH2D * noMaskLvEnRotExpo = new TH2D("noMaskLvEnRotExpo","noMaskLvEnRotExpo",4000,0,168.6,1000,0,10);
	noMaskLvEnRotExpo->GetXaxis()->SetRangeUser(0,10);
	TH2D * noMaskLvEnRotTheta = new TH2D("noMaskLvEnRotTheta","noMaskLvEnRotTheta",4000,0,168.6,1000,0,10);
	noMaskLvEnRotTheta->GetXaxis()->SetRangeUser(0,10);


	// TFile* noMaskFile = new TFile("$trees/cf252.noMask1.trees.root");
	// TCutG *fragCut1 = new TCutG("fragCut1",12);

	TCutG *fragCut1 = new TCutG("fragCut1",12);
	fragCut1->SetVarX("adc");
	fragCut1->SetVarY("length");
	fragCut1->SetTitle("Graph");
	fragCut1->SetFillColor(1);

	fragCut1->SetLineColor(kViolet);
	fragCut1->SetLineWidth(3);
	fragCut1->SetPoint(0,2.10961,0.931008);
	fragCut1->SetPoint(1,15,2.35);
	fragCut1->SetPoint(2,71,3.15);
	fragCut1->SetPoint(3,150,3.65);
	fragCut1->SetPoint(4,150,0.5);
	fragCut1->SetPoint(5,1.50961,0.5);
	fragCut1->SetPoint(6,1.50961,0.5);
	fragCut1->SetPoint(7,1.60961,0.569992);
	fragCut1->SetPoint(8,1.70961,0.640711);
	fragCut1->SetPoint(9,1.80961,0.712165);
	fragCut1->SetPoint(10,1.90961,0.78436);
	fragCut1->SetPoint(11,2.00961,0.857305);
	fragCut1->SetPoint(12,2.10961,0.931008);

	TCanvas *c1 = new TCanvas("c1","c1",1000,700);
	gStyle->SetOptStat(0);

	noMaskTracks->Draw(
	"length:adc*168.6/40000>>noMaskLvEn",
	"((start.x()*start.x()+start.y()*start.y())<2)&&!(-1<direction.Phi()&&direction.Phi()<0)&&((-0.2>direction.CosTheta()&&direction.CosTheta()>-0.8)||(0.2<direction.CosTheta()&&direction.CosTheta()<0.8))&&run>100001856&&run!=100001870&&nDigits>100",
	"colz");


	double par0 =0.14986;
	double par1 =0.111091;
	double par2 =3.09982;
	double par3 =-3.71542;

	TF1 *fitLvEn = new TF1("fitLvEn","[3] + [2]*TMath::Exp( [1]*x + [0] )",1,5);
	fitLvEn->SetParameter(0,par0);
	fitLvEn->SetParameter(1,par1);
	fitLvEn->SetParameter(2,par2);
	fitLvEn->SetParameter(3,par3);

	TF1 *fitdLdEn = new TF1("fitdLdEn","[2]*[1]*TMath::Exp( [1]*x + [0] )",1,5);
	fitdLdEn->SetParameter(0,par0);
	fitdLdEn->SetParameter(1,par1);
	fitdLdEn->SetParameter(2,par2);

	TF1 *thetaRotationOfEn = new TF1("thetaRotationOfEn","TMath::ATan([2]*[1]*TMath::Exp( [1]*x + [0] ))",1,5);
	thetaRotationOfEn->SetParameter(0,par0);
	thetaRotationOfEn->SetParameter(1,par1);
	thetaRotationOfEn->SetParameter(2,par2);

	TF1 *rot_fitLvEn = new TF1("rot_fitLvEn","",1,5);
	fitLvEn->SetParameter(0,par0);
	fitLvEn->SetParameter(1,par1);
	fitLvEn->SetParameter(2,par2);
	fitLvEn->SetParameter(3,par3);

	char plotname[234];

	double en=0,len=0,enRotExpo=0,lenRotExpo=0,enRotTheta=0,lenRotTheta=0;
	int counts=0;
	double thetaShift = 10*TMath::Pi()/180;
	double enCal=16.86/400;


	for (int xBin = 0; xBin < 4000; ++xBin)
	{
		for (int yBin = 0; yBin < 1000; ++yBin)
		{

			en=xBin*enCal;
			len=yBin/(double)100;
			if (yBin < fitLvEn->Eval(en)*100 - 1) continue;

			noMaskLvEn->SetBinContent(xBin,fitLvEn->Eval(en)*100,10000);
			counts=noMaskLvEn->GetBinContent(xBin,yBin);
			enRotExpo=	en*TMath::Cos(thetaRotationOfEn->Eval(en))
					+len*TMath::Sin(thetaRotationOfEn->Eval(en));		
			lenRotExpo=-en*TMath::Sin(thetaRotationOfEn->Eval(en))
					+len*TMath::Cos(thetaRotationOfEn->Eval(en));
			noMaskLvEnRotExpo->Fill(enRotExpo,lenRotExpo+0.5*fitLvEn->Eval(en)+1,counts);

		}
	}

	for (int xBin = 0; xBin < 4000; ++xBin)
	{
		for (int yBin = 0; yBin < 1000; ++yBin)
		{
			counts=noMaskLvEnRotExpo->GetBinContent(xBin,yBin);

			enRotTheta=	xBin*TMath::Cos(thetaShift)
						+yBin*TMath::Sin(thetaShift);		
			lenRotTheta=-xBin*TMath::Sin(thetaShift)
						+yBin*TMath::Cos(thetaShift);
			noMaskLvEnRotTheta->SetBinContent(enRotTheta,lenRotTheta,counts);

		}
	}


	TFile* out = new TFile("rot_noMaskLvEn.root","recreate");
	out->cd();
	c1->SetLogz();

	noMaskLvEn->Draw("colz");
	fitLvEn->Draw("same");
	c1->SetLogz();
	c1->SaveAs("noMaskLvEn.png");

	noMaskLvEnRotExpo->Write();
	noMaskLvEnRotExpo->Draw("colz");
	c1->SaveAs("noMaskLvEnRotExpo.png");

	noMaskLvEnRotTheta->Draw("colz");
	noMaskLvEnRotTheta->Write();
	c1->SaveAs("noMaskLvEnRotTheta.png");


}