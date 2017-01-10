#!/bin/bash
nEvents=-1
runListInputFile=$1

if [ $# -gt 1 ];then
	nEvents=$2
fi

outRunTimeFile=`basename $runListInputFile .list`.nEvents-$nEvents.runTime.txt
logFile=`basename $runListInputFile .list`.nEvents-$nEvents.runTime.log
echo "began " `date` >> $logFile
echo root -b -q $myana/anahists/ratio/runTime/runTime.C\+\(\"$runListInputFile\"\,\"$outRunTimeFile\",$nEvents\) >> $logFile &
root -b -q $myana/anahists/ratio/runTime/runTime.C\+\(\"$runListInputFile\"\,\"$outRunTimeFile\",$nEvents\) >> $logFile &

echo `date` >> $logFile
