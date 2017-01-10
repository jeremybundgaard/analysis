
// NIFFTE Libraries
#include "NiffteRootIO.h"
#include "NiffteDataBucket.h"
#include "NiffteEventHandle.h"
#include "NiffteTPCTrack.h"
#include "NiffteTPCDigit.h"
#include "NiffteTPCADCSignal.h"
#include "NiffteMCParticle.h"
#include "NiffteMCHit.h"
#include "NiffteGeometryMap.h"
#include "NiffteAnalysisManager.h"
#include "TPCTimingOffset.h"
#include "TPCGeometry.h"
#include "MsgLog.h"

// ROOT libraries
#include "TROOT.h"
#include "TRint.h"
#include "TObjArray.h"

// C++ libraries
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <numeric>
#include <climits>
#include <vector>
#include <time.h>


NiffteGeometryMap* ngm = NiffteGeometryMap::Instance("v2_03");

void runTime(const char* infile = "infile-list.txt", const char* outfile="Analysis-RunXXX.root", int nEvents = -1) {

//Niffte Analysis------------------------------
std::string geo("v2_03");
std::string ofile(outfile);
NiffteAnalysisManager aMgr(infile,ofile,geo);

//Open file list -----------------------------------------
int nevt=-1;
if(nevt == -1)
	nevt = INT_MAX;

int nSkip = 0;
int SparseFactor = 1000000;

aMgr.Execute(nevt,nSkip,SparseFactor);
TPCResult_t status;
while (true){

	status = aMgr.NextEvent();
	if (status != kTPCSuccess && status != kTPCNewRun ) break;
	if(!(nEvents > aMgr.EventNumber() || nEvents==-1))
		break;
}


aMgr.Terminate();
gROOT->SetStyle("Plain");
gApplication->Terminate();

}
