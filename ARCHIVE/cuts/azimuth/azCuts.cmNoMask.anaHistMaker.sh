#!/bin/bash
nEvents=-1
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

# echo ./azCutsAnaHistMaker.sh $myana/listRecoData/cm/blocksOfRuns/cmNoMask.1stPreamp.1922-23.list $nEvents $azMin $azMax;
# $myana/anahists/cuts/azimuth/azCutsAnaHistMaker.sh $myana/listRecoData/cm/blocksOfRuns/cmNoMask.1stPreamp.1922-23.list $nEvents $azMin $azMax; sleep 5

echo $myana/anahists/cuts/azimuth/azCutsAnaHistMaker.sh $myana/listRecoData/cm/blocksOfRuns/cmNoMask.2ndPreamp.2250-52.54-56.list $nEvents $azMin $azMax;
$myana/anahists/cuts/azimuth/azCutsAnaHistMaker.sh $myana/listRecoData/cm/blocksOfRuns/cmNoMask.2ndPreamp.2250-52.54-56.list $nEvents $azMin $azMax; sleep 5
