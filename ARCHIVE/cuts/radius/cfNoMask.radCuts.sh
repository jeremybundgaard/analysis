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

echo $myana/anahists/cuts/azimuth/azCutsAnaHistMaker.sh $myana/listRecoData/cf/blocksOfRuns/cfNoMask.1stpreamp.1866-72.1874-82.list $nEvents $radMin $radMax;
$myana/anahists/cuts/azimuth/azCutsAnaHistMaker.sh $myana/listRecoData/cf/blocksOfRuns/cfNoMask.1stpreamp.1866-72.1874-82.list $nEvents $radMin $radMax; sleep 5
echo $myana/anahists/cuts/azimuth/azCutsAnaHistMaker.sh $myana/listRecoData/cf/blocksOfRuns/cfNoMask.2ndPreamp.2055-61.list $nEvents $radMin $radMax;
$myana/anahists/cuts/azimuth/azCutsAnaHistMaker.sh $myana/listRecoData/cf/blocksOfRuns/cfNoMask.2ndPreamp.2055-61.list $nEvents $radMin $radMax; sleep 5