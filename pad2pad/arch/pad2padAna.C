// NIFFTE Libraries
#include "NiffteRootIO.h"
#include "NiffteDataBucket.h"
#include "NiffteEventHandle.h"
#include "NiffteEventHandle.h"
#include "NiffteTPCTrack.h"
#include "NiffteTPCDigit.h"
#include "NiffteTPCADCSignal.h"
#include "NiffteMCParticle.h"
#include "NiffteMCHit.h"
#include "NiffteGeometryMap.h"
#include "NiffteAnalysisManager.h"
#include "AnaHistoList.h"
#include "AnaH1D.h"
#include "AnaH2D.h"
#include "AnaH2PadPlane.h"
#include "AnaH1DR.h"
#include "AnaH2DR.h"
#include "MsgLog.h"

// ROOT libraries
#include "TROOT.h"
#include "TRint.h"
#include "TObjArray.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include "TH2Poly.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TPaletteAxis.h"
#include "TGraph.h"
#include "TFile.h"
#include "TCutG.h"
#include "TStopwatch.h"

// C++ libraries
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <numeric>
#include <climits>
#include <vector>
#include <time.h>
#include <map>
#include <set>
#include <stdio.h>
#include <stdlib.h>



TObjArray *sigArray;
TObjArray *digArray;
TObjArray *trkArray;
NiffteGeometryMap* ngm = NiffteGeometryMap::Instance("v2_03");

void pad2padAna(const char* infile = "infile-list.txt", const char* outfile="Analysis-RunXXX.root", int nCutEvt = -1) {


// stopwatch
TStopwatch stopwatch; stopwatch.Start(); std::cout<<"starting stopwatch"<<std::endl;

///////////////////////////////////////////////////////////////////
////////////////  find centroid of charge  ////////////////////////
///////////////////////////////////////////////////////////////////
std::cout<<"finding centeriod of charge"<<std::endl;


////////////////  define/set loop variables   ////////////////////////
double xdig=0, ydig=0, radius=0;
double weightedChargeXvol0=0,weightedChargeYvol0=0,weightedChargeXvol1=0,weightedChargeYvol1=0;
double totalChargeXvol0=0,totalChargeYvol0=0,totalChargeXvol1=0,totalChargeYvol1=0;
double chargeCenterXvol0=0,chargeCenterYvol0=0,chargeCenterXvol1=0,chargeCenterYvol1=0;

////////////////  set analysis manager params   ////////////////////////
int iTrk = 0;
int volume=0;
std::string geo("v2_03");
std::string ofile(outfile);
NiffteAnalysisManager aMgrFindCentroid(infile,ofile,geo);
int nEventLimit=-1;
if(nEventLimit == -1){nEventLimit = INT_MAX;}
int nSkip = 0, SparseFactor = 0;
aMgrFindCentroid.Execute(nEventLimit,nSkip,SparseFactor);
TPCResult_t status;
while (true){
	status = aMgrFindCentroid.NextEvent();
	if (status != kTPCSuccess && status != kTPCNewRun )
		break;
  if(aMgrFindCentroid.EventNumber()%1000==0){
  	std::cout <<"centroiding events so far: " << aMgrFindCentroid.EventNumber() << std::endl;
		// std::cout<<"center of charge vol1: "<<chargeCenterXvol1<<","<<chargeCenterYvol1<<std::endl;
		// std::cout<<"center of charge vol0: "<<chargeCenterXvol0<<","<<chargeCenterYvol0<<std::endl;
	}
  if(aMgrFindCentroid.NTracks()==1)
  	continue;
	for(iTrk = 0; iTrk < aMgrFindCentroid.NTracks(); iTrk++){
	    //Digits______________________________________________
		for(int iDig = 0; iDig < aMgrFindCentroid.NDigits(); iDig++){

			const NiffteTPCDigit* currdig = aMgrFindCentroid.GetDigit(iDig);
			xdig=0;
			ydig=0;
			radius=0;
			ngm->MapVolRowColtoXY(currdig->Volume(),currdig->PadRow(),currdig->Column(),xdig,ydig);
			volume=currdig->Volume();
			if (volume==0)
			{
				weightedChargeXvol0 += xdig*currdig->ADC();
				totalChargeXvol0  += currdig->ADC();
				chargeCenterXvol0 = weightedChargeXvol0/totalChargeXvol0;

				weightedChargeYvol0 += ydig*currdig->ADC();
				totalChargeYvol0  += currdig->ADC();
				chargeCenterYvol0 = weightedChargeYvol0/totalChargeYvol0;
			}
			if (volume==1)
			{
				weightedChargeXvol1 += xdig*currdig->ADC();
				totalChargeXvol1  += currdig->ADC();
				chargeCenterXvol1 = weightedChargeXvol1/totalChargeXvol1;

				weightedChargeYvol1 += ydig*currdig->ADC();
				totalChargeYvol1  += currdig->ADC();
				chargeCenterYvol1 = weightedChargeYvol1/totalChargeYvol1;
			}
		}
	}
	if(!(nCutEvt > aMgrFindCentroid.EventNumber() || nCutEvt==-1))
	{
		std::cout<<"\n"<< aMgrFindCentroid.EventNumber() << " total centroiding events" << "\n"<<std::endl;
		std::cout << "center of charge in volume 0 = ( "<<chargeCenterXvol0<<" , "<<chargeCenterYvol0<<" )"<<endl;
		std::cout << "center of charge in volume 1 = ( "<<chargeCenterXvol1<<" , "<<chargeCenterYvol1<<" )"<<"\n" << endl;
		break;
	}
}
aMgrFindCentroid.Terminate();


////////////////////////////////////////////////////////
////////////////  annular anal  ////////////////////////
////////////////////////////////////////////////////////
std::cout<<"beginning annular analysis"<<std::endl;

////////////////  define intensity wrt annulus histograms  ////////////////////////
TH1D* intensityvol0 = new TH1D("intensityvol0","intensityvol0",100,0,1); TH1D* intensityvol1 = new TH1D("intensityvol1","intensityvol1",100,0,1);
TH1D* intensityvol0rad00to04 = new TH1D("intensityvol0rad00to04","intensityvol0rad00to04",100,0,1); TH1D* intensityvol1rad00to04 = new TH1D("intensityvol1rad00to04","intensityvol1rad00to04",100,0,1);
TH1D* intensityvol0rad04to08 = new TH1D("intensityvol0rad04to08","intensityvol0rad04to08",100,0,1); TH1D* intensityvol1rad04to08 = new TH1D("intensityvol1rad04to08","intensityvol1rad04to08",100,0,1);
TH1D* intensityvol0rad08to12 = new TH1D("intensityvol0rad08to12","intensityvol0rad08to12",100,0,1); TH1D* intensityvol1rad08to12 = new TH1D("intensityvol1rad08to12","intensityvol1rad08to12",100,0,1);
TH1D* intensityvol0rad12to16 = new TH1D("intensityvol0rad12to16","intensityvol0rad12to16",100,0,1); TH1D* intensityvol1rad12to16 = new TH1D("intensityvol1rad12to16","intensityvol1rad12to16",100,0,1);
TH1D* intensityvol0rad16to20 = new TH1D("intensityvol0rad16to20","intensityvol0rad16to20",100,0,1); TH1D* intensityvol1rad16to20 = new TH1D("intensityvol1rad16to20","intensityvol1rad16to20",100,0,1);
TH1D* intensityvol0rad20to24 = new TH1D("intensityvol0rad20to24","intensityvol0rad20to24",100,0,1); TH1D* intensityvol1rad20to24 = new TH1D("intensityvol1rad20to24","intensityvol1rad20to24",100,0,1);
TH1D* intensityvol0rad24to28 = new TH1D("intensityvol0rad24to28","intensityvol0rad24to28",100,0,1); TH1D* intensityvol1rad24to28 = new TH1D("intensityvol1rad24to28","intensityvol1rad24to28",100,0,1);
TH1D* intensityvol0rad28to32 = new TH1D("intensityvol0rad28to32","intensityvol0rad28to32",100,0,1); TH1D* intensityvol1rad28to32 = new TH1D("intensityvol1rad28to32","intensityvol1rad28to32",100,0,1);
TH1D* intensityvol0rad32to36 = new TH1D("intensityvol0rad32to36","intensityvol0rad32to36",100,0,1); TH1D* intensityvol1rad32to36 = new TH1D("intensityvol1rad32to36","intensityvol1rad32to36",100,0,1);
TH1D* intensityvol0rad36to40 = new TH1D("intensityvol0rad36to40","intensityvol0rad36to40",100,0,1); TH1D* intensityvol1rad36to40 = new TH1D("intensityvol1rad36to40","intensityvol1rad36to40",100,0,1);
TH1D* intensityvol0rad40to44 = new TH1D("intensityvol0rad40to44","intensityvol0rad40to44",100,0,1); TH1D* intensityvol1rad40to44 = new TH1D("intensityvol1rad40to44","intensityvol1rad40to44",100,0,1);
TH1D* intensityvol0rad44to48 = new TH1D("intensityvol0rad44to48","intensityvol0rad44to48",100,0,1); TH1D* intensityvol1rad44to48 = new TH1D("intensityvol1rad44to48","intensityvol1rad44to48",100,0,1);
TH1D* intensityvol0rad48to52 = new TH1D("intensityvol0rad48to52","intensityvol0rad48to52",100,0,1); TH1D* intensityvol1rad48to52 = new TH1D("intensityvol1rad48to52","intensityvol1rad48to52",100,0,1);
TH1D* intensityvol0rad52to56 = new TH1D("intensityvol0rad52to56","intensityvol0rad52to56",100,0,1); TH1D* intensityvol1rad52to56 = new TH1D("intensityvol1rad52to56","intensityvol1rad52to56",100,0,1);
TH1D* intensityvol0rad56to60 = new TH1D("intensityvol0rad56to60","intensityvol0rad56to60",100,0,1); TH1D* intensityvol1rad56to60 = new TH1D("intensityvol1rad56to60","intensityvol1rad56to60",100,0,1);
TH1D* intensityvol0rad60to64 = new TH1D("intensityvol0rad60to64","intensityvol0rad60to64",100,0,1); TH1D* intensityvol1rad60to64 = new TH1D("intensityvol1rad60to64","intensityvol1rad60to64",100,0,1);
TH1D* intensityvol0rad64to68 = new TH1D("intensityvol0rad64to68","intensityvol0rad64to68",100,0,1); TH1D* intensityvol1rad64to68 = new TH1D("intensityvol1rad64to68","intensityvol1rad64to68",100,0,1);
TH1D* intensityvol0rad68to72 = new TH1D("intensityvol0rad68to72","intensityvol0rad68to72",100,0,1); TH1D* intensityvol1rad68to72 = new TH1D("intensityvol1rad68to72","intensityvol1rad68to72",100,0,1);

////////////////  define annulus histograms  ////////////////////////
AnaH2PadPlane *hdigADCvol0 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol0"," ",0); AnaH2PadPlane *hdigADCvol1 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol1"," ",1);
AnaH2PadPlane *hdigADCvol0rad00to04 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol0rad00to04"," ",0); AnaH2PadPlane *hdigADCvol1rad00to04 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol1rad00to04"," ",1);
AnaH2PadPlane *hdigADCvol0rad04to08 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol0rad04to08"," ",0); AnaH2PadPlane *hdigADCvol1rad04to08 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol1rad04to08"," ",1);
AnaH2PadPlane *hdigADCvol0rad08to12 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol0rad08to12"," ",0); AnaH2PadPlane *hdigADCvol1rad08to12 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol1rad08to12"," ",1);
AnaH2PadPlane *hdigADCvol0rad12to16 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol0rad12to16"," ",0); AnaH2PadPlane *hdigADCvol1rad12to16 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol1rad12to16"," ",1);
AnaH2PadPlane *hdigADCvol0rad16to20 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol0rad16to20"," ",0); AnaH2PadPlane *hdigADCvol1rad16to20 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol1rad16to20"," ",1);
AnaH2PadPlane *hdigADCvol0rad20to24 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol0rad20to24"," ",0); AnaH2PadPlane *hdigADCvol1rad20to24 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol1rad20to24"," ",1);
AnaH2PadPlane *hdigADCvol0rad24to28 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol0rad24to28"," ",0); AnaH2PadPlane *hdigADCvol1rad24to28 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol1rad24to28"," ",1);
AnaH2PadPlane *hdigADCvol0rad28to32 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol0rad28to32"," ",0); AnaH2PadPlane *hdigADCvol1rad28to32 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol1rad28to32"," ",1);
AnaH2PadPlane *hdigADCvol0rad32to36 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol0rad32to36"," ",0); AnaH2PadPlane *hdigADCvol1rad32to36 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol1rad32to36"," ",1);
AnaH2PadPlane *hdigADCvol0rad36to40 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol0rad36to40"," ",0); AnaH2PadPlane *hdigADCvol1rad36to40 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol1rad36to40"," ",1);
AnaH2PadPlane *hdigADCvol0rad40to44 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol0rad40to44"," ",0); AnaH2PadPlane *hdigADCvol1rad40to44 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol1rad40to44"," ",1);
AnaH2PadPlane *hdigADCvol0rad44to48 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol0rad44to48"," ",0); AnaH2PadPlane *hdigADCvol1rad44to48 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol1rad44to48"," ",1);
AnaH2PadPlane *hdigADCvol0rad48to52 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol0rad48to52"," ",0); AnaH2PadPlane *hdigADCvol1rad48to52 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol1rad48to52"," ",1);
AnaH2PadPlane *hdigADCvol0rad52to56 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol0rad52to56"," ",0); AnaH2PadPlane *hdigADCvol1rad52to56 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol1rad52to56"," ",1);
AnaH2PadPlane *hdigADCvol0rad56to60 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol0rad56to60"," ",0); AnaH2PadPlane *hdigADCvol1rad56to60 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol1rad56to60"," ",1);
AnaH2PadPlane *hdigADCvol0rad60to64 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol0rad60to64"," ",0); AnaH2PadPlane *hdigADCvol1rad60to64 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol1rad60to64"," ",1);
AnaH2PadPlane *hdigADCvol0rad64to68 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol0rad64to68"," ",0); AnaH2PadPlane *hdigADCvol1rad64to68 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol1rad64to68"," ",1);
AnaH2PadPlane *hdigADCvol0rad68to72 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol0rad68to72"," ",0); AnaH2PadPlane *hdigADCvol1rad68to72 = new AnaH2PadPlane(NiffteGeometryMap::Instance(),"hdigADCvol1rad68to72"," ",1);

