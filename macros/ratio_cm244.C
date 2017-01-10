#include "THStack.h"
#include <climits>
#include <vector>
#include "TROOT.h"
#include "TRint.h"
// #include "MsgLog.h"
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
#include "TStyle.h"
// #include "NiffteGeometryMap.h"
// #include "NifftePlotUtilities.h"

#include <math.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>


void ratio_cm244(const int preamp) {

char noMaskFileName[345];
char cftFileName[345];

TCutG *fragCut = new TCutG("fragCut",8);
fragCut->SetLineColor(kViolet);
fragCut->SetLineWidth(3);

TPolyLine* fragPoly = new TPolyLine(13,"");
fragPoly->SetFillColorAlpha(kViolet,0.25);
fragPoly->SetLineColor(kViolet);
fragPoly->SetLineWidth(3);

char noMaskCut[345] = "";
char cftCut[345] = "";

if (preamp==1)
{
	sprintf(noMaskCut,"run!=100001995 && fitType==5");
	sprintf(cftCut,"fitType==5");
	sprintf(noMaskFileName,"$trees/rev3821/cm244/cmNoMask1.trees.root");
	sprintf(cftFileName,"$trees/rev3821/cm244/noAlphas.cmCFT1.trees.root");

	fragCut->SetPoint(0,2.71991,1.03077);
	fragCut->SetPoint(1,15,1.9);
	fragCut->SetPoint(2,35,2.35);
	fragCut->SetPoint(3,71,3.15);
	fragCut->SetPoint(4,150,3.65);
	fragCut->SetPoint(5,150,0.5);
	fragCut->SetPoint(6,2.01991,0.5);
	fragCut->SetPoint(7,2.11991,0.573987);
	fragCut->SetPoint(8,2.21991,0.648579);
	fragCut->SetPoint(9,2.31991,0.723779);
	fragCut->SetPoint(10,2.41991,0.799594);
	fragCut->SetPoint(11,2.51991,0.876028);
	fragCut->SetPoint(12,2.61991,0.953086);
	fragCut->SetPoint(13,2.71991,1.03077);
}
else if (preamp==2)
{
	sprintf(noMaskCut,"!(-1<direction.Phi()&&direction.Phi()<0) && fitType==5");
	sprintf(   cftCut,"!(-1<direction.Phi()&&direction.Phi()<0) && fitType==5");
	sprintf(noMaskFileName,"$trees/rev3821/cm244/cmNoMask2.trees.root");
	sprintf(cftFileName,"$trees/rev3821/cm244/noAlphas.cmCFT2.trees.root");

	fragCut->SetPoint(0,2.49341,0.982877);
	fragCut->SetPoint(1,15,1.9);
	fragCut->SetPoint(2,35,2.35);
	fragCut->SetPoint(3,71,3.15);
	fragCut->SetPoint(4,150,3.65);
	fragCut->SetPoint(5,150,0.5);
	fragCut->SetPoint(6,1.59341,0.5);
	fragCut->SetPoint(7,1.69341,0.55162);
	fragCut->SetPoint(8,1.79341,0.603737);
	fragCut->SetPoint(9,1.89341,0.656355);
	fragCut->SetPoint(10,1.99341,0.709481);
	fragCut->SetPoint(11,2.09341,0.763117);
	fragCut->SetPoint(12,2.19341,0.81727);
	fragCut->SetPoint(13,2.29341,0.871945);
	fragCut->SetPoint(14,2.39341,0.927145);
	fragCut->SetPoint(15,2.49341,0.982877);
}



std::cout <<"noMaskCut = " << noMaskCut << std::endl;
std::cout <<"cftCut = " << cftCut << std::endl;

TFile* cftFile = new TFile(cftFileName);
TFile* noMaskFile = new TFile(noMaskFileName);
TTree* noMaskTracks = (TTree*)noMaskFile->Get("tracks");
TTree* cftTracks = (TTree*)cftFile->Get("tracks");
TH2D* noMaskLvEn = new TH2D("noMaskLvEn","noMaskLvEn",4000,1,168.6,100,0,10);
TH2D* cftLvEn = new TH2D("cftLvEn","cftLvEn",4000,1,168.6,100,0,10);

TCanvas *c1 = new TCanvas("c1","c1",1000,700);
char c1PlotName[345];
// gStyle->SetOptStat(0);

cftLvEn->GetXaxis()->SetTitle("Track Energy [MeV]");
cftLvEn->GetXaxis()->CenterTitle();
cftLvEn->GetYaxis()->SetTitle("Track Length [cm]");
cftLvEn->GetYaxis()->CenterTitle();
cftLvEn->SetTitle(cftCut);
cftTracks->Draw("length:adc*168.6/40000>>cftLvEn",cftCut,"colz");

c1->SetLogx(1);
c1->SaveAs("cftLvEn.logx.png");
cftLvEn->Draw("[fragCut] && colz");
c1->SaveAs("cftLvEn.logx.fragCut.png");
fragCut->Draw("same");
c1->SaveAs("cftLvEn.logx.showFragCut.png");
c1->SetLogx(0);
c1->SaveAs("cftLvEn.png");
cftLvEn->Draw("[fragCut] && colz");
c1->SaveAs("cftLvEn.fragCut.png");
fragCut->Draw("same");
c1->SaveAs("cftLvEn.showFragCut.png");

noMaskLvEn->GetXaxis()->SetTitle("Track Energy [MeV]");
noMaskLvEn->GetXaxis()->CenterTitle();
noMaskLvEn->GetYaxis()->SetTitle("Track Length [cm]");
noMaskLvEn->GetYaxis()->CenterTitle();
noMaskLvEn->SetTitle(noMaskCut);
noMaskTracks->Draw("length:adc*168.6/40000>>noMaskLvEn",noMaskCut,"colz");
noMaskLvEn->Draw("[fragCut] && colz");
c1->SetLogz(1);
c1->SetLogx(1);
c1->SaveAs("noMaskLvEn.logx.png");
noMaskLvEn->Draw("colz");
c1->SaveAs("noMaskLvEn.logx.fragCut.png");
fragCut->Draw("same");
c1->SaveAs("noMaskLvEn.logx.showFragCut.png");
c1->SetLogx(0);
c1->SaveAs("noMaskLvEn.png");
noMaskLvEn->Draw("[fragCut] && colz");
c1->SaveAs("noMaskLvEn.fragCut.png");
fragCut->Draw("same");
c1->SaveAs("noMaskLvEn.showFragCut.png");

}
