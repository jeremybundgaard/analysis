#include "THStack.h"
#include <climits>
#include <vector>
#include "TROOT.h"
#include "TRint.h"
#include "MsgLog.h"
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
#include "TText.h"
#include "NiffteGeometryMap.h"
#include "NifftePlotUtilities.h"

#include <math.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>


void cftAnaPlots(const int preamp, const char* recoType) {

char noMaskFileName[234];
char cftFileName[234];

TCutG *fragCut = new TCutG("fragCut",8);
fragCut->SetLineColor(kViolet);
fragCut->SetLineWidth(3);

TPolyLine* fragPoly = new TPolyLine(13,"");
fragPoly->SetFillColorAlpha(kViolet,0.25);
fragPoly->SetLineColor(kViolet);
fragPoly->SetLineWidth(3);

char noMaskCut[234];
char cftCut[234];
char fitCut[123];
char noMaskRunCut[123];
char cftRunCut[123];
char azCut[123];



if (preamp==1)
{

	sprintf(noMaskRunCut,"run > 100001856 && run !=100001870");

	if (!(strcmp(recoType,"hk"))){
		sprintf(fitCut,"fitType==5");

		sprintf(noMaskFileName,"$trees/hk.cfNoMask.1stPreamp.trees.root");
		sprintf(cftFileName,"$trees/hk.cfCFT.1stPreamp.trees.root");

		fragCut->SetPoint(0,2.71991,1.03077);
		fragCut->SetPoint(1,15,1.9);
		fragCut->SetPoint(2,35,2.35);
		fragCut->SetPoint(3,71,3.15);
		fragCut->SetPoint(4,150,3.65);
		fragCut->SetPoint(5,150,1.65);
		fragCut->SetPoint(6,2.01991,0.5);
		fragCut->SetPoint(7,2.01991,0.5);
		fragCut->SetPoint(8,2.11991,0.573987);
		fragCut->SetPoint(9,2.21991,0.648579);
		fragCut->SetPoint(10,2.31991,0.723779);
		fragCut->SetPoint(11,2.41991,0.799594);
		fragCut->SetPoint(12,2.51991,0.876028);
		fragCut->SetPoint(13,2.61991,0.953086);
		fragCut->SetPoint(14,2.71991,1.03077);

		fragPoly->SetNextPoint(2.71991,1.03077);
		fragPoly->SetNextPoint(15,1.9);
		fragPoly->SetNextPoint(35,2.35);
		fragPoly->SetNextPoint(71,3.15);
		fragPoly->SetNextPoint(150,3.65);
		fragPoly->SetNextPoint(150,1.65);
		fragPoly->SetNextPoint(2.01991,0.5);
		fragPoly->SetNextPoint(2.01991,0.5);
		fragPoly->SetNextPoint(2.11991,0.573987);
		fragPoly->SetNextPoint(2.21991,0.648579);
		fragPoly->SetNextPoint(2.31991,0.723779);
		fragPoly->SetNextPoint(2.41991,0.799594);
		fragPoly->SetNextPoint(2.51991,0.876028);
		fragPoly->SetNextPoint(2.61991,0.953086);
		fragPoly->SetNextPoint(2.71991,1.03077);

	}
	if ( !(strcmp(recoType,"fp"))){

		sprintf(fitCut,"bestFit && trackNo < 3");
		sprintf(noMaskFileName,"$trees/fp.cfNoMask.1stPreamp.trees.root");
		sprintf(cftFileName,"$trees/fp.cfCFT.1stPreamp.trees.root");

		fragCut->SetPoint(0,2,0.856419);
		fragCut->SetPoint(1,15,1.5);
		fragCut->SetPoint(2,35,2.5);
		fragCut->SetPoint(3,60,3.25);
		fragCut->SetPoint(4,140,3.5);
		fragCut->SetPoint(5,140,1.25);
		fragCut->SetPoint(6,1,0);
		fragCut->SetPoint(7,1,0.434625);
		fragCut->SetPoint(8,1.2,0.496664);
		fragCut->SetPoint(9,1.4,0.56915);
		fragCut->SetPoint(10,1.6,0.652886);
		fragCut->SetPoint(11,1.8,0.748508);
		fragCut->SetPoint(12,2,0.856419);

		fragPoly->SetNextPoint(2,0.856419);
		fragPoly->SetNextPoint(15,1.5);
		fragPoly->SetNextPoint(35,2.5);
		fragPoly->SetNextPoint(60,3.25);
		fragPoly->SetNextPoint(140,3.5);
		fragPoly->SetNextPoint(140,1.25);
		fragPoly->SetNextPoint(1,0);
		fragPoly->SetNextPoint(1,0.434625);
		fragPoly->SetNextPoint(1.2,0.496664);
		fragPoly->SetNextPoint(1.4,0.56915);
		fragPoly->SetNextPoint(1.6,0.652886);
		fragPoly->SetNextPoint(1.8,0.748508);
		fragPoly->SetNextPoint(2,0.856419);

	}
	sprintf(noMaskCut," %s && %s ",fitCut,noMaskRunCut);
	sprintf(cftCut,"%s",fitCut);


}
else if (preamp==2)
{

	if (!(strcmp(recoType,"hk"))){
		sprintf(fitCut,"fitType==5");
		sprintf(azCut,"!(-1 < direction.Phi() && direction.Phi() < 0)");

		sprintf(noMaskFileName,"$trees/hk.cfNoMask.2ndPreamp.trees.root");
		sprintf(cftFileName,"$trees/hk.cfCFT.2ndPreamp.trees.root");

		fragCut->SetPoint(0,2.49341,0.982877);
		fragCut->SetPoint(1,15,1.9);
		fragCut->SetPoint(2,35,2.35);
		fragCut->SetPoint(3,71,3.15);
		fragCut->SetPoint(4,150,3.65);
		fragCut->SetPoint(5,150,1.65);
		fragCut->SetPoint(6,1.59341,0.5);
		fragCut->SetPoint(7,1.59341,0.5);
		fragCut->SetPoint(8,1.69341,0.55162);
		fragCut->SetPoint(9,1.79341,0.603737);
		fragCut->SetPoint(10,1.89341,0.656355);
		fragCut->SetPoint(11,1.99341,0.709481);
		fragCut->SetPoint(12,2.09341,0.763117);
		fragCut->SetPoint(13,2.19341,0.81727);
		fragCut->SetPoint(14,2.29341,0.871945);
		fragCut->SetPoint(15,2.39341,0.927145);
		fragCut->SetPoint(16,2.49341,0.982877);

		fragPoly->SetNextPoint(2.49341,0.982877);
		fragPoly->SetNextPoint(15,1.9);
		fragPoly->SetNextPoint(35,2.35);
		fragPoly->SetNextPoint(71,3.15);
		fragPoly->SetNextPoint(150,3.65);
		fragPoly->SetNextPoint(150,1.65);
		fragPoly->SetNextPoint(1.59341,0.5);
		fragPoly->SetNextPoint(1.59341,0.5);
		fragPoly->SetNextPoint(1.69341,0.55162);
		fragPoly->SetNextPoint(1.79341,0.603737);
		fragPoly->SetNextPoint(1.89341,0.656355);
		fragPoly->SetNextPoint(1.99341,0.709481);
		fragPoly->SetNextPoint(2.09341,0.763117);
		fragPoly->SetNextPoint(2.19341,0.81727);
		fragPoly->SetNextPoint(2.29341,0.871945);
		fragPoly->SetNextPoint(2.39341,0.927145);
		fragPoly->SetNextPoint(2.49341,0.982877);

	}
	if ( !(strcmp(recoType,"fp"))){
		
		sprintf(fitCut,"bestFit");
		sprintf(azCut,"direction.Phi() < 2.2");

		sprintf(noMaskFileName,"$trees/fp.cfNoMask.2ndPreamp.trees.root");
		sprintf(cftFileName,"$trees/fp.cfCFT.2ndPreamp.trees.root");

		fragCut->SetPoint(0,2,0.700327);
		fragCut->SetPoint(1,15,1.5);
		fragCut->SetPoint(2,35,2.5);
		fragCut->SetPoint(3,60,3.25);
		fragCut->SetPoint(4,140,3.5);
		fragCut->SetPoint(5,140,1.25);
		fragCut->SetPoint(6,1,0);
		fragCut->SetPoint(7,1,0.295582);
		fragCut->SetPoint(8,1.2,0.363805);
		fragCut->SetPoint(9,1.4,0.438273);
		fragCut->SetPoint(10,1.6,0.519138);
		fragCut->SetPoint(11,1.8,0.606485);
		fragCut->SetPoint(12,2,0.700327);

		fragPoly->SetNextPoint(2,0.700327);
		fragPoly->SetNextPoint(15,1.5);
		fragPoly->SetNextPoint(35,2.5);
		fragPoly->SetNextPoint(60,3.25);
		fragPoly->SetNextPoint(140,3.5);
		fragPoly->SetNextPoint(140,1.25);
		fragPoly->SetNextPoint(1,0);
		fragPoly->SetNextPoint(1,0.295582);
		fragPoly->SetNextPoint(1.2,0.363805);
		fragPoly->SetNextPoint(1.4,0.438273);
		fragPoly->SetNextPoint(1.6,0.519138);
		fragPoly->SetNextPoint(1.8,0.606485);
		fragPoly->SetNextPoint(2,0.700327);

	}
	sprintf(noMaskCut," %s && %s ",fitCut,azCut);
	sprintf(cftCut," %s && %s ",fitCut,azCut);

}

if (preamp==3)
{
	if (!(strcmp(recoType,"hk"))){
		sprintf(fitCut,"fitType==5");

		sprintf(noMaskFileName,"$trees/hk.suppGood.trees.root");
		sprintf(cftFileName,"$trees/hk.suppGood.trees.root");
		
	}
	if ( !(strcmp(recoType,"fp"))){
		
		sprintf(fitCut,"bestFit && trackNo < 3");
		sprintf(noMaskFileName,"$trees/fp.suppGood.trees.root");
		sprintf(cftFileName,"$trees/fp.suppGood.trees.root");

	}
	sprintf(noMaskCut,"%s",fitCut);
	sprintf(cftCut,"%s",fitCut);

	fragCut->SetPoint(0,2.5,1.1);
	fragCut->SetPoint(1,15,1.9);
	fragCut->SetPoint(2,35,2.35);
	fragCut->SetPoint(3,71,4.15);
	fragCut->SetPoint(4,150,4.15);
	fragCut->SetPoint(5,150,1.65);
	fragCut->SetPoint(6,1.5,0.4);
	fragCut->SetPoint(7,2.5,1.1);

}

std::cout <<"noMaskCut = " << noMaskCut << std::endl;
std::cout <<"cftCut = " << cftCut << std::endl;

TFile* cftFile = new TFile(cftFileName);
TFile* noMaskFile = new TFile(noMaskFileName);
TTree* noMaskTracks = (TTree*)noMaskFile->Get("tracks");
TTree* cftTracks = (TTree*)cftFile->Get("tracks");
TH2D* noMaskLvEn = new TH2D("noMaskLvEn","noMaskLvEn",40000,0,168.6,1000,0,30);
TH2D* cftLvEn = new TH2D("cftLvEn","cftLvEn",40000,0,168.6,1000,0,30);

TCanvas *c1 = new TCanvas("c1","c1",1000,700);
char c1PlotName[123];
gStyle->SetOptStat(0);

cftLvEn->GetXaxis()->SetTitle("Track Energy [MeV]");
cftLvEn->GetXaxis()->CenterTitle();
cftLvEn->GetYaxis()->SetTitle("Track Length [cm]");
cftLvEn->GetYaxis()->CenterTitle();
cftLvEn->SetTitle(cftCut);
cftTracks->Draw("length:adc*168.6/40000>>cftLvEn",cftCut);

TH1D* cftFrags = cftLvEn->ProjectionX("cftFrags",0,40000,"[fragCut]");
cftFrags->GetXaxis()->SetTitle("MeV");
cftFrags->GetXaxis()->CenterTitle();
cftFrags->GetYaxis()->SetTitle("counts");
cftFrags->GetYaxis()->CenterTitle();
cftFrags->SetTitle("fragCut [Fission Trigger]");
cftFrags->SetLineColor(4);
cftFrags->SetLineWidth(2);

TH1D* cftNotFrags = cftLvEn->ProjectionX("cftNotFrags",0,40000,"[!fragCut]");

noMaskLvEn->GetXaxis()->SetTitle("Track Energy [MeV]");
noMaskLvEn->GetXaxis()->CenterTitle();
noMaskLvEn->GetYaxis()->SetTitle("Track Length [cm]");
noMaskLvEn->GetYaxis()->CenterTitle();
noMaskLvEn->SetTitle(noMaskCut);
noMaskTracks->Draw("length:adc*168.6/40000>>noMaskLvEn",noMaskCut);

TH1D* noMaskFrags = noMaskLvEn->ProjectionX("noMaskFrags",0,40000,"[fragCut]");
noMaskFrags->GetXaxis()->SetTitle("MeV");
noMaskFrags->GetXaxis()->CenterTitle();
noMaskFrags->GetYaxis()->SetTitle("counts");
noMaskFrags->GetYaxis()->CenterTitle();
noMaskFrags->SetTitle("fragCut [No Trigger]");
noMaskFrags->SetLineColor(2);
noMaskFrags->SetLineWidth(2);

TH1D* noMaskNotFrags = noMaskLvEn->ProjectionX("noMaskNotFrags",0,40000,"[!fragCut]");

double scaleCFT = noMaskFrags->Integral(5000,40000)/cftFrags->Integral(5000,40000);
TH1D* scaledCftFrags = (TH1D*)cftFrags->Clone("scaledCftFrags");
scaledCftFrags->Scale(scaleCFT);
cftNotFrags->Scale(scaleCFT);
cftLvEn->Scale(scaleCFT);

//////////////////////////////////////////
//////////////  rebinning ////////////////
//////////////////////////////////////////
int rebinInt=1;
TH1D* cftFragsRebin = (TH1D*)scaledCftFrags->Clone("cftFragsRebin");
cftFragsRebin->Rebin(rebinInt);
TH1D* noMaskFragsRebin = (TH1D*)noMaskFrags->Clone("noMaskFragsRebin");
noMaskFragsRebin->Rebin(rebinInt);
TH2D* noMaskLvEn_2dFrag = (TH2D*)noMaskFrags->Clone("noMaskFragsRebin");
TH2D* cftLvEn_2dFrag = (TH2D*)cftFrags->Clone("cftFragsRebin");


TH1D* cftEfficiency = (TH1D*)cftFragsRebin->Clone("cftEfficiency");
cftEfficiency->SetTitle("cftEfficiency = cft / noMask");
cftEfficiency->Divide(noMaskFragsRebin);


////////////////////////////////////////////
//////////////  count frags ////////////////
////////////////////////////////////////////
int cftFragIntegral=cftFragsRebin->Integral();
int cftIntegral=cftLvEn->Integral();
int noMaskFragIntegral=noMaskFragsRebin->Integral();
int noMaskIntegral=noMaskLvEn->Integral();
int cft_NOT_FragCut=noMaskIntegral - cftFragIntegral;
int noMask_NOT_FragCut=noMaskIntegral - noMaskFragIntegral;
double noMask_aSF_ratio=2*noMask_NOT_FragCut/(double)noMaskFragIntegral;
double cft_aSF_ratio=2*cft_NOT_FragCut/(double)cftFragIntegral;
char cftFragChar[123], noMaskFragChar[123],
	noMask_aSF_ratioChar[123],cft_aSF_ratioChar[123],
	noMask_NOT_FragCutChar[123],cft_NOT_FragCutChar[123],
	nFragRejectedChar[123],nNotFragRejectedChar[123];
sprintf(nFragRejectedChar,"nFragRejected = %.2f%%",100*TMath::Abs(1 - noMaskFragIntegral/(double)cftFragIntegral));
sprintf(nNotFragRejectedChar,"nNotFragRejected = %.2f%%",100*TMath::Abs(1 - cft_NOT_FragCut/(double)noMask_NOT_FragCut));
sprintf(cft_aSF_ratioChar,"cft_aSF_ratio = %.3f",cft_aSF_ratio);
sprintf(noMask_aSF_ratioChar,"noMask_aSF_ratio = %.3f",noMask_aSF_ratio);
sprintf(cft_NOT_FragCutChar,"cft_NOT_FragCut = %d",cft_NOT_FragCut);
sprintf(noMask_NOT_FragCutChar,"noMask_NOT_FragCut = %d",noMask_NOT_FragCut);
sprintf(cftFragChar,"nFragsCFT = %d",cftFragIntegral);
sprintf(noMaskFragChar,"nFragsNoMask = %d",noMaskFragIntegral);

TText fragCountText;
fragCountText.SetTextAlign(13);
fragCountText.SetTextSize(0.03);
fragCountText.SetTextFont(42);


//////////////////////////////////////////////////////////////////
//////////////////// plot fragment cut ////////////////
//////////////////////////////////////////////////////////////////

c1->SetLogx(1);
c1->SetLogy(1);
cftFragsRebin->GetXaxis()->SetRangeUser(1,150);
cftFragsRebin->GetYaxis()->SetRangeUser(0.5,10000);
cftFragsRebin->Draw();
fragCountText.DrawTextNDC(0.15,0.83,nFragRejectedChar);
fragCountText.DrawTextNDC(0.15,0.86,noMaskFragChar);
fragCountText.DrawTextNDC(0.15,0.89,cftFragChar);
sprintf(c1PlotName,"%s.frags.full.cft.png",recoType);
c1->SaveAs(c1PlotName,"recreate");

noMaskFragsRebin->GetXaxis()->SetRangeUser(1,150);
noMaskFragsRebin->GetYaxis()->SetRangeUser(0.5,10000);
noMaskFragsRebin->SetMaximum(noMaskFragsRebin->GetMaximum());
noMaskFragsRebin->Draw();
fragCountText.DrawTextNDC(0.15,0.83,nFragRejectedChar);
fragCountText.DrawTextNDC(0.15,0.86,noMaskFragChar);
fragCountText.DrawTextNDC(0.15,0.89,cftFragChar);
sprintf(c1PlotName,"%s.frags.full.noMask.png",recoType);
c1->SaveAs(c1PlotName,"recreate");

c1->SetLogx(0);
cftFragsRebin->Draw();
fragCountText.DrawTextNDC(0.15,0.83,nFragRejectedChar);
fragCountText.DrawTextNDC(0.15,0.86,noMaskFragChar);
fragCountText.DrawTextNDC(0.15,0.89,cftFragChar);
sprintf(c1PlotName,"%s.frags.full.lin.cft.png",recoType);
c1->SaveAs(c1PlotName,"recreate");

cftFragsRebin->GetXaxis()->SetRangeUser(0.1,20);
cftFragsRebin->Draw();
fragCountText.DrawTextNDC(0.15,0.83,nFragRejectedChar);
fragCountText.DrawTextNDC(0.15,0.86,noMaskFragChar);
fragCountText.DrawTextNDC(0.15,0.89,cftFragChar);
sprintf(c1PlotName,"%s.frags.lowEn.cft.png",recoType);
c1->SaveAs(c1PlotName,"recreate");

noMaskFragsRebin->Draw();
fragCountText.DrawTextNDC(0.15,0.83,nFragRejectedChar);
fragCountText.DrawTextNDC(0.15,0.86,noMaskFragChar);
fragCountText.DrawTextNDC(0.15,0.89,cftFragChar);
sprintf(c1PlotName,"%s.frags.full.lin.noMask.png",recoType);
c1->SaveAs(c1PlotName,"recreate");

noMaskFragsRebin->GetXaxis()->SetRangeUser(0.1,20);
noMaskFragsRebin->Draw();
fragCountText.DrawTextNDC(0.15,0.83,nFragRejectedChar);
fragCountText.DrawTextNDC(0.15,0.86,noMaskFragChar);
fragCountText.DrawTextNDC(0.15,0.89,cftFragChar);
sprintf(c1PlotName,"%s.frags.lowEn.noMask.png",recoType);
c1->SaveAs(c1PlotName,"recreate");

TLegend *legend1=new TLegend(0.4,0.8,0.6,0.89);
legend1->SetTextFont(42);
legend1->SetTextSize(0.03);
legend1->SetFillColorAlpha(kWhite,0.25);
legend1->AddEntry(noMaskFragsRebin,"No Trigger");
legend1->AddEntry(cftFragsRebin,"Fission Trigger");

//////////////////////////////////////////////////////////////////
//////////////////// cft & noMask fragment same plot /////////////
//////////////////////////////////////////////////////////////////

// for plotting the scaled region
TH1D* cftFragsScaleRegion = cftLvEn->ProjectionX("cftFragsScaleRegion",0,40000,"[fragCut]");
for (int i = 0; i < 5000; ++i) cftFragsScaleRegion->SetBinContent(i,0);
cftFragsScaleRegion->Rebin(rebinInt);
cftFragsScaleRegion->SetFillColorAlpha(9,0.25);

c1->SetLogx(1);
c1->SetLogy(1);
noMaskFragsRebin->GetXaxis()->SetRangeUser(1,150);
noMaskFragsRebin->GetYaxis()->SetRangeUser(0.5,10000);
cftFragsRebin->GetXaxis()->SetRangeUser(1,150);
cftFragsRebin->GetYaxis()->SetRangeUser(0.5,10000);
noMaskFragsRebin->Draw();
noMaskFragsRebin->SetTitle("fragCut [Trigger vs No Trigger]");
cftFragsRebin->Draw("same");
legend1->Draw("same");
fragCountText.DrawTextNDC(0.15,0.83,nFragRejectedChar);
fragCountText.DrawTextNDC(0.15,0.86,noMaskFragChar);
fragCountText.DrawTextNDC(0.15,0.89,cftFragChar);
sprintf(c1PlotName,"%s.bothFragsCut.logxy.png",recoType);
c1->SaveAs(c1PlotName,"recreate");
cftFragsScaleRegion->Draw("same");
sprintf(c1PlotName,"%s.bothFragsCut.logxy.showScalingRegion.png",recoType);
c1->SaveAs(c1PlotName,"recreate");

c1->SetLogx(0);
noMaskFragsRebin->SetMinimum(1);
noMaskFragsRebin->GetXaxis()->SetRangeUser(0,150);
cftFragsRebin->GetXaxis()->SetRangeUser(0,150);
noMaskFragsRebin->Draw();
cftFragsRebin->Draw("same");
legend1->Draw("same");
sprintf(c1PlotName,"%s.bothFragsCut.lin.png",recoType);
c1->SaveAs(c1PlotName,"recreate");
cftFragsScaleRegion->Draw("same");
sprintf(c1PlotName,"%s.bothFragsCut.lin.showScalingRegion.png",recoType);
c1->SaveAs(c1PlotName,"recreate");

TLegend *legendCFTefficiency=new TLegend(0.4,0.15,0.6,0.3);
legendCFTefficiency->SetTextFont(42);
legendCFTefficiency->SetTextSize(0.03);
legendCFTefficiency->SetFillColorAlpha(kWhite,0.25);
legendCFTefficiency->AddEntry(noMaskFragsRebin,"No Trigger");
legendCFTefficiency->AddEntry(cftFragsRebin,"Fission Trigger");
legendCFTefficiency->AddEntry(cftEfficiency,"CFT / no CFT");

// cft efficiency -> noMask / cft fragments
c1->SetGridx(1);
c1->SetGridy(1);
c1->SetLogx(0);
c1->SetLogy(0);
noMaskFragsRebin->GetXaxis()->SetRangeUser(0.1,20);
cftFragsRebin->GetXaxis()->SetRangeUser(0.1,20);
cftEfficiency->GetXaxis()->SetRangeUser(0.1,20);
cftEfficiency->GetYaxis()->SetRangeUser(0,2);
cftEfficiency->SetLineColor(6);
cftEfficiency->Draw();
fragCountText.DrawTextNDC(0.15,0.83,nFragRejectedChar);
fragCountText.DrawTextNDC(0.15,0.86,noMaskFragChar);
fragCountText.DrawTextNDC(0.15,0.89,cftFragChar);

sprintf(c1PlotName,"%s.cftEfficiency.png",recoType);
c1->SaveAs(c1PlotName,"recreate");
noMaskFragsRebin->GetYaxis()->SetRangeUser(0,400);
cftFragsRebin->GetYaxis()->SetRangeUser(0,400);
noMaskFragsRebin->Draw();
cftFragsRebin->Draw("same");
legend1->Draw("same");
cftFragsScaleRegion->Draw("same");

sprintf(c1PlotName,"%s.cftEfficiencyWithFrags.png",recoType);
c1->SaveAs(c1PlotName,"recreate");

c1->SetLogy(1);
cftEfficiency->GetXaxis()->SetRangeUser(0,30);
cftEfficiency->GetYaxis()->SetRangeUser(0.1,30);
cftEfficiency->SetLineColor(6);
cftEfficiency->Draw();

fragCountText.DrawTextNDC(0.15,0.83,nFragRejectedChar);
fragCountText.DrawTextNDC(0.15,0.86,noMaskFragChar);
fragCountText.DrawTextNDC(0.15,0.89,cftFragChar);
sprintf(c1PlotName,"%s.cftEfficiency.zoom.log.png",recoType);
c1->SaveAs(c1PlotName,"recreate");

noMaskFragsRebin->GetYaxis()->SetRangeUser(0.001,8000);
cftFragsRebin->GetYaxis()->SetRangeUser(0.001,8000);
cftEfficiency->GetYaxis()->SetRangeUser(0.001,8000);
noMaskFragsRebin->Draw();
cftFragsRebin->Draw("same");
cftEfficiency->Draw("same");
legendCFTefficiency->Draw("same");

fragCountText.DrawTextNDC(0.15,0.83,nFragRejectedChar);
fragCountText.DrawTextNDC(0.15,0.86,noMaskFragChar);
fragCountText.DrawTextNDC(0.15,0.89,cftFragChar);
sprintf(c1PlotName,"%s.bothFragsCut.zoom.png",recoType);
c1->SaveAs(c1PlotName,"recreate");

// ///////////////////////////////////////////////////////////////////
// ///////////////////////  Plot lenght VS ADC ///////////////////////
// ///////////////////////////////////////////////////////////////////

c1->cd();
c1->SetGridy(0);
c1->SetGridx(0);
c1->SetLogy(0);
c1->SetLogx(1);
c1->SetLogz(1);
cftLvEn->GetZaxis()->SetRangeUser(1,1000);
noMaskLvEn->GetZaxis()->SetRangeUser(1,1000);

cftLvEn->GetXaxis()->SetRangeUser(0.5,150);
cftLvEn->GetYaxis()->SetRangeUser(0,30);
cftLvEn->Draw("colz");

sprintf(c1PlotName,"%s.cftLvEn.full.log.png",recoType);
c1->SaveAs(c1PlotName,"recreate");
cftLvEn->GetYaxis()->SetRangeUser(0,7);
sprintf(c1PlotName,"%s.cftLvEn.full.log.zoom.png",recoType);
c1->SaveAs(c1PlotName,"recreate");

c1->cd();
c1->SetLogx(0);
cftLvEn->GetXaxis()->SetRangeUser(0,150);
cftLvEn->GetYaxis()->SetRangeUser(0,7);
cftLvEn->Draw("Colz");
// fragCut->Draw("same");

sprintf(c1PlotName,"%s.cftLvEn.full.lin.png",recoType);
c1->SaveAs(c1PlotName,"recreate");
fragCut->Draw("same");
fragCountText.DrawTextNDC(0.5,0.63,cft_aSF_ratioChar);
fragCountText.DrawTextNDC(0.5,0.66,cftFragChar);
fragCountText.DrawTextNDC(0.5,0.69,cft_NOT_FragCutChar);
sprintf(c1PlotName,"%s.cftLvEn.full.lin.plusFragCut.png",recoType);
c1->SaveAs(c1PlotName,"recreate");


c1->cd();
c1->SetLogx(0);
cftLvEn->GetXaxis()->SetRangeUser(0.1,20);
cftLvEn->Draw("Colz");
fragCut->Draw("same");

sprintf(c1PlotName,"%s.cftLvEn.lowEn.png",recoType);
c1->SaveAs(c1PlotName,"recreate");
fragCountText.DrawTextNDC(0.5,0.43,cft_aSF_ratioChar);
fragCountText.DrawTextNDC(0.5,0.46,cftFragChar);
fragCountText.DrawTextNDC(0.5,0.49,cft_NOT_FragCutChar);
sprintf(c1PlotName,"%s.cftLvEn.lowEn.plusFragCut.png",recoType);
c1->SaveAs(c1PlotName,"recreate");
fragPoly->Draw("f same");
sprintf(c1PlotName,"%s.cftLvEn.lowEn.plusFragCutFilled.png",recoType);
c1->SaveAs(c1PlotName,"recreate");

c1->cd();
c1->SetLogx(1);
noMaskLvEn->GetXaxis()->SetRangeUser(0.5,150);
noMaskLvEn->GetYaxis()->SetRangeUser(0,30);
noMaskLvEn->Draw("colz");

sprintf(c1PlotName,"%s.noMaskLvEn.full.log.png",recoType);
c1->SaveAs(c1PlotName,"recreate");
sprintf(c1PlotName,"%s.noMaskLvEn.full.log.png",recoType);
c1->SaveAs(c1PlotName,"recreate");
noMaskLvEn->GetYaxis()->SetRangeUser(0,7);
sprintf(c1PlotName,"%s.noMaskLvEn.full.log.zoom.png",recoType);
c1->SaveAs(c1PlotName,"recreate");
c1->SetLogx(0);
sprintf(c1PlotName,"%s.noMaskLvEn.full.lin.png",recoType);
c1->SaveAs(c1PlotName,"recreate");

c1->cd();
c1->SetLogx(0);
noMaskLvEn->GetXaxis()->SetRangeUser(0,150);
noMaskLvEn->GetYaxis()->SetRangeUser(0,7);
noMaskLvEn->Draw("Colz");
fragCut->Draw("same");
fragCountText.DrawTextNDC(0.5,0.63,noMask_aSF_ratioChar);
fragCountText.DrawTextNDC(0.5,0.66,noMaskFragChar);
fragCountText.DrawTextNDC(0.5,0.69,noMask_NOT_FragCutChar);
sprintf(c1PlotName,"%s.noMaskLvEn.full.lin.plusFragCut.png",recoType);
c1->SaveAs(c1PlotName,"recreate");
fragPoly->Draw("f same");
sprintf(c1PlotName,"%s.noMaskLvEn.full.lin.plusFragCutFilled.png",recoType);
c1->SaveAs(c1PlotName,"recreate");

c1->cd();
c1->SetLogx(0);
noMaskLvEn->GetXaxis()->SetRangeUser(0,30);
noMaskLvEn->GetYaxis()->SetRangeUser(0,7);
noMaskLvEn->Draw("Colz");

sprintf(c1PlotName,"%s.noMaskLvEn.lowEn.png",recoType);
c1->SaveAs(c1PlotName,"recreate");
fragCut->Draw("same");
fragCountText.DrawTextNDC(0.5,0.43,noMask_aSF_ratioChar);
fragCountText.DrawTextNDC(0.5,0.46,noMaskFragChar);
fragCountText.DrawTextNDC(0.5,0.49,noMask_NOT_FragCutChar);
sprintf(c1PlotName,"%s.noMaskLvEn.lowEn.plusFragCut.png",recoType);
c1->SaveAs(c1PlotName,"recreate");



// //////////////////////////////////////////////////////////////////
// //////////////////// polar cuts & projections ////////////////////
// //////////////////////////////////////////////////////////////////

TCutG *fragCutADC = new TCutG("fragCutADC",8);
fragCutADC->SetLineColor(kViolet);
fragCutADC->SetLineWidth(3);
fragCutADC->SetVarX("adc");
fragCutADC->SetVarY("length");
if (preamp==1)
{
	fragCutADC->SetPoint(0 ,474,0.856419);
	fragCutADC->SetPoint(1 ,3558,1.5);
	fragCutADC->SetPoint(2 ,8303,2.5);
	fragCutADC->SetPoint(3 ,14234,3.25);
	fragCutADC->SetPoint(4 ,33214,3.5);
	fragCutADC->SetPoint(5 ,33214,1.25);
	fragCutADC->SetPoint(6 ,237,0);
	fragCutADC->SetPoint(7 ,237,0.434625);
	fragCutADC->SetPoint(8 ,284,0.496664);
	fragCutADC->SetPoint(9 ,332,0.56915);
	fragCutADC->SetPoint(10,379,0.652886);
	fragCutADC->SetPoint(11,427,0.748508);
	fragCutADC->SetPoint(12,474,0.856419);

}
else if (preamp==2)
{
	fragCutADC->SetPoint(0 ,474,0.700327);
	fragCutADC->SetPoint(1 ,3558,1.5);
	fragCutADC->SetPoint(2 ,8303,2.5);
	fragCutADC->SetPoint(3 ,14234,3.25);
	fragCutADC->SetPoint(4 ,33214,3.5);
	fragCutADC->SetPoint(5 ,33214,1.25);
	fragCutADC->SetPoint(6 ,237,0);
	fragCutADC->SetPoint(7 ,237,0.295582);
	fragCutADC->SetPoint(8 ,284,0.363805);
	fragCutADC->SetPoint(9 ,332,0.438273);
	fragCutADC->SetPoint(10,379,0.519138);
	fragCutADC->SetPoint(11,427,0.606485);
	fragCutADC->SetPoint(12,474,0.700327);
}

double deg2rad = TMath::Pi()/(double)180;
double solidAngle, perSA, theta;
double binWidth = 90/(double)500;


TH1D* noMaskVsTheta0to180 = new TH1D("noMaskVsTheta0to180","noMaskVsTheta0to180",1000,0,180);
TH1D* noMaskVsCosThetaNeg1to1 = new TH1D("noMaskVsCosThetaNeg1to1","noMaskVsCosThetaNeg1to1",1000,-1,1);
noMaskTracks->Draw("direction.Theta()/TMath::Pi()*180>>noMaskVsTheta0to180",noMaskCut);
noMaskTracks->Draw("direction.CosTheta()>>noMaskVsCosThetaNeg1to1",noMaskCut);
TH1D* noMaskVsTheta = new TH1D("noMaskVsTheta","noMaskVsTheta",500,0,90);
TH1D* noMaskVsThetaPerSA = new TH1D("noMaskVsThetaPerSA","noMaskVsThetaPerSA",500,0,90);
TH1D* noMaskVsCosTheta = new TH1D("noMaskVsCosTheta","noMaskVsCosTheta",500,0,1);
TH1D* noMaskVsCosThetaPerSA = new TH1D("noMaskVsCosThetaPerSA","noMaskVsCosThetaPerSA",500,0,1);

char noMaskFragCut[234];sprintf(noMaskFragCut,"%s && fragCutADC", noMaskCut);
TH1D* noMaskFragVsTheta0to180 = new TH1D("noMaskFragVsTheta0to180","noMaskFragVsTheta0to180",1000,0,180);
TH1D* noMaskFragVsCosThetaNeg1to1 = new TH1D("noMaskFragVsCosThetaNeg1to1","noMaskFragVsCosThetaNeg1to1",1000,-1,1);
noMaskTracks->Draw("direction.Theta()/TMath::Pi()*180>>noMaskFragVsTheta0to180",noMaskFragCut);
noMaskTracks->Draw("direction.CosTheta()>>noMaskFragVsCosThetaNeg1to1",noMaskFragCut);
TH1D* noMaskFragVsTheta = new TH1D("noMaskFragVsTheta","noMaskFragVsTheta",500,0,90);
TH1D* noMaskFragVsThetaPerSA = new TH1D("noMaskFragVsThetaPerSA","noMaskFragVsThetaPerSA",500,0,90);
TH1D* noMaskFragVsCosTheta = new TH1D("noMaskFragVsCosTheta","noMaskFragVsCosTheta",500,0,1);
TH1D* noMaskFragVsCosThetaPerSA = new TH1D("noMaskFragVsCosThetaPerSA","noMaskFragVsCosThetaPerSA",500,0,1);

char noMaskNotFragCut[234];sprintf(noMaskFragCut,"%s && !fragCutADC",noMaskCut);
TH1D* noMaskNotFragVsTheta0to180 = new TH1D("noMaskNotFragVsTheta0to180","noMaskNotFragVsTheta0to180",1000,0,180);
TH1D* noMaskNotFragVsCosThetaNeg1to1 = new TH1D("noMaskNotFragVsCosThetaNeg1to1","noMaskNotFragVsCosThetaNeg1to1",1000,-1,1);
noMaskTracks->Draw("direction.Theta()/TMath::Pi()*180>>noMaskNotFragVsTheta0to180",noMaskFragCut);
noMaskTracks->Draw("direction.CosTheta()>>noMaskNotFragVsCosThetaNeg1to1",noMaskFragCut);
TH1D* noMaskNotFragVsTheta = new TH1D("noMaskNotFragVsTheta","noMaskNotFragVsTheta",500,0,90);
TH1D* noMaskNotFragVsThetaPerSA = new TH1D("noMaskNotFragVsThetaPerSA","noMaskNotFragVsThetaPerSA",500,0,90);
TH1D* noMaskNotFragVsCosTheta = new TH1D("noMaskNotFragVsCosTheta","noMaskNotFragVsCosTheta",500,0,1);
TH1D* noMaskNotFragVsCosThetaPerSA = new TH1D("noMaskNotFragVsCosThetaPerSA","noMaskNotFragVsCosThetaPerSA",500,0,1);

TH1D* cftVsTheta0to180 = new TH1D("cftVsTheta0to180","cftVsTheta0to180",1000,0,180);
TH1D* cftVsCosThetaNeg1to1 = new TH1D("cftVsCosThetaNeg1to1","cftVsCosThetaNeg1to1",1000,-1,1);
cftTracks->Draw("direction.Theta()/TMath::Pi()*180>>cftVsTheta0to180",cftCut);
cftTracks->Draw("direction.CosTheta()>>cftVsCosThetaNeg1to1",cftCut);
TH1D* cftVsTheta = new TH1D("cftVsTheta","cftVsTheta",500,0,90);
TH1D* cftVsThetaPerSA = new TH1D("cftVsThetaPerSA","cftVsThetaPerSA",500,0,90);
TH1D* cftVsCosTheta = new TH1D("cftVsCosTheta","cftVsCosTheta",500,0,1);
TH1D* cftVsCosThetaPerSA = new TH1D("cftVsCosThetaPerSA","cftVsCosThetaPerSA",500,0,1);

char cftFragCut[234];sprintf(cftFragCut,"%s && fragCutADC", cftCut);
TH1D* cftFragVsTheta0to180 = new TH1D("cftFragVsTheta0to180","cftFragVsTheta0to180",1000,0,180);
TH1D* cftFragVsCosThetaNeg1to1 = new TH1D("cftFragVsCosThetaNeg1to1","cftFragVsCosThetaNeg1to1",1000,-1,1);
cftTracks->Draw("direction.Theta()/TMath::Pi()*180>>cftFragVsTheta0to180",cftFragCut);
cftTracks->Draw("direction.CosTheta()>>cftFragVsCosThetaNeg1to1",cftFragCut);
TH1D* cftFragVsTheta = new TH1D("cftFragVsTheta","cftFragVsTheta",500,0,90);
TH1D* cftFragVsThetaPerSA = new TH1D("cftFragVsThetaPerSA","cftFragVsThetaPerSA",500,0,90);
TH1D* cftFragVsCosTheta = new TH1D("cftFragVsCosTheta","cftFragVsCosTheta",500,0,1);
TH1D* cftFragVsCosThetaPerSA = new TH1D("cftFragVsCosThetaPerSA","cftFragVsCosThetaPerSA",500,0,1);

char cftNotFragCut[234];sprintf(cftFragCut,"%s && !fragCutADC",cftCut);
TH1D* cftNotFragVsTheta0to180 = new TH1D("cftNotFragVsTheta0to180","cftNotFragVsTheta0to180",1000,0,180);
TH1D* cftNotFragVsCosThetaNeg1to1 = new TH1D("cftNotFragVsCosThetaNeg1to1","cftNotFragVsCosThetaNeg1to1",1000,-1,1);
cftTracks->Draw("direction.Theta()/TMath::Pi()*180>>cftNotFragVsTheta0to180",cftNotFragCut);
cftTracks->Draw("direction.CosTheta()>>cftNotFragVsCosThetaNeg1to1",cftNotFragCut);
TH1D* cftNotFragVsTheta = new TH1D("cftNotFragVsTheta","cftNotFragVsTheta",500,0,90);
TH1D* cftNotFragVsThetaPerSA = new TH1D("cftNotFragVsThetaPerSA","cftNotFragVsThetaPerSA",500,0,90);
TH1D* cftNotFragVsCosTheta = new TH1D("cftNotFragVsCosTheta","cftNotFragVsCosTheta",500,0,1);
TH1D* cftNotFragVsCosThetaPerSA = new TH1D("cftNotFragVsCosThetaPerSA","cftNotFragVsCosThetaPerSA",500,0,1);


for (int i = 0; i < 500; ++i)
{

	theta=i*90/(double)500*deg2rad;
	solidAngle = 2*TMath::Pi()*(TMath::Cos(theta)-TMath::Cos(theta + binWidth));
	perSA = 1/(double)solidAngle;

	noMaskVsTheta->SetBinContent(500-i,noMaskVsTheta0to180->GetBinContent(i)+noMaskVsTheta0to180->GetBinContent(1000-i));
	noMaskVsThetaPerSA->SetBinContent(500-i,(noMaskVsTheta0to180->GetBinContent(i)+noMaskVsTheta0to180->GetBinContent(1000-i))*perSA);
	noMaskVsCosTheta->SetBinContent(500-i,noMaskVsCosThetaNeg1to1->GetBinContent(i)+noMaskVsCosThetaNeg1to1->GetBinContent(1000-i));
	noMaskVsCosThetaPerSA->SetBinContent(500-i,(noMaskVsCosThetaNeg1to1->GetBinContent(i)+noMaskVsCosThetaNeg1to1->GetBinContent(1000-i))*perSA);
	noMaskFragVsTheta->SetBinContent(500-i,noMaskFragVsTheta0to180->GetBinContent(i)+noMaskFragVsTheta0to180->GetBinContent(1000-i));
	noMaskFragVsThetaPerSA->SetBinContent(500-i,(noMaskFragVsTheta0to180->GetBinContent(i)+noMaskFragVsTheta0to180->GetBinContent(1000-i))*perSA);
	noMaskFragVsCosTheta->SetBinContent(500-i,noMaskFragVsCosThetaNeg1to1->GetBinContent(i)+noMaskFragVsCosThetaNeg1to1->GetBinContent(1000-i));
	noMaskFragVsCosThetaPerSA->SetBinContent(500-i,(noMaskFragVsCosThetaNeg1to1->GetBinContent(i)+noMaskFragVsCosThetaNeg1to1->GetBinContent(1000-i))*perSA);
	noMaskNotFragVsTheta->SetBinContent(500-i,noMaskNotFragVsTheta0to180->GetBinContent(i)+noMaskNotFragVsTheta0to180->GetBinContent(1000-i));
	noMaskNotFragVsThetaPerSA->SetBinContent(500-i,(noMaskNotFragVsTheta0to180->GetBinContent(i)+noMaskNotFragVsTheta0to180->GetBinContent(1000-i))*perSA);
	noMaskNotFragVsCosTheta->SetBinContent(500-i,noMaskNotFragVsCosThetaNeg1to1->GetBinContent(i)+noMaskNotFragVsCosThetaNeg1to1->GetBinContent(1000-i));
	noMaskNotFragVsCosThetaPerSA->SetBinContent(500-i,(noMaskNotFragVsCosThetaNeg1to1->GetBinContent(i)+noMaskNotFragVsCosThetaNeg1to1->GetBinContent(1000-i))*perSA);

	cftVsTheta->SetBinContent(500-i,cftVsTheta0to180->GetBinContent(i)+cftVsTheta0to180->GetBinContent(1000-i));
	cftVsThetaPerSA->SetBinContent(500-i,(cftVsTheta0to180->GetBinContent(i)+cftVsTheta0to180->GetBinContent(1000-i))*perSA);
	cftVsCosTheta->SetBinContent(500-i,cftVsCosThetaNeg1to1->GetBinContent(i)+cftVsCosThetaNeg1to1->GetBinContent(1000-i));
	cftVsCosThetaPerSA->SetBinContent(500-i,(cftVsCosThetaNeg1to1->GetBinContent(i)+cftVsCosThetaNeg1to1->GetBinContent(1000-i))*perSA);
	cftFragVsTheta->SetBinContent(500-i,cftFragVsTheta0to180->GetBinContent(i)+cftFragVsTheta0to180->GetBinContent(1000-i));
	cftFragVsThetaPerSA->SetBinContent(500-i,(cftFragVsTheta0to180->GetBinContent(i)+cftFragVsTheta0to180->GetBinContent(1000-i))*perSA);
	cftFragVsCosTheta->SetBinContent(500-i,cftFragVsCosThetaNeg1to1->GetBinContent(i)+cftFragVsCosThetaNeg1to1->GetBinContent(1000-i));
	cftFragVsCosThetaPerSA->SetBinContent(500-i,(cftFragVsCosThetaNeg1to1->GetBinContent(i)+cftFragVsCosThetaNeg1to1->GetBinContent(1000-i))*perSA);
	cftNotFragVsTheta->SetBinContent(500-i,cftNotFragVsTheta0to180->GetBinContent(i)+cftNotFragVsTheta0to180->GetBinContent(1000-i));
	cftNotFragVsThetaPerSA->SetBinContent(500-i,(cftNotFragVsTheta0to180->GetBinContent(i)+cftNotFragVsTheta0to180->GetBinContent(1000-i))*perSA);
	cftNotFragVsCosTheta->SetBinContent(500-i,cftNotFragVsCosThetaNeg1to1->GetBinContent(i)+cftNotFragVsCosThetaNeg1to1->GetBinContent(1000-i));
	cftNotFragVsCosThetaPerSA->SetBinContent(500-i,(cftNotFragVsCosThetaNeg1to1->GetBinContent(i)+cftNotFragVsCosThetaNeg1to1->GetBinContent(1000-i))*perSA);

}


noMaskFragVsTheta0to180->SetTitle("noMaskFragVsTheta0to180");
noMaskFragVsTheta0to180->SetLineColor(kViolet);
noMaskFragVsTheta0to180->SetFillColorAlpha(kViolet,0.25);
noMaskFragVsTheta0to180->GetXaxis()->SetTitle("#theta");
noMaskFragVsTheta0to180->GetYaxis()->SetTitle("allTrks");
sprintf(c1PlotName,"%s.noMaskFragVsTheta0to180.png",recoType);
noMaskFragVsTheta0to180->Draw();
c1->SaveAs(c1PlotName);
noMaskFragVsCosThetaNeg1to1->SetTitle("noMaskFragVsCosThetaNeg1to1");
noMaskFragVsCosThetaNeg1to1->SetLineColor(kViolet);
noMaskFragVsCosThetaNeg1to1->SetFillColorAlpha(kViolet,0.25);
noMaskFragVsCosThetaNeg1to1->GetXaxis()->SetTitle("Cos #theta");
noMaskFragVsCosThetaNeg1to1->GetYaxis()->SetTitle("allTrks");
noMaskFragVsCosThetaNeg1to1->GetYaxis()->SetTitleOffset(1.4);
sprintf(c1PlotName,"%s.noMaskFragVsCosThetaNeg1to1.png",recoType);
noMaskFragVsCosThetaNeg1to1->Draw();
c1->SaveAs(c1PlotName);
noMaskFragVsTheta->SetTitle("noMaskFragVsTheta");
noMaskFragVsTheta->SetLineColor(kViolet);
noMaskFragVsTheta->SetFillColorAlpha(kViolet,0.25);
noMaskFragVsTheta->GetXaxis()->SetTitle("#theta");
noMaskFragVsTheta->GetYaxis()->SetTitle("allTrks");
noMaskFragVsTheta->GetYaxis()->SetTitleOffset(1.4);
sprintf(c1PlotName,"%s.noMaskFragVsTheta.png",recoType);
noMaskFragVsTheta->Draw();
c1->SaveAs(c1PlotName);
noMaskFragVsThetaPerSA->SetTitle("noMaskFragVsThetaPerSA");
noMaskFragVsThetaPerSA->SetLineColor(kViolet);
noMaskFragVsThetaPerSA->SetFillColorAlpha(kViolet,0.25);
noMaskFragVsThetaPerSA->GetXaxis()->SetTitle("#theta");
noMaskFragVsThetaPerSA->GetYaxis()->SetTitle("allTrks/d#Omega");
noMaskFragVsThetaPerSA->GetYaxis()->SetTitleOffset(1.4);
sprintf(c1PlotName,"%s.noMaskFragVsThetaPerSA.png",recoType);
noMaskFragVsThetaPerSA->Draw();
c1->SaveAs(c1PlotName);
noMaskFragVsCosTheta->SetTitle("noMaskFragVsCosTheta");
noMaskFragVsCosTheta->SetLineColor(kViolet);
noMaskFragVsCosTheta->SetFillColorAlpha(kViolet,0.25);
noMaskFragVsCosTheta->GetXaxis()->SetTitle("cos(#theta)");
noMaskFragVsCosTheta->GetYaxis()->SetTitle("fragTrks");
noMaskFragVsCosTheta->GetYaxis()->SetTitleOffset(1.4);
sprintf(c1PlotName,"%s.noMaskFragVsCosTheta.png",recoType);
noMaskFragVsCosTheta->Draw();
c1->SaveAs(c1PlotName);
noMaskFragVsCosThetaPerSA->SetTitle("noMaskFragVsCosThetaPerSA");
noMaskFragVsCosThetaPerSA->SetLineColor(kViolet);
noMaskFragVsCosThetaPerSA->SetFillColorAlpha(kViolet,0.25);
noMaskFragVsCosThetaPerSA->GetXaxis()->SetTitle("cos(#theta)");
noMaskFragVsCosThetaPerSA->GetYaxis()->SetTitle("fragTrks/d#Omega");
noMaskFragVsCosThetaPerSA->GetYaxis()->SetTitleOffset(1.4);
sprintf(c1PlotName,"%s.noMaskFragVsCosThetaPerSA.png",recoType);
noMaskFragVsCosThetaPerSA->Draw();
c1->SaveAs(c1PlotName);

noMaskNotFragVsTheta0to180->SetTitle("noMaskNotFragVsTheta0to180");
noMaskNotFragVsTheta0to180->SetFillColorAlpha(kGreen,0.25);
noMaskNotFragVsTheta0to180->SetLineColor(kGreen);
noMaskNotFragVsTheta0to180->GetXaxis()->SetTitle("#theta");
noMaskNotFragVsTheta0to180->GetYaxis()->SetTitle("notFragTrks");
noMaskNotFragVsTheta0to180->GetYaxis()->SetTitleOffset(1.4);
sprintf(c1PlotName,"%s.noMaskNotFragVsTheta0to180.png",recoType);
noMaskNotFragVsTheta0to180->Draw();
c1->SaveAs(c1PlotName);
noMaskNotFragVsCosThetaNeg1to1->SetTitle("noMaskNotFragVsCosThetaNeg1to1");
noMaskNotFragVsCosThetaNeg1to1->SetFillColorAlpha(kGreen,0.25);
noMaskNotFragVsCosThetaNeg1to1->SetLineColor(kGreen);
noMaskNotFragVsCosThetaNeg1to1->GetXaxis()->SetTitle("Cos #theta");
noMaskNotFragVsCosThetaNeg1to1->GetYaxis()->SetTitle("notFragTrks");
noMaskNotFragVsCosThetaNeg1to1->GetYaxis()->SetTitleOffset(1.4);
sprintf(c1PlotName,"%s.noMaskNotFragVsCosThetaNeg1to1.png",recoType);
noMaskNotFragVsCosThetaNeg1to1->Draw();
c1->SaveAs(c1PlotName);
noMaskNotFragVsTheta->SetTitle("noMaskNotFragVsTheta");
noMaskNotFragVsTheta->SetFillColorAlpha(kGreen,0.25);
noMaskNotFragVsTheta->SetLineColor(kGreen);
noMaskNotFragVsTheta->GetXaxis()->SetTitle("#theta");
noMaskNotFragVsTheta->GetYaxis()->SetTitle("notFragTrks");
noMaskNotFragVsTheta->GetYaxis()->SetTitleOffset(1.4);
sprintf(c1PlotName,"%s.noMaskNotFragVsTheta.png",recoType);
noMaskNotFragVsTheta->Draw();
c1->SaveAs(c1PlotName);
noMaskNotFragVsThetaPerSA->SetTitle("noMaskNotFragVsThetaPerSA");
noMaskNotFragVsThetaPerSA->SetFillColorAlpha(kGreen,0.25);
noMaskNotFragVsThetaPerSA->SetLineColor(kGreen);
noMaskNotFragVsThetaPerSA->GetXaxis()->SetTitle("#theta");
noMaskNotFragVsThetaPerSA->GetYaxis()->SetTitle("notFragTrks/d#Omega");
noMaskNotFragVsThetaPerSA->GetYaxis()->SetTitleOffset(1.4);
sprintf(c1PlotName,"%s.noMaskNotFragVsThetaPerSA.png",recoType);
noMaskNotFragVsThetaPerSA->Draw();
c1->SaveAs(c1PlotName);
noMaskNotFragVsCosTheta->SetFillColorAlpha(kGreen,0.25);
noMaskNotFragVsCosTheta->SetLineColor(kGreen);
noMaskNotFragVsCosTheta->GetXaxis()->SetTitle("cos(#theta)");
noMaskNotFragVsCosTheta->GetYaxis()->SetTitle("notFragTrks");
noMaskNotFragVsCosTheta->GetYaxis()->SetTitleOffset(1.4);
sprintf(c1PlotName,"%s.noMaskNotFragVsCosTheta.png",recoType);
noMaskNotFragVsCosTheta->Draw();
c1->SaveAs(c1PlotName);
noMaskNotFragVsCosThetaPerSA->SetTitle("noMaskNotFragVsCosThetaPerSA");
noMaskNotFragVsCosThetaPerSA->SetFillColorAlpha(kGreen,0.25);
noMaskNotFragVsCosThetaPerSA->SetLineColor(kGreen);
noMaskNotFragVsCosThetaPerSA->GetXaxis()->SetTitle("cos(#theta)");
noMaskNotFragVsCosThetaPerSA->GetYaxis()->SetTitle("notFragTrks/d#Omega");
noMaskNotFragVsCosThetaPerSA->GetYaxis()->SetTitleOffset(1.4);
sprintf(c1PlotName,"%s.noMaskNotFragVsCosThetaPerSA.png",recoType);
noMaskNotFragVsCosThetaPerSA->Draw();
c1->SaveAs(c1PlotName);

cftFragVsTheta0to180->SetTitle("cftFragVsTheta0to180");
cftFragVsTheta0to180->SetFillColorAlpha(kViolet,0.25);
cftFragVsTheta0to180->SetLineColor(kViolet);
cftFragVsTheta0to180->GetXaxis()->SetTitle("#theta");
cftFragVsTheta0to180->GetYaxis()->SetTitle("allTrks");
cftFragVsTheta0to180->GetYaxis()->SetTitleOffset(1.4);
sprintf(c1PlotName,"%s.cftFragVsTheta0to180.png",recoType);
cftFragVsTheta0to180->Draw();
c1->SaveAs(c1PlotName);
cftFragVsCosThetaNeg1to1->SetTitle("cftFragVsCosThetaNeg1to1");
cftFragVsCosThetaNeg1to1->SetFillColorAlpha(kViolet,0.25);
cftFragVsCosThetaNeg1to1->SetLineColor(kViolet);
cftFragVsCosThetaNeg1to1->GetXaxis()->SetTitle("Cos #theta");
cftFragVsCosThetaNeg1to1->GetYaxis()->SetTitle("allTrks");
cftFragVsCosThetaNeg1to1->GetYaxis()->SetTitleOffset(1.4);
sprintf(c1PlotName,"%s.cftFragVsCosThetaNeg1to1.png",recoType);
cftFragVsCosThetaNeg1to1->Draw();
c1->SaveAs(c1PlotName);
cftFragVsTheta->SetTitle("cftFragVsTheta");
cftFragVsTheta->SetFillColorAlpha(kViolet,0.25);
cftFragVsTheta->SetLineColor(kViolet);
cftFragVsTheta->GetXaxis()->SetTitle("#theta");
cftFragVsTheta->GetYaxis()->SetTitle("allTrks");
cftFragVsTheta->GetYaxis()->SetTitleOffset(1.4);
sprintf(c1PlotName,"%s.cftFragVsTheta.png",recoType);
cftFragVsTheta->Draw();
c1->SaveAs(c1PlotName);
cftFragVsThetaPerSA->SetTitle("cftFragVsThetaPerSA");
cftFragVsThetaPerSA->SetFillColorAlpha(kViolet,0.25);
cftFragVsThetaPerSA->SetLineColor(kViolet);
cftFragVsThetaPerSA->GetXaxis()->SetTitle("#theta");
cftFragVsThetaPerSA->GetYaxis()->SetTitle("allTrks/d#Omega");
cftFragVsThetaPerSA->GetYaxis()->SetTitleOffset(1.4);
sprintf(c1PlotName,"%s.cftFragVsThetaPerSA.png",recoType);
cftFragVsThetaPerSA->Draw();
c1->SaveAs(c1PlotName);
cftFragVsCosTheta->SetTitle("cftFragVsCosTheta");
cftFragVsCosTheta->SetFillColorAlpha(kViolet,0.25);
cftFragVsCosTheta->SetLineColor(kViolet);
cftFragVsCosTheta->GetXaxis()->SetTitle("cos(#theta)");
cftFragVsCosTheta->GetYaxis()->SetTitle("fragTrks");
cftFragVsCosTheta->GetYaxis()->SetTitleOffset(1.4);
sprintf(c1PlotName,"%s.cftFragVsCosTheta.png",recoType);
cftFragVsCosTheta->Draw();
c1->SaveAs(c1PlotName);
cftFragVsCosThetaPerSA->SetTitle("cftFragVsCosThetaPerSA");
cftFragVsCosThetaPerSA->SetFillColorAlpha(kViolet,0.25);
cftFragVsCosThetaPerSA->SetLineColor(kViolet);
cftFragVsCosThetaPerSA->GetXaxis()->SetTitle("cos(#theta)");
cftFragVsCosThetaPerSA->GetYaxis()->SetTitle("fragTrks/d#Omega");
cftFragVsCosThetaPerSA->GetYaxis()->SetTitleOffset(1.4);
sprintf(c1PlotName,"%s.cftFragVsCosThetaPerSA.png",recoType);
cftFragVsCosThetaPerSA->Draw();
c1->SaveAs(c1PlotName);

cftNotFragVsTheta0to180->SetTitle("cftNotFragVsTheta0to180");
cftNotFragVsTheta0to180->SetFillColorAlpha(kGreen,0.25);
cftNotFragVsTheta0to180->SetLineColor(kGreen);
cftNotFragVsTheta0to180->GetXaxis()->SetTitle("#theta");
cftNotFragVsTheta0to180->GetYaxis()->SetTitle("notFragTrks");
cftNotFragVsTheta0to180->GetYaxis()->SetTitleOffset(1.4);
sprintf(c1PlotName,"%s.cftNotFragVsTheta0to180.png",recoType);
cftNotFragVsTheta0to180->Draw();
c1->SaveAs(c1PlotName);
cftNotFragVsCosThetaNeg1to1->SetTitle("cftNotFragVsCosThetaNeg1to1");
cftNotFragVsCosThetaNeg1to1->SetFillColorAlpha(kGreen,0.25);
cftNotFragVsCosThetaNeg1to1->SetLineColor(kGreen);
cftNotFragVsCosThetaNeg1to1->GetXaxis()->SetTitle("Cos #theta");
cftNotFragVsCosThetaNeg1to1->GetYaxis()->SetTitle("notFragTrks");
cftNotFragVsCosThetaNeg1to1->GetYaxis()->SetTitleOffset(1.4);
sprintf(c1PlotName,"%s.cftNotFragVsCosThetaNeg1to1.png",recoType);
cftNotFragVsCosThetaNeg1to1->Draw();
c1->SaveAs(c1PlotName);
cftNotFragVsTheta->SetTitle("cftNotFragVsTheta");
cftNotFragVsTheta->SetFillColorAlpha(kGreen,0.25);
cftNotFragVsTheta->SetLineColor(kGreen);
cftNotFragVsTheta->GetXaxis()->SetTitle("#theta");
cftNotFragVsTheta->GetYaxis()->SetTitle("notFragTrks");
cftNotFragVsTheta->GetYaxis()->SetTitleOffset(1.4);
sprintf(c1PlotName,"%s.cftNotFragVsTheta.png",recoType);
cftNotFragVsTheta->Draw();
c1->SaveAs(c1PlotName);
cftNotFragVsThetaPerSA->SetTitle("cftNotFragVsThetaPerSA");
cftNotFragVsThetaPerSA->SetFillColorAlpha(kGreen,0.25);
cftNotFragVsThetaPerSA->SetLineColor(kGreen);
cftNotFragVsThetaPerSA->GetXaxis()->SetTitle("#theta");
cftNotFragVsThetaPerSA->GetYaxis()->SetTitle("notFragTrks/d#Omega");
cftNotFragVsThetaPerSA->GetYaxis()->SetTitleOffset(1.4);
sprintf(c1PlotName,"%s.cftNotFragVsThetaPerSA.png",recoType);
cftNotFragVsThetaPerSA->Draw();
c1->SaveAs(c1PlotName);
cftNotFragVsCosTheta->SetTitle("cftNotFragVsCosTheta");
cftNotFragVsCosTheta->SetFillColorAlpha(kGreen,0.25);
cftNotFragVsCosTheta->SetLineColor(kGreen);
cftNotFragVsCosTheta->GetXaxis()->SetTitle("cos(#theta)");
cftNotFragVsCosTheta->GetYaxis()->SetTitle("notFragTrks");
cftNotFragVsCosTheta->GetYaxis()->SetTitleOffset(1.4);
sprintf(c1PlotName,"%s.cftNotFragVsCosTheta.png",recoType);
cftNotFragVsCosTheta->Draw();
c1->SaveAs(c1PlotName);
cftNotFragVsCosThetaPerSA->SetTitle("cftNotFragVsCosThetaPerSA");
cftNotFragVsCosThetaPerSA->SetFillColorAlpha(kGreen,0.25);
cftNotFragVsCosThetaPerSA->SetLineColor(kGreen);
cftNotFragVsCosThetaPerSA->GetXaxis()->SetTitle("cos(#theta)");
cftNotFragVsCosThetaPerSA->GetYaxis()->SetTitle("notFragTrks/d#Omega");
cftNotFragVsCosThetaPerSA->GetYaxis()->SetTitleOffset(1.4);
sprintf(c1PlotName,"%s.cftNotFragVsCosThetaPerSA.png",recoType);
cftNotFragVsCosThetaPerSA->Draw();
c1->SaveAs(c1PlotName);

////////////////////////////////////////////////////////////////////////
//////////////////// polar stack cuts & projections ////////////////////
////////////////////////////////////////////////////////////////////////

THStack *noMaskVsTheta0to180Stack = new THStack("noMaskVsTheta0to180Stack","");
THStack *noMaskVsCosThetaNeg1to1Stack = new THStack("noMaskVsCosThetaNeg1to1Stack","");
THStack *noMaskVsThetaStack = new THStack("noMaskVsThetaStack","");
THStack *noMaskVsThetaPerSAStack = new THStack("noMaskVsThetaPerSAStack","");
THStack *noMaskVsCosThetaStack = new THStack("noMaskVsCosThetaStack","");
THStack *noMaskVsCosThetaPerSAStack = new THStack("noMaskVsCosThetaPerSAStack","");

noMaskVsTheta0to180Stack->Add(noMaskFragVsTheta0to180);
noMaskVsTheta0to180Stack->Add(noMaskNotFragVsTheta0to180);
noMaskVsCosThetaNeg1to1Stack->Add(noMaskFragVsCosThetaNeg1to1);
noMaskVsCosThetaNeg1to1Stack->Add(noMaskNotFragVsCosThetaNeg1to1);
noMaskVsThetaStack->Add(noMaskFragVsTheta);
noMaskVsThetaStack->Add(noMaskNotFragVsTheta);
noMaskVsThetaPerSAStack->Add(noMaskFragVsThetaPerSA);
noMaskVsThetaPerSAStack->Add(noMaskNotFragVsThetaPerSA);
noMaskVsCosThetaStack->Add(noMaskFragVsCosTheta);
noMaskVsCosThetaStack->Add(noMaskNotFragVsCosTheta);
noMaskVsCosThetaPerSAStack->Add(noMaskFragVsCosThetaPerSA);
noMaskVsCosThetaPerSAStack->Add(noMaskNotFragVsCosThetaPerSA);

noMaskVsTheta0to180Stack->Draw();
noMaskVsTheta0to180Stack->SetTitle("noMaskVsTheta0to180Stack");
noMaskVsTheta0to180Stack->GetXaxis()->SetTitle("#theta");
noMaskVsTheta0to180Stack->GetYaxis()->SetTitle("allTrks");
noMaskVsTheta0to180Stack->GetYaxis()->SetTitleOffset(1.4);
sprintf(c1PlotName,"%s.noMaskVsTheta0to180.png",recoType);
c1->SaveAs(c1PlotName);
noMaskVsCosThetaNeg1to1Stack->Draw();
noMaskVsCosThetaNeg1to1Stack->SetTitle("noMaskVsCosThetaNeg1to1Stack");
noMaskVsCosThetaNeg1to1Stack->GetXaxis()->SetTitle("Cos #theta");
noMaskVsCosThetaNeg1to1Stack->GetYaxis()->SetTitle("allTrks");
noMaskVsCosThetaNeg1to1Stack->GetYaxis()->SetTitleOffset(1.4);
sprintf(c1PlotName,"%s.noMaskVsCosThetaNeg1to1.png",recoType);
c1->SaveAs(c1PlotName);
noMaskVsThetaStack->Draw();
noMaskVsThetaStack->SetTitle("noMaskVsThetaStack");
noMaskVsThetaStack->GetXaxis()->SetTitle("#theta");
noMaskVsThetaStack->GetYaxis()->SetTitle("allTrks");
noMaskVsThetaStack->GetYaxis()->SetTitleOffset(1.4);
sprintf(c1PlotName,"%s.noMaskVsTheta.png",recoType);
c1->SaveAs(c1PlotName);
noMaskVsThetaPerSAStack->Draw();
noMaskVsThetaPerSAStack->SetTitle("noMaskVsThetaPerSAStack");
noMaskVsThetaPerSAStack->GetXaxis()->SetTitle("#theta");
noMaskVsThetaPerSAStack->GetYaxis()->SetTitle("allTrks/d#Omega");
noMaskVsThetaPerSAStack->GetYaxis()->SetTitleOffset(1.4);
sprintf(c1PlotName,"%s.noMaskVsThetaPerSA.png",recoType);
c1->SaveAs(c1PlotName);
noMaskVsCosThetaStack->Draw();
noMaskVsCosThetaStack->SetTitle("noMaskVsCosThetaStack");
noMaskVsCosThetaStack->GetXaxis()->SetTitle("cos(#theta)");
noMaskVsCosThetaStack->GetYaxis()->SetTitle("allTrks");
noMaskVsCosThetaStack->GetYaxis()->SetTitleOffset(1.4);
sprintf(c1PlotName,"%s.noMaskVsCosTheta.png",recoType);
c1->SaveAs(c1PlotName);
noMaskVsCosThetaPerSAStack->Draw();
noMaskVsCosThetaPerSAStack->SetTitle("noMaskVsCosThetaPerSAStack");
noMaskVsCosThetaPerSAStack->GetXaxis()->SetTitle("cos(#theta)");
noMaskVsCosThetaPerSAStack->GetYaxis()->SetTitle("allTrks/d#Omega");
noMaskVsCosThetaPerSAStack->GetYaxis()->SetTitleOffset(1.4);
sprintf(c1PlotName,"%s.noMaskVsCosThetaPerSA.png",recoType);
c1->SaveAs(c1PlotName);

THStack *cftVsTheta0to180Stack = new THStack("cftVsTheta0to180Stack","");
THStack *cftVsCosThetaNeg1to1Stack = new THStack("cftVsCosThetaNeg1to1Stack","");
THStack *cftVsThetaStack = new THStack("cftVsThetaStack","");
THStack *cftVsThetaPerSAStack = new THStack("cftVsThetaPerSAStack","");
THStack *cftVsCosThetaStack = new THStack("cftVsCosThetaStack","");
THStack *cftVsCosThetaPerSAStack = new THStack("cftVsCosThetaPerSAStack","");

cftVsTheta0to180Stack->Add(cftFragVsTheta0to180);
cftVsTheta0to180Stack->Add(cftNotFragVsTheta0to180);
cftVsCosThetaNeg1to1Stack->Add(cftFragVsCosThetaNeg1to1);
cftVsCosThetaNeg1to1Stack->Add(cftNotFragVsCosThetaNeg1to1);
cftVsThetaStack->Add(cftFragVsTheta);
cftVsThetaStack->Add(cftNotFragVsTheta);
cftVsThetaPerSAStack->Add(cftFragVsThetaPerSA);
cftVsThetaPerSAStack->Add(cftNotFragVsThetaPerSA);
cftVsCosThetaStack->Add(cftFragVsCosTheta);
cftVsCosThetaStack->Add(cftNotFragVsCosTheta);
cftVsCosThetaPerSAStack->Add(cftFragVsCosThetaPerSA);
cftVsCosThetaPerSAStack->Add(cftNotFragVsCosThetaPerSA);

cftVsTheta0to180Stack->Draw();
cftVsTheta0to180Stack->SetTitle("cftVsTheta0to180Stack");
cftVsTheta0to180Stack->GetXaxis()->SetTitle("#theta");
cftVsTheta0to180Stack->GetYaxis()->SetTitle("allTrks");
cftVsTheta0to180Stack->GetYaxis()->SetTitleOffset(1.4);
sprintf(c1PlotName,"%s.cftVsTheta0to180.png",recoType);
c1->SaveAs(c1PlotName);
cftVsCosThetaNeg1to1Stack->Draw();
cftVsCosThetaNeg1to1Stack->SetTitle("cftVsCosThetaNeg1to1Stack");
cftVsCosThetaNeg1to1Stack->GetXaxis()->SetTitle("Cos #theta");
cftVsCosThetaNeg1to1Stack->GetYaxis()->SetTitle("allTrks");
cftVsCosThetaNeg1to1Stack->GetYaxis()->SetTitleOffset(1.4);
sprintf(c1PlotName,"%s.cftVsCosThetaNeg1to1.png",recoType);
c1->SaveAs(c1PlotName);
cftVsThetaStack->Draw();
cftVsThetaStack->SetTitle("cftVsThetaStack");
cftVsThetaStack->GetXaxis()->SetTitle("#theta");
cftVsThetaStack->GetYaxis()->SetTitle("allTrks");
cftVsThetaStack->GetYaxis()->SetTitleOffset(1.4);
sprintf(c1PlotName,"%s.cftVsTheta.png",recoType);
c1->SaveAs(c1PlotName);
cftVsThetaPerSAStack->Draw();
cftVsThetaPerSAStack->SetTitle("cftVsThetaPerSAStack");
cftVsThetaPerSAStack->GetXaxis()->SetTitle("#theta");
cftVsThetaPerSAStack->GetYaxis()->SetTitle("allTrks/d#Omega");
cftVsThetaPerSAStack->GetYaxis()->SetTitleOffset(1.4);
sprintf(c1PlotName,"%s.cftVsThetaPerSA.png",recoType);
c1->SaveAs(c1PlotName);
cftVsCosThetaStack->Draw();
cftVsCosThetaStack->SetTitle("cftVsCosThetaStack");
cftVsCosThetaStack->GetXaxis()->SetTitle("cos(#theta)");
cftVsCosThetaStack->GetYaxis()->SetTitle("allTrks");
cftVsCosThetaStack->GetYaxis()->SetTitleOffset(1.4);
sprintf(c1PlotName,"%s.cftVsCosTheta.png",recoType);
c1->SaveAs(c1PlotName);
cftVsCosThetaPerSAStack->Draw();
cftVsCosThetaPerSAStack->SetTitle("cftVsCosThetaPerSAStack");
cftVsCosThetaPerSAStack->GetXaxis()->SetTitle("cos(#theta)");
cftVsCosThetaPerSAStack->GetYaxis()->SetTitle("allTrks/d#Omega");
cftVsCosThetaPerSAStack->GetYaxis()->SetTitleOffset(1.4);
sprintf(c1PlotName,"%s.cftVsCosThetaPerSA.png",recoType);
c1->SaveAs(c1PlotName);

///////////////////  write histograms to file ///////////////////
TFile* plotTreeHistgrams = new TFile("plotTreeHistgrams.root","recreate");
noMaskLvEn->Write();
cftLvEn->Write();
cftFrags->Write();
noMaskFrags->Write();
scaledCftFrags->Write();
cftFragsRebin->Write();
noMaskFragsRebin->Write();
cftEfficiency->Write();
cftFragsScaleRegion->Write();

fragCut->Write();
fragCutADC->Write();

noMaskFragVsTheta0to180->Write();
noMaskFragVsCosThetaNeg1to1->Write();
noMaskFragVsTheta->Write();
noMaskFragVsThetaPerSA->Write();
noMaskFragVsCosTheta->Write();
noMaskFragVsCosThetaPerSA->Write();
noMaskNotFragVsTheta0to180->Write();
noMaskNotFragVsCosThetaNeg1to1->Write();
noMaskNotFragVsTheta->Write();
noMaskNotFragVsThetaPerSA->Write();
noMaskNotFragVsCosTheta->Write();
noMaskNotFragVsCosThetaPerSA->Write();
cftFragVsTheta0to180->Write();
cftFragVsCosThetaNeg1to1->Write();
cftFragVsTheta->Write();
cftFragVsThetaPerSA->Write();
cftFragVsCosTheta->Write();
cftFragVsCosThetaPerSA->Write();
cftNotFragVsTheta0to180->Write();
cftNotFragVsCosThetaNeg1to1->Write();
cftNotFragVsTheta->Write();
cftNotFragVsThetaPerSA->Write();
cftNotFragVsCosTheta->Write();
cftNotFragVsCosThetaPerSA->Write();
noMaskVsTheta0to180Stack->Write();
noMaskVsCosThetaNeg1to1Stack->Write();
noMaskVsThetaStack->Write();
noMaskVsThetaPerSAStack->Write();
noMaskVsCosThetaStack->Write();
noMaskVsCosThetaPerSAStack->Write();
cftVsTheta0to180Stack->Write();
cftVsCosThetaNeg1to1Stack->Write();
cftVsThetaStack->Write();
cftVsThetaPerSAStack->Write();
cftVsCosThetaStack->Write();
cftVsCosThetaPerSAStack->Write();

}
