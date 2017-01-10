#!/bin/bash

plotdirSuppGoodHK=buildAlphaRidgeCut.SuppGoodHK.`date +%d%b%y_%H%M.%S`
mkdir $plotdirSuppGoodHK
cp $macros/buildAlphaRidgeCut/buildAlphaRidgeCutSuppGoodHK.C $plotdirSuppGoodHK
cd $plotdirSuppGoodHK
root -l -q -b buildAlphaRidgeCutSuppGoodHK.C\+ &


cd -
plotdirSuppGoodFP=buildAlphaRidgeCut.SuppGoodFP.`date +%d%b%y_%H%M.%S`
mkdir $plotdirSuppGoodFP
cp $macros/buildAlphaRidgeCut/buildAlphaRidgeCutSuppGoodFP.C $plotdirSuppGoodFP
cd $plotdirSuppGoodFP
root -l -q -b buildAlphaRidgeCutSuppGoodFP.C\+ &
