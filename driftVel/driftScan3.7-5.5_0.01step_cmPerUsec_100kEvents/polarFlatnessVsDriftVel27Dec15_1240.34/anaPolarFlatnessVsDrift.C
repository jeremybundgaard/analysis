#include "THStack.h"
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
#include "NiffteGeometryMap.h"
#include "NifftePlotUtilities.h"

#include <math.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

TCutG* fragCut_lVsADC(int preamp, int dADC=0, int dLength=0, const char* fragCutName="");
void fillDriftVel_polarSlopHist(double driftVel, const char* rootFileName, TH1D* fragSlopeVsDriftVel, TH1D* alphaSlopeVsDriftVel, TH2D* fragPolarVsDriftVel, TH2D* alphaPolarVsDriftVel);

void anaPolarFlatnessVsDrift(){

	std::map<float,const char*> driftVel_polarSlopeMap;

	// driftVel_polarSlopeMap[3.70] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_3.70_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[3.75] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_3.75_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[3.80] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_3.80_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[3.85] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_3.85_run100002055.nEvents_100000.trees.root";
	driftVel_polarSlopeMap[3.90] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_3.90_run100002055.nEvents_100000.trees.root";
	driftVel_polarSlopeMap[3.95] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_3.95_run100002055.nEvents_100000.trees.root";
	driftVel_polarSlopeMap[4.00] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.00_run100002055.nEvents_100000.trees.root";
	driftVel_polarSlopeMap[4.05] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.05_run100002055.nEvents_100000.trees.root";
	driftVel_polarSlopeMap[4.10] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.10_run100002055.nEvents_100000.trees.root";
	driftVel_polarSlopeMap[4.15] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.15_run100002055.nEvents_100000.trees.root";
	driftVel_polarSlopeMap[4.20] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.20_run100002055.nEvents_100000.trees.root";
	driftVel_polarSlopeMap[4.25] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.25_run100002055.nEvents_100000.trees.root";
	driftVel_polarSlopeMap[4.30] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.30_run100002055.nEvents_100000.trees.root";
	driftVel_polarSlopeMap[4.35] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.35_run100002055.nEvents_100000.trees.root";
	driftVel_polarSlopeMap[4.40] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.40_run100002055.nEvents_100000.trees.root";
	driftVel_polarSlopeMap[4.45] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.45_run100002055.nEvents_100000.trees.root";
	driftVel_polarSlopeMap[4.50] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.50_run100002055.nEvents_100000.trees.root";
	driftVel_polarSlopeMap[4.55] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.55_run100002055.nEvents_100000.trees.root";
	driftVel_polarSlopeMap[4.60] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.60_run100002055.nEvents_100000.trees.root";
	driftVel_polarSlopeMap[4.65] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.65_run100002055.nEvents_100000.trees.root";
	driftVel_polarSlopeMap[4.70] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.70_run100002055.nEvents_100000.trees.root";
	driftVel_polarSlopeMap[4.75] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.75_run100002055.nEvents_100000.trees.root";
	driftVel_polarSlopeMap[4.80] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.80_run100002055.nEvents_100000.trees.root";
	driftVel_polarSlopeMap[4.85] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.85_run100002055.nEvents_100000.trees.root";
	driftVel_polarSlopeMap[4.90] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.90_run100002055.nEvents_100000.trees.root";
	driftVel_polarSlopeMap[4.95] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.95_run100002055.nEvents_100000.trees.root";
	driftVel_polarSlopeMap[5.00] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.00_run100002055.nEvents_100000.trees.root";
	driftVel_polarSlopeMap[5.05] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.05_run100002055.nEvents_100000.trees.root";
	driftVel_polarSlopeMap[5.10] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.10_run100002055.nEvents_100000.trees.root";
	driftVel_polarSlopeMap[5.15] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.15_run100002055.nEvents_100000.trees.root";
	driftVel_polarSlopeMap[5.20] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.20_run100002055.nEvents_100000.trees.root";
	driftVel_polarSlopeMap[5.25] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.25_run100002055.nEvents_100000.trees.root";
	driftVel_polarSlopeMap[5.30] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.30_run100002055.nEvents_100000.trees.root";
	driftVel_polarSlopeMap[5.35] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.35_run100002055.nEvents_100000.trees.root";
	driftVel_polarSlopeMap[5.40] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.40_run100002055.nEvents_100000.trees.root";
	driftVel_polarSlopeMap[5.45] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.45_run100002055.nEvents_100000.trees.root";
	driftVel_polarSlopeMap[5.50] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.50_run100002055.nEvents_100000.trees.root";

	// driftVel_polarSlopeMap[3.70] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_3.70_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[3.71] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_3.71_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[3.72] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_3.72_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[3.73] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_3.73_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[3.74] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_3.74_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[3.75] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_3.75_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[3.76] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_3.76_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[3.77] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_3.77_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[3.78] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_3.78_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[3.79] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_3.79_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[3.80] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_3.80_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[3.81] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_3.81_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[3.82] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_3.82_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[3.83] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_3.83_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[3.84] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_3.84_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[3.85] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_3.85_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[3.86] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_3.86_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[3.87] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_3.87_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[3.88] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_3.88_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[3.89] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_3.89_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[3.90] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_3.90_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[3.91] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_3.91_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[3.92] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_3.92_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[3.93] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_3.93_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[3.94] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_3.94_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[3.95] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_3.95_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[3.96] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_3.96_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[3.97] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_3.97_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[3.98] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_3.98_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[3.99] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_3.99_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.00] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.00_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.01] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.01_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.02] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.02_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.03] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.03_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.04] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.04_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.05] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.05_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.06] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.06_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.07] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.07_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.08] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.08_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.09] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.09_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.10] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.10_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.11] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.11_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.12] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.12_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.13] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.13_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.14] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.14_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.15] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.15_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.16] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.16_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.17] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.17_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.18] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.18_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.19] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.19_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.20] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.20_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.21] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.21_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.22] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.22_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.23] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.23_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.24] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.24_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.25] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.25_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.26] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.26_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.27] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.27_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.28] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.28_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.29] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.29_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.30] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.30_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.31] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.31_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.32] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.32_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.33] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.33_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.34] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.34_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.35] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.35_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.36] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.36_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.37] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.37_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.38] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.38_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.39] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.39_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.40] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.40_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.41] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.41_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.42] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.42_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.43] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.43_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.44] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.44_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.45] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.45_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.46] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.46_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.47] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.47_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.48] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.48_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.49] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.49_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.50] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.50_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.51] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.51_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.52] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.52_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.53] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.53_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.54] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.54_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.55] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.55_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.56] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.56_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.57] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.57_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.58] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.58_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.59] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.59_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.60] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.60_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.61] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.61_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.62] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.62_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.63] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.63_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.64] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.64_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.65] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.65_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.66] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.66_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.67] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.67_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.68] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.68_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.69] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.69_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.70] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.70_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.71] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.71_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.72] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.72_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.73] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.73_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.74] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.74_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.75] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.75_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.76] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.76_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.77] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.77_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.78] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.78_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.79] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.79_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.80] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.80_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.81] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.81_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.82] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.82_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.83] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.83_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.84] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.84_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.85] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.85_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.86] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.86_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.87] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.87_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.88] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.88_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.89] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.89_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.90] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.90_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.91] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.91_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.92] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.92_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.93] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.93_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.94] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.94_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.95] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.95_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.96] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.96_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.97] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.97_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.98] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.98_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[4.99] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_4.99_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.00] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.00_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.01] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.01_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.02] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.02_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.03] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.03_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.04] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.04_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.05] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.05_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.06] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.06_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.07] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.07_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.08] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.08_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.09] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.09_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.10] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.10_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.11] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.11_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.12] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.12_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.13] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.13_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.14] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.14_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.15] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.15_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.16] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.16_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.17] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.17_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.18] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.18_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.19] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.19_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.20] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.20_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.21] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.21_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.22] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.22_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.23] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.23_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.24] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.24_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.25] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.25_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.26] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.26_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.27] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.27_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.28] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.28_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.29] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.29_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.30] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.30_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.31] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.31_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.32] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.32_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.33] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.33_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.34] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.34_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.35] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.35_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.36] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.36_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.37] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.37_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.38] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.38_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.39] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.39_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.40] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.40_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.41] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.41_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.42] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.42_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.43] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.43_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.44] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.44_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.45] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.45_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.46] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.46_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.47] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.47_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.48] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.48_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.49] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.49_run100002055.nEvents_100000.trees.root";
	// driftVel_polarSlopeMap[5.50] = "/p/lscratche/jerbundg/data/thesisData/drift/driftScan3.7-5.5_0.01step_cmPerUsec_100kEvents/rootFiles/driftVel_5.50_run100002055.nEvents_100000.trees.root";


	TH1D *fragSlopeVsDriftVelGlobal = new TH1D("fragSlopeVsDriftVelGlobal","fragSlopeVsDriftVelGlobal",181,3.7,5.5);
	TH1D *alphaSlopeVsDriftVelGlobal = new TH1D("alphaSlopeVsDriftVelGlobal","alphaSlopeVsDriftVelGlobal",181,3.7,5.5);
	TH2D *fragPolarVsDriftVelGlobal = new TH2D("fragPolarVsDriftVelGlobal","fragPolarVsDriftVelGlobal",181,3.7,5.5,400,-1,1);
	TH2D *alphaPolarVsDriftVelGlobal = new TH2D("alphaPolarVsDriftVelGlobal","alphaPolarVsDriftVelGlobal",181,3.7,5.5,400,-1,1);


	for (std::map<float,const char*>::iterator driftVel_polarSlopeMapIter = driftVel_polarSlopeMap.begin();
	  	driftVel_polarSlopeMapIter != driftVel_polarSlopeMap.end();
	 	++driftVel_polarSlopeMapIter)
	{
		fillDriftVel_polarSlopHist(
			driftVel_polarSlopeMapIter->first,
			driftVel_polarSlopeMapIter->second,
			fragSlopeVsDriftVelGlobal,
			alphaSlopeVsDriftVelGlobal,
			fragPolarVsDriftVelGlobal,
			alphaPolarVsDriftVelGlobal
			);
	}

	fragSlopeVsDriftVelGlobal->SetTitle("polar flatness (0=flat)");
	fragSlopeVsDriftVelGlobal->GetYaxis()->SetTitle("slope polar dist");
	fragSlopeVsDriftVelGlobal->GetXaxis()->SetTitle("drift velocity [cm/#musec]");
	fragSlopeVsDriftVelGlobal->SetLineColor(kViolet);
	fragSlopeVsDriftVelGlobal->SetLineWidth(4);
	fragSlopeVsDriftVelGlobal->GetXaxis()->SetRangeUser(3.7,5.4);

	alphaSlopeVsDriftVelGlobal->SetLineColor(kGreen+2);
	alphaSlopeVsDriftVelGlobal->SetLineWidth(4);
	alphaSlopeVsDriftVelGlobal->GetXaxis()->SetRangeUser(3.7,5.4);

	TF1* zero = new TF1("zero","0",3.7,5.5);
	zero->SetLineColor(kRed);
	zero->SetLineWidth(1);
	zero->SetLineStyle(3);

	TLegend *legend=new TLegend(0.5,0.7,0.7,0.8);
	legend->SetTextFont(42);
	legend->SetTextSize(0.04);
	legend->SetFillColorAlpha(kWhite,0.25);
	legend->AddEntry(alphaSlopeVsDriftVelGlobal,"#alpha");
	legend->AddEntry(fragSlopeVsDriftVelGlobal,"frags");

	TCanvas *c1 = new TCanvas("c1","c1",1000,700);
	gStyle->SetOptStat(0);
	
	fragSlopeVsDriftVelGlobal->Draw();
	alphaSlopeVsDriftVelGlobal->Draw("same");
	zero->Draw("same");
	legend->Draw("same");
	c1->SaveAs("polarSlopeVsDriftVel.png");

	TFile* driftVel_polarSlopeFile = new TFile("polarSlopeVsDriftVel.root","recreate");
	fragSlopeVsDriftVelGlobal->Write();
	alphaSlopeVsDriftVelGlobal->Write();
	fragPolarVsDriftVelGlobal->Write();
	alphaPolarVsDriftVelGlobal->Write();

}

