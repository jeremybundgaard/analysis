#include "TRint.h"
#include "TROOT.h"
#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "runtimeCalc.C"
#include "runList.C"

void alphaRate(const char* actinide,int preamp){

	const char* treeFileName;
	bool fissionTrigger=0;
	std::vector<std::string> runs = runList(actinide,preamp,fissionTrigger);

	Double_t runtime,alphaRate;
	UInt_t runNumber,nAlphas;
	TTree* alphaRateTree = new TTree("alphaRateTree","alphaRateTree");
	alphaRateTree->Branch("runtime",&runtime);
	alphaRateTree->Branch("nAlphas",&nAlphas);
	alphaRateTree->Branch("runNumber",&runNumber);
	alphaRateTree->Branch("alphaRate",&alphaRate);
	TH1D* alphaRateHist = new TH1D("alphaRateHist","alphaRateHist",20,7800,8000);

	for (std::vector<std::string>::iterator runsIter = runs.begin() ; runsIter != runs.end(); ++runsIter){
		treeFileName = runsIter->c_str();
		runtime = runtimeCalc(treeFileName);
		TFile* trackFile = new TFile(treeFileName);
		TTree* tracks = (TTree*)trackFile->Get("tracks");
		TH1D* adcHist = new TH1D("adcHist","adcHist",4000,0,40000);
		tracks->Draw("adc>>adcHist");
		nAlphas = adcHist->Integral(0,20000);
		runNumber = stoi(runsIter->substr(67,4));
		alphaRate = nAlphas/runtime;
		alphaRateHist->Fill(alphaRate);

	
		cout<<"runFile: "<< *runsIter <<endl;
		cout<<"runNumber: "<< runNumber <<endl;
		cout<<"runtime: "<<runtime <<endl;
		cout<<"nAlphas: "<<nAlphas <<endl;
		cout<<"alphaRate: "<< nAlphas/runtime <<'\n'<<endl;
	}

	TCanvas *c1 = new TCanvas("c1","c1",1000,700);
	char buff[56];
	sprintf(buff,"noMask.preamp%d.alphaHist.png",preamp);
	alphaRateHist->Draw();
	alphaRateHist->GetXaxis()->SetTitle("alphaRate");
 	c1->SaveAs(buff);

	sprintf(buff,"alphaRate%d.trees.root",preamp);
	TFile* f = new TFile(buff,"recreate");
	alphaRateHist->Write();
	alphaRateTree->Write();
}
