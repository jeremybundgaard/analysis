#!/bin/bash
nEvents=-1
runListInputFile=$1
radMin=0
radMax=7

if [ $# -gt 1 ];then
	nEvents=$2
fi

if [ $# -gt 2 ];then
	radMin=$3
fi

if [ $# -gt 3 ];then
	radMax=$4
fi


outputRootHistogramFile=histogramsRadCut.`basename $runListInputFile .list`.nEvents-$nEvents.root
logFile=log.`basename $runListInputFile .list`.nEvents-$nEvents
echo "began " `date` >> $logFile
echo root -b -q $myana/anahists/pad2pad/pad2padAna.C\+\+\(\"$runListInputFile\"\,\"$outputRootHistogramFile\",$nEvents\) >> $logFile 
root -b -q $myana/anahists/pad2pad/pad2padAna.C\+\+\(\"$runListInputFile\"\,\"$outputRootHistogramFile\",$nEvents\) >> $logFile &
echo `date` >> $logFile
sleep 3
