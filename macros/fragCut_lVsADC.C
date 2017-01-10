#include "TROOT.h"
#include "TRint.h"
#include "TCutG.h"

#include <math.h>
#include <iomanip>
#include <iostream>

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