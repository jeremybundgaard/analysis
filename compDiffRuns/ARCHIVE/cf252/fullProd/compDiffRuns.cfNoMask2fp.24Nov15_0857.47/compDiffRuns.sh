
if [[ $# != 3 ]]; then
	echo "USAGE: $macros/compDiffRuns.sh <cfCFT1|cfCFT2|cfNoMask1|cfNoMask2> <hk|fp> <inputTreeFile.root>"
	exit
fi

runType=$1
recoType=$2
inputTreeFile=$3
plotdir=`pwd`/compDiffRuns.${runType}${recoType}.`date +%d%b%y_%H%M.%S`
mkdir $plotdir
cd $plotdir
cp $macros/compDiffRuns.{sh,C} $plotdir

echo root -l -q -b compDiffRuns.C\+\(\"$runType\",\"$recoType\",\"$inputTreeFile\"\)
time root -l -q -b compDiffRuns.C\+\(\"$runType\",\"$recoType\",\"$inputTreeFile\"\)
wait

rm compDiffRuns_C*

