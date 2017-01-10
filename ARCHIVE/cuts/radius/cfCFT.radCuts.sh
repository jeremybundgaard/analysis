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

$myana/anahists/cuts/azimuth/azCutsAnaHistMaker.sh $myana/listRecoData/cf/blocksOfRuns/cfCFT.1stpreamp.1865.73.83.list $nEvents $radMin $radMax; sleep 5
$myana/anahists/cuts/azimuth/azCutsAnaHistMaker.sh $myana/listRecoData/cf/blocksOfRuns/cfCFT.2ndPreamp.2069.list $nEvents $radMin $radMax; sleep 5