////////////////  define map of pairs  ////////////////////////
typedef map<pair<float,float>,pair<int,int> > mapPairInt2PairInt;

////////////////  define vol0 maps + iterators  ////////////////////////
mapPairInt2PairInt mapXY_totalDigADCvol0rad00to04; mapPairInt2PairInt::iterator mapXY_totalDigADCvol0rad00to04Iter;
mapPairInt2PairInt mapXY_totalDigADCvol0rad04to08; mapPairInt2PairInt::iterator mapXY_totalDigADCvol0rad04to08Iter;
mapPairInt2PairInt mapXY_totalDigADCvol0rad08to12; mapPairInt2PairInt::iterator mapXY_totalDigADCvol0rad08to12Iter;
mapPairInt2PairInt mapXY_totalDigADCvol0rad12to16; mapPairInt2PairInt::iterator mapXY_totalDigADCvol0rad12to16Iter;
mapPairInt2PairInt mapXY_totalDigADCvol0rad16to20; mapPairInt2PairInt::iterator mapXY_totalDigADCvol0rad16to20Iter;
mapPairInt2PairInt mapXY_totalDigADCvol0rad20to24; mapPairInt2PairInt::iterator mapXY_totalDigADCvol0rad20to24Iter;
mapPairInt2PairInt mapXY_totalDigADCvol0rad24to28; mapPairInt2PairInt::iterator mapXY_totalDigADCvol0rad24to28Iter;
mapPairInt2PairInt mapXY_totalDigADCvol0rad28to32; mapPairInt2PairInt::iterator mapXY_totalDigADCvol0rad28to32Iter;
mapPairInt2PairInt mapXY_totalDigADCvol0rad32to36; mapPairInt2PairInt::iterator mapXY_totalDigADCvol0rad32to36Iter;
mapPairInt2PairInt mapXY_totalDigADCvol0rad36to40; mapPairInt2PairInt::iterator mapXY_totalDigADCvol0rad36to40Iter;
mapPairInt2PairInt mapXY_totalDigADCvol0rad40to44; mapPairInt2PairInt::iterator mapXY_totalDigADCvol0rad40to44Iter;
mapPairInt2PairInt mapXY_totalDigADCvol0rad44to48; mapPairInt2PairInt::iterator mapXY_totalDigADCvol0rad44to48Iter;
mapPairInt2PairInt mapXY_totalDigADCvol0rad48to52; mapPairInt2PairInt::iterator mapXY_totalDigADCvol0rad48to52Iter;
mapPairInt2PairInt mapXY_totalDigADCvol0rad52to56; mapPairInt2PairInt::iterator mapXY_totalDigADCvol0rad52to56Iter;
mapPairInt2PairInt mapXY_totalDigADCvol0rad56to60; mapPairInt2PairInt::iterator mapXY_totalDigADCvol0rad56to60Iter;
mapPairInt2PairInt mapXY_totalDigADCvol0rad60to64; mapPairInt2PairInt::iterator mapXY_totalDigADCvol0rad60to64Iter;
mapPairInt2PairInt mapXY_totalDigADCvol0rad64to68; mapPairInt2PairInt::iterator mapXY_totalDigADCvol0rad64to68Iter;
mapPairInt2PairInt mapXY_totalDigADCvol0rad68to72; mapPairInt2PairInt::iterator mapXY_totalDigADCvol0rad68to72Iter;

////////////////  define vol0 dig & ADC counters  ////////////////////////
int runningTallyDigvol0rad00to04=0, runningTallyADCvol0rad00to04=0;
int runningTallyDigvol0rad04to08=0, runningTallyADCvol0rad04to08=0;
int runningTallyDigvol0rad08to12=0, runningTallyADCvol0rad08to12=0;
int runningTallyDigvol0rad12to16=0, runningTallyADCvol0rad12to16=0;
int runningTallyDigvol0rad16to20=0, runningTallyADCvol0rad16to20=0;
int runningTallyDigvol0rad20to24=0, runningTallyADCvol0rad20to24=0;
int runningTallyDigvol0rad24to28=0, runningTallyADCvol0rad24to28=0;
int runningTallyDigvol0rad28to32=0, runningTallyADCvol0rad28to32=0;
int runningTallyDigvol0rad32to36=0, runningTallyADCvol0rad32to36=0;
int runningTallyDigvol0rad36to40=0, runningTallyADCvol0rad36to40=0;
int runningTallyDigvol0rad40to44=0, runningTallyADCvol0rad40to44=0;
int runningTallyDigvol0rad44to48=0, runningTallyADCvol0rad44to48=0;
int runningTallyDigvol0rad48to52=0, runningTallyADCvol0rad48to52=0;
int runningTallyDigvol0rad52to56=0, runningTallyADCvol0rad52to56=0;
int runningTallyDigvol0rad56to60=0, runningTallyADCvol0rad56to60=0;
int runningTallyDigvol0rad60to64=0, runningTallyADCvol0rad60to64=0;
int runningTallyDigvol0rad64to68=0, runningTallyADCvol0rad64to68=0;
int runningTallyDigvol0rad68to72=0, runningTallyADCvol0rad68to72=0;

