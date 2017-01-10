#!/bin/bash

if [ $# -lt 1 ]||[ $# -gt 2 ] ;then

	echo "number of args = $#"
	echo "1 arg USAGE: ./anaHistMaker.SH <runListInputFile>"
	echo "2 arg USAGE: ./anaHistMaker.SH <runListInputFile> <nEvents>"
	exit
fi

runListInputFile=$1
nEvents=-1
if [ $# -gt 1 ];then
	nEvents=$2
fi

outputRootHistogramFile=`basename $runListInputFile .list`.nEvents-$nEvents.histograms.root
logFile=`basename $runListInputFile .list`.nEvents-$nEvents.log
echo "began " `date` >> $logFile
root -b -q anaHistMaker.C\+\+\(\"$runListInputFile\"\,\"$outputRootHistogramFile\",$nEvents\) >> $logFile &


echo `date` >> $logFile