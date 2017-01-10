
#include "TROOT.h"
#include "TRint.h"
#include "TH2.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TStyle.h"

void niffteTreePlots(const char* infile, const char* trackCut) {

TFile* trackFile = new TFile(infile);
TTree* tracks = (TTree*)trackFile->Get("tracks");
char histName[345],plotName[345];

UInt_t runNumber;
tracks->SetBranchAddress("run",&runNumber);
tracks->GetEntry(0);

TCanvas *c1 = new TCanvas("c1","c1",1000,700);
gStyle->SetOptStat(0);
gStyle->SetPalette(55);
gStyle->SetNumberContours(999);


c1->SetLogz(1);
TH2D* lVsEn = new TH2D("lVsEn","lVsEn",10000,0.3,180,200,0,10);
lVsEn->GetXaxis()->SetTitle("energy [MeV]");
lVsEn->GetYaxis()->SetTitle("length [cm]");
sprintf(histName,"%d.lVsEn{%s}",runNumber,trackCut);
lVsEn->SetTitle(histName);
tracks->Draw("length:adc/200>>lVsEn",trackCut,"colz");
sprintf(plotName,"lVsEn.%d.png",runNumber);
c1->SaveAs(plotName);
c1->SetLogx(1);
lVsEn->Draw("colz");
sprintf(plotName,"lVsEn.logx.%d.png",runNumber);
c1->SaveAs(plotName);
c1->SetLogx(0);

c1->SetLogy(1);
TH2D* enVsAz = new TH2D("enVsAz","enVsAz",200,-3.2,3.2,10000,0.3,180); 
enVsAz->GetXaxis()->SetTitle("#phi [radians]");
enVsAz->GetYaxis()->SetTitle("energy [MeV]");
sprintf(histName,"%d.enVsAz{%s}",runNumber,trackCut);
enVsAz->SetTitle(histName);
enVsAz->GetYaxis()->SetRangeUser(0.1,170);
tracks->Draw("adc/200:direction.Phi()>>enVsAz",trackCut,"colz");
sprintf(plotName,"enVsAz.%d.png",runNumber);
c1->SaveAs(plotName);

TH2D* enVsPolar = new TH2D("enVsPolar","enVsPolar",200,0,3.2,10000,0.3,180);
enVsPolar->GetXaxis()->SetTitle("#theta [radians]");
enVsPolar->GetYaxis()->SetTitle("energy [MeV]");
sprintf(histName,"%d.enVsPolar{%s}",runNumber,trackCut);
enVsPolar->SetTitle(histName);
enVsPolar->GetYaxis()->SetRangeUser(0.1,170);
tracks->Draw("adc/200:direction.Theta()>>enVsPolar",trackCut,"colz");
sprintf(plotName,"enVsPolar.%d.png",runNumber);
c1->SaveAs(plotName);

TH2D* enVsCosPolar = new TH2D("enVsCosPolar","enVsCosPolar",200,-1,1,10000,0.3,180);
enVsCosPolar->GetXaxis()->SetTitle("cos(#theta)");
enVsCosPolar->GetYaxis()->SetTitle("energy [MeV]");
sprintf(histName,"%d.enVsCosPolar{%s}",runNumber,trackCut);
enVsCosPolar->SetTitle(histName);
enVsCosPolar->GetYaxis()->SetRangeUser(0.1,170);	
tracks->Draw("adc/200:direction.CosTheta()>>enVsCosPolar",trackCut,"colz");
sprintf(plotName,"enVsCosPolar.%d.png",runNumber);
c1->SaveAs(plotName);
c1->SetLogy(0);

TH2D* xyStart = new TH2D("xyStart","xyStart",1000,-7,7,1000,-7,7);
xyStart->GetXaxis()->SetTitle("x [cm]");
xyStart->GetYaxis()->SetTitle("y [cm]");
sprintf(histName,"%d.xyStart{%s}",runNumber,trackCut);
xyStart->SetTitle(histName);
tracks->Draw("start.x():start.y()>>xyStart",trackCut,"colz");
sprintf(plotName,"xyStart.%d.png",runNumber);
c1->SaveAs(plotName);

TH2D* xyEnd = new TH2D("xyEnd","xyEnd",1000,-7,7,1000,-7,7);
xyEnd->GetXaxis()->SetTitle("x [cm]");
xyEnd->GetYaxis()->SetTitle("y [cm]");
sprintf(histName,"%d.xyEnd{%s}",runNumber,trackCut);
xyEnd->SetTitle(histName);
tracks->Draw("end.x():end.y()>>xyEnd",trackCut,"colz");
sprintf(plotName,"xyEnd.%d.png",runNumber);
c1->SaveAs(plotName);

TH1D* en = new TH1D("en","en",10000,0.3,180);
en->GetXaxis()->SetTitle("energy [MeV]");
tracks->Draw("adc/200>>en","fitType==5","");
sprintf(plotName,"en.%d.png",runNumber);
c1->SaveAs(plotName);
c1->SetLogy(1);
en->Draw("colz");
sprintf(plotName,"en.log.%d.png",runNumber);
c1->SaveAs(plotName);
c1->SetLogy(0);

TH1D* length = new TH1D("length","length",200,0,10);
length->GetXaxis()->SetTitle("length [cm]");
tracks->Draw("length>>length",trackCut,"");
sprintf(plotName,"length.%d.png",runNumber);
c1->SaveAs(plotName);
c1->SetLogy(1);
length->Draw("colz");
sprintf(plotName,"length.log.%d.png",runNumber);
c1->SaveAs(plotName);
c1->SetLogy(0);

TH1D* az = new TH1D("az","az",200,-3.2,3.2);
az->GetXaxis()->SetTitle("#phi [radians]");
tracks->Draw("direction.Phi()>>az",trackCut,"");
sprintf(plotName,"az.%d.png",runNumber);
c1->SaveAs(plotName);

TH1D* cosPolar = new TH1D("cosPolar","cosPolar",200,-1,1);
cosPolar->GetXaxis()->SetTitle("cos(#theta)");
tracks->Draw("direction.CosTheta()>>cosPolar",trackCut,"");
sprintf(plotName,"cosPolar.%d.png",runNumber);
c1->SaveAs(plotName);

TH1D* polar = new TH1D("polar","polar",200,0,3.2);
polar->GetXaxis()->SetTitle("#theta [radians]");
tracks->Draw("direction.Theta()>>polar",trackCut,"");
sprintf(plotName,"polar.%d.png",runNumber);
c1->SaveAs(plotName);


}