////////////////  define vol1 maps + iterators  ////////////////////////
mapPairInt2PairInt mapXY_totalDigADCvol1rad00to04; mapPairInt2PairInt::iterator mapXY_totalDigADCvol1rad00to04Iter;
mapPairInt2PairInt mapXY_totalDigADCvol1rad04to08; mapPairInt2PairInt::iterator mapXY_totalDigADCvol1rad04to08Iter;
mapPairInt2PairInt mapXY_totalDigADCvol1rad08to12; mapPairInt2PairInt::iterator mapXY_totalDigADCvol1rad08to12Iter;
mapPairInt2PairInt mapXY_totalDigADCvol1rad12to16; mapPairInt2PairInt::iterator mapXY_totalDigADCvol1rad12to16Iter;
mapPairInt2PairInt mapXY_totalDigADCvol1rad16to20; mapPairInt2PairInt::iterator mapXY_totalDigADCvol1rad16to20Iter;
mapPairInt2PairInt mapXY_totalDigADCvol1rad20to24; mapPairInt2PairInt::iterator mapXY_totalDigADCvol1rad20to24Iter;
mapPairInt2PairInt mapXY_totalDigADCvol1rad24to28; mapPairInt2PairInt::iterator mapXY_totalDigADCvol1rad24to28Iter;
mapPairInt2PairInt mapXY_totalDigADCvol1rad28to32; mapPairInt2PairInt::iterator mapXY_totalDigADCvol1rad28to32Iter;
mapPairInt2PairInt mapXY_totalDigADCvol1rad32to36; mapPairInt2PairInt::iterator mapXY_totalDigADCvol1rad32to36Iter;
mapPairInt2PairInt mapXY_totalDigADCvol1rad36to40; mapPairInt2PairInt::iterator mapXY_totalDigADCvol1rad36to40Iter;
mapPairInt2PairInt mapXY_totalDigADCvol1rad40to44; mapPairInt2PairInt::iterator mapXY_totalDigADCvol1rad40to44Iter;
mapPairInt2PairInt mapXY_totalDigADCvol1rad44to48; mapPairInt2PairInt::iterator mapXY_totalDigADCvol1rad44to48Iter;
mapPairInt2PairInt mapXY_totalDigADCvol1rad48to52; mapPairInt2PairInt::iterator mapXY_totalDigADCvol1rad48to52Iter;
mapPairInt2PairInt mapXY_totalDigADCvol1rad52to56; mapPairInt2PairInt::iterator mapXY_totalDigADCvol1rad52to56Iter;
mapPairInt2PairInt mapXY_totalDigADCvol1rad56to60; mapPairInt2PairInt::iterator mapXY_totalDigADCvol1rad56to60Iter;
mapPairInt2PairInt mapXY_totalDigADCvol1rad60to64; mapPairInt2PairInt::iterator mapXY_totalDigADCvol1rad60to64Iter;
mapPairInt2PairInt mapXY_totalDigADCvol1rad64to68; mapPairInt2PairInt::iterator mapXY_totalDigADCvol1rad64to68Iter;
mapPairInt2PairInt mapXY_totalDigADCvol1rad68to72; mapPairInt2PairInt::iterator mapXY_totalDigADCvol1rad68to72Iter;

////////////////  define vol1 dig & ADC counters  ////////////////////////
int runningTallyDigvol1rad00to04=0, runningTallyADCvol1rad00to04=0;
int runningTallyDigvol1rad04to08=0, runningTallyADCvol1rad04to08=0;
int runningTallyDigvol1rad08to12=0, runningTallyADCvol1rad08to12=0;
int runningTallyDigvol1rad12to16=0, runningTallyADCvol1rad12to16=0;
int runningTallyDigvol1rad16to20=0, runningTallyADCvol1rad16to20=0;
int runningTallyDigvol1rad20to24=0, runningTallyADCvol1rad20to24=0;
int runningTallyDigvol1rad24to28=0, runningTallyADCvol1rad24to28=0;
int runningTallyDigvol1rad28to32=0, runningTallyADCvol1rad28to32=0;
int runningTallyDigvol1rad32to36=0, runningTallyADCvol1rad32to36=0;
int runningTallyDigvol1rad36to40=0, runningTallyADCvol1rad36to40=0;
int runningTallyDigvol1rad40to44=0, runningTallyADCvol1rad40to44=0;
int runningTallyDigvol1rad44to48=0, runningTallyADCvol1rad44to48=0;
int runningTallyDigvol1rad48to52=0, runningTallyADCvol1rad48to52=0;
int runningTallyDigvol1rad52to56=0, runningTallyADCvol1rad52to56=0;
int runningTallyDigvol1rad56to60=0, runningTallyADCvol1rad56to60=0;
int runningTallyDigvol1rad60to64=0, runningTallyADCvol1rad60to64=0;
int runningTallyDigvol1rad64to68=0, runningTallyADCvol1rad64to68=0;
int runningTallyDigvol1rad68to72=0, runningTallyADCvol1rad68to72=0;


////////////////  set analysis manager params   ////////////////////////
NiffteAnalysisManager aMgrAnnularAna(infile,ofile,geo);
nEventLimit=-1;
int totNumEventsCurrentTally=0;
if(nEventLimit == -1){nEventLimit = INT_MAX;}
nSkip = 0, SparseFactor = 0;
aMgrAnnularAna.Execute(nEventLimit,nSkip,SparseFactor);
status;


