#!/bin/bash


cftFile=$1
bnameCftFile=`basename $cftFile`
noMaskFile=$2
bnameNoMaskFile=`basename $noMaskFile`

outdir=`pwd`/output.stepThruFragCut.`date +%d%b%y_%H%M.%S`
mkdir $outdir $outdir/plots
cp {$cftFile,$noMaskFile,$ana/cft/triggerQuantication/stepThruFragCut.C} $outdir
cp $cftFile $outdir
cd $outdir


logFile=log.`basename $1`

echo "began " `date` >> $logFile
root  -b -q stepThruFragCut.C\+\(\"$bnameCftFile\",\"$bnameNoMaskFile\"\) >> $logFile
echo `date` >> $logFile


sleep 1
rm $outdir/stepThruFragCut_*
mv *png plots/.

cd -
