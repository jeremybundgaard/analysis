
preamp=$1
plotdir=`pwd`/nDigPlots.${preamp}preamp.`date +%d%b%y_%H%M.%S`
mkdir $plotdir
cd $plotdir
cp $macros/nDigitDependence.{sh,C} $plotdir

echo root -l -q -b nDigitDependence.C\+\($preamp\)
time root -l -q -b nDigitDependence.C\+\($preamp\)
wait

rm nDigitDependence_C*

