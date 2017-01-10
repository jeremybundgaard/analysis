#include "TCanvas.h"
#include "TCut.h"
#include "TCutG.h"
#include "TDirectory.h"
#include "TF1.h"
#include "TFile.h"
#include "TGraphErrors.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "THStack.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TLine.h"
#include "TList.h"
#include "TMarker.h"
#include "TMath.h"
#include "TPaveStats.h"
#include "TPaveText.h"
#include "TPolyLine3D.h"
#include "TPolyMarker3D.h"
#include "TROOT.h"
#include "TRint.h"
#include "TString.h"
#include "TStyle.h"
#include "TText.h"
#include "TTree.h"
#include "TVector3.h"

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace std;
using namespace RooFit;

void MakeLVsADCPlotWithLegend(TH2F *lvsADCHist, TString histName, TCanvas *c1);
Double_t RooFitAlphasTwoExpGaus(TH1 *alphaHistAll);
Double_t RooFitFragsTwoExpGaus(TH1 *fragHistAll);

void extrapolation(const char *infile) {
  TFile *trackFile = new TFile(infile);
  trackFile->cd();
  TTree *tracks = (TTree *)trackFile->Get("tracks");

  TCutG *frag_cut = new TCutG("frag_cut", 6);
  frag_cut->SetVarX("adc");
  frag_cut->SetVarY("length");
  frag_cut->SetPoint(0, 500, .95);
  frag_cut->SetPoint(1, 500, .5);
  frag_cut->SetPoint(2, 30000, .5);
  frag_cut->SetPoint(3, 30000, 3.5);
  frag_cut->SetPoint(4, 4000, 2);
  frag_cut->SetPoint(5, 500, .95);
  frag_cut->SetFillColorAlpha(kViolet, 0.3);

  TCutG *alpha_cut = new TCutG("alpha_cut", 7);
  alpha_cut->SetVarX("adc");
  alpha_cut->SetVarY("length");
  alpha_cut->SetPoint(0, 840, 2.5);
  alpha_cut->SetPoint(1, 1080, 3.4);
  alpha_cut->SetPoint(2, 1300, 4.7);
  alpha_cut->SetPoint(3, 1650, 4.7);
  alpha_cut->SetPoint(4, 1650, 4.2);
  alpha_cut->SetPoint(5, 1150, 2.5);
  alpha_cut->SetPoint(6, 840, 2.5);
  alpha_cut->SetFillColorAlpha(kSpring, 0.3);

  TCutG *middle_alpha_cut = new TCutG("middle_alpha_cut", 6);
  middle_alpha_cut->SetVarX("adc");
  middle_alpha_cut->SetVarY("length");
  middle_alpha_cut->SetPoint(0, 840, 2.5);
  middle_alpha_cut->SetPoint(1, 1150, 2.5);
  middle_alpha_cut->SetPoint(2, 800, 1.4);
  middle_alpha_cut->SetPoint(3, 500, .95);
  middle_alpha_cut->SetPoint(4, 500, 1.6);
  middle_alpha_cut->SetPoint(5, 840, 2.5);
  middle_alpha_cut->SetFillColorAlpha(kTeal, 0.3);

  TCutG *left_cut = new TCutG("left_cut", 6);
  left_cut->SetVarX("adc");
  left_cut->SetVarY("length");
  left_cut->SetPoint(0, 840, 2.5);
  left_cut->SetPoint(1, 1080, 3.4);
  left_cut->SetPoint(2, 1300, 4.7);
  left_cut->SetPoint(3, 700, 4.7);
  left_cut->SetPoint(4, 500, 2.7);
  left_cut->SetPoint(5, 840, 2.5);
  left_cut->SetFillColorAlpha(kRed + 1, 0.3);

  TCutG *middle_left_cut = new TCutG("middle_left_cut", 7);
  middle_left_cut->SetVarX("adc");
  middle_left_cut->SetVarY("length");
  middle_left_cut->SetPoint(0, 500, 2.7);
  middle_left_cut->SetPoint(1, 840, 2.5);
  middle_left_cut->SetPoint(2, 500, 1.6);
  middle_left_cut->SetPoint(3, 325, 1.1);
  middle_left_cut->SetPoint(4, 100, 1);
  middle_left_cut->SetPoint(5, 100, 2.7);
  middle_left_cut->SetPoint(6, 500, 2.7);
  middle_left_cut->SetFillColorAlpha(kYellow, 0.3);

  TCutG *junk_cut = new TCutG("junk_cut", 7);
  junk_cut->SetVarX("adc");
  junk_cut->SetVarY("length");
  junk_cut->SetPoint(0, 325, 1.1);
  junk_cut->SetPoint(1, 500, 1.6);
  junk_cut->SetPoint(2, 500, .95);
  junk_cut->SetPoint(3, 500, .5);
  junk_cut->SetPoint(4, 100, .2);
  junk_cut->SetPoint(5, 100, 1);
  junk_cut->SetPoint(6, 325, 1.1);
  junk_cut->SetFillColorAlpha(kOrange + 7, 0.3);

  TFile *cutTreeFile = new TFile("cutTreeFile", "recreate");
  cutTreeFile->cd();
  TString cut = "fitType == 5 && !(direction.Phi()>-1 && direction.Phi()<0)";
  TTree *cutTree = (TTree *)tracks->CopyTree(cut);

  TCanvas *c1 = new TCanvas("c1", "c1", 1000, 700);
  gStyle->SetOptStat(0);
  TH2F *lvsADC = new TH2F("lvsADC", "lvsADC", 3000, 90, 30000, 200, 0, 6);
  lvsADC->GetXaxis()->SetTitle("adc");
  lvsADC->GetYaxis()->SetTitle("length [cm]");
  lvsADC->SetTitle("Length Vs Energy");
  tracks->Draw("length:adc>>lvsADC", cut, "colz");
  Double_t junkCount = junk_cut->IntegralHist(lvsADC);
  MakeLVsADCPlotWithLegend(lvsADC, "lvsADC", c1);

  alphaBins = (2000 - 100) / 10;
  TH1D *alphaHistAll =
      new TH1D("alphaHistAll", "alphaHistAll", alphaBins, 100, 2000);
  alphaHistAll->GetXaxis()->SetTitle("Energy [adc]");
  alphaHistAll->GetYaxis()->SetTitle("counts");
  alphaHistAll->SetTitle("Fragment Region");
  alphaHistAll->SetFillColor(kTeal + 5);

  TString junkAlphaFragCut =
      cut + "&& (alpha_cut || middle_alpha_cut || junk_cut || frag_cut)";
  tracks->Draw("length:adc>>lvsADC", junkAlphaFragCut, "colz");
  MakeLVsADCPlotWithLegend(lvsADC, "regions_of_interest_lvsADC", c1);

  TString alphaCut = cut + " && (alpha_cut || middle_alpha_cut)";
  tracks->Draw("length:adc>>lvsADC", alphaCut, "colz");
  // MakeLVsADCPlotWithLegend(lvsADC,"alpha_cut_lvsADC",c1);
  tracks->Draw("adc>>alphaHistAll", alphaCut);
  Double_t roofit_alpha_count_norm = RooFitAlphasTwoExpGaus(alphaHistAll);
  Double_t roofit_alpha_count =
      roofit_alpha_count_norm * alphaHistAll->GetEntries();

  fragBins = (30000 - 100) / 100;
  TH1D *fragHistAll =
      new TH1D("fragHistAll", "fragHistAll", fragBins, 100, 30000);
  fragHistAll->GetXaxis()->SetTitle("Energy [adc]");
  fragHistAll->GetYaxis()->SetTitle("counts");
  fragHistAll->SetTitle("Fragment Region");
  fragHistAll->SetFillColor(kViolet);

  // TString junkCut = cut + " && junk_cut";
  // tracks->Draw("length:adc>>lvsADC",junkCut,"colz");
  // MakeLVsADCPlotWithLegend(lvsADC,"junk_cut_lvsADC",c1);

  TString fragCut = cut + " && frag_cut";
  // lvsADC->Clear();
  // tracks->Draw("length:adc>>lvsADC",fragCut,"colz");
  // MakeLVsADCPlotWithLegend(lvsADC,"frag_cut_lvsADC",c1);
  tracks->Draw("adc>>fragHistAll", fragCut);
  Double_t roofit_frag_count_norm = RooFitFragsTwoExpGaus(fragHistAll);
  Double_t roofit_frag_count =
      roofit_frag_count_norm * fragHistAll->GetEntries();

  cout << "alpha extrapolation count: " << roofit_alpha_count << endl;
  cout << "frag extrapolation count: " << roofit_frag_count << endl;
  cout << "junk count: " << junkCount << endl;

  // // Double_t alphaExtrapolation = alphaFit->Integral(100,600);
  // Double_t fragExtrapolation = fragFit->Integral(100,600);
  // cout << "alpha extrapolation count: " << alphaExtrapolation << endl;
  // cout << "frag extrapolation count: " << fragExtrapolation << endl;
  // Double_t sum = alphaExtrapolation + fragExtrapolation;
  // cout << "sum: " << sum << endl;
  // cout << "junk_cut count: " << junkCount << endl;
  Double_t percentDiff =
      TMath::Abs(((roofit_alpha_count + roofit_frag_count) - junkCount)) /
      (junkCount)*100;
  cout << "percentDiff: " << percentDiff << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////Fitting the entire alpha histogram with convolution of Gaussian and
/// two exponentials //////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
Double_t RooFitAlphasTwoExpGaus(TH1 *alphaHistAll) {
  TCanvas *canvas = new TCanvas("canvas", "canvas", 1000, 700);
  RooRealVar x("x", "x", 500, 2000);
  RooDataHist *alphaHist =
      new RooDataHist("alphaHist", "alphaHist", x, Import(*alphaHistAll));

  // RooRealVar A("A","A",2,1,10);
  RooRealVar n("n", "n", .2, 0, 1.);
  RooRealVar to("to", "to", 900, 100, 1500);
  RooRealVar xbar("xbar", "xbar", 1450, 1300, 1550);
  RooRealVar s("s", "s", 60, 10, 150);
  RooRealVar tt("tt", "tt", 120, 20, 200);
  RooGenericPdf *gausTwoExpConv =
      new RooGenericPdf("gausTwoExpConv", "gausTwoExpConv",
                        "n/to*exp((x-xbar)/to+s^2/(2*to^2))*TMath::Erfc(1/"
                        "TMath::Sqrt(2)*((x-xbar)/s+s/to)) + "
                        "(1-n)/tt*exp((x-xbar)/tt+s^2/(2*tt^2))*TMath::Erfc(1/"
                        "TMath::Sqrt(2)*((x-xbar)/s+s/tt))",
                        RooArgList(x, n, to, xbar, s, tt));

  gausTwoExpConv->fitTo(*alphaHist);

  RooPlot *preFitFrame = x.frame(Title("Alpha Region Energy Projection"));
  alphaHist->plotOn(preFitFrame, RooFit::MarkerColor(kTeal + 5));
  preFitFrame->GetXaxis()->SetTitle("ADC");
  preFitFrame->Draw();
  canvas->SaveAs("alpha_energy_projection.png");

  RooPlot *frame = x.frame(Title(
      "Alpha Region fit with Convolution of a Gaussian and Two Exponentials"));
  alphaHist->plotOn(frame, RooFit::MarkerColor(kTeal + 5));
  gausTwoExpConv->plotOn(frame, RooFit::LineColor(kRed));
  frame->GetXaxis()->SetTitle("ADC");

  frame->Draw();
  canvas->SaveAs("roofit_alpha_convolution.png");
  canvas->SetLogx(1);
  canvas->SaveAs("roofit_alpha_convolution_logx.png");
  canvas->SetLogy(1);
  canvas->SaveAs("roofit_alpha_convolution_logxy.png");

  canvas->SetLogx(0);
  canvas->SetLogy(0);
  gausTwoExpConv->paramOn(frame);
  frame->Draw();
  canvas->SaveAs("roofit_alpha_convolution_params.png");

  x.setRange("integralRange", 100, 2000);
  RooAbsReal *integral =
      gausTwoExpConv->createIntegral(x, NormSet(x), Range("integralRange"));
  Double_t integral_result = integral->getVal();

  return integral_result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////Fitting the entire frag histogram with convolution of Gaussian and
/// two exponentials //////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
Double_t RooFitFragsTwoExpGaus(TH1 *fragHistAll) {
  TCanvas *canvas = new TCanvas("canvas", "canvas", 1000, 700);
  RooRealVar x("x", "x", 500, 30000);
  RooDataHist *fragHist =
      new RooDataHist("fragHist", "fragHist", x, Import(*fragHistAll));

  RooRealVar n("n", "n", .2, 0, 1.);
  RooRealVar to("to", "to", 900, 1, 1000);
  RooRealVar xbar("xbar", "xbar", 15000, 13000, 17000);
  RooRealVar s("s", "s", 12000, 100, 5000);
  RooRealVar tt("tt", "tt", 50000, 20, 80000);
  RooGenericPdf *gausTwoExpConv =
      new RooGenericPdf("gausTwoExpConv", "gausTwoExpConv",
                        "n/to*exp((x-xbar)/to+s^2/(2*to^2))*TMath::Erfc(1/"
                        "TMath::Sqrt(2)*((x-xbar)/s+s/to)) + "
                        "(1-n)/tt*exp((x-xbar)/tt+s^2/(2*tt^2))*TMath::Erfc(1/"
                        "TMath::Sqrt(2)*((x-xbar)/s+s/tt))",
                        RooArgList(x, n, to, xbar, s, tt));

  // RooRealVar A("A","A",2,1,10);
  RooRealVar n_l("n_l", "n_l", .2, .1, 1.);
  RooRealVar to_l("to_l", "to_l", 1000, 500, 3000);
  RooRealVar xbar_l("xbar_l", "xbar_l", 15000, 13000, 20000);
  RooRealVar s_l("s_l", "s_l", 4500, 300, 7000);
  RooRealVar tt_l("tt_l", "tt_l", 50000, 1000, 80000);
  RooGenericPdf *gausTwoExpConv_l = new RooGenericPdf(
      "gausTwoExpConv_l", "gausTwoExpConv_l",
      "n_l/to_l*exp((x-xbar_l)/to_l+s_l^2/(2*to_l^2))*TMath::Erfc(1/"
      "TMath::Sqrt(2)*((x-xbar_l)/s_l+s_l/to_l)) + "
      "(1-n_l)/tt_l*exp((x-xbar_l)/tt_l+s_l^2/(2*tt_l^2))*TMath::Erfc(1/"
      "TMath::Sqrt(2)*((x-xbar_l)/s_l+s_l/tt_l))",
      RooArgList(x, n_l, to_l, xbar_l, s_l, tt_l));

  RooRealVar n_r("n_r", "n_r", .2, .1, 1.);
  RooRealVar to_r("to_r", "to_r", 5000, 500, 10000);
  RooRealVar xbar_r("xbar_r", "xbar_r", 21000, 19000, 25000);
  RooRealVar s_r("s_r", "s_r", 2000, 600, 4000);
  RooRealVar tt_r("tt_r", "tt_r", 50000, 1000, 80000);
  RooGenericPdf *gausTwoExpConv_r = new RooGenericPdf(
      "gausTwoExpConv_r", "gausTwoExpConv_r",
      "n_r/to_r*exp((x-xbar_r)/to_r+s_r^2/(2*to_r^2))*TMath::Erfc(1/"
      "TMath::Sqrt(2)*((x-xbar_r)/s_r+s_r/to_r)) + "
      "(1-n_r)/tt_r*exp((x-xbar_r)/tt_r+s_r^2/(2*tt_r^2))*TMath::Erfc(1/"
      "TMath::Sqrt(2)*((x-xbar_r)/s_r+s_r/tt_r))",
      RooArgList(x, n_r, to_r, xbar_r, s_r, tt_r));
  RooRealVar coef("coef", "coef", .08, 0., 1.);
  RooAddPdf *gausTwoExpConv_tot =
      new RooAddPdf("gausTwoExpConv_tot", "gausTwoExpConv_tot",
                    *gausTwoExpConv_l, *gausTwoExpConv_r, coef);

  gausTwoExpConv_tot->fitTo(*fragHist);

  RooPlot *preFitFrame = x.frame(Title("Fragment Region Energy Projection"));
  fragHist->plotOn(preFitFrame, RooFit::MarkerColor(kViolet));
  preFitFrame->GetXaxis()->SetTitle("ADC");
  preFitFrame->Draw();
  canvas->SaveAs("frag_energy_projection.png");

  RooPlot *frame =
      x.frame(Title("Fragment Region Fit With the Sum of Two Convolutions"));
  frame->GetXaxis()->SetTitle("ADC");
  fragHist->plotOn(frame, RooFit::MarkerColor(kViolet));
  gausTwoExpConv_tot->plotOn(frame, RooFit::Components(*gausTwoExpConv_l),
                             RooFit::LineColor(kBlue), RooFit::LineStyle(2));
  gausTwoExpConv_tot->plotOn(frame, RooFit::Components(*gausTwoExpConv_r),
                             RooFit::LineColor(kOrange), RooFit::LineStyle(2));
  gausTwoExpConv_tot->plotOn(frame, RooFit::LineColor(kRed));
  frame->Draw();
  canvas->SaveAs("roofit_frag_convolution.png");
  canvas->SetLogx(1);
  canvas->SaveAs("roofit_frag_convolution_logx.png");
  canvas->SetLogy(1);
  canvas->SaveAs("roofit_frag_convolution_logxy.png");

  canvas->SetLogx(0);
  canvas->SetLogy(0);
  gausTwoExpConv_tot->paramOn(frame);
  frame->Draw();
  canvas->SaveAs("roofit_frag_convolution_params.png");

  // RooRealVar integral_range("integral_range","integral_range",100,600);
  // RooAbsReal* integral_value = gausTwoExpConv_tot->createIntegral(x);
  x.setRange("integralRange", 100, 30000);
  RooAbsReal *integral =
      gausTwoExpConv_tot->createIntegral(x, NormSet(x), Range("integralRange"));
  Double_t integral_result = integral->getVal();
  cout << "integral result: " << integral_result << endl;

  return integral_result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Making Legends for the Length vs Energy Histograms
/////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MakeLVsADCPlotWithLegend(TH2F *lvsADCHist, TString histName, TCanvas *c1) {

  TCutG *frag_cut = new TCutG("frag_cut", 6);
  frag_cut->SetVarX("adc");
  frag_cut->SetVarY("length");
  frag_cut->SetPoint(0, 500, .95);
  frag_cut->SetPoint(1, 500, .5);
  frag_cut->SetPoint(2, 30000, .5);
  frag_cut->SetPoint(3, 30000, 3.5);
  frag_cut->SetPoint(4, 4000, 2);
  frag_cut->SetPoint(5, 500, .95);
  frag_cut->SetFillColorAlpha(kViolet, 0.3);

  TCutG *alpha_cut = new TCutG("alpha_cut", 7);
  alpha_cut->SetVarX("adc");
  alpha_cut->SetVarY("length");
  alpha_cut->SetPoint(0, 840, 2.5);
  alpha_cut->SetPoint(1, 1080, 3.4);
  alpha_cut->SetPoint(2, 1300, 4.7);
  alpha_cut->SetPoint(3, 1650, 4.7);
  alpha_cut->SetPoint(4, 1650, 4.2);
  alpha_cut->SetPoint(5, 1150, 2.5);
  alpha_cut->SetPoint(6, 840, 2.5);
  alpha_cut->SetFillColorAlpha(kSpring, 0.3);

  TCutG *middle_alpha_cut = new TCutG("middle_alpha_cut", 6);
  middle_alpha_cut->SetVarX("adc");
  middle_alpha_cut->SetVarY("length");
  middle_alpha_cut->SetPoint(0, 840, 2.5);
  middle_alpha_cut->SetPoint(1, 1150, 2.5);
  middle_alpha_cut->SetPoint(2, 800, 1.4);
  middle_alpha_cut->SetPoint(3, 500, .95);
  middle_alpha_cut->SetPoint(4, 500, 1.6);
  middle_alpha_cut->SetPoint(5, 840, 2.5);
  middle_alpha_cut->SetFillColorAlpha(kTeal, 0.3);

  TCutG *left_cut = new TCutG("left_cut", 6);
  left_cut->SetVarX("adc");
  left_cut->SetVarY("length");
  left_cut->SetPoint(0, 840, 2.5);
  left_cut->SetPoint(1, 1080, 3.4);
  left_cut->SetPoint(2, 1300, 4.7);
  left_cut->SetPoint(3, 700, 4.7);
  left_cut->SetPoint(4, 500, 2.7);
  left_cut->SetPoint(5, 840, 2.5);
  left_cut->SetFillColorAlpha(kRed + 1, 0.3);

  TCutG *middle_left_cut = new TCutG("middle_left_cut", 7);
  middle_left_cut->SetVarX("adc");
  middle_left_cut->SetVarY("length");
  middle_left_cut->SetPoint(0, 500, 2.7);
  middle_left_cut->SetPoint(1, 840, 2.5);
  middle_left_cut->SetPoint(2, 500, 1.6);
  middle_left_cut->SetPoint(3, 325, 1.1);
  middle_left_cut->SetPoint(4, 100, 1);
  middle_left_cut->SetPoint(5, 100, 2.7);
  middle_left_cut->SetPoint(6, 500, 2.7);
  middle_left_cut->SetFillColorAlpha(kYellow, 0.3);

  TCutG *junk_cut = new TCutG("junk_cut", 7);
  junk_cut->SetVarX("adc");
  junk_cut->SetVarY("length");
  junk_cut->SetPoint(0, 325, 1.1);
  junk_cut->SetPoint(1, 500, 1.6);
  junk_cut->SetPoint(2, 500, .95);
  junk_cut->SetPoint(3, 500, .5);
  junk_cut->SetPoint(4, 100, .2);
  junk_cut->SetPoint(5, 100, 1);
  junk_cut->SetPoint(6, 325, 1.1);
  junk_cut->SetFillColorAlpha(kOrange + 7, 0.3);

  gStyle->SetOptStat(0);

  Double_t frag_cut_count = frag_cut->IntegralHist(lvsADCHist);
  Double_t alpha_cut_count = alpha_cut->IntegralHist(lvsADCHist);
  Double_t middle_alpha_cut_count = middle_alpha_cut->IntegralHist(lvsADCHist);
  Double_t middle_left_cut_count = middle_left_cut->IntegralHist(lvsADCHist);
  Double_t left_cut_count = left_cut->IntegralHist(lvsADCHist);
  Double_t junk_cut_count = junk_cut->IntegralHist(lvsADCHist);
  Double_t total_counts = lvsADCHist->Integral();
  Double_t other_cut_count =
      total_counts -
      (frag_cut_count + alpha_cut_count + middle_alpha_cut_count +
       middle_left_cut_count + left_cut_count + junk_cut_count);

  TLegend *lvADC_legend = new TLegend(0.65, 0.65, 0.9, 0.9);
  lvADC_legend->AddEntry(
      frag_cut, TString::Format("counts: %.0f, %.3f %%", frag_cut_count,
                                frag_cut_count * 100 / total_counts),
      "f");
  lvADC_legend->AddEntry(
      alpha_cut, TString::Format("counts: %.0f, %.3f %%", alpha_cut_count,
                                 alpha_cut_count * 100 / total_counts),
      "f");
  lvADC_legend->AddEntry(
      middle_alpha_cut,
      TString::Format("counts: %.0f, %.3f %%", middle_alpha_cut_count,
                      middle_alpha_cut_count * 100 / total_counts),
      "f");
  lvADC_legend->AddEntry(
      middle_left_cut,
      TString::Format("counts: %.0f, %.3f %%", middle_left_cut_count,
                      middle_left_cut_count * 100 / total_counts),
      "f");
  lvADC_legend->AddEntry(
      left_cut, TString::Format("counts: %.0f, %.3f %%", left_cut_count,
                                left_cut_count * 100 / total_counts),
      "f");
  lvADC_legend->AddEntry(
      junk_cut, TString::Format("counts: %.0f, %.3f %%", junk_cut_count,
                                junk_cut_count * 100 / total_counts),
      "f");
  lvADC_legend->AddEntry(
      (TObject *)0, TString::Format("counts: %.0f, %.3f %%", other_cut_count,
                                    other_cut_count * 100 / total_counts),
      "f");

  lvsADCHist->Draw("colz");
  frag_cut->Draw("same f");
  left_cut->Draw("same f");
  junk_cut->Draw("same f");
  alpha_cut->Draw("same f");
  middle_alpha_cut->Draw("same f");
  middle_left_cut->Draw("same f");
  lvADC_legend->Draw("same");
  c1->SetLogx(1);
  c1->SetLogy(0);
  c1->SaveAs(histName + ".png");
  c1->SetLogx(0);
}