while (true){
	status = aMgrAnnularAna.NextEvent();
	if (status != kTPCSuccess && status != kTPCNewRun ) break;
    if(aMgrAnnularAna.EventNumber()%1000==0)
    {
		std::cout << "annualar ana events so far: " << aMgrAnnularAna.EventNumber() << std::endl;
		totNumEventsCurrentTally+=1000;
    }
    if(aMgrAnnularAna.NTracks()==1)
    	continue;
	for(iTrk = 0; iTrk < aMgrAnnularAna.NTracks(); iTrk++){
	    //Digits______________________________________________
		for(int iDig = 0; iDig < aMgrAnnularAna.NDigits(); iDig++){
			const NiffteTPCDigit* currdig = aMgrAnnularAna.GetDigit(iDig);
			xdig=0;
			ydig=0;
			radius=0;
			ngm->MapVolRowColtoXY(currdig->Volume(),currdig->PadRow(),currdig->Column(),xdig,ydig);
			volume=currdig->Volume();

			if (volume==0)	
			{

				hdigADCvol0->Fill(xdig,ydig,currdig->ADC());

				radius = sqrt(pow(xdig - chargeCenterXvol0,2) + pow(ydig - chargeCenterYvol0,2));
				if (0.0 < radius && radius < 0.4 && currdig->ADC() <3000){
					hdigADCvol0rad00to04->Fill(xdig,ydig,currdig->ADC());
					runningTallyDigvol0rad00to04=mapXY_totalDigADCvol0rad00to04[make_pair(xdig,ydig)].first + currdig->ADC();
					runningTallyADCvol0rad00to04=mapXY_totalDigADCvol0rad00to04[make_pair(xdig,ydig)].second +1;
					mapXY_totalDigADCvol0rad00to04[make_pair(xdig,ydig)] = make_pair(runningTallyDigvol0rad00to04,runningTallyADCvol0rad00to04);
				}
				if (0.4 < radius && radius < 0.8 && currdig->ADC() <3000){
					hdigADCvol0rad04to08->Fill(xdig,ydig,currdig->ADC());
					runningTallyDigvol0rad04to08=mapXY_totalDigADCvol0rad04to08[make_pair(xdig,ydig)].first + currdig->ADC();
					runningTallyADCvol0rad04to08=mapXY_totalDigADCvol0rad04to08[make_pair(xdig,ydig)].second +1;
					mapXY_totalDigADCvol0rad04to08[make_pair(xdig,ydig)] = make_pair(runningTallyDigvol0rad04to08,runningTallyADCvol0rad04to08);
				}
				if (0.8 < radius && radius < 1.2 && currdig->ADC() <3000){
					hdigADCvol0rad08to12->Fill(xdig,ydig,currdig->ADC());
					runningTallyDigvol0rad08to12=mapXY_totalDigADCvol0rad08to12[make_pair(xdig,ydig)].first + currdig->ADC();
					runningTallyADCvol0rad08to12=mapXY_totalDigADCvol0rad08to12[make_pair(xdig,ydig)].second +1;
					mapXY_totalDigADCvol0rad08to12[make_pair(xdig,ydig)] = make_pair(runningTallyDigvol0rad08to12,runningTallyADCvol0rad08to12);
				}
				if (1.2 < radius && radius < 1.6 && currdig->ADC() <3000){
					hdigADCvol0rad12to16->Fill(xdig,ydig,currdig->ADC());
					runningTallyDigvol0rad12to16=mapXY_totalDigADCvol0rad12to16[make_pair(xdig,ydig)].first + currdig->ADC();
					runningTallyADCvol0rad12to16=mapXY_totalDigADCvol0rad12to16[make_pair(xdig,ydig)].second +1;
					mapXY_totalDigADCvol0rad12to16[make_pair(xdig,ydig)] = make_pair(runningTallyDigvol0rad12to16,runningTallyADCvol0rad12to16);
				}
				if (1.6 < radius && radius < 2.0 && currdig->ADC() <3000){
					hdigADCvol0rad16to20->Fill(xdig,ydig,currdig->ADC());
					runningTallyDigvol0rad16to20=mapXY_totalDigADCvol0rad16to20[make_pair(xdig,ydig)].first + currdig->ADC();
					runningTallyADCvol0rad16to20=mapXY_totalDigADCvol0rad16to20[make_pair(xdig,ydig)].second +1;
					mapXY_totalDigADCvol0rad16to20[make_pair(xdig,ydig)] = make_pair(runningTallyDigvol0rad16to20,runningTallyADCvol0rad16to20);
				}
				if (2.0 < radius && radius < 2.4 && currdig->ADC() <3000){
					hdigADCvol0rad20to24->Fill(xdig,ydig,currdig->ADC());
					runningTallyDigvol0rad20to24=mapXY_totalDigADCvol0rad20to24[make_pair(xdig,ydig)].first + currdig->ADC();
					runningTallyADCvol0rad20to24=mapXY_totalDigADCvol0rad20to24[make_pair(xdig,ydig)].second +1;
					mapXY_totalDigADCvol0rad20to24[make_pair(xdig,ydig)] = make_pair(runningTallyDigvol0rad20to24,runningTallyADCvol0rad20to24);
				}
				if (2.4 < radius && radius < 2.8 && currdig->ADC() <3000){
					hdigADCvol0rad24to28->Fill(xdig,ydig,currdig->ADC());
					runningTallyDigvol0rad24to28=mapXY_totalDigADCvol0rad24to28[make_pair(xdig,ydig)].first + currdig->ADC();
					runningTallyADCvol0rad24to28=mapXY_totalDigADCvol0rad24to28[make_pair(xdig,ydig)].second +1;
					mapXY_totalDigADCvol0rad24to28[make_pair(xdig,ydig)] = make_pair(runningTallyDigvol0rad24to28,runningTallyADCvol0rad24to28);
				}
				if (2.8 < radius && radius < 3.2 && currdig->ADC() <3000){
					hdigADCvol0rad28to32->Fill(xdig,ydig,currdig->ADC());
					runningTallyDigvol0rad28to32=mapXY_totalDigADCvol0rad28to32[make_pair(xdig,ydig)].first + currdig->ADC();
					runningTallyADCvol0rad28to32=mapXY_totalDigADCvol0rad28to32[make_pair(xdig,ydig)].second +1;
					mapXY_totalDigADCvol0rad28to32[make_pair(xdig,ydig)] = make_pair(runningTallyDigvol0rad28to32,runningTallyADCvol0rad28to32);
				}
				if (3.2 < radius && radius < 3.6 && currdig->ADC() <3000){
					hdigADCvol0->Fill(xdig,ydig,currdig->ADC());
					runningTallyDigvol0rad32to36=mapXY_totalDigADCvol0rad32to36[make_pair(xdig,ydig)].first + currdig->ADC();
					runningTallyADCvol0rad32to36=mapXY_totalDigADCvol0rad32to36[make_pair(xdig,ydig)].second +1;
					mapXY_totalDigADCvol0rad32to36[make_pair(xdig,ydig)] = make_pair(runningTallyDigvol0rad32to36,runningTallyADCvol0rad32to36);
				}
				if (3.6 < radius && radius < 4.0 && currdig->ADC() <3000){
					hdigADCvol0rad36to40->Fill(xdig,ydig,currdig->ADC());
					runningTallyDigvol0rad36to40=mapXY_totalDigADCvol0rad36to40[make_pair(xdig,ydig)].first + currdig->ADC();
					runningTallyADCvol0rad36to40=mapXY_totalDigADCvol0rad36to40[make_pair(xdig,ydig)].second +1;
					mapXY_totalDigADCvol0rad36to40[make_pair(xdig,ydig)] = make_pair(runningTallyDigvol0rad36to40,runningTallyADCvol0rad36to40);
				}
				if (4.0 < radius && radius < 4.4 && currdig->ADC() <3000){
					hdigADCvol0rad40to44->Fill(xdig,ydig,currdig->ADC());
					runningTallyDigvol0rad40to44=mapXY_totalDigADCvol0rad40to44[make_pair(xdig,ydig)].first + currdig->ADC();
					runningTallyADCvol0rad40to44=mapXY_totalDigADCvol0rad40to44[make_pair(xdig,ydig)].second +1;
					mapXY_totalDigADCvol0rad40to44[make_pair(xdig,ydig)] = make_pair(runningTallyDigvol0rad40to44,runningTallyADCvol0rad40to44);
				}
				if (4.4 < radius && radius < 4.8 && currdig->ADC() <3000){
					hdigADCvol0rad44to48->Fill(xdig,ydig,currdig->ADC());
					runningTallyDigvol0rad44to48=mapXY_totalDigADCvol0rad44to48[make_pair(xdig,ydig)].first + currdig->ADC();
					runningTallyADCvol0rad44to48=mapXY_totalDigADCvol0rad44to48[make_pair(xdig,ydig)].second +1;
					mapXY_totalDigADCvol0rad44to48[make_pair(xdig,ydig)] = make_pair(runningTallyDigvol0rad44to48,runningTallyADCvol0rad44to48);
				}
				if (4.8 < radius && radius < 5.2 && currdig->ADC() <3000){
					hdigADCvol0rad48to52->Fill(xdig,ydig,currdig->ADC());
					runningTallyDigvol0rad48to52=mapXY_totalDigADCvol0rad48to52[make_pair(xdig,ydig)].first + currdig->ADC();
					runningTallyADCvol0rad48to52=mapXY_totalDigADCvol0rad48to52[make_pair(xdig,ydig)].second +1;
					mapXY_totalDigADCvol0rad48to52[make_pair(xdig,ydig)] = make_pair(runningTallyDigvol0rad48to52,runningTallyADCvol0rad48to52);
				}
				if (5.2 < radius && radius < 5.6 && currdig->ADC() <3000){
					hdigADCvol0rad52to56->Fill(xdig,ydig,currdig->ADC());
					runningTallyDigvol0rad52to56=mapXY_totalDigADCvol0rad52to56[make_pair(xdig,ydig)].first + currdig->ADC();
					runningTallyADCvol0rad52to56=mapXY_totalDigADCvol0rad52to56[make_pair(xdig,ydig)].second +1;
					mapXY_totalDigADCvol0rad52to56[make_pair(xdig,ydig)] = make_pair(runningTallyDigvol0rad52to56,runningTallyADCvol0rad52to56);
				}
				if (5.6 < radius && radius < 6.0 && currdig->ADC() <3000){
					hdigADCvol0rad56to60->Fill(xdig,ydig,currdig->ADC());
					runningTallyDigvol0rad56to60=mapXY_totalDigADCvol0rad56to60[make_pair(xdig,ydig)].first + currdig->ADC();
					runningTallyADCvol0rad56to60=mapXY_totalDigADCvol0rad56to60[make_pair(xdig,ydig)].second +1;
					mapXY_totalDigADCvol0rad56to60[make_pair(xdig,ydig)] = make_pair(runningTallyDigvol0rad56to60,runningTallyADCvol0rad56to60);
				}
				if (6.0 < radius && radius < 6.4 && currdig->ADC() <3000){
					hdigADCvol0rad60to64->Fill(xdig,ydig,currdig->ADC());
					runningTallyDigvol0rad60to64=mapXY_totalDigADCvol0rad60to64[make_pair(xdig,ydig)].first + currdig->ADC();
					runningTallyADCvol0rad60to64=mapXY_totalDigADCvol0rad60to64[make_pair(xdig,ydig)].second +1;
					mapXY_totalDigADCvol0rad60to64[make_pair(xdig,ydig)] = make_pair(runningTallyDigvol0rad60to64,runningTallyADCvol0rad60to64);
				}
				if (6.4 < radius && radius < 6.8 && currdig->ADC() <3000){
					hdigADCvol0rad64to68->Fill(xdig,ydig,currdig->ADC());
					runningTallyDigvol0rad64to68=mapXY_totalDigADCvol0rad64to68[make_pair(xdig,ydig)].first + currdig->ADC();
					runningTallyADCvol0rad64to68=mapXY_totalDigADCvol0rad64to68[make_pair(xdig,ydig)].second +1;
					mapXY_totalDigADCvol0rad64to68[make_pair(xdig,ydig)] = make_pair(runningTallyDigvol0rad64to68,runningTallyADCvol0rad64to68);
				}
				if (6.8 < radius && radius < 7.2 && currdig->ADC() <3000){
					hdigADCvol0rad68to72->Fill(xdig,ydig,currdig->ADC());
					runningTallyDigvol0rad68to72=mapXY_totalDigADCvol0rad68to72[make_pair(xdig,ydig)].first + currdig->ADC();
					runningTallyADCvol0rad68to72=mapXY_totalDigADCvol0rad68to72[make_pair(xdig,ydig)].second +1;
					mapXY_totalDigADCvol0rad68to72[make_pair(xdig,ydig)] = make_pair(runningTallyDigvol0rad68to72,runningTallyADCvol0rad68to72);
				}

			}			
			if (volume==1)	
			{

				hdigADCvol1->Fill(xdig,ydig,currdig->ADC());

				radius = sqrt(pow(xdig - chargeCenterXvol1,2) + pow(ydig - chargeCenterYvol1,2));
				if (0.0 < radius && radius < 0.4 && currdig->ADC() <3000){
					hdigADCvol1rad00to04->Fill(xdig,ydig,currdig->ADC());
					runningTallyDigvol1rad00to04=mapXY_totalDigADCvol1rad00to04[make_pair(xdig,ydig)].first + currdig->ADC();
					runningTallyADCvol1rad00to04=mapXY_totalDigADCvol1rad00to04[make_pair(xdig,ydig)].second +1;
					mapXY_totalDigADCvol1rad00to04[make_pair(xdig,ydig)] = make_pair(runningTallyDigvol1rad00to04,runningTallyADCvol1rad00to04);
				}
				if (0.4 < radius && radius < 0.8 && currdig->ADC() <3000){
					hdigADCvol1rad04to08->Fill(xdig,ydig,currdig->ADC());
					runningTallyDigvol1rad04to08=mapXY_totalDigADCvol1rad04to08[make_pair(xdig,ydig)].first + currdig->ADC();
					runningTallyADCvol1rad04to08=mapXY_totalDigADCvol1rad04to08[make_pair(xdig,ydig)].second +1;
					mapXY_totalDigADCvol1rad04to08[make_pair(xdig,ydig)] = make_pair(runningTallyDigvol1rad04to08,runningTallyADCvol1rad04to08);
				}
				if (0.8 < radius && radius < 1.2 && currdig->ADC() <3000){
					hdigADCvol1rad08to12->Fill(xdig,ydig,currdig->ADC());
					runningTallyDigvol1rad08to12=mapXY_totalDigADCvol1rad08to12[make_pair(xdig,ydig)].first + currdig->ADC();
					runningTallyADCvol1rad08to12=mapXY_totalDigADCvol1rad08to12[make_pair(xdig,ydig)].second +1;
					mapXY_totalDigADCvol1rad08to12[make_pair(xdig,ydig)] = make_pair(runningTallyDigvol1rad08to12,runningTallyADCvol1rad08to12);
				}
				if (1.2 < radius && radius < 1.6 && currdig->ADC() <3000){
					hdigADCvol1rad12to16->Fill(xdig,ydig,currdig->ADC());
					runningTallyDigvol1rad12to16=mapXY_totalDigADCvol1rad12to16[make_pair(xdig,ydig)].first + currdig->ADC();
					runningTallyADCvol1rad12to16=mapXY_totalDigADCvol1rad12to16[make_pair(xdig,ydig)].second +1;
					mapXY_totalDigADCvol1rad12to16[make_pair(xdig,ydig)] = make_pair(runningTallyDigvol1rad12to16,runningTallyADCvol1rad12to16);
				}
				if (1.6 < radius && radius < 2.0 && currdig->ADC() <3000){
					hdigADCvol1rad16to20->Fill(xdig,ydig,currdig->ADC());
					runningTallyDigvol1rad16to20=mapXY_totalDigADCvol1rad16to20[make_pair(xdig,ydig)].first + currdig->ADC();
					runningTallyADCvol1rad16to20=mapXY_totalDigADCvol1rad16to20[make_pair(xdig,ydig)].second +1;
					mapXY_totalDigADCvol1rad16to20[make_pair(xdig,ydig)] = make_pair(runningTallyDigvol1rad16to20,runningTallyADCvol1rad16to20);
				}
				if (2.0 < radius && radius < 2.4 && currdig->ADC() <3000){
					hdigADCvol1rad20to24->Fill(xdig,ydig,currdig->ADC());
					runningTallyDigvol1rad20to24=mapXY_totalDigADCvol1rad20to24[make_pair(xdig,ydig)].first + currdig->ADC();
					runningTallyADCvol1rad20to24=mapXY_totalDigADCvol1rad20to24[make_pair(xdig,ydig)].second +1;
					mapXY_totalDigADCvol1rad20to24[make_pair(xdig,ydig)] = make_pair(runningTallyDigvol1rad20to24,runningTallyADCvol1rad20to24);
				}
				if (2.4 < radius && radius < 2.8 && currdig->ADC() <3000){
					hdigADCvol1rad24to28->Fill(xdig,ydig,currdig->ADC());
					runningTallyDigvol1rad24to28=mapXY_totalDigADCvol1rad24to28[make_pair(xdig,ydig)].first + currdig->ADC();
					runningTallyADCvol1rad24to28=mapXY_totalDigADCvol1rad24to28[make_pair(xdig,ydig)].second +1;
					mapXY_totalDigADCvol1rad24to28[make_pair(xdig,ydig)] = make_pair(runningTallyDigvol1rad24to28,runningTallyADCvol1rad24to28);
				}
				if (2.8 < radius && radius < 3.2 && currdig->ADC() <3000){
					hdigADCvol1rad28to32->Fill(xdig,ydig,currdig->ADC());
					runningTallyDigvol1rad28to32=mapXY_totalDigADCvol1rad28to32[make_pair(xdig,ydig)].first + currdig->ADC();
					runningTallyADCvol1rad28to32=mapXY_totalDigADCvol1rad28to32[make_pair(xdig,ydig)].second +1;
					mapXY_totalDigADCvol1rad28to32[make_pair(xdig,ydig)] = make_pair(runningTallyDigvol1rad28to32,runningTallyADCvol1rad28to32);
				}
				if (3.2 < radius && radius < 3.6 && currdig->ADC() <3000){
					hdigADCvol1->Fill(xdig,ydig,currdig->ADC());
					runningTallyDigvol1rad32to36=mapXY_totalDigADCvol1rad32to36[make_pair(xdig,ydig)].first + currdig->ADC();
					runningTallyADCvol1rad32to36=mapXY_totalDigADCvol1rad32to36[make_pair(xdig,ydig)].second +1;
					mapXY_totalDigADCvol1rad32to36[make_pair(xdig,ydig)] = make_pair(runningTallyDigvol1rad32to36,runningTallyADCvol1rad32to36);
				}
				if (3.6 < radius && radius < 4.0 && currdig->ADC() <3000){
					hdigADCvol1rad36to40->Fill(xdig,ydig,currdig->ADC());
					runningTallyDigvol1rad36to40=mapXY_totalDigADCvol1rad36to40[make_pair(xdig,ydig)].first + currdig->ADC();
					runningTallyADCvol1rad36to40=mapXY_totalDigADCvol1rad36to40[make_pair(xdig,ydig)].second +1;
					mapXY_totalDigADCvol1rad36to40[make_pair(xdig,ydig)] = make_pair(runningTallyDigvol1rad36to40,runningTallyADCvol1rad36to40);
				}
				if (4.0 < radius && radius < 4.4 && currdig->ADC() <3000){
					hdigADCvol1rad40to44->Fill(xdig,ydig,currdig->ADC());
					runningTallyDigvol1rad40to44=mapXY_totalDigADCvol1rad40to44[make_pair(xdig,ydig)].first + currdig->ADC();
					runningTallyADCvol1rad40to44=mapXY_totalDigADCvol1rad40to44[make_pair(xdig,ydig)].second +1;
					mapXY_totalDigADCvol1rad40to44[make_pair(xdig,ydig)] = make_pair(runningTallyDigvol1rad40to44,runningTallyADCvol1rad40to44);
				}
				if (4.4 < radius && radius < 4.8 && currdig->ADC() <3000){
					hdigADCvol1rad44to48->Fill(xdig,ydig,currdig->ADC());
					runningTallyDigvol1rad44to48=mapXY_totalDigADCvol1rad44to48[make_pair(xdig,ydig)].first + currdig->ADC();
					runningTallyADCvol1rad44to48=mapXY_totalDigADCvol1rad44to48[make_pair(xdig,ydig)].second +1;
					mapXY_totalDigADCvol1rad44to48[make_pair(xdig,ydig)] = make_pair(runningTallyDigvol1rad44to48,runningTallyADCvol1rad44to48);
				}
				if (4.8 < radius && radius < 5.2 && currdig->ADC() <3000){
					hdigADCvol1rad48to52->Fill(xdig,ydig,currdig->ADC());
					runningTallyDigvol1rad48to52=mapXY_totalDigADCvol1rad48to52[make_pair(xdig,ydig)].first + currdig->ADC();
					runningTallyADCvol1rad48to52=mapXY_totalDigADCvol1rad48to52[make_pair(xdig,ydig)].second +1;
					mapXY_totalDigADCvol1rad48to52[make_pair(xdig,ydig)] = make_pair(runningTallyDigvol1rad48to52,runningTallyADCvol1rad48to52);
				}
				if (5.2 < radius && radius < 5.6 && currdig->ADC() <3000){
					hdigADCvol1rad52to56->Fill(xdig,ydig,currdig->ADC());
					runningTallyDigvol1rad52to56=mapXY_totalDigADCvol1rad52to56[make_pair(xdig,ydig)].first + currdig->ADC();
					runningTallyADCvol1rad52to56=mapXY_totalDigADCvol1rad52to56[make_pair(xdig,ydig)].second +1;
					mapXY_totalDigADCvol1rad52to56[make_pair(xdig,ydig)] = make_pair(runningTallyDigvol1rad52to56,runningTallyADCvol1rad52to56);
				}
				if (5.6 < radius && radius < 6.0 && currdig->ADC() <3000){
					hdigADCvol1rad56to60->Fill(xdig,ydig,currdig->ADC());
					runningTallyDigvol1rad56to60=mapXY_totalDigADCvol1rad56to60[make_pair(xdig,ydig)].first + currdig->ADC();
					runningTallyADCvol1rad56to60=mapXY_totalDigADCvol1rad56to60[make_pair(xdig,ydig)].second +1;
					mapXY_totalDigADCvol1rad56to60[make_pair(xdig,ydig)] = make_pair(runningTallyDigvol1rad56to60,runningTallyADCvol1rad56to60);
				}
				if (6.0 < radius && radius < 6.4 && currdig->ADC() <3000){
					hdigADCvol1rad60to64->Fill(xdig,ydig,currdig->ADC());
					runningTallyDigvol1rad60to64=mapXY_totalDigADCvol1rad60to64[make_pair(xdig,ydig)].first + currdig->ADC();
					runningTallyADCvol1rad60to64=mapXY_totalDigADCvol1rad60to64[make_pair(xdig,ydig)].second +1;
					mapXY_totalDigADCvol1rad60to64[make_pair(xdig,ydig)] = make_pair(runningTallyDigvol1rad60to64,runningTallyADCvol1rad60to64);
				}
				if (6.4 < radius && radius < 6.8 && currdig->ADC() <3000){
					hdigADCvol1rad64to68->Fill(xdig,ydig,currdig->ADC());
					runningTallyDigvol1rad64to68=mapXY_totalDigADCvol1rad64to68[make_pair(xdig,ydig)].first + currdig->ADC();
					runningTallyADCvol1rad64to68=mapXY_totalDigADCvol1rad64to68[make_pair(xdig,ydig)].second +1;
					mapXY_totalDigADCvol1rad64to68[make_pair(xdig,ydig)] = make_pair(runningTallyDigvol1rad64to68,runningTallyADCvol1rad64to68);
				}
				if (6.8 < radius && radius < 7.2 && currdig->ADC() <3000){
					hdigADCvol1rad68to72->Fill(xdig,ydig,currdig->ADC());
					runningTallyDigvol1rad68to72=mapXY_totalDigADCvol1rad68to72[make_pair(xdig,ydig)].first + currdig->ADC();
					runningTallyADCvol1rad68to72=mapXY_totalDigADCvol1rad68to72[make_pair(xdig,ydig)].second +1;
					mapXY_totalDigADCvol1rad68to72[make_pair(xdig,ydig)] = make_pair(runningTallyDigvol1rad68to72,runningTallyADCvol1rad68to72);
				}

			}			
		}
	}
	if(!(nCutEvt > aMgrAnnularAna.EventNumber() || nCutEvt==-1)){
		std::cout<<"wrote ~"<<totNumEventsCurrentTally<<" events"<<std::endl;break;		
	}
}

