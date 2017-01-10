
if [[ $# != 2 ]]; then
	echo "USAGE:  $macros/cftAnaPlots.sh <1|2> <hk|fp>"
	exit
fi

preamp=$1
recoType=$2

plotdir=`pwd`/cftAnaPlots.${preamp}preamp.${recoType}.`date +%d%b%y_%H%M.%S`
mkdir $plotdir
cd $plotdir
cp $macros/cftAnaPlots.{sh,C} $plotdir

echo root -l -q -b cftAnaPlots.C\+\($preamp,\"$recoType\"\)
time root -l -q -b cftAnaPlots.C\+\($preamp,\"$recoType\"\)
wait

# rm cftAnaPlots_C*

# if [[ "`uname`" != "Linux" ]]; then exit; fi

# ########################################################################
# ######################### polar cuts & projections #####################
# ########################################################################

# polardir=$plotdir/polar
# mkdir $polardir$pol

# polarMontageDir=$polardir/montage
# mkdir $polarMontageDir


# #################### grouped by angle axis #####################
# montage -geometry 1000x700 \
# noMask*VsTheta0to180.png montage.noMaskVsTheta0to180.png
# echo "created montage.noMaskVsTheta0to180.png"
# mv montage.noMaskVsTheta0to180.png $polarMontageDir
# sleep 0.3;wait

# montage -geometry 1000x700 \
# noMask*CosThetaNeg1to1.png montage.noMaskVsCosThetaNeg1to1.png
# echo "created montage.noMaskVsCosThetaNeg1to1.png"
# mv montage.noMaskVsCosThetaNeg1to1.png $polarMontageDir
# sleep 0.3;wait

# montage -geometry 1000x700 \
# noMask*VsTheta.png montage.noMaskTheta.png
# echo "created montage.noMaskTheta.png"
# mv montage.noMaskTheta.png $polarMontageDir
# sleep 0.3;wait

# montage -geometry 1000x700 \
# noMask*VsThetaPerSA.png montage.noMaskThetaPerSA.png
# echo "created montage.noMaskThetaPerSA.png"
# mv montage.noMaskThetaPerSA.png $polarMontageDir
# sleep 0.3;wait

# montage -geometry 1000x700 \
# noMask*VsCosTheta.png montage.noMaskCosTheta.png
# echo "created montage.noMaskCosTheta.png"
# mv montage.noMaskCosTheta.png $polarMontageDir
# sleep 0.3;wait

# montage -geometry 1000x700 \
# noMask*VsCosThetaPerSA.png montage.noMaskCosThetaPerSA.png
# echo "created montage.noMaskCosThetaPerSA.png"
# mv montage.noMaskCosThetaPerSA.png $polarMontageDir
# sleep 0.3;wait

# montage -geometry 1000x700 \
# cft*VsTheta0to180.png montage.cftVsTheta0to180.png
# echo "created montage.cftVsTheta0to180.png"
# mv montage.cftVsTheta0to180.png $polarMontageDir
# sleep 0.3;wait

# montage -geometry 1000x700 \
# cft*CosThetaNeg1to1.png montage.cftVsCosThetaNeg1to1.png
# echo "created montage.cftVsCosThetaNeg1to1.png"
# mv montage.cftVsCosThetaNeg1to1.png $polarMontageDir
# sleep 0.3;wait

# montage -geometry 1000x700 \
# cft*VsTheta.png montage.cftTheta.png
# echo "created montage.cftTheta.png"
# mv montage.cftTheta.png $polarMontageDir
# sleep 0.3;wait

# montage -geometry 1000x700 \
# cft*VsThetaPerSA.png montage.cftThetaPerSA.png
# echo "created montage.cftThetaPerSA.png"
# mv montage.cftThetaPerSA.png $polarMontageDir
# sleep 0.3;wait

# montage -geometry 1000x700 \
# cft*VsCosTheta.png montage.cftCosTheta.png
# echo "created montage.cftCosTheta.png"
# mv montage.cftCosTheta.png $polarMontageDir
# sleep 0.3;wait

# montage -geometry 1000x700 \
# cft*VsCosThetaPerSA.png montage.cftCosThetaPerSA.png
# echo "created montage.cftCosThetaPerSA.png"
# mv montage.cftCosThetaPerSA.png $polarMontageDir
# sleep 0.3;wait


# #################### grouped by pid #####################
# montage -geometry 1000x700 \
# noMaskVs* montage.noMaskVs.png
# echo "created montage.noMaskVs.png"
# mv noMaskVs* $polardir/.
# mv montage.noMaskVs.png $polarMontageDir
# sleep 0.3;wait

# montage -geometry 1000x700 \
# noMaskFragVs* montage.noMaskFragVs.png
# echo "created montage.noMaskFragVs.png"
# mv noMaskFragVs* $polardir/.
# mv montage.noMaskFragVs.png $polarMontageDir
# sleep 0.3;wait

# montage -geometry 1000x700 \
# noMaskNotFragVs* montage.noMaskNotFragVs.png
# echo "created montage.noMaskNotFragVs.png"
# mv noMaskNotFragVs* $polardir/.
# mv montage.noMaskNotFragVs.png $polarMontageDir
# sleep 0.3;wait

# montage -geometry 1000x700 \
# cftVs* montage.cftVs.png
# echo "created montage.cftVs.png"
# mv cftVs* $polardir/.
# mv montage.cftVs.png $polarMontageDir
# sleep 0.3;wait

# montage -geometry 1000x700 \
# cftFragVs* montage.cftFragVs.png
# echo "created montage.cftFragVs.png"
# mv cftFragVs* $polardir/.
# mv montage.cftFragVs.png $polarMontageDir
# sleep 0.3;wait

# montage -geometry 1000x700 \
# cftNotFragVs* montage.cftNotFragVs.png
# echo "created montage.cftNotFragVs.png"
# mv cftNotFragVs* $polardir/.
# mv montage.cftNotFragVs.png $polarMontageDir
# sleep 0.3;wait





# ########################################################################
# #################### Length v Energy & projections #####################
# ########################################################################

# lvendir=$plotdir/lven
# mkdir $lvendir

# lvenMontageDir=$lvendir/montage
# mkdir $lvenMontageDir

# montage -geometry 1000x700 \
# noMaskLvEn.full.lin.png cftLvEn.full.lin.png \
# noMaskLvEn.full.log.zoom.png cftLvEn.full.log.zoom.png \
# montage.LvEnSummary.png
# mv noMaskLvEn.full.lin.png cftLvEn.full.lin.png \
# noMaskLvEn.full.log.zoom.png cftLvEn.full.log.zoom.png \
# $lvendir/.
# echo "created montage.LvEnSummary.png"
# mv montage.LvEnSummary.png $lvenMontageDir/.
# sleep 0.3;wait

# montage -geometry 1000x700 \
# noMaskLvEn.full.lin.plusFragCut.png cftLvEn.full.lin.plusFragCut.png \
# frags.full.lin.noMask.png frags.full.lin.cft.png \
# montage.LvEnFragProj.png
# mv noMaskLvEn.full.lin.plusFragCut.png cftLvEn.full.lin.plusFragCut.png \
# frags.full.lin.noMask.png frags.full.lin.cft.png \
# $lvendir/.
# echo "created montage.LvEnFragProj.png"
# mv montage.LvEnFragProj.png $lvenMontageDir/.
# sleep 0.3;wait

# montage -geometry 1000x700 \
# noMaskLvEn.lowEn.plusFragCut.png cftLvEn.lowEn.png \
# frags.lowEn.noMask.png frags.lowEn.cft.png \
# montage.LvEnFragProj.lowEn.png
# mv noMaskLvEn.lowEn.plusFragCut.png cftLvEn.lowEn.png \
# frags.lowEn.noMask.png frags.lowEn.cft.png \
# $lvendir/.
# echo "created montage.LvEnFragProj.lowEn.png"
# mv montage.LvEnFragProj.lowEn.png $lvenMontageDir/.
# sleep 0.3;wait

