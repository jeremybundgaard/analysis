#!/bin/bash
nEvents=1000
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

echo $myana/anahists/cuts/azimuth/azCutsAnaHistMaker.sh autoradgraph.list $nEvents $azMin $azMax;
$myana/anahists/cuts/azimuth/azCutsAnaHistMaker.sh autoradgraph.list $nEvents $azMin $azMax; sleep 5