// write niffte ana hists
aMgrAnnularAna.Terminate();
gROOT->SetStyle("Plain");



//////////////////////////////////////////////////////////////////////////
////////////////  build intensity WRT annulus volume 0  //////////////////
//////////////////////////////////////////////////////////////////////////

int totalDig=0,totalADC=0;
float ADCperDig=0;

for (mapXY_totalDigADCvol0rad00to04Iter = mapXY_totalDigADCvol0rad00to04.begin(); mapXY_totalDigADCvol0rad00to04Iter != mapXY_totalDigADCvol0rad00to04.end(); ++mapXY_totalDigADCvol0rad00to04Iter)
{
	xdig = mapXY_totalDigADCvol0rad00to04Iter->first.first;
	ydig = mapXY_totalDigADCvol0rad00to04Iter->first.second;
	totalDig = mapXY_totalDigADCvol0rad00to04Iter->second.first;
	totalADC = mapXY_totalDigADCvol0rad00to04Iter->second.second;
	ADCperDig = totalADC/(float)totalDig;
	cout << "xdig,ydig " << xdig << ","<<ydig<< '\t' <<"ADC/dig " << ADCperDig <<endl;
	intensityvol0rad00to04->Fill(ADCperDig);
}

for (mapXY_totalDigADCvol0rad04to08Iter = mapXY_totalDigADCvol0rad04to08.begin(); mapXY_totalDigADCvol0rad04to08Iter != mapXY_totalDigADCvol0rad04to08.end(); ++mapXY_totalDigADCvol0rad04to08Iter)
{
	xdig = mapXY_totalDigADCvol0rad04to08Iter->first.first;
	ydig = mapXY_totalDigADCvol0rad04to08Iter->first.second;
	totalDig = mapXY_totalDigADCvol0rad04to08Iter->second.first;
	totalADC = mapXY_totalDigADCvol0rad04to08Iter->second.second;
	ADCperDig = totalADC/(float)totalDig;
	// cout << "xdig,ydig " << xdig << ","<<ydig<< '\t' <<"ADC/dig " << ADCperDig <<endl;
	intensityvol0rad04to08->Fill(ADCperDig);
}

