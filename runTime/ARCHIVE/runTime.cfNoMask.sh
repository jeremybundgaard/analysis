#!/bin/bash
nEvents=-1
runListInputFile=$1

if [ $# -gt 0 ];then
	nEvents=$1
fi

echo $myana/anahists/ratio/runTime/runTime.sh $myana/listRecoData/cf/blocksOfRuns/cfNoMask.1stpreamp.1866-72.1874-82.list $nEvents;
$myana/anahists/ratio/runTime/runTime.sh $myana/listRecoData/cf/blocksOfRuns/cfNoMask.1stpreamp.1866-72.1874-82.list $nEvents; sleep 5
echo $myana/anahists/ratio/runTime/runTime.sh $myana/listRecoData/cf/blocksOfRuns/cfNoMask.2ndPreamp.2055-61.list $nEvents;
$myana/anahists/ratio/runTime/runTime.sh $myana/listRecoData/cf/blocksOfRuns/cfNoMask.2ndPreamp.2055-61.list $nEvents; sleep 5