#!/bin/bash

curdir=`pwd`

cd $cft/pid/zCut
$macros/pidCut_zCut.sh -preamp 1 -noMaskTree $trees/cf252.noMask1.trees.root &
$macros/pidCut_zCut.sh -preamp 2 -noMaskTree $trees/cf252.noMask2.trees.root &

# cd $cft/pid/expo
# $macros/pidCut_alphaExponential.sh -preamp 1 -noMaskTree $trees/cf252.noMask1.trees.root &
# $macros/pidCut_alphaExponential.sh -preamp 2 -noMaskTree $trees/cf252.noMask2.trees.root &

cd $curdir


