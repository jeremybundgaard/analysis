#include "TROOT.h"
#include "TRint.h"
#include "TPolyLine.h"

#include <math.h>
#include <iomanip>
#include <iostream>

TPolyLine* fragCutPoly_lVsEnergy(int preamp, double dEnergy=0, double dLength=0){

	TPolyLine *fragCutPolyEnergy = new TPolyLine(8,"");
	fragCutPolyEnergy->SetLineColor(kViolet);
	fragCutPolyEnergy->SetLineWidth(3);

	if (preamp==1)
	{


		fragCutPolyEnergy->SetPoint(0,2.71991+dEnergy,1.03077+dLength);
		fragCutPolyEnergy->SetPoint(1,15.0+dEnergy,2.35+dLength);
		fragCutPolyEnergy->SetPoint(2,71.0+dEnergy,3.15+dLength);
		fragCutPolyEnergy->SetPoint(3,150.0+dEnergy,3.65+dLength);
		fragCutPolyEnergy->SetPoint(4,150.0+dEnergy,1.65+dLength);
		fragCutPolyEnergy->SetPoint(5,2.01991+dEnergy,0.5+dLength);
		fragCutPolyEnergy->SetPoint(6,2.01991+dEnergy,0.5+dLength);
		fragCutPolyEnergy->SetPoint(7,2.11991+dEnergy,0.573987+dLength);
		fragCutPolyEnergy->SetPoint(8,2.21991+dEnergy,0.648579+dLength);
		fragCutPolyEnergy->SetPoint(9,2.31991+dEnergy,0.723779+dLength);
		fragCutPolyEnergy->SetPoint(10,2.41991+dEnergy,0.799594+dLength);
		fragCutPolyEnergy->SetPoint(11,2.51991+dEnergy,0.876028+dLength);
		fragCutPolyEnergy->SetPoint(12,2.61991+dEnergy,0.953086+dLength);
		fragCutPolyEnergy->SetPoint(13,2.71991+dEnergy,1.03077+dLength);

	}
	else if (preamp==2)
	{
		fragCutPolyEnergy->SetPoint(0,2.49341+dEnergy,0.982877+dLength);
		fragCutPolyEnergy->SetPoint(1,15.0+dEnergy,2.35+dLength);
		fragCutPolyEnergy->SetPoint(2,71.0+dEnergy,3.15+dLength);
		fragCutPolyEnergy->SetPoint(3,150.0+dEnergy,3.65+dLength);
		fragCutPolyEnergy->SetPoint(4,150.0+dEnergy,1.65+dLength);
		fragCutPolyEnergy->SetPoint(5,1.59341+dEnergy,0.5+dLength);
		fragCutPolyEnergy->SetPoint(6,1.59341+dEnergy,0.5+dLength);
		fragCutPolyEnergy->SetPoint(7,1.69341+dEnergy,0.55162+dLength);
		fragCutPolyEnergy->SetPoint(8,1.79341+dEnergy,0.603737+dLength);
		fragCutPolyEnergy->SetPoint(9,1.89341+dEnergy,0.656355+dLength);
		fragCutPolyEnergy->SetPoint(10,1.99341+dEnergy,0.709481+dLength);
		fragCutPolyEnergy->SetPoint(11,2.09341+dEnergy,0.763117+dLength);
		fragCutPolyEnergy->SetPoint(12,2.19341+dEnergy,0.81727+dLength);
		fragCutPolyEnergy->SetPoint(13,2.29341+dEnergy,0.871945+dLength);
		fragCutPolyEnergy->SetPoint(14,2.39341+dEnergy,0.927145+dLength);
		fragCutPolyEnergy->SetPoint(15,2.49341+dEnergy,0.982877+dLength);

	}
	return fragCutPolyEnergy;
}