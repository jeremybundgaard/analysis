#!/bin/bash
nEvents=-1
runListInputFile=$1
azMin=-180
azMax=180

if [ $# -gt 0 ];then
	nEvents=$1
fi
if [ $# -gt 1 ];then
	azMin=$2
fi
if [ $# -gt 2 ];then
	azMax=$3
fi

for i in $(ls $myana/listRecoData/cm/blocksOfRuns/{cmCFT.2ndPreamp.cm*list,cmCFT.1stPreamp.all*list}); do

	./azCutsAnaHistMaker.sh $i $nEvents $azMin $azMax 
	echo "launched anaHistMaker.sh $i $nEvents $azMin $azMax"
	sleep 5

done

$myana/combineCmCFT2ndpreamp.sh
$myana/cleanup.sh
