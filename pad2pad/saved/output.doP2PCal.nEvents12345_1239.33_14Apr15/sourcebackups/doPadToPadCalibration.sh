#!/bin/bash


nEvents=-1
if [ $# -gt 0 ];then
	nEvents=$1
fi

workdir=`pwd`/output.doP2PCal.nEvents$nEvents\_`date +%H%M.%S_%d%b%y`
mkdir $workdir
cd $workdir


# compile any changes
cd $NIFFTE/tpc/calib;make;make install;cd -

mkdir $workdir/sourcebackups
cp $pad2pad/doPadToPadCalibration.sh $workdir/sourcebackups/.
cp $NIFFTE/tpc/calib/TPCPadToPadCalibration.{cxx,h} $workdir/sourcebackups/.
cp $NIFFTE/tpc/calib/TPCBuildAverageBraggCurve.{cxx,h} $workdir/sourcebackups/.

mkdir $pad2pad/sourcebackups
cp $pad2pad/doPadToPadCalibration.sh $pad2pad//sourcebackups/.
cp $NIFFTE/tpc/calib/TPCPadToPadCalibration.{cxx,h} $pad2pad//sourcebackups/.
cp $NIFFTE/tpc/calib/TPCBuildAverageBraggCurve.{cxx,h} $pad2pad//sourcebackups/.

logfile=log.`basename $workdir`
echo "niffte -c /g/g21/jerbundg/niffte/trunk/build/TPCBuildAverageBraggCurve.xml -i /p/lscratche/jerbundg/data/thesisData/raw/cm/noMask/1stPreamp/niffte-run100001922_20Jun2013_11-04.raw -n $nEvents" >> $logfile

echo "start building average bragg curves:   `date +%H%M.%S_%d%b%y` "
niffte -c /g/g21/jerbundg/niffte/trunk/build/TPCBuildAverageBraggCurve.xml -i /p/lscratche/jerbundg/data/thesisData/raw/cm/noMask/1stPreamp/niffte-run100001922_20Jun2013_11-04.raw -n $nEvents >> $logfile
echo "finished building average bragg curves:   `date +%H%M.%S_%d%b%y` "

mkdir buildingAvgBraggs
mkdir buildingAvgBraggs/runningBraggCurve
mkdir buildingAvgBraggs/braggCurvesPerEvent
mv runningBraggCurve*png buildingAvgBraggs/runningBraggCurve/.
mv braggCurve*png buildingAvgBraggs/braggCurvesPerEvent/.

echo "niffte -c /g/g21/jerbundg/niffte/trunk/build/TPCPadToPadCalibration.xml -i /p/lscratche/jerbundg/data/thesisData/raw/cm/noMask/1stPreamp/niffte-run100001922_20Jun2013_11-04.raw -n $nEvents" >> $logfile

echo "start computing scale factors:   `date +%H%M.%S_%d%b%y` "
niffte -c /g/g21/jerbundg/niffte/trunk/build/TPCPadToPadCalibration.xml -i /p/lscratche/jerbundg/data/thesisData/raw/cm/noMask/1stPreamp/niffte-run100001922_20Jun2013_11-04.raw -n $nEvents >> $logfile
echo "scale factors computed:   `date +%H%M.%S_%d%b%y` "

rm niffte-output.root

mkdir scaleFactors
mkdir scaleFactors/evtLengthBinScalePlots
mkdir scaleFactors/padIndexScaleHistPlots
mkdir scaleFactors/padIndexScaleHistPlots/log
mkdir scaleFactors/padIndexScaleHistPlots/linear

mv lengthBinScalesPerEvt_evt*png scaleFactors/evtLengthBinScalePlots/.
mv log.padIndex_*png scaleFactors/padIndexScaleHistPlots/log/.
mv padIndex*png scaleFactors/padIndexScaleHistPlots/linear/.

cd -
