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

echo $myana/anahists/cuts/azimuth/azCutsAnaHistMaker.sh $myana/listRecoData/cf/blocksOfRuns/cfNoMask.1stpreamp.1866-72.1874-82.list $nEvents $azMin $azMax;
$myana/anahists/cuts/azimuth/azCutsAnaHistMaker.sh $myana/listRecoData/cf/blocksOfRuns/cfNoMask.1stpreamp.1866-72.1874-82.list $nEvents $azMin $azMax; sleep 5
echo $myana/anahists/cuts/azimuth/azCutsAnaHistMaker.sh $myana/listRecoData/cf/blocksOfRuns/cfNoMask.2ndPreamp.2055-61.list $nEvents $azMin $azMax;
$myana/anahists/cuts/azimuth/azCutsAnaHistMaker.sh $myana/listRecoData/cf/blocksOfRuns/cfNoMask.2ndPreamp.2055-61.list $nEvents $azMin $azMax; sleep 5