for (mapXY_totalDigADCvol0rad08to12Iter = mapXY_totalDigADCvol0rad08to12.begin(); mapXY_totalDigADCvol0rad08to12Iter != mapXY_totalDigADCvol0rad08to12.end(); ++mapXY_totalDigADCvol0rad08to12Iter)
{
	xdig = mapXY_totalDigADCvol0rad08to12Iter->first.first;
	ydig = mapXY_totalDigADCvol0rad08to12Iter->first.second;
	totalDig = mapXY_totalDigADCvol0rad08to12Iter->second.first;
	totalADC = mapXY_totalDigADCvol0rad08to12Iter->second.second;
	ADCperDig = totalADC/(float)totalDig;
	// cout << "xdig,ydig " << xdig << ","<<ydig<< '\t' <<"ADC/dig " << ADCperDig <<endl;
	intensityvol0rad08to12->Fill(ADCperDig);
}

for (mapXY_totalDigADCvol0rad12to16Iter = mapXY_totalDigADCvol0rad12to16.begin(); mapXY_totalDigADCvol0rad12to16Iter != mapXY_totalDigADCvol0rad12to16.end(); ++mapXY_totalDigADCvol0rad12to16Iter)
{
	xdig = mapXY_totalDigADCvol0rad12to16Iter->first.first;
	ydig = mapXY_totalDigADCvol0rad12to16Iter->first.second;
	totalDig = mapXY_totalDigADCvol0rad12to16Iter->second.first;
	totalADC = mapXY_totalDigADCvol0rad12to16Iter->second.second;
	ADCperDig = totalADC/(float)totalDig;
	// cout << "xdig,ydig " << xdig << ","<<ydig<< '\t' <<"ADC/dig " << ADCperDig <<endl;
	intensityvol0rad12to16->Fill(ADCperDig);
}

for (mapXY_totalDigADCvol0rad16to20Iter = mapXY_totalDigADCvol0rad16to20.begin(); mapXY_totalDigADCvol0rad16to20Iter != mapXY_totalDigADCvol0rad16to20.end(); ++mapXY_totalDigADCvol0rad16to20Iter)
{
	xdig = mapXY_totalDigADCvol0rad16to20Iter->first.first;
	ydig = mapXY_totalDigADCvol0rad16to20Iter->first.second;
	totalDig = mapXY_totalDigADCvol0rad16to20Iter->second.first;
	totalADC = mapXY_totalDigADCvol0rad16to20Iter->second.second;
	ADCperDig = totalADC/(float)totalDig;
	// cout << "xdig,ydig " << xdig << ","<<ydig<< '\t' <<"ADC/dig " << ADCperDig <<endl;
	intensityvol0rad16to20->Fill(ADCperDig);
}

for (mapXY_totalDigADCvol0rad20to24Iter = mapXY_totalDigADCvol0rad20to24.begin(); mapXY_totalDigADCvol0rad20to24Iter != mapXY_totalDigADCvol0rad20to24.end(); ++mapXY_totalDigADCvol0rad20to24Iter)
{
	xdig = mapXY_totalDigADCvol0rad20to24Iter->first.first;
	ydig = mapXY_totalDigADCvol0rad20to24Iter->first.second;
	totalDig = mapXY_totalDigADCvol0rad20to24Iter->second.first;
	totalADC = mapXY_totalDigADCvol0rad20to24Iter->second.second;
	ADCperDig = totalADC/(float)totalDig;
	// cout << "xdig,ydig " << xdig << ","<<ydig<< '\t' <<"ADC/dig " << ADCperDig <<endl;
	intensityvol0rad20to24->Fill(ADCperDig);
}

for (mapXY_totalDigADCvol0rad24to28Iter = mapXY_totalDigADCvol0rad24to28.begin(); mapXY_totalDigADCvol0rad24to28Iter != mapXY_totalDigADCvol0rad24to28.end(); ++mapXY_totalDigADCvol0rad24to28Iter)
{
	xdig = mapXY_totalDigADCvol0rad24to28Iter->first.first;
	ydig = mapXY_totalDigADCvol0rad24to28Iter->first.second;
	totalDig = mapXY_totalDigADCvol0rad24to28Iter->second.first;
	totalADC = mapXY_totalDigADCvol0rad24to28Iter->second.second;
	ADCperDig = totalADC/(float)totalDig;
	// cout << "xdig,ydig " << xdig << ","<<ydig<< '\t' <<"ADC/dig " << ADCperDig <<endl;
	intensityvol0rad24to28->Fill(ADCperDig);
}

for (mapXY_totalDigADCvol0rad28to32Iter = mapXY_totalDigADCvol0rad28to32.begin(); mapXY_totalDigADCvol0rad28to32Iter != mapXY_totalDigADCvol0rad28to32.end(); ++mapXY_totalDigADCvol0rad28to32Iter)
{
	xdig = mapXY_totalDigADCvol0rad28to32Iter->first.first;
	ydig = mapXY_totalDigADCvol0rad28to32Iter->first.second;
	totalDig = mapXY_totalDigADCvol0rad28to32Iter->second.first;
	totalADC = mapXY_totalDigADCvol0rad28to32Iter->second.second;
	ADCperDig = totalADC/(float)totalDig;
	// cout << "xdig,ydig " << xdig << ","<<ydig<< '\t' <<"ADC/dig " << ADCperDig <<endl;
	intensityvol0rad28to32->Fill(ADCperDig);
}

for (mapXY_totalDigADCvol0rad32to36Iter = mapXY_totalDigADCvol0rad32to36.begin(); mapXY_totalDigADCvol0rad32to36Iter != mapXY_totalDigADCvol0rad32to36.end(); ++mapXY_totalDigADCvol0rad32to36Iter)
{
	xdig = mapXY_totalDigADCvol0rad32to36Iter->first.first;
	ydig = mapXY_totalDigADCvol0rad32to36Iter->first.second;
	totalDig = mapXY_totalDigADCvol0rad32to36Iter->second.first;
	totalADC = mapXY_totalDigADCvol0rad32to36Iter->second.second;
	ADCperDig = totalADC/(float)totalDig;
	// cout << "xdig,ydig " << xdig << ","<<ydig<< '\t' <<"ADC/dig " << ADCperDig <<endl;
	intensityvol0rad32to36->Fill(ADCperDig);
}

for (mapXY_totalDigADCvol0rad36to40Iter = mapXY_totalDigADCvol0rad36to40.begin(); mapXY_totalDigADCvol0rad36to40Iter != mapXY_totalDigADCvol0rad36to40.end(); ++mapXY_totalDigADCvol0rad36to40Iter)
{
	xdig = mapXY_totalDigADCvol0rad36to40Iter->first.first;
	ydig = mapXY_totalDigADCvol0rad36to40Iter->first.second;
	totalDig = mapXY_totalDigADCvol0rad36to40Iter->second.first;
	totalADC = mapXY_totalDigADCvol0rad36to40Iter->second.second;
	ADCperDig = totalADC/(float)totalDig;
	// cout << "xdig,ydig " << xdig << ","<<ydig<< '\t' <<"ADC/dig " << ADCperDig <<endl;
	intensityvol0rad36to40->Fill(ADCperDig);
}

for (mapXY_totalDigADCvol0rad40to44Iter = mapXY_totalDigADCvol0rad40to44.begin(); mapXY_totalDigADCvol0rad40to44Iter != mapXY_totalDigADCvol0rad40to44.end(); ++mapXY_totalDigADCvol0rad40to44Iter)
{
	xdig = mapXY_totalDigADCvol0rad40to44Iter->first.first;
	ydig = mapXY_totalDigADCvol0rad40to44Iter->first.second;
	totalDig = mapXY_totalDigADCvol0rad40to44Iter->second.first;
	totalADC = mapXY_totalDigADCvol0rad40to44Iter->second.second;
	ADCperDig = totalADC/(float)totalDig;
	// cout << "xdig,ydig " << xdig << ","<<ydig<< '\t' <<"ADC/dig " << ADCperDig <<endl;
	intensityvol0rad40to44->Fill(ADCperDig);
}

for (mapXY_totalDigADCvol0rad44to48Iter = mapXY_totalDigADCvol0rad44to48.begin(); mapXY_totalDigADCvol0rad44to48Iter != mapXY_totalDigADCvol0rad44to48.end(); ++mapXY_totalDigADCvol0rad44to48Iter)
{
	xdig = mapXY_totalDigADCvol0rad44to48Iter->first.first;
	ydig = mapXY_totalDigADCvol0rad44to48Iter->first.second;
	totalDig = mapXY_totalDigADCvol0rad44to48Iter->second.first;
	totalADC = mapXY_totalDigADCvol0rad44to48Iter->second.second;
	ADCperDig = totalADC/(float)totalDig;
	// cout << "xdig,ydig " << xdig << ","<<ydig<< '\t' <<"ADC/dig " << ADCperDig <<endl;
	intensityvol0rad44to48->Fill(ADCperDig);
}

for (mapXY_totalDigADCvol0rad48to52Iter = mapXY_totalDigADCvol0rad48to52.begin(); mapXY_totalDigADCvol0rad48to52Iter != mapXY_totalDigADCvol0rad48to52.end(); ++mapXY_totalDigADCvol0rad48to52Iter)
{
	xdig = mapXY_totalDigADCvol0rad48to52Iter->first.first;
	ydig = mapXY_totalDigADCvol0rad48to52Iter->first.second;
	totalDig = mapXY_totalDigADCvol0rad48to52Iter->second.first;
	totalADC = mapXY_totalDigADCvol0rad48to52Iter->second.second;
	ADCperDig = totalADC/(float)totalDig;
	// cout << "xdig,ydig " << xdig << ","<<ydig<< '\t' <<"ADC/dig " << ADCperDig <<endl;
	intensityvol0rad48to52->Fill(ADCperDig);
}

for (mapXY_totalDigADCvol0rad52to56Iter = mapXY_totalDigADCvol0rad52to56.begin(); mapXY_totalDigADCvol0rad52to56Iter != mapXY_totalDigADCvol0rad52to56.end(); ++mapXY_totalDigADCvol0rad52to56Iter)
{
	xdig = mapXY_totalDigADCvol0rad52to56Iter->first.first;
	ydig = mapXY_totalDigADCvol0rad52to56Iter->first.second;
	totalDig = mapXY_totalDigADCvol0rad52to56Iter->second.first;
	totalADC = mapXY_totalDigADCvol0rad52to56Iter->second.second;
	ADCperDig = totalADC/(float)totalDig;
	// cout << "xdig,ydig " << xdig << ","<<ydig<< '\t' <<"ADC/dig " << ADCperDig <<endl;
	intensityvol0rad52to56->Fill(ADCperDig);
}

