#include "TRint.h"
#include "TROOT.h"
#include "TTree.h"
#include "TText.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TFile.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <stdio.h>


Double_t runtimeCalc(const char* treeFileName) {

	TFile* trackFile = new TFile(treeFileName);
	TTree* tracks = (TTree*)trackFile->Get("tracks");

	Double_t runtime;
 	Int_t eventID;
	Int_t nentries = tracks->GetEntries();
	UInt_t runNumber;
	ULong64_t tick;
	ULong64_t stopTick;
	ULong64_t startTick;
	ULong64_t diffTick;
	char runNumChar[324];
	char runtimeChar[324];
	long diffPerEntry = 0;
	long adjust = 0;
	std::vector<long> tickVec;

	tracks->SetBranchAddress("eventID",&eventID);
	tracks->SetBranchAddress("tick",&tick);
	tracks->SetBranchAddress("run",&runNumber);

	tracks->GetEntry(0);
	startTick = tick;
	tickVec.push_back(startTick);

	TH1D* tickVsEntry = new TH1D("tickVsEntry","tickVsEntry",nentries,0,nentries);

	for (int entry = 1; entry < nentries; ++entry)
	{

		tracks->GetEntry(entry);
		tickVec.push_back(tick - adjust);
		diffPerEntry=tickVec.at(entry)-tickVec.at(entry-1);

		// cout<<entry<<'\t'<<tickVec.at(entry)<<'\t'<<tickVec.at(entry-1)<<'\t'<<diffPerEntry<<endl;

		if (diffPerEntry > 900000000000)
		{
			adjust=diffPerEntry;
			tickVec.pop_back();
			tickVec.push_back(tick - adjust);		
		}

		tickVsEntry->SetBinContent(entry,tickVec.at(entry));
	}


	stopTick = tickVec.at(nentries-1);
	diffTick   = stopTick-startTick;
	runtime   = diffTick/(double)50000000;

	sprintf(runtimeChar,"runtime = %f",runtime);
	TText *timeText = new TText(.2,.8,runtimeChar);
	timeText->SetTextAlign(12);
	timeText->SetTextColor(kRed);
	timeText->SetTextFont(43);
	timeText->SetTextSize(40);
	timeText->SetNDC();
	sprintf(runNumChar,"%d",runNumber);
	TText *runNumText = new TText(.2,.7,runNumChar);
	runNumText->SetTextAlign(12);
	runNumText->SetTextColor(kBlue);
	runNumText->SetTextFont(43);
	runNumText->SetTextSize(40);
	runNumText->SetNDC();
	gStyle->SetOptStat(0);
	char plotname[234];
	// tickVsEntry->Draw();
	// runNumText->Draw("same");
	// timeText->Draw("same");
	// sprintf(plotname,"tick%d.png",runNumber);
	// c1->SaveAs(plotname);

	// sprintf(runNumChar,"%d.difftick",runNumber);
	// cout<<runNumChar<<endl;
	// ofstream outFile;
	// outFile.open(runNumChar);
	// outFile<<"startTick = "<<startTick<<endl;
	// outFile<<"stopTick = "<<stopTick<<endl;
	// outFile<<"diffTick = "<<diffTick<<endl;
	// outFile<<"runtime = "<<runtime<<endl;
	// outFile.close();
	
	// cout<<"runNumber = "<<runNumber<<endl;
	// cout<<"startTick = "<<startTick<<endl;
	// cout<<"stopTick = "<<stopTick<<endl;
	// cout<<"diffTick = "<<diffTick<<endl;
	// cout<<"runtime = "<<runtime<<endl;
	
	delete trackFile;
	return runtime;

}
