#!/bin/bash
nEvents=-1
radMin=0
radMax=7


if [ $# -gt 0 ];then
	nEvents=$1
fi
if [ $# -gt 1 ];then
	radMin=$2
fi
if [ $# -gt 2 ];then
	radMax=$3
fi

for i in $(ls $myana/listRecoData/cm/blocksOfRuns/{cmCFT.2ndPreamp.cm*list,cmCFT.1stPreamp.all*list}); do

	$myana/anahists/cuts/azimuth/azCutsAnaHistMaker.sh $i $nEvents $radMin $radMax 
	echo "launched anaHistMaker.sh $i $nEvents $radMin $radMax"
	sleep 5

done

$myana/combineCmCFT2ndpreamp.sh
