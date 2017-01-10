//
// A simple test macro for loading Niffte
// code into ROOT and running it
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

// C++ libraries
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <numeric>
#include <climits>
#include <vector>
#include <ctime>


void cutsFromHist(const char* infile, const char* alphaCutFileName) {

time_t now = time(0);   
char* dt = ctime(&now);
std::cout<<dt<<std::endl;



TFile *uweCutFile = new TFile("uweCutFile");
TCutG* cftCut1stPreamp = (TCutG*)uweCutFile->Get("uweCutADC800to1600Len2mm12mm");

TFile *histFile = new TFile(infile);
AnaH2D * LengthvsADC = (AnaH2D*)histFile->Get("LengthvsADC");



now = time(0);dt = ctime(&now);std::cout<<dt<<std::endl;

}