void fillDriftVel_polarSlopHist(double driftVel, const char* rootFileName, TH1D* fragSlopeVsDriftVel, TH1D* alphaSlopeVsDriftVel, TH2D* fragPolarVsDriftVel, TH2D* alphaPolarVsDriftVel){


	TCutG *fragCutADC = fragCut_lVsADC(2, 0,0,"fragCutADC");

	double deg2rad = TMath::Pi()/(double)180;
	double solidAngle, perSA, theta;
	double binWidth = 90/(double)500;

	char noMaskCut[234];
	char fitCut[123];
	char noMaskRunCut[123];
	char azCut[123];

	sprintf(fitCut,"fitType==5");
	sprintf(azCut,"!(-1 < direction.Phi() && direction.Phi() < 0)");
	sprintf(noMaskCut," %s && %s ",fitCut,azCut);

	std::cout <<"noMaskCut = " << noMaskCut << std::endl;
	char histName[234];

	cout<< "driftVel_polarSlopeMap["<<driftVel<<"] = "<< rootFileName << endl;

	TFile* noMaskFile = new TFile(rootFileName);
	TTree* noMaskTracks = (TTree*)noMaskFile->Get("tracks");

	char noMaskFragCut[234];sprintf(noMaskFragCut,"%s && fragCutADC", noMaskCut);
	TH1D* noMaskFragVsCosThetaNeg1to1 = new TH1D("noMaskFragVsCosThetaNeg1to1","noMaskFragVsCosThetaNeg1to1",400,-1,1);
	noMaskTracks->Draw("direction.CosTheta()>>noMaskFragVsCosThetaNeg1to1",noMaskFragCut);

	char noMaskAlphaCut[234];sprintf(noMaskFragCut,"%s && !fragCutADC",noMaskCut);
	TH1D* noMaskAlphaVsCosThetaNeg1to1 = new TH1D("noMaskAlphaVsCosThetaNeg1to1","noMaskAlphaVsCosThetaNeg1to1",400,-1,1);
	noMaskTracks->Draw("direction.CosTheta()>>noMaskAlphaVsCosThetaNeg1to1",noMaskFragCut);

	///////////////////////////////////////////////////////
	//////////////////// flatness fits ////////////////////
	///////////////////////////////////////////////////////

	TF1 *alphaSlope = new TF1("alphaSlope", "pol1",-0.8,-0.2);
	TF1 *fragSlope = new TF1("fragSlope", "pol1",-0.8,-0.2);
	noMaskAlphaVsCosThetaNeg1to1->Fit("alphaSlope","R");
	noMaskFragVsCosThetaNeg1to1->Fit("fragSlope","R");
	// fragSlopeVsDriftVel->Fill(driftVel,TMath::Abs( alphaSlope->GetParameter(1) ) );
	// alphaSlopeVsDriftVel->Fill(driftVel,TMath::Abs( fragSlope->GetParameter(1) ) );
	fragSlopeVsDriftVel->Fill(driftVel,fragSlope->GetParameter(1));
	alphaSlopeVsDriftVel->Fill(driftVel,alphaSlope->GetParameter(1));

	int driftBin=0;
	for (int cosThetaBin = 0; cosThetaBin < 400; ++cosThetaBin)
	{
		driftBin=fragSlopeVsDriftVel->FindBin(driftVel);
		fragPolarVsDriftVel->SetBinContent(driftBin,cosThetaBin,noMaskFragVsCosThetaNeg1to1->GetBinContent(cosThetaBin));
		alphaPolarVsDriftVel->SetBinContent(driftBin,cosThetaBin,noMaskAlphaVsCosThetaNeg1to1->GetBinContent(cosThetaBin));

	}

	// char fragPolarSlopeText[234];
	// sprintf(fragPolarSlopeText,"fragSlope = %.3f",fragSlope->GetParameter(1));
	// TText fragPolarSlope;
	// fragPolarSlope.SetTextColor(kViolet);
	// fragPolarSlope.SetTextAlign(13);
	// fragPolarSlope.SetTextSize(0.03);
	// fragPolarSlope.SetTextFont(42);

	// char alphaPolarSlopeText[234];
	// sprintf(alphaPolarSlopeText,"alphaSlope = %.3f",alphaSlope->GetParameter(1));
	// TText alphaPolarSlope;
	// alphaPolarSlope.SetTextColor(kGreen+2);
	// alphaPolarSlope.SetTextAlign(13);
	// alphaPolarSlope.SetTextSize(0.03);
	// alphaPolarSlope.SetTextFont(42);

	// noMaskFragVsCosThetaNeg1to1->SetLineColor(kViolet);
	// noMaskFragVsCosThetaNeg1to1->SetFillColorAlpha(kViolet,0.25);
	// noMaskFragVsCosThetaNeg1to1->GetXaxis()->SetTitle("Cos #theta");
	// noMaskFragVsCosThetaNeg1to1->GetYaxis()->SetTitle("allTrks");
	// noMaskFragVsCosThetaNeg1to1->GetYaxis()->SetTitleOffset(1.4);
	// noMaskFragVsCosThetaNeg1to1->Draw();

	// cout<<"fragPolarSlopeText = "<<fragPolarSlopeText<<endl;
	// fragPolarSlope.DrawTextNDC(0.6,0.8,fragPolarSlopeText);
	// sprintf(c1PlotName,"driftVel_%s_noMaskFragVsCosThetaNeg1to1.png",driftVel);
	// c1->SaveAs(c1PlotName);

	// noMaskAlphaVsCosThetaNeg1to1->SetFillColorAlpha(kGreen,0.25);
	// noMaskAlphaVsCosThetaNeg1to1->SetLineColor(kGreen);
	// noMaskAlphaVsCosThetaNeg1to1->GetXaxis()->SetTitle("Cos #theta");
	// noMaskAlphaVsCosThetaNeg1to1->GetYaxis()->SetTitle("alphaTrks");
	// noMaskAlphaVsCosThetaNeg1to1->GetYaxis()->SetTitleOffset(1.4);
	// noMaskAlphaVsCosThetaNeg1to1->Draw();
	// alphaPolarSlope.DrawTextNDC(0.6,0.80,alphaPolarSlopeText);
	// sprintf(c1PlotName,"driftVel_%s_noMaskAlphaVsCosThetaNeg1to1.png",driftVel);
	// c1->SaveAs(c1PlotName);

	// sprintf(histName,"driftVel_%s_cosPolar_alphaFrag_SupImp",driftVel);
	// noMaskAlphaVsCosThetaNeg1to1->SetTitle(histName);
	// noMaskFragVsCosThetaNeg1to1->Draw("same");
	// fragPolarSlope.DrawTextNDC(0.6,0.83,fragPolarSlopeText);
	// sprintf(c1PlotName,"driftVel_%s_noMaskAlphaVsCosThetaNeg1to1.superImposed.png",driftVel);
	// c1->SaveAs(c1PlotName);

}

