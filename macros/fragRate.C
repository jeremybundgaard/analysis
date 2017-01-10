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
#include "fragCount.C"
#include "runList.C"

void fragRate(const char* actinide,int preamp){

	const char* treeFileName;
	bool fissionTrigger=1;
	std::vector<std::string> runs = runList(actinide,preamp,fissionTrigger);

	Double_t runtime,nFrags,fragmentRate;
	UInt_t runNumber;
	TTree* fragRateTree = new TTree("fragRateTree","fragRateTree");
	fragRateTree->Branch("runtime",&runtime);
	fragRateTree->Branch("nFrags",&nFrags);
	fragRateTree->Branch("runNumber",&runNumber);
	fragRateTree->Branch("fragmentRate",&fragmentRate);

	for (std::vector<std::string>::iterator runsIter = runs.begin() ; runsIter != runs.end(); ++runsIter){
		treeFileName = runsIter->c_str();
		runtime = runtimeCalc(treeFileName);
		nFrags = fragCount(treeFileName);
		runNumber = stoi(runsIter->substr(67,4));
		fragmentRate = nFrags/runtime;
		fragRateTree->Fill();
	
		cout<<"runFile: "<< *runsIter <<endl;
		cout<<"runNumber: "<< runNumber <<endl;
		cout<<"runtime: "<<runtime <<endl;
		cout<<"nFrags: "<<nFrags <<endl;
		cout<<"fragmentRate: "<< nFrags/runtime <<'\n'<<endl;
	}

	TCanvas *c1 = new TCanvas("c1","c1",1000,700);
	char buff[56];
	sprintf(buff,"cft.preamp%d.fragHist.png",preamp);
	TH1D* fr = new TH1D("fr","fragRate",50,0,0.1);
	fr->GetXaxis()->SetTitle("fragmentRate");
	fragRateTree->Draw("fragmentRate>>fr(100,0.0,0.1)");
 	c1->SaveAs(buff);

	sprintf(buff,"fragRate%d.trees.root",preamp);
	TFile* f = new TFile(buff,"recreate");
	fragRateTree->Write();
	fr->Write();
}
