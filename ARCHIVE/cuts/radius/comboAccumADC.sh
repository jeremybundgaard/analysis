#!/bin/bash

# for j in {00..35}; do 
# 	for i in $(ls individualPlots/*.$j.*);do 
# 		plotName=`basename $i .histograms.root.png`
# 		accumADChash=individualPlots/digADCvol0*.$j.*
# 		# echo $accumADChash
# 		# echo $i
# 		# echo " "
# 		montage -geometry 600x600 $i $accumADChash $plotName.wAccumADC.png
# 		echo creating $plotName.wAccumADC.png
# 	done
# done
 
montage -geometry 600x600 intensityvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin0.0.radMax1.0.histograms.root.png digADCvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin0.0.radMax1.0.histograms.root.png intensityvol0.cmNoMask.1stPreamp.radMin0.0.radMax1.0.wAccumADC.png   
montage -geometry 600x600 intensityvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin0.2.radMax1.2.histograms.root.png digADCvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin0.2.radMax1.2.histograms.root.png intensityvol0.cmNoMask.1stPreamp.radMin0.2.radMax1.2.wAccumADC.png
montage -geometry 600x600 intensityvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin0.4.radMax1.4.histograms.root.png digADCvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin0.4.radMax1.4.histograms.root.png intensityvol0.cmNoMask.1stPreamp.radMin0.4.radMax1.4.wAccumADC.png
montage -geometry 600x600 intensityvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin0.6.radMax1.6.histograms.root.png digADCvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin0.6.radMax1.6.histograms.root.png intensityvol0.cmNoMask.1stPreamp.radMin0.6.radMax1.6.wAccumADC.png
montage -geometry 600x600 intensityvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin0.8.radMax1.8.histograms.root.png digADCvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin0.8.radMax1.8.histograms.root.png intensityvol0.cmNoMask.1stPreamp.radMin0.8.radMax1.8.wAccumADC.png
montage -geometry 600x600 intensityvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin1.0.radMax2.0.histograms.root.png digADCvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin1.0.radMax2.0.histograms.root.png intensityvol0.cmNoMask.1stPreamp.radMin1.0.radMax2.0.wAccumADC.png
montage -geometry 600x600 intensityvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin1.2.radMax2.2.histograms.root.png digADCvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin1.2.radMax2.2.histograms.root.png intensityvol0.cmNoMask.1stPreamp.radMin1.2.radMax2.2.wAccumADC.png
montage -geometry 600x600 intensityvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin1.4.radMax2.4.histograms.root.png digADCvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin1.4.radMax2.4.histograms.root.png intensityvol0.cmNoMask.1stPreamp.radMin1.4.radMax2.4.wAccumADC.png
montage -geometry 600x600 intensityvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin1.6.radMax2.6.histograms.root.png digADCvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin1.6.radMax2.6.histograms.root.png intensityvol0.cmNoMask.1stPreamp.radMin1.6.radMax2.6.wAccumADC.png
montage -geometry 600x600 intensityvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin1.8.radMax2.8.histograms.root.png digADCvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin1.8.radMax2.8.histograms.root.png intensityvol0.cmNoMask.1stPreamp.radMin1.8.radMax2.8.wAccumADC.png
montage -geometry 600x600 intensityvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin2.0.radMax3.0.histograms.root.png digADCvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin2.0.radMax3.0.histograms.root.png intensityvol0.cmNoMask.1stPreamp.radMin2.0.radMax3.0.wAccumADC.png
montage -geometry 600x600 intensityvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin2.2.radMax3.2.histograms.root.png digADCvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin2.2.radMax3.2.histograms.root.png intensityvol0.cmNoMask.1stPreamp.radMin2.2.radMax3.2.wAccumADC.png
montage -geometry 600x600 intensityvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin2.4.radMax3.4.histograms.root.png digADCvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin2.4.radMax3.4.histograms.root.png intensityvol0.cmNoMask.1stPreamp.radMin2.4.radMax3.4.wAccumADC.png
montage -geometry 600x600 intensityvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin2.6.radMax3.6.histograms.root.png digADCvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin2.6.radMax3.6.histograms.root.png intensityvol0.cmNoMask.1stPreamp.radMin2.6.radMax3.6.wAccumADC.png
montage -geometry 600x600 intensityvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin2.8.radMax3.8.histograms.root.png digADCvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin2.8.radMax3.8.histograms.root.png intensityvol0.cmNoMask.1stPreamp.radMin2.8.radMax3.8.wAccumADC.png
montage -geometry 600x600 intensityvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin3.0.radMax4.0.histograms.root.png digADCvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin3.0.radMax4.0.histograms.root.png intensityvol0.cmNoMask.1stPreamp.radMin3.0.radMax4.0.wAccumADC.png
montage -geometry 600x600 intensityvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin3.2.radMax4.2.histograms.root.png digADCvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin3.2.radMax4.2.histograms.root.png intensityvol0.cmNoMask.1stPreamp.radMin3.2.radMax4.2.wAccumADC.png
montage -geometry 600x600 intensityvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin3.4.radMax4.4.histograms.root.png digADCvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin3.4.radMax4.4.histograms.root.png intensityvol0.cmNoMask.1stPreamp.radMin3.4.radMax4.4.wAccumADC.png
montage -geometry 600x600 intensityvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin3.6.radMax4.6.histograms.root.png digADCvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin3.6.radMax4.6.histograms.root.png intensityvol0.cmNoMask.1stPreamp.radMin3.6.radMax4.6.wAccumADC.png
montage -geometry 600x600 intensityvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin3.8.radMax4.8.histograms.root.png digADCvol0.cmNoMask.1stPreamp.1922-23.nEvents-54321.radMin3.8.radMax4.8.histograms.root.png intensityvol0.cmNoMask.1stPreamp.radMin3.8.radMax4.8.wAccumADC.png























