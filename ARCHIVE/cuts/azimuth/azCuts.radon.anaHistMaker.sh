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

echo $myana/anahists/cuts/azimuth/azCutsAnaHistMaker.sh $myana/listRecoData/radon1499-1501.list $nEvents $azMin $azMax;
$myana/anahists/cuts/azimuth/azCutsAnaHistMaker.sh $myana/listRecoData/radon1499-1501.list $nEvents $azMin $azMax; sleep 5
