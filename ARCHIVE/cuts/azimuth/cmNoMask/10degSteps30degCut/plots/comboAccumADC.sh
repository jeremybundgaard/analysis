#!/bin/bash
pngDir=$1

for j in {0..3}; do 
	if (( $j < 10)); then
		j=0$j
	fi
	for i in $(ls $pngDir*.$j.*);do 
		plotName=`basename $i .histograms.root.png`
		accumADChash=$pngDir/digADCvol0*.$j.*
		# echo $plotName
		# echo $accumADChash
		# echo $i
		montage -geometry 600x600 $i $accumADChash $plotName.wAccumADC.png
		echo created $plotName.wAccumADC.png
	done
done
