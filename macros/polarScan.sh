if [[ $# != 2 ]]; then
	echo "USAGE: $macros/polarScan.sh <1|2> <hk|fp>"
	exit
fi


preamp=$1
recoType=$2
thetaStepSize=2
plotdir=`pwd`/polarScanPlots.${preamp}preamp.${recoType}.reco.`date +%d%b%y_%H%M.%S`
mkdir $plotdir
cd $plotdir


for (( i = 0; i < 180; i+=30 )); do
	thetaMin=$i
	thetaMax=$((i + 30))
	thetadir=$plotdir/thetaMin${thetaMin}-thetaMax${thetaMax}
	mkdir $thetadir
	cd $thetadir
	cp $macros/polarScan.C $thetadir/.
	echo root -l -q -b polarScan.C\+\($preamp,\"$recoType\",$thetaMin,$thetaMax,$thetaStepSize\)
	time root -l -q -b polarScan.C\+\($preamp,\"$recoType\",$thetaMin,$thetaMax,$thetaStepSize\) >> $plotdir/log.output.thetaMin${thetaMin} &
	sleep 1
	cd -
done

# wait
# touch i.waited

# for i in `ls log.output.thetaMin*`;do cat $i >> log.output; done
# rm log.output.thetaMin*

# find $plotdir -name "*.png" -exec mv {} $plotdir/. \;

# find $plotdir -name "*.root" -exec mv {} $plotdir/. \;
# hadd numVsTheta.root numVsTheta.thetaMin*.root

# if [[ "`uname`" == "Linux" ]]; then

# 	# for (( i = 0; i <= 80; i+=2 )); do

# 	# 	thMin=$i
# 	# 	thMax=$((i+10))
# 	# 	if [[ ${i} -lt 10 ]]; then thMin=0$i; fi
# 	# 	echo $thMin $thMax

# 	# 	montage -geometry 1000x700 \
# 	# 	noMaskLvEn.full.lin.thetaMin0$thMin*png cftLvEn.full.lin.thetaMin0$thMin*png \
# 	# 	noMaskLvEn.full.log.zoom.thetaMin0$thMin*png cftLvEn.full.log.zoom.thetaMin0$thMin*png \
# 	# 	LvEnSummary.thetaMin0$thMin.thetaMax0$thMax.png
# 	# 	echo "created LvEnSummary.thetaMin0$thMin.thetaMax0$thMax.png"
# 	# 	sleep 0.3;wait

# 	# 	montage -geometry 1000x700 \
# 	# 	noMaskLvEn.full.lin.plusFragCut.thetaMin0$thMin*png cftLvEn.full.lin.plusFragCut.thetaMin0$thMin*png \
# 	# 	frags.full.lin.noMask.thetaMin0$thMin*png frags.full.lin.cft.thetaMin0$thMin*png \
# 	# 	LvEnFragProj.thetaMin0$thMin.thetaMax0$thMax.png
# 	# 	echo "created LvEnFragProj.thetaMin0$thMin.thetaMax0$thMax.png"
# 	# 	sleep 0.3;wait

# 	# 	montage -geometry 1000x700 \
# 	# 	noMaskLvEn.lowEn.plusFragCut.thetaMin0$thMin*png cftLvEn.lowEn.plusFragCut.thetaMin0$thMin*png \
# 	# 	frags.lowEn.noMask.thetaMin0$thMin*png frags.lowEn.cft.thetaMin0$thMin*png \
# 	# 	LvEnFragProj.thetaMin0$thMin.thetaMax0$thMax.png
# 	# 	echo "created LvEnFragProj.thetaMin0$thMin.thetaMax0$thMax.png"
# 	# 	sleep 0.3;wait


# 	# done

# fi
