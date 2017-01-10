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

$myana/anahists/cuts/azimuth/azCutsAnaHistMaker.sh $myana/listRecoData/cf/blocksOfRuns/cfCFT.1stpreamp.1865.73.83.list $nEvents $azMin $azMax; sleep 5
$myana/anahists/cuts/azimuth/azCutsAnaHistMaker.sh $myana/listRecoData/cf/blocksOfRuns/cfCFT.2ndPreamp.2069.list $nEvents $azMin $azMax; sleep 5
rm *_C.*