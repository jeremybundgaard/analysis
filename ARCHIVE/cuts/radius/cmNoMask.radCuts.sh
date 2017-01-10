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

echo ./radiusCuts.AnaHistMaker.sh $myana/listRecoData/cm/blocksOfRuns/cmNoMask.1stPreamp.1922-23.list $nEvents $radMin $radMax;
 ./radiusCuts.AnaHistMaker.sh $myana/listRecoData/cm/blocksOfRuns/cmNoMask.1stPreamp.1922-23.list $nEvents $radMin $radMax; sleep 5
# echo $myana/anahists/cuts/radius/radiusCuts.AnaHistMaker.sh $myana/listRecoData/cm/blocksOfRuns/cmNoMask.2ndPreamp.2250-52.54-56.list $nEvents $radMin $radMax;
#  $myana/anahists/cuts/radius/radiusCuts.AnaHistMaker.sh $myana/listRecoData/cm/blocksOfRuns/cmNoMask.2ndPreamp.2250-52.54-56.list $nEvents $radMin $radMax; sleep 5
