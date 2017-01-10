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
#include "TGaxis.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TGaxis.h"
#include "TChain.h"
#include "TTree.h"
#include "TPaletteAxis.h"
#include "TPaveText.h"
#include "TObjArray.h"
#include "TMath.h"
#include "TLine.h"
#include "TMarker.h"
#include "TLegend.h"
#include "TLatex.h"

#include "NiffteGeometryMap.h"
#include "NifftePlotUtilities.h"

#include <math.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>


void nDigitDependence2ndPreamp() {

TFile* cftFile = new TFile("/Users/jeremy/niffte/trees/cfCFT.2ndPreamp.trees.2068-9.root");
TFile* noMaskFile = new TFile("/Users/jeremy/niffte/trees/cfNoMask.2ndPreamp.trees.2057-61.root");
// TFile* cftFile = new TFile("/Users/jeremy/niffte/trees/hkReco.cfCFT.2ndPreamp.trees.2068-9.root");
// TFile* noMaskFile = new TFile("/Users/jeremy/niffte/trees/hkReco.cfNoMask.2ndPreamp.trees.2057-61.root");

TTree* noMaskTracks = (TTree*)noMaskFile->Get("tracks");
TTree* cftTracks = (TTree*)cftFile->Get("tracks");

std::stringstream nDigCut;
double origin=0;
char pngname[123];

//// fission fragment cuts
TCutG *fragCutSimple = new TCutG("fragCutSimple",8);
fragCutSimple->SetLineColor(kTeal-6);
fragCutSimple->SetPoint(0,  1,1.45-0.75);
fragCutSimple->SetPoint(1, 15,2.25-0.75);
fragCutSimple->SetPoint(2, 35,2.70-0.75);
fragCutSimple->SetPoint(3, 71,3.50-0.75);
fragCutSimple->SetPoint(4,150,4.00-0.75);
fragCutSimple->SetPoint(5,150,2.00-0.75);
fragCutSimple->SetPoint(6,  1,0.75-0.75);
fragCutSimple->SetPoint(7,  1,1.45-0.75);

TCutG *fragCut = new TCutG("fragCut",8);
fragCutSimple->SetLineColor(kTeal-6);
fragCut->SetPoint(0,2,0.700327);
fragCut->SetPoint(1,15,1.5);
fragCut->SetPoint(2,35,1.95);
fragCut->SetPoint(3,71,2.75);
fragCut->SetPoint(4,150,3.25);
fragCut->SetPoint(5,150,1.25);
fragCut->SetPoint(6,1,0);
fragCut->SetPoint(7,1,0.295582);
fragCut->SetPoint(8,1.2,0.363805);
fragCut->SetPoint(9,1.4,0.438273);
fragCut->SetPoint(10,1.6,0.519138);
fragCut->SetPoint(11,1.8,0.606485);
fragCut->SetPoint(12,2,0.700327);

// fragCut->SetPoint(13,2.2,0.800597);
// fragCut->SetPoint(14,2.4,0.907136);
// fragCut->SetPoint(15,2.6,1.01969);
// fragCut->SetPoint(16,2.8,1.1379);
// fragCut->SetPoint(17,3,1.26131);


//// polar loop
for (int nDig = 0; nDig <= 40; nDig+=2){

	TCanvas *c1 = new TCanvas("c1","c1",1000,700);
	gStyle->SetOptStat(0);

	nDigCut.str("");
    nDigCut<<"nDigits < "<< nDig <<" && fitType==10 && trackNo==1";
	std::cout << nDigCut.str().c_str() << std::endl;

	TH2D * noMaskLvEn = new TH2D("noMaskLvEn","",40000,0,168.6,1000,0,10);
	TH2D * cftLvEn = new TH2D("cftLvEn","",40000,0,168.6,1000,0,10);

	cftLvEn->GetXaxis()->SetTitle("Track Energy [MeV]");
	cftLvEn->GetXaxis()->CenterTitle();
	cftLvEn->GetYaxis()->SetTitle("Track Length [cm]");
	cftLvEn->GetYaxis()->CenterTitle();
	cftLvEn->SetTitle(nDigCut.str().c_str());
	cftTracks->Draw("length:adc*168.6/40000>>cftLvEn",nDigCut.str().c_str());

	// TH1D * cftFrags = cftLvEn->ProjectionX("cftFrags",0,40000,"[fragCut]");
	// cftFrags->GetXaxis()->SetTitle("MeV");
	// cftFrags->GetXaxis()->CenterTitle();
	// cftFrags->GetYaxis()->SetTitle("counts");
	// cftFrags->GetYaxis()->CenterTitle();
	// cftFrags->SetTitle("fragCut [Fission Trigger]");
	// cftFrags->SetLineColor(9);
	// cftFrags->SetLineWidth(2);

	noMaskLvEn->GetXaxis()->SetTitle("Track Energy [MeV]");
	noMaskLvEn->GetXaxis()->CenterTitle();
	noMaskLvEn->GetYaxis()->SetTitle("Track Length [cm]");
	noMaskLvEn->GetYaxis()->CenterTitle();
	noMaskLvEn->SetTitle(nDigCut.str().c_str());
	noMaskTracks->Draw("length:adc*168.6/40000>>noMaskLvEn",nDigCut.str().c_str());

	// TH1D * noMaskFrags = noMaskLvEn->ProjectionX("noMaskFrags",0,40000,"[fragCut]");
	// noMaskFrags->GetXaxis()->SetTitle("MeV");
	// noMaskFrags->GetXaxis()->CenterTitle();
	// noMaskFrags->GetYaxis()->SetTitle("counts");
	// noMaskFrags->GetYaxis()->CenterTitle();
	// noMaskFrags->SetTitle("fragCut [No Trigger]");
	// noMaskFrags->SetLineColor(2);
	// noMaskFrags->SetLineWidth(2);

	// // double scaleCFT = noMaskFrags->Integral(5000,40000)/cftFrags->Integral(5000,40000);
	// // TH1D* scaledCftFrags = (TH1D*)cftFrags->Clone("scaledCftFrags");
	// // scaledCftFrags->Scale(scaleCFT);

	// //////////////////////////////////////////
	// //////////////  rebinning ////////////////
	// //////////////////////////////////////////
	// int rebinInt=10;
	// TH1D* cftFragsRebin = (TH1D*)scaledCftFrags->Clone("cftFragsRebin");
	// cftFragsRebin->Rebin(rebinInt);
	// TH1D* noMaskFragsRebin = (TH1D*)noMaskFrags->Clone("noMaskFragsRebin");
	// noMaskFragsRebin->Rebin(rebinInt);

	// TH1D* cftEfficiency = (TH1D*)cftFragsRebin->Clone("cftEfficiency");
	// cftEfficiency->SetTitle("cftEfficiency = cft / noMask");
	// cftEfficiency->Divide(noMaskFragsRebin);


	//////////////////////////////////////////////////////////////////
	///////////////////////  Plot fragment cut ///////////////////////
	//////////////////////////////////////////////////////////////////

	// c1->SetGridx(1);
	// c1->SetGridy(1);
	// c1->SetLogx(1);
	// c1->SetLogy(1);
	// cftFragsRebin->GetXaxis()->SetRangeUser(1,150);
	// cftFragsRebin->Draw();
	// char charContainer[128];
	// sprintf(pngname,"frags.full.cft.2ndPreamp.above%0.3dDigits.png",nDig);
	// c1->SaveAs(pngname,"recreate");

	// noMaskFragsRebin->GetXaxis()->SetRangeUser(1,150);
	// noMaskFragsRebin->SetMaximum(noMaskFragsRebin->GetMaximum());
	// noMaskFragsRebin->Draw();
	// sprintf(pngname,"frags.full.noMask.2ndPreamp.above%0.3dDigits.png",nDig);
	// c1->SaveAs(pngname,"recreate");

	// TLegend *legend1=new TLegend(0.6,0.15,0.8,0.25);
	// legend1->SetTextFont(42);
	// legend1->SetTextSize(0.03);
	// legend1->SetFillColor(kWhite);
	// legend1->AddEntry(noMaskFragsRebin,"No Trigger");
	// legend1->AddEntry(cftFragsRebin,"Fission Trigger");

	// // cft & noMask fragment same plot
	// noMaskFragsRebin->GetXaxis()->SetRangeUser(1,150);
	// cftFragsRebin->GetXaxis()->SetRangeUser(1,150);
	// c1->SetLogx(1);
	// c1->SetLogy(1);
	// noMaskFragsRebin->Draw();
	// noMaskFragsRebin->SetTitle("fragCut [Tirgger vs No Trigger]");
	// cftFragsRebin->Draw("same");
	// legend1->Draw("same");
	// sprintf(pngname,"bothFragsCut.withFits.2ndPreamp.above%0.3dDigits.png",nDig);
	// c1->SaveAs(pngname,"recreate");
	// c1->SetLogx(0);
	// noMaskFragsRebin->SetMinimum(1);
	// noMaskFragsRebin->GetXaxis()->SetRangeUser(1,150);
	// cftFragsRebin->GetXaxis()->SetRangeUser(1,150);
	// cftFragsRebin->Draw("same");
	// legend1->Draw("same");
	// sprintf(pngname,"lowEn.plusCFT.2ndPreamp.above%0.3dDigits.png",nDig);
	// c1->SaveAs(pngname,"recreate");

	// TLegend *legendCFTefficiency=new TLegend(0.6,0.15,0.8,0.3);
	// legendCFTefficiency->SetTextFont(42);
	// legendCFTefficiency->SetTextSize(0.03);
	// legendCFTefficiency->SetFillColor(kWhite);
	// legendCFTefficiency->AddEntry(noMaskFragsRebin,"No Trigger");
	// legendCFTefficiency->AddEntry(cftFragsRebin,"Fission Trigger");
	// legendCFTefficiency->AddEntry(cftEfficiency,"CFT Efficiency");

	// // cft efficiency -> noMask / cft fragments
	// c1->SetLogx(0);
	// c1->SetLogy(0);
	// noMaskFragsRebin->GetXaxis()->SetRangeUser(1,20);
	// cftFragsRebin->GetXaxis()->SetRangeUser(1,20);
	// cftEfficiency->GetXaxis()->SetRangeUser(1,20);
	// cftEfficiency->SetLineColor(6);
	// cftEfficiency->Draw();
	// sprintf(pngname,"cftEfficiency.2ndPreamp.above%0.3dDigits.png",nDig);
	// c1->SaveAs(pngname,"recreate");
	// noMaskFragsRebin->SetMinimum(0.001);
	// noMaskFragsRebin->Draw();
	// cftFragsRebin->Draw("same");
	// cftEfficiency->Draw("same");
	// legendCFTefficiency->Draw("same");
	// sprintf(pngname,"cftEfficiencyWithFrags.2ndPreamp.above%0.3dDigits.png",nDig);
	// c1->SaveAs(pngname,"recreate");

	// c1->SetLogy(1);
	// cftEfficiency->GetXaxis()->SetRangeUser(1,20);
	// cftEfficiency->SetLineColor(6);
	// cftEfficiency->Draw();
	// sprintf(pngname,"cftEfficiency.log.2ndPreamp.above%0.3dDigits.png",nDig);
	// c1->SaveAs(pngname,"recreate");
	// noMaskFragsRebin->SetMinimum(0.001);
	// noMaskFragsRebin->Draw();
	// cftFragsRebin->Draw("same");
	// cftEfficiency->Draw("same");
	// legendCFTefficiency->Draw("same");
	// sprintf(pngname,"cftEfficiencyWithFrags.log.2ndPreamp.above%0.3dDigits.png",nDig);
	// c1->SaveAs(pngname,"recreate");

	// ///////////////////////////////////////////////////////////////////
	// ///////////////////////  Plot lenght VS ADC ///////////////////////
	// ///////////////////////////////////////////////////////////////////
	c1->cd();
	c1->SetGridy(0);
	c1->SetGridx(0);
	c1->SetLogy(0);
	c1->SetLogx(1);
	cftLvEn->GetXaxis()->SetRangeUser(0.01,150);
	cftLvEn->GetYaxis()->SetRangeUser(0,10);
	cftLvEn->Draw("colz");
	sprintf(pngname,"cftLvEn.full.log.above%0.3dDigits.png",nDig);
	c1->SaveAs(pngname,"recreate");
	cftLvEn->GetYaxis()->SetRangeUser(0,2);
	sprintf(pngname,"cftLvEn.full.log.zoom.above%0.3dDigits.png",nDig);
	c1->SaveAs(pngname,"recreate");

	c1->cd();
	c1->SetLogx(0);
	cftLvEn->GetXaxis()->SetRangeUser(0.01,150);
	cftLvEn->GetYaxis()->SetRangeUser(0,2);
	cftLvEn->Draw("Colz");
	fragCut->Draw("same");
	sprintf(pngname,"cftLvEn.full.above%0.3dDigits.png",nDig);
	c1->SaveAs(pngname,"recreate");

	c1->cd();
	c1->SetLogx(0);
	cftLvEn->GetXaxis()->SetRangeUser(0.01,6);
	cftLvEn->Draw("Colz");
	fragCut->Draw("same");
	sprintf(pngname,"cftLvEn.lowEn.above%0.3dDigits.png",nDig);
	c1->SaveAs(pngname,"recreate");

	c1->cd();
	c1->SetLogx(1);
	noMaskLvEn->GetXaxis()->SetRangeUser(0.01,150);
	noMaskLvEn->GetYaxis()->SetRangeUser(0,10);
	noMaskLvEn->Draw("colz");
	sprintf(pngname,"noMaskLvEn.full.log.above%0.3dDigits.png",nDig);
	c1->SaveAs(pngname,"recreate");
	noMaskLvEn->GetYaxis()->SetRangeUser(0,2);
	sprintf(pngname,"noMaskLvEn.full.log.zoom.above%0.3dDigits.png",nDig);
	c1->SaveAs(pngname,"recreate");

	c1->cd();
	c1->SetLogx(0);
	noMaskLvEn->GetXaxis()->SetRangeUser(0.01,150);
	noMaskLvEn->GetYaxis()->SetRangeUser(0,2);
	noMaskLvEn->Draw("Colz");
	// fragCut->Draw("same");
	sprintf(pngname,"noMaskLvEn.full.above%0.3dDigits.png",nDig);
	c1->SaveAs(pngname,"recreate");

	c1->cd();
	c1->SetLogx(0);
	noMaskLvEn->GetXaxis()->SetRangeUser(0.01,6);
	noMaskLvEn->Draw("Colz");
	fragCut->Draw("same");
	sprintf(pngname,"noMaskLvEn.lowEn.above%0.3dDigits.png",nDig);
	c1->SaveAs(pngname,"recreate");

	}
}