for (mapXY_totalDigADCvol0rad56to60Iter = mapXY_totalDigADCvol0rad56to60.begin(); mapXY_totalDigADCvol0rad56to60Iter != mapXY_totalDigADCvol0rad56to60.end(); ++mapXY_totalDigADCvol0rad56to60Iter)
{
	xdig = mapXY_totalDigADCvol0rad56to60Iter->first.first;
	ydig = mapXY_totalDigADCvol0rad56to60Iter->first.second;
	totalDig = mapXY_totalDigADCvol0rad56to60Iter->second.first;
	totalADC = mapXY_totalDigADCvol0rad56to60Iter->second.second;
	ADCperDig = totalADC/(float)totalDig;
	// cout << "xdig,ydig " << xdig << ","<<ydig<< '\t' <<"ADC/dig " << ADCperDig <<endl;
	intensityvol0rad56to60->Fill(ADCperDig);
}

for (mapXY_totalDigADCvol0rad60to64Iter = mapXY_totalDigADCvol0rad60to64.begin(); mapXY_totalDigADCvol0rad60to64Iter != mapXY_totalDigADCvol0rad60to64.end(); ++mapXY_totalDigADCvol0rad60to64Iter)
{
	xdig = mapXY_totalDigADCvol0rad60to64Iter->first.first;
	ydig = mapXY_totalDigADCvol0rad60to64Iter->first.second;
	totalDig = mapXY_totalDigADCvol0rad60to64Iter->second.first;
	totalADC = mapXY_totalDigADCvol0rad60to64Iter->second.second;
	ADCperDig = totalADC/(float)totalDig;
	// cout << "xdig,ydig " << xdig << ","<<ydig<< '\t' <<"ADC/dig " << ADCperDig <<endl;
	intensityvol0rad60to64->Fill(ADCperDig);
}

for (mapXY_totalDigADCvol0rad64to68Iter = mapXY_totalDigADCvol0rad64to68.begin(); mapXY_totalDigADCvol0rad64to68Iter != mapXY_totalDigADCvol0rad64to68.end(); ++mapXY_totalDigADCvol0rad64to68Iter)
{
	xdig = mapXY_totalDigADCvol0rad64to68Iter->first.first;
	ydig = mapXY_totalDigADCvol0rad64to68Iter->first.second;
	totalDig = mapXY_totalDigADCvol0rad64to68Iter->second.first;
	totalADC = mapXY_totalDigADCvol0rad64to68Iter->second.second;
	ADCperDig = totalADC/(float)totalDig;
	// cout << "xdig,ydig " << xdig << ","<<ydig<< '\t' <<"ADC/dig " << ADCperDig <<endl;
	intensityvol0rad64to68->Fill(ADCperDig);
}

for (mapXY_totalDigADCvol0rad68to72Iter = mapXY_totalDigADCvol0rad68to72.begin(); mapXY_totalDigADCvol0rad68to72Iter != mapXY_totalDigADCvol0rad68to72.end(); ++mapXY_totalDigADCvol0rad68to72Iter)
{
	xdig = mapXY_totalDigADCvol0rad68to72Iter->first.first;
	ydig = mapXY_totalDigADCvol0rad68to72Iter->first.second;
	totalDig = mapXY_totalDigADCvol0rad68to72Iter->second.first;
	totalADC = mapXY_totalDigADCvol0rad68to72Iter->second.second;
	ADCperDig = totalADC/(float)totalDig;
	// cout << "xdig,ydig " << xdig << ","<<ydig<< '\t' <<"ADC/dig " << ADCperDig <<endl;
	intensityvol0rad68to72->Fill(ADCperDig);
}

//////////////////////////////////////////////////////////////////////////
////////////////  build intensity WRT annulus volume 1  //////////////////
//////////////////////////////////////////////////////////////////////////

for (mapXY_totalDigADCvol1rad00to04Iter = mapXY_totalDigADCvol1rad00to04.begin(); mapXY_totalDigADCvol1rad00to04Iter != mapXY_totalDigADCvol1rad00to04.end(); ++mapXY_totalDigADCvol1rad00to04Iter)
{
	xdig = mapXY_totalDigADCvol1rad00to04Iter->first.first;
	ydig = mapXY_totalDigADCvol1rad00to04Iter->first.second;
	totalDig = mapXY_totalDigADCvol1rad00to04Iter->second.first;
	totalADC = mapXY_totalDigADCvol1rad00to04Iter->second.second;
	ADCperDig = totalADC/(float)totalDig;
	// cout << "xdig,ydig " << xdig << ","<<ydig<< '\t' <<"ADC/dig " << ADCperDig <<endl;
	intensityvol1rad00to04->Fill(ADCperDig);
}

for (mapXY_totalDigADCvol1rad04to08Iter = mapXY_totalDigADCvol1rad04to08.begin(); mapXY_totalDigADCvol1rad04to08Iter != mapXY_totalDigADCvol1rad04to08.end(); ++mapXY_totalDigADCvol1rad04to08Iter)
{
	xdig = mapXY_totalDigADCvol1rad04to08Iter->first.first;
	ydig = mapXY_totalDigADCvol1rad04to08Iter->first.second;
	totalDig = mapXY_totalDigADCvol1rad04to08Iter->second.first;
	totalADC = mapXY_totalDigADCvol1rad04to08Iter->second.second;
	ADCperDig = totalADC/(float)totalDig;
	// cout << "xdig,ydig " << xdig << ","<<ydig<< '\t' <<"ADC/dig " << ADCperDig <<endl;
	intensityvol1rad04to08->Fill(ADCperDig);
}

for (mapXY_totalDigADCvol1rad08to12Iter = mapXY_totalDigADCvol1rad08to12.begin(); mapXY_totalDigADCvol1rad08to12Iter != mapXY_totalDigADCvol1rad08to12.end(); ++mapXY_totalDigADCvol1rad08to12Iter)
{
	xdig = mapXY_totalDigADCvol1rad08to12Iter->first.first;
	ydig = mapXY_totalDigADCvol1rad08to12Iter->first.second;
	totalDig = mapXY_totalDigADCvol1rad08to12Iter->second.first;
	totalADC = mapXY_totalDigADCvol1rad08to12Iter->second.second;
	ADCperDig = totalADC/(float)totalDig;
	// cout << "xdig,ydig " << xdig << ","<<ydig<< '\t' <<"ADC/dig " << ADCperDig <<endl;
	intensityvol1rad08to12->Fill(ADCperDig);
}

for (mapXY_totalDigADCvol1rad12to16Iter = mapXY_totalDigADCvol1rad12to16.begin(); mapXY_totalDigADCvol1rad12to16Iter != mapXY_totalDigADCvol1rad12to16.end(); ++mapXY_totalDigADCvol1rad12to16Iter)
{
	xdig = mapXY_totalDigADCvol1rad12to16Iter->first.first;
	ydig = mapXY_totalDigADCvol1rad12to16Iter->first.second;
	totalDig = mapXY_totalDigADCvol1rad12to16Iter->second.first;
	totalADC = mapXY_totalDigADCvol1rad12to16Iter->second.second;
	ADCperDig = totalADC/(float)totalDig;
	// cout << "xdig,ydig " << xdig << ","<<ydig<< '\t' <<"ADC/dig " << ADCperDig <<endl;
	intensityvol1rad12to16->Fill(ADCperDig);
}

for (mapXY_totalDigADCvol1rad16to20Iter = mapXY_totalDigADCvol1rad16to20.begin(); mapXY_totalDigADCvol1rad16to20Iter != mapXY_totalDigADCvol1rad16to20.end(); ++mapXY_totalDigADCvol1rad16to20Iter)
{
	xdig = mapXY_totalDigADCvol1rad16to20Iter->first.first;
	ydig = mapXY_totalDigADCvol1rad16to20Iter->first.second;
	totalDig = mapXY_totalDigADCvol1rad16to20Iter->second.first;
	totalADC = mapXY_totalDigADCvol1rad16to20Iter->second.second;
	ADCperDig = totalADC/(float)totalDig;
	// cout << "xdig,ydig " << xdig << ","<<ydig<< '\t' <<"ADC/dig " << ADCperDig <<endl;
	intensityvol1rad16to20->Fill(ADCperDig);
}

for (mapXY_totalDigADCvol1rad20to24Iter = mapXY_totalDigADCvol1rad20to24.begin(); mapXY_totalDigADCvol1rad20to24Iter != mapXY_totalDigADCvol1rad20to24.end(); ++mapXY_totalDigADCvol1rad20to24Iter)
{
	xdig = mapXY_totalDigADCvol1rad20to24Iter->first.first;
	ydig = mapXY_totalDigADCvol1rad20to24Iter->first.second;
	totalDig = mapXY_totalDigADCvol1rad20to24Iter->second.first;
	totalADC = mapXY_totalDigADCvol1rad20to24Iter->second.second;
	ADCperDig = totalADC/(float)totalDig;
	// cout << "xdig,ydig " << xdig << ","<<ydig<< '\t' <<"ADC/dig " << ADCperDig <<endl;
	intensityvol1rad20to24->Fill(ADCperDig);
}

for (mapXY_totalDigADCvol1rad24to28Iter = mapXY_totalDigADCvol1rad24to28.begin(); mapXY_totalDigADCvol1rad24to28Iter != mapXY_totalDigADCvol1rad24to28.end(); ++mapXY_totalDigADCvol1rad24to28Iter)
{
	xdig = mapXY_totalDigADCvol1rad24to28Iter->first.first;
	ydig = mapXY_totalDigADCvol1rad24to28Iter->first.second;
	totalDig = mapXY_totalDigADCvol1rad24to28Iter->second.first;
	totalADC = mapXY_totalDigADCvol1rad24to28Iter->second.second;
	ADCperDig = totalADC/(float)totalDig;
	// cout << "xdig,ydig " << xdig << ","<<ydig<< '\t' <<"ADC/dig " << ADCperDig <<endl;
	intensityvol1rad24to28->Fill(ADCperDig);
}

for (mapXY_totalDigADCvol1rad28to32Iter = mapXY_totalDigADCvol1rad28to32.begin(); mapXY_totalDigADCvol1rad28to32Iter != mapXY_totalDigADCvol1rad28to32.end(); ++mapXY_totalDigADCvol1rad28to32Iter)
{
	xdig = mapXY_totalDigADCvol1rad28to32Iter->first.first;
	ydig = mapXY_totalDigADCvol1rad28to32Iter->first.second;
	totalDig = mapXY_totalDigADCvol1rad28to32Iter->second.first;
	totalADC = mapXY_totalDigADCvol1rad28to32Iter->second.second;
	ADCperDig = totalADC/(float)totalDig;
	// cout << "xdig,ydig " << xdig << ","<<ydig<< '\t' <<"ADC/dig " << ADCperDig <<endl;
	intensityvol1rad28to32->Fill(ADCperDig);
}

