#!/bin/bash
nEvents=-1

if [ $# -gt 0 ];then
	nEvents=$1
fi

echo $myana/anahists/ratio/runTime/runTime.sh $myana/listRecoData/cm/blocksOfRuns/cmNoMask.1stPreamp.1922-23.list $nEvents;
$myana/anahists/ratio/runTime/runTime.sh $myana/listRecoData/cm/blocksOfRuns/cmNoMask.1stPreamp.1922-23.list $nEvents; sleep 5

echo $myana/anahists/ratio/runTime/runTime.sh $myana/listRecoData/cm/blocksOfRuns/cmNoMask.2ndPreamp.2250-52.54-56.list $nEvents;
$myana/anahists/ratio/runTime/runTime.sh $myana/listRecoData/cm/blocksOfRuns/cmNoMask.2ndPreamp.2250-52.54-56.list $nEvents; sleep 5
