#MSUB -l walltime=200:00:00
#MSUB -q pbatch
#MSUB -r y

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

outputRootHistogramFile=histograms.`basename $runListInputFile .list`.nEvents-$nEvents.root
logFile=log.`basename $runListInputFile .list`.nEvents-$nEvents
echo "began " `date` >> $logFile
root -b -q $myana/anahists/pad2pad/pad2pad.C\(\"$runListInputFile\"\,\"$outputRootHistogramFile\",$nEvents\) >> $logFile &


echo `date` >> $logFile