TCutG* fragCut_lVsADC(int preamp, int dADC=0, int dLength=0, const char* fragCutName=""){


	TCutG *fragCutADC = new TCutG(fragCutName,8);
	fragCutADC->SetLineColor(kViolet);
	fragCutADC->SetLineWidth(3);
	fragCutADC->SetVarX("adc");
	fragCutADC->SetVarY("length");
	if (preamp==1)
	{

		fragCutADC->SetPoint(0,644+dADC,1.03077+dLength);
		fragCutADC->SetPoint(1,3554+dADC,2.35+dLength);
		fragCutADC->SetPoint(2,16824+dADC,3.15+dLength);
		fragCutADC->SetPoint(3,35545+dADC,3.65+dLength);
		fragCutADC->SetPoint(4,35545+dADC,1.65+dLength);
		fragCutADC->SetPoint(5,478+dADC,0.5+dLength);
		fragCutADC->SetPoint(6,478+dADC,0.5+dLength);
		fragCutADC->SetPoint(7,502+dADC,0.573987+dLength);
		fragCutADC->SetPoint(8,526+dADC,0.648579+dLength);
		fragCutADC->SetPoint(9,549+dADC,0.723779+dLength);
		fragCutADC->SetPoint(10,573+dADC,0.799594+dLength);
		fragCutADC->SetPoint(11,597+dADC,0.876028+dLength);
		fragCutADC->SetPoint(12,620+dADC,0.953086+dLength);
		fragCutADC->SetPoint(13,644+dADC,1.03077+dLength);

	}
	else if (preamp==2)
	{

		fragCutADC->SetPoint(0,591+dADC,0.982877+dLength);
		fragCutADC->SetPoint(1,3558+dADC,2.35+dLength);
		fragCutADC->SetPoint(2,16844+dADC,3.15+dLength);
		fragCutADC->SetPoint(3,35587+dADC,3.65+dLength);
		fragCutADC->SetPoint(4,35587+dADC,1.65+dLength);
		fragCutADC->SetPoint(5,378+dADC,0.5+dLength);
		fragCutADC->SetPoint(6,378+dADC,0.5+dLength);
		fragCutADC->SetPoint(7,401+dADC,0.55162+dLength);
		fragCutADC->SetPoint(8,425+dADC,0.603737+dLength);
		fragCutADC->SetPoint(9,449+dADC,0.656355+dLength);
		fragCutADC->SetPoint(10,472+dADC,0.709481+dLength);
		fragCutADC->SetPoint(11,496+dADC,0.763117+dLength);
		fragCutADC->SetPoint(12,520+dADC,0.81727+dLength);
		fragCutADC->SetPoint(13,544+dADC,0.871945+dLength);
		fragCutADC->SetPoint(14,567+dADC,0.927145+dLength);
		fragCutADC->SetPoint(15,591+dADC,0.982877+dLength);

	}
	return fragCutADC;
}