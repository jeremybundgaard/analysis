#!/bin/bash
nEvents=-1
runListInputFile=$1
azMin=-180
azMax=180

if [ $# -gt 1 ];then
	nEvents=$2
fi
if [ $# -gt 2 ];then
	azMin=$3
fi
if [ $# -gt 3 ];then
	azMax=$4
fi

outputRootHistogramFile=`basename $runListInputFile .list`.nEvents-$nEvents.azMin$azMin.azMax$azMax.histograms.root
logFile=`basename $runListInputFile .list`.nEvents-$nEvents.azMin$azMin.azMax$azMax.log
echo "began " `date` >> $logFile
echo root -b -q $myana/anahists/cuts/azimuth/azCutsAnaHistMaker.C\+\(\"$runListInputFile\"\,\"$outputRootHistogramFile\",$nEvents,$azMin,$azMax\) >> $logFile &
root -b -q $myana/anahists/cuts/azimuth/azCutsAnaHistMaker.C\+\(\"$runListInputFile\"\,\"$outputRootHistogramFile\",$nEvents,$azMin,$azMax\) >> $logFile &

echo `date` >> $logFile
sleep 5
rm *_C.*