for (mapXY_totalDigADCvol1rad32to36Iter = mapXY_totalDigADCvol1rad32to36.begin(); mapXY_totalDigADCvol1rad32to36Iter != mapXY_totalDigADCvol1rad32to36.end(); ++mapXY_totalDigADCvol1rad32to36Iter)
{
	xdig = mapXY_totalDigADCvol1rad32to36Iter->first.first;
	ydig = mapXY_totalDigADCvol1rad32to36Iter->first.second;
	totalDig = mapXY_totalDigADCvol1rad32to36Iter->second.first;
	totalADC = mapXY_totalDigADCvol1rad32to36Iter->second.second;
	ADCperDig = totalADC/(float)totalDig;
	// cout << "xdig,ydig " << xdig << ","<<ydig<< '\t' <<"ADC/dig " << ADCperDig <<endl;
	intensityvol1rad32to36->Fill(ADCperDig);
}

for (mapXY_totalDigADCvol1rad36to40Iter = mapXY_totalDigADCvol1rad36to40.begin(); mapXY_totalDigADCvol1rad36to40Iter != mapXY_totalDigADCvol1rad36to40.end(); ++mapXY_totalDigADCvol1rad36to40Iter)
{
	xdig = mapXY_totalDigADCvol1rad36to40Iter->first.first;
	ydig = mapXY_totalDigADCvol1rad36to40Iter->first.second;
	totalDig = mapXY_totalDigADCvol1rad36to40Iter->second.first;
	totalADC = mapXY_totalDigADCvol1rad36to40Iter->second.second;
	ADCperDig = totalADC/(float)totalDig;
	// cout << "xdig,ydig " << xdig << ","<<ydig<< '\t' <<"ADC/dig " << ADCperDig <<endl;
	intensityvol1rad36to40->Fill(ADCperDig);
}

for (mapXY_totalDigADCvol1rad40to44Iter = mapXY_totalDigADCvol1rad40to44.begin(); mapXY_totalDigADCvol1rad40to44Iter != mapXY_totalDigADCvol1rad40to44.end(); ++mapXY_totalDigADCvol1rad40to44Iter)
{
	xdig = mapXY_totalDigADCvol1rad40to44Iter->first.first;
	ydig = mapXY_totalDigADCvol1rad40to44Iter->first.second;
	totalDig = mapXY_totalDigADCvol1rad40to44Iter->second.first;
	totalADC = mapXY_totalDigADCvol1rad40to44Iter->second.second;
	ADCperDig = totalADC/(float)totalDig;
	// cout << "xdig,ydig " << xdig << ","<<ydig<< '\t' <<"ADC/dig " << ADCperDig <<endl;
	intensityvol1rad40to44->Fill(ADCperDig);
}

for (mapXY_totalDigADCvol1rad44to48Iter = mapXY_totalDigADCvol1rad44to48.begin(); mapXY_totalDigADCvol1rad44to48Iter != mapXY_totalDigADCvol1rad44to48.end(); ++mapXY_totalDigADCvol1rad44to48Iter)
{
	xdig = mapXY_totalDigADCvol1rad44to48Iter->first.first;
	ydig = mapXY_totalDigADCvol1rad44to48Iter->first.second;
	totalDig = mapXY_totalDigADCvol1rad44to48Iter->second.first;
	totalADC = mapXY_totalDigADCvol1rad44to48Iter->second.second;
	ADCperDig = totalADC/(float)totalDig;
	// cout << "xdig,ydig " << xdig << ","<<ydig<< '\t' <<"ADC/dig " << ADCperDig <<endl;
	intensityvol1rad44to48->Fill(ADCperDig);
}

for (mapXY_totalDigADCvol1rad48to52Iter = mapXY_totalDigADCvol1rad48to52.begin(); mapXY_totalDigADCvol1rad48to52Iter != mapXY_totalDigADCvol1rad48to52.end(); ++mapXY_totalDigADCvol1rad48to52Iter)
{
	xdig = mapXY_totalDigADCvol1rad48to52Iter->first.first;
	ydig = mapXY_totalDigADCvol1rad48to52Iter->first.second;
	totalDig = mapXY_totalDigADCvol1rad48to52Iter->second.first;
	totalADC = mapXY_totalDigADCvol1rad48to52Iter->second.second;
	ADCperDig = totalADC/(float)totalDig;
	// cout << "xdig,ydig " << xdig << ","<<ydig<< '\t' <<"ADC/dig " << ADCperDig <<endl;
	intensityvol1rad48to52->Fill(ADCperDig);
}

for (mapXY_totalDigADCvol1rad52to56Iter = mapXY_totalDigADCvol1rad52to56.begin(); mapXY_totalDigADCvol1rad52to56Iter != mapXY_totalDigADCvol1rad52to56.end(); ++mapXY_totalDigADCvol1rad52to56Iter)
{
	xdig = mapXY_totalDigADCvol1rad52to56Iter->first.first;
	ydig = mapXY_totalDigADCvol1rad52to56Iter->first.second;
	totalDig = mapXY_totalDigADCvol1rad52to56Iter->second.first;
	totalADC = mapXY_totalDigADCvol1rad52to56Iter->second.second;
	ADCperDig = totalADC/(float)totalDig;
	// cout << "xdig,ydig " << xdig << ","<<ydig<< '\t' <<"ADC/dig " << ADCperDig <<endl;
	intensityvol1rad52to56->Fill(ADCperDig);
}

for (mapXY_totalDigADCvol1rad56to60Iter = mapXY_totalDigADCvol1rad56to60.begin(); mapXY_totalDigADCvol1rad56to60Iter != mapXY_totalDigADCvol1rad56to60.end(); ++mapXY_totalDigADCvol1rad56to60Iter)
{
	xdig = mapXY_totalDigADCvol1rad56to60Iter->first.first;
	ydig = mapXY_totalDigADCvol1rad56to60Iter->first.second;
	totalDig = mapXY_totalDigADCvol1rad56to60Iter->second.first;
	totalADC = mapXY_totalDigADCvol1rad56to60Iter->second.second;
	ADCperDig = totalADC/(float)totalDig;
	// cout << "xdig,ydig " << xdig << ","<<ydig<< '\t' <<"ADC/dig " << ADCperDig <<endl;
	intensityvol1rad56to60->Fill(ADCperDig);
}

for (mapXY_totalDigADCvol1rad60to64Iter = mapXY_totalDigADCvol1rad60to64.begin(); mapXY_totalDigADCvol1rad60to64Iter != mapXY_totalDigADCvol1rad60to64.end(); ++mapXY_totalDigADCvol1rad60to64Iter)
{
	xdig = mapXY_totalDigADCvol1rad60to64Iter->first.first;
	ydig = mapXY_totalDigADCvol1rad60to64Iter->first.second;
	totalDig = mapXY_totalDigADCvol1rad60to64Iter->second.first;
	totalADC = mapXY_totalDigADCvol1rad60to64Iter->second.second;
	ADCperDig = totalADC/(float)totalDig;
	// cout << "xdig,ydig " << xdig << ","<<ydig<< '\t' <<"ADC/dig " << ADCperDig <<endl;
	intensityvol1rad60to64->Fill(ADCperDig);
}

for (mapXY_totalDigADCvol1rad64to68Iter = mapXY_totalDigADCvol1rad64to68.begin(); mapXY_totalDigADCvol1rad64to68Iter != mapXY_totalDigADCvol1rad64to68.end(); ++mapXY_totalDigADCvol1rad64to68Iter)
{
	xdig = mapXY_totalDigADCvol1rad64to68Iter->first.first;
	ydig = mapXY_totalDigADCvol1rad64to68Iter->first.second;
	totalDig = mapXY_totalDigADCvol1rad64to68Iter->second.first;
	totalADC = mapXY_totalDigADCvol1rad64to68Iter->second.second;
	ADCperDig = totalADC/(float)totalDig;
	// cout << "xdig,ydig " << xdig << ","<<ydig<< '\t' <<"ADC/dig " << ADCperDig <<endl;
	intensityvol1rad64to68->Fill(ADCperDig);
}

for (mapXY_totalDigADCvol1rad68to72Iter = mapXY_totalDigADCvol1rad68to72.begin(); mapXY_totalDigADCvol1rad68to72Iter != mapXY_totalDigADCvol1rad68to72.end(); ++mapXY_totalDigADCvol1rad68to72Iter)
{
	xdig = mapXY_totalDigADCvol1rad68to72Iter->first.first;
	ydig = mapXY_totalDigADCvol1rad68to72Iter->first.second;
	totalDig = mapXY_totalDigADCvol1rad68to72Iter->second.first;
	totalADC = mapXY_totalDigADCvol1rad68to72Iter->second.second;
	ADCperDig = totalADC/(float)totalDig;
	// cout << "xdig,ydig " << xdig << ","<<ydig<< '\t' <<"ADC/dig " << ADCperDig <<endl;
	intensityvol1rad68to72->Fill(ADCperDig);
}


// write other hists to outfile
TFile * f = new TFile(outfile,"UPDATE");
intensityvol0rad00to04->Write();intensityvol1rad00to04->Write();
intensityvol0rad04to08->Write();intensityvol1rad04to08->Write();
intensityvol0rad08to12->Write();intensityvol1rad08to12->Write();
intensityvol0rad12to16->Write();intensityvol1rad12to16->Write();
intensityvol0rad16to20->Write();intensityvol1rad16to20->Write();
intensityvol0rad20to24->Write();intensityvol1rad20to24->Write();
intensityvol0rad24to28->Write();intensityvol1rad24to28->Write();
intensityvol0rad28to32->Write();intensityvol1rad28to32->Write();
intensityvol0rad32to36->Write();intensityvol1rad32to36->Write();
intensityvol0rad36to40->Write();intensityvol1rad36to40->Write();
intensityvol0rad40to44->Write();intensityvol1rad40to44->Write();
intensityvol0rad44to48->Write();intensityvol1rad44to48->Write();
intensityvol0rad48to52->Write();intensityvol1rad48to52->Write();
intensityvol0rad52to56->Write();intensityvol1rad52to56->Write();
intensityvol0rad56to60->Write();intensityvol1rad56to60->Write();
intensityvol0rad60to64->Write();intensityvol1rad60to64->Write();
intensityvol0rad64to68->Write();intensityvol1rad64to68->Write();
intensityvol0rad68to72->Write();intensityvol1rad68to72->Write();


stopwatch.Stop();
std::cout<<"this program ran for "<<stopwatch.RealTime()<< " sec" << std::endl;
system("./cleanup.sh");

gApplication->Terminate();
}
