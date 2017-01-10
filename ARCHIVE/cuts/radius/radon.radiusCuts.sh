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

echo $myana/anahists/cuts/radius/radiusCuts.AnaHistMaker.sh $myana/listRecoData/radon1499-1501.list $nEvents $radMin $radMax;
$myana/anahists/cuts/radius/radiusCuts.AnaHistMaker.sh $myana/listRecoData/radon1499-1501.list $nEvents $radMin $radMax;
