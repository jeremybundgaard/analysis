#!/bin/bash


nEvents=-1
if [ $# -gt 0 ];then
	nEvents=$1
fi

workdir=binCut46.outputDir.nEvents$nEvents\_`date +%H%M.%S_%d%b%y`
mkdir $workdir
cd $workdir

# compile any changes
cd $NIFFTE/tpc/calib;make;make install;cd -

logfile=log.$workdir
echo "niffte -c /g/g21/jerbundg/niffte/trunk/build/TPCBuildAverageBraggCurve.xml -i /p/lscratche/jerbundg/data/thesisData/raw/cm/noMask/1stPreamp/niffte-run100001922_20Jun2013_11-04.raw -n $nEvents" >> $logfile

echo "start time:   `date +%H%M.%S_%d%b%y` "
niffte -c /g/g21/jerbundg/niffte/trunk/build/TPCBuildAverageBraggCurve.xml -i /p/lscratche/jerbundg/data/thesisData/raw/cm/noMask/1stPreamp/niffte-run100001922_20Jun2013_11-04.raw -n $nEvents >> $logfile
echo "end time:   `date +%H%M.%S_%d%b%y` "

rm niffte-output.root
cd -
