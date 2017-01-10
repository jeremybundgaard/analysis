#!/bin/bash
delay=40
cutName=.01.azMin-170.azMax-140.wAccumADC.png

for i in $(ls plots/*.01.*)
do
	plottypes=`basename $i $cutName`
	# echo $plottypes
	convert -delay $delay -loop 0 plots/$plottypes* gifs/$plottypes.delay$delay.gif 
	echo created $plottypes.gif 
done
