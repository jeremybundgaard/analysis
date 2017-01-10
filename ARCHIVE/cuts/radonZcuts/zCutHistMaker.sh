#!/bin/bash


runListInputFile=$1
nEvents=-1
if [ $# -gt 1 ];then
	nEvents=$2
fi

outputRootHistogramFile="zCut."`basename $runListInputFile .list`.nEvents-$nEvents.histograms.root
logFile="zCut."`basename $runListInputFile .list`.nEvents-$nEvents.log
echo "began " `date` >> $logFile
root -b -q zCutHistMaker.C\+\(\"$runListInputFile\"\,\"$outputRootHistogramFile\",$nEvents\) >> $logFile &


echo `date` >> $logFile