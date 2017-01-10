
if [[ $# != 1 ]]; then
	echo "USAGE: $macros/extrapolation.sh <inputTreeFile.root>"
	echo "$#"
	return
fi

inputTreeFile=$1
plotdir=`pwd`/extrapolation.`basename $inputTreeFile .root`.`date +%d%b%y_%H%M`
mkdir $plotdir
cd $plotdir
cp $macros/extrapolation.{sh,C} $plotdir

echo root -l -q -b extrapolation.C\(\"$inputTreeFile\"\)
time root -l -q -b extrapolation.C\(\"$inputTreeFile\"\)
wait

rm extrapolation_C* 
