#include "TROOT.h"
#include "TRint.h"
#include "TCutG.h"

#include <math.h>
#include <iomanip>
#include <iostream>

TCutG* fragCut_lVsEnergy(int preamp, double dEnergy=0, double dLength=0, const char* fragCutName=""){

	TCutG *fragCutEnergy = new TCutG(fragCutName,8);
	fragCutEnergy->SetLineColor(kViolet);
	fragCutEnergy->SetLineWidth(3);
	fragCutEnergy->SetVarX("adc");
	fragCutEnergy->SetVarY("length");

	if (preamp==1)
	{
		fragCutEnergy->SetPoint(0,2.71991+dEnergy,1.03077+dLength);
		fragCutEnergy->SetPoint(1,15.0+dEnergy,2.35+dLength);
		fragCutEnergy->SetPoint(2,71.0+dEnergy,3.15+dLength);
		fragCutEnergy->SetPoint(3,150.0+dEnergy,3.65+dLength);
		fragCutEnergy->SetPoint(4,150.0+dEnergy,1.65+dLength);
		fragCutEnergy->SetPoint(5,2.01991+dEnergy,0.5+dLength);
		fragCutEnergy->SetPoint(6,2.01991+dEnergy,0.5+dLength);
		fragCutEnergy->SetPoint(7,2.11991+dEnergy,0.573987+dLength);
		fragCutEnergy->SetPoint(8,2.21991+dEnergy,0.648579+dLength);
		fragCutEnergy->SetPoint(9,2.31991+dEnergy,0.723779+dLength);
		fragCutEnergy->SetPoint(10,2.41991+dEnergy,0.799594+dLength);
		fragCutEnergy->SetPoint(11,2.51991+dEnergy,0.876028+dLength);
		fragCutEnergy->SetPoint(12,2.61991+dEnergy,0.953086+dLength);
		fragCutEnergy->SetPoint(13,2.71991+dEnergy,1.03077+dLength);

	}
	else if (preamp==2)
	{
		fragCutEnergy->SetPoint(0,2.49341+dEnergy,0.982877+dLength);
		fragCutEnergy->SetPoint(1,15.0+dEnergy,2.35+dLength);
		fragCutEnergy->SetPoint(2,71.0+dEnergy,3.15+dLength);
		fragCutEnergy->SetPoint(3,150.0+dEnergy,3.65+dLength);
		fragCutEnergy->SetPoint(4,150.0+dEnergy,1.65+dLength);
		fragCutEnergy->SetPoint(5,1.59341+dEnergy,0.5+dLength);
		fragCutEnergy->SetPoint(6,1.59341+dEnergy,0.5+dLength);
		fragCutEnergy->SetPoint(7,1.69341+dEnergy,0.55162+dLength);
		fragCutEnergy->SetPoint(8,1.79341+dEnergy,0.603737+dLength);
		fragCutEnergy->SetPoint(9,1.89341+dEnergy,0.656355+dLength);
		fragCutEnergy->SetPoint(10,1.99341+dEnergy,0.709481+dLength);
		fragCutEnergy->SetPoint(11,2.09341+dEnergy,0.763117+dLength);
		fragCutEnergy->SetPoint(12,2.19341+dEnergy,0.81727+dLength);
		fragCutEnergy->SetPoint(13,2.29341+dEnergy,0.871945+dLength);
		fragCutEnergy->SetPoint(14,2.39341+dEnergy,0.927145+dLength);
		fragCutEnergy->SetPoint(15,2.49341+dEnergy,0.982877+dLength);

	}
	return fragCutEnergy;
}