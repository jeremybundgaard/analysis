#!/bin/bash
nEvents=-1
if [ $# -gt 0 ];then
	nEvents=$1
fi


for i in $(ls $myana/listRecoData/cm/blocksOfRuns/{cmCFT.2ndPreamp.cm*list,cmCFT.1stPreamp.all*list}); do

	$myana/anahists/ratio/runTime/runTime.sh $i $nEvents
	echo "launched runTime.sh $i $nEvents"
	sleep 5

done

