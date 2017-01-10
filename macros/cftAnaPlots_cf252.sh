#!/bin/bash



pidType="linear"
lineardir=$cft/$pidType.cf252.cftAnaPlots.`date +%d%b%y_%H%M.%S`
mkdir $lineardir
cd $lineardir

for pidCut in {3..19}
do
	for preamp in {1,2}
	do
		$macros/cftAnaPlots.sh \
		-preamp $preamp \
		-actinide cf252 \
		-noMaskTree $trees/cf252.noMask$preamp.nEv100000.trees.root \
		-cftTree $trees/cf252.cft$preamp.nEv100000.trees.root \
		-pidType $pidType \
		-pidCut $pidCut
	done 
done

ls cftAnaPlots.cf252.1preamp.pidType2.pidCut3*/cftPlots/*png|while read i
do
	name=`basename $i`
	name=${name#*pid2.}
	echo $name
	gm convert -loop 0 -delay 20 \
	`ls cftAnaPlots.cf252.1preamp.pidType*/cftPlots/*$name|sort` \
	`ls cftAnaPlots.cf252.1preamp.pidType*/cftPlots/*$name|sort -r` \
	preamp1.${name%png}gif
done

ls cftAnaPlots.cf252.2preamp.pidType2.pidCut3*/cftPlots/*png|while read i
do
	name=`basename $i`
	name=${name#*pid2.}
	echo $name
	gm convert -loop 0 -delay 20 \
	`ls cftAnaPlots.cf252.2preamp.pidType*/cftPlots/*$name|sort` \
	`ls cftAnaPlots.cf252.2preamp.pidType*/cftPlots/*$name|sort -r` \
	preamp2.${name%png}gif
done

# preamp=1
# pidCut=3
# pidType="linear"

# $macros/cftAnaPlots.sh \
# -preamp $preamp \
# -actinide cf252 \
# -noMaskTree $trees/cf252.noMask$preamp.nEv100000.trees.root \
# -cftTree $trees/cf252.cft$preamp.nEv100000.trees.root \
# -pidType $pidType \
# -pidCut $pidCut &
