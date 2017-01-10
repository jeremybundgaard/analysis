#!/bin/bash
plotDir=$1
delay=40

for i in $(ls $plotDir/*.01.*)
do
	plottypes=`basename $i .01.azMin-170.azMax-140.wAccumADC.png`
	# echo $plottypes
	convert -delay $delay -loop 0 $plotDir$plottypes* $plottypes.delay$delay.gif 
	echo created $plottypes.gif 
done
