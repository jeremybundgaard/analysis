#!/bin/bash


cftFile=$1
bnameCftFile=`basename $cftFile`
noMaskFile=$2
bnameNoMaskFile=`basename $noMaskFile`

cosThetaMin=$3
cosThetaMax=$4

outdir=`pwd`/output.stepThruFragCutTree.cosMin${cosThetaMin}.cosMax${cosThetaMax}.`date +%d%b%y_%H%M.%S`
mkdir $outdir $outdir/plots
cp {$cftFile,$noMaskFile,$ana/cft/triggerQuantication/stepThruFragCutTree.C} $outdir
cp $cftFile $outdir
cd $outdir


logFile=log.`basename $1`

echo "began " `date` >> $logFile
root  -b -q stepThruFragCutTree.C\+\(\"$bnameCftFile\",\"$bnameNoMaskFile\",$cosThetaMin,$cosThetaMax\) >> $logFile
echo `date` >> $logFile

sleep 1
rm $outdir/stepThruFragCutTree_*

for i in `ls *png`;do
	mv $i ${i%.png}.cosMin${cosThetaMin}.cosMax${cosThetaMax}.png;
done

mv *png plots/.

cd -
