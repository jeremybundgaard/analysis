#!/bin/bash


usage ()
{
	echo "required input: -preamp <1|2> -actinide <cf252|cm244> -noMaskTree </path/to/noMaskTree.trees.root> -cftTree </path/to/cftTree.trees.root>"
	echo s
	echo "other inputs eg: -cuts \"&&0.2<direction.CosTheta()&&direction.CosTheta()<0.8\" "
	echo
	exit
}

cuts="1&&fitType==5"
pidType="zCut"
actinide="cf252"

echo
array=( "$@" )
arraylength=${#array[@]}
for (( i=1; i<${arraylength}+1; i++ ));
do
	if [[ "${array[$i-1]}" = "-preamp" ]]; then
		preamp="${array[$i]}"
		echo "-preamp $preamp"
	fi
	if [[ "${array[$i-1]}" = "-actinide" ]]; then
		actinide="${array[$i]}"
		echo "-actinide $actinide"
	fi
	if [[ "${array[$i-1]}" = "-noMaskTree" ]]; then
		noMaskTree="${array[$i]}"
		echo "-noMaskTree $noMaskTree"
	fi
	if [[ "${array[$i-1]}" = "-pidFile" ]]; then
		pidFile="${array[$i]}"
		echo "-pidFile $pidFile"
	fi
	if [[ "${array[$i-1]}" = "-cftTree" ]]; then
		cftTree="${array[$i]}"
		echo "-cftTree $cftTree"
	fi
	if [[ "${array[$i-1]}" = "-cuts" ]]; then
		cuts="${array[$i]}"
		echo "-cuts $cuts"
	fi
	if [[ "${array[$i-1]}" = "-pidType" ]]; then
		pidType="${array[$i]}"
		echo "-pidType $pidType"
	fi
	if [[ "${array[$i-1]}" = "-driftVel" ]]; then
		driftVel="${array[$i]}"
		echo "-driftVel $driftVel"
	fi
done

if [[ -z $preamp ]]; then
	echo "-preamp not set"
	usage
fi
if [[ ! -f $pidFile ]]; then
	echo "pidFile file doesn't exist: $pidFile"
	exit
fi
if [[ ! -f $noMaskTree ]]; then
	echo "noMaskTree file doesn't exist: $noMaskTree"
	exit
fi
if [[ ! -f $cftTree ]]; then
	echo "cftTree file doesn't exist: $cftTree"
	exit
fi

driftVel=4.9
addGuide="False"

plotdir=`pwd`/cftAnaPlots.${actinide}.${preamp}preamp.$pidType.pidCut$pidCut.`date +%d%b%y_%H%M.%S`
mkdir $plotdir
cd $plotdir
cp $macros/cftAnaPlots.{sh,C} $plotdir

echo root -l -q -b $macros/cftAnaPlots.C\+\($preamp,\"$actinide\"\,\"$pidFile\"\,\"$noMaskTree\"\,\"$cftTree\"\,\"$cuts\"\,\"$driftVel\"\,\"$addGuide\"\)
time root -l -q -b $macros/cftAnaPlots.C\+\($preamp,\"$actinide\"\,\"$pidFile\"\,\"$noMaskTree\"\,\"$cftTree\"\,\"$cuts\"\,\"$driftVel\"\,\"$addGuide\"\)
wait
mkdir backups pngs grid_plots
mv cftAnaPlots.{sh,C} backups/.

#
#
# gm montage -mode concatenate -tile 2x2 \
# noMaskLvEn.cuts.fullEn.logx.png cftLvEn.cuts.fullEn.logx.png \
# noMask_pidCuts_En_Stack_logxy_fullEn.png cft_pidCuts_En_Stack_logxy_fullEn.png \
# 2x2grid.cuts.fullEn.logx.png
# wait
# echo "created 2x2grid.cuts.fullEn.logx.png"
# mv \
# noMaskLvEn.cuts.fullEn.logx.png cftLvEn.cuts.fullEn.logx.png \
# noMask_pidCuts_En_Stack_logxy_fullEn.png cft_pidCuts_En_Stack_logxy_fullEn.png \
# pngs/.
#
# gm montage -mode concatenate -tile 2x2 \
# noMaskLvEn.cuts.lowEn.png cftLvEn.cuts.lowEn.png \
# noMask_pidCuts_En_Stack_logy_lowEn.png cft_pidCuts_En_Stack_logy_lowEn.png \
# 2x2grid.cuts.lowEn.logx.png
# wait
# echo "created 2x2grid.cuts.lowEn.logx.png"
# mv \
# noMaskLvEn.cuts.lowEn.png cftLvEn.cuts.lowEn.png \
# noMask_pidCuts_En_Stack_logy_lowEn.png cft_pidCuts_En_Stack_logy_lowEn.png \
# pngs/.
#
# gm montage -mode concatenate -tile 2x2 \
# noMaskCuts.asf.fullEn.logxy.png cftCuts.asf.fullEn.logxy.png \
# cf252.preamp${preamp}.noMaskEn.fullEn.logxy.png cf252.preamp${preamp}.cftEn.fullEn.logxy.png \
# 2x2grid.asf.fullEn.logxy.png
# wait
# echo "created 2x2grid.asf.fullEn.logx.png"
# mv \
# noMaskCuts.asf.fullEn.logxy.png cftCuts.asf.fullEn.logxy.png \
# cf252.preamp${preamp}.noMaskEn.fullEn.logxy.png cf252.preamp${preamp}.cftEn.fullEn.logxy.png \
# pngs/.
#
# gm montage -mode concatenate -tile 2x2 \
# noMaskLvEn.fullEn.logx.png cftLvEn.fullEn.logx.png \
# noMaskEn.fullEn.logx.png cftEn.fullEn.logx.png \
# 2x2grid.noCuts.fullEn.logx.png
# wait
# echo "created 2x2grid.noCuts.fullEn.logx.png"
# mv \
# noMaskLvEn.fullEn.logx.png cftLvEn.fullEn.logx.png \
# noMaskEn.fullEn.logx.png cftEn.fullEn.logx.png \
# pngs/.
#
# gm montage -mode concatenate -tile 2x2 \
# noMaskLvEn.lowEn.png cftLvEn.lowEn.png \
# noMaskEn.lowEn.png cftEn.lowEn.png \
# 2x2grid.noCuts.lowEn.png
# wait
# echo "created 2x2grid.noCuts.lowEn.png"
# mv \
# noMaskLvEn.lowEn.png cftLvEn.lowEn.png \
# noMaskEn.lowEn.png cftEn.lowEn.png \
# pngs/.
#
# gm montage -mode concatenate -tile 2x2 \
# noMaskCuts.asf.lowEn.png cftCuts.asf.lowEn.png \
# cf252.preamp${preamp}.noMaskEn.lowEn.logy.png cf252.preamp${preamp}.cftEn.lowEn.logy.png \
# 2x2grid.asf.lowEn.logx.png
# wait
# echo "created 2x2grid.asf.lowEn.logx.png"
# mv \
# noMaskCuts.asf.lowEn.png cftCuts.asf.lowEn.png \
# cf252.preamp${preamp}.noMaskEn.lowEn.logy.png cf252.preamp${preamp}.cftEn.lowEn.logy.png \
# pngs/.
#
# gm montage -mode concatenate -tile 3x1 \
# cf252.preamp${preamp}.bothFragsCut.fullEn.logy.png \
# cf252.preamp${preamp}.bothFragsCut.fullEn.logxy.png \
# cf252.preamp${preamp}.bothFragsCut.lowEn.logy.png \
# 1x3grid.cftEfficiency.png
# wait
# echo "created 1x3grid.cftEfficiency.png"
# mv \
# cf252.preamp${preamp}.bothFragsCut.fullEn.logy.png \
# cf252.preamp${preamp}.bothFragsCut.fullEn.logxy.png \
# cf252.preamp${preamp}.bothFragsCut.lowEn.logy.png \
# pngs/.
#
# mv 2x2grid*png grid_plots/.
# mv *.png pngs/.
#
# tar -zcf backups.tar.gz backups
# tar -zcf pngs.tar.gz pngs
# rm -rf backups pngs
#
# rm cftAnaPlots_*
# date
