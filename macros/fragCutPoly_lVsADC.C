#include "TROOT.h"
#include "TRint.h"
#include "TPolyLine.h"

#include <math.h>
#include <iomanip>
#include <iostream>

TPolyLine* fragCutPoly_lVsADC(int preamp, int dADC=0, int dLength=0){

	TPolyLine *fragCutPolyADC = new TPolyLine(8,"");
	fragCutPolyADC->SetLineColor(kViolet);
	fragCutPolyADC->SetLineWidth(3);

	if (preamp==1)
	{
		fragCutPolyADC->SetPoint(0,644+dADC,1.03077+dLength);
		fragCutPolyADC->SetPoint(1,3554+dADC,1.9+dLength);
		fragCutPolyADC->SetPoint(2,8293+dADC,2.35+dLength);
		fragCutPolyADC->SetPoint(3,16824+dADC,3.15+dLength);
		fragCutPolyADC->SetPoint(4,35545+dADC,3.65+dLength);
		fragCutPolyADC->SetPoint(5,35545+dADC,1.65+dLength);
		fragCutPolyADC->SetPoint(6,478+dADC,0.5+dLength);
		fragCutPolyADC->SetPoint(7,478+dADC,0.5+dLength);
		fragCutPolyADC->SetPoint(8,502+dADC,0.573987+dLength);
		fragCutPolyADC->SetPoint(9,526+dADC,0.648579+dLength);
		fragCutPolyADC->SetPoint(10,549+dADC,0.723779+dLength);
		fragCutPolyADC->SetPoint(11,573+dADC,0.799594+dLength);
		fragCutPolyADC->SetPoint(12,597+dADC,0.876028+dLength);
		fragCutPolyADC->SetPoint(13,620+dADC,0.953086+dLength);
		fragCutPolyADC->SetPoint(14,644+dADC,1.03077+dLength);

	}
	else if (preamp==2)
	{
		fragCutPolyADC->SetPoint(0,591+dADC,0.982877+dLength);
		fragCutPolyADC->SetPoint(1,3558+dADC,1.9+dLength);
		fragCutPolyADC->SetPoint(2,8303+dADC,2.35+dLength);
		fragCutPolyADC->SetPoint(3,16844+dADC,3.15+dLength);
		fragCutPolyADC->SetPoint(4,35587+dADC,3.65+dLength);
		fragCutPolyADC->SetPoint(5,35587+dADC,1.65+dLength);
		fragCutPolyADC->SetPoint(6,378+dADC,0.5+dLength);
		fragCutPolyADC->SetPoint(7,378+dADC,0.5+dLength);
		fragCutPolyADC->SetPoint(8,401+dADC,0.55162+dLength);
		fragCutPolyADC->SetPoint(9,425+dADC,0.603737+dLength);
		fragCutPolyADC->SetPoint(10,449+dADC,0.656355+dLength);
		fragCutPolyADC->SetPoint(11,472+dADC,0.709481+dLength);
		fragCutPolyADC->SetPoint(12,496+dADC,0.763117+dLength);
		fragCutPolyADC->SetPoint(13,520+dADC,0.81727+dLength);
		fragCutPolyADC->SetPoint(14,544+dADC,0.871945+dLength);
		fragCutPolyADC->SetPoint(15,567+dADC,0.927145+dLength);
		fragCutPolyADC->SetPoint(16,591+dADC,0.982877+dLength);

	}
	return fragCutPolyADC;
}