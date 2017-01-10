
if [[ $# != 2 ]]; then
	echo "USAGE: $macros/compDiffRuns.sh <cfCFT1|cfCFT2|cfNoMask1|cfNoMask2> <inputTreeFile.root>"
	exit
fi

runType=$1
inputTreeFile=$2
plotdir=`pwd`/compDiffRuns.${runType}${recoType}.`date +%d%b%y_%H%M.%S`
mkdir $plotdir
cd $plotdir
cp $macros/compDiffRuns.{sh,C} $plotdir

echo root -l -q -b compDiffRuns.C\+\(\"$runType\",\"$inputTreeFile\"\)
time root -l -q -b compDiffRuns.C\+\(\"$runType\",\"$inputTreeFile\"\)
wait

rm compDiffRuns_C*

