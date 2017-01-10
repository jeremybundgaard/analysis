#!/bin/bash
nEvents=-1

if [ $# -gt 0 ];then
	nEvents=$1
fi

$myana/anahists/ratio/runTime/runTime.cfNoMask.sh $nEvents
$myana/anahists/ratio/runTime/runTime.cfCFT.sh $nEvents