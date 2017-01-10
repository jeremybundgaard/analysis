
if [[ $# != 1 ]]; then
	echo "USAGE: $macros/digitDriftSpeed.sh <inputTreeFile.root>"
	#exit
else

inputTreeFile=$1
plotdir=`pwd`/digitDriftSpeed.`basename $inputTreeFile .root`.`date +%d%b%y_%H%M.%S`
mkdir $plotdir
cd $plotdir
cp $macros/digitDriftSpeed.{sh,C} $plotdir

echo root -l -q -b digitDriftSpeed.C\+\(\"$inputTreeFile\",\"$plotdir\"\)
time root -l -q -b digitDriftSpeed.C\+\(\"$inputTreeFile\",\"$plotdir\"\)
wait

rm digitDriftSpeed_C*

fi