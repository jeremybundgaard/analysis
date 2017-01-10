#!/bin/bash


pidType="zCut"
cuts="1"

echo 
array=( "$@" )
arraylength=${#array[@]}
for (( i=1; i<${arraylength}+1; i++ ));
do
	if [[ "${array[$i-1]}" = "-cuts" ]]; then
		cuts="${array[$i]}"
		echo "-cuts $cuts"
	fi
	if [[ "${array[$i-1]}" = "-pidType" ]]; then
		pidType="${array[$i]}"
		echo "-pidType $pidType"
	fi
done

if [[ -z $pidType ]]; then
	echo "-pidType not set"
	usage
fi

topdir=$cft/summaryPlots/${pidType}_cftAnaPlots.cf252.`date +%d%b%y_%H%M.%S`
mkdir $topdir
cd $topdir


cd $topdir
mkdir pidCuts
cd pidCuts

# preamp=1
# mkdir preamp$preamp
# cd preamp$preamp
# launchScript=launchScript_preamp${preamp}_pidCut${pidCut}.sh
# echo $macros/cftAnaPlots.sh \
# -preamp $preamp \
# -actinide cf252 \
# -noMaskTree $trees/cf252.noMask$preamp.nEv10k.trees.root \
# -cftTree $trees/cf252.cft$preamp.nEv10k.trees.root \
# -pidType $pidType \
# >> $launchScript
# chmod 750 $launchScript
# time ./$launchScript &
# cd -

preamp=2
mkdir preamp$preamp
cd preamp$preamp
launchScript=launchScript_preamp${preamp}_pidCut${pidCut}.sh
echo $macros/cftAnaPlots.sh \
-preamp $preamp \
-actinide cf252 \
-noMaskTree $trees/cf252.noMask$preamp.nEv10k.trees.root \
-cftTree $trees/cf252.cft$preamp.nEv10k.trees.root \
-pidType $pidType \
>> $launchScript
chmod 750 $launchScript
time ./$launchScript &
cd -
