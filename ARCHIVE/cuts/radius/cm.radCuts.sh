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

$myana/anahists/cuts/azimuth/azCuts.cmNoMask.anaHistMaker.sh $nEvents $radMin $radMax
$myana/anahists/cuts/azimuth/azCuts.cmCFT.anaHistMaker.sh $nEvents $radMin $radMax