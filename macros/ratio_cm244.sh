
if [[ $# != 1 ]]; then
	echo "USAGE:  $macros/ratio_cm244.sh <1|2>"
	exit
fi

preamp=$1

plotdir=`pwd`/ratio_cm244Plots.${preamp}preamp.`date +%d%b%y_%H%M.%S`
mkdir $plotdir
cd $plotdir
cp $macros/ratio_cm244.{sh,C} $plotdir

echo root -l -q -b ratio_cm244.C\+\($preamp\)
time root -l -q -b ratio_cm244.C\+\($preamp\)
wait
