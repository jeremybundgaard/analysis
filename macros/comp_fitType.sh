
if [[ $# != 1 ]]; then
	echo "USAGE: $macros/comp_fitType.sh <inputTreeFile.root>"
	exit
fi

inputTreeFile=$1
plotdir=`pwd`/comp_fitType.`basename $inputTreeFile .root`.`date +%d%b%y_%H%M.%S`
mkdir $plotdir
cd $plotdir
chmod -R 750 $macros
cp $macros/{makeNewTree,niffteTreePlots}.{sh,C} $plotdir


for i in {2,3,5,102,103,105};
do
	mkdir fitType$i
	cd fitType$i
	treeCut="fitType==$i"
	echo root -l -q -b $macros/niffteTreePlots.C\+\(\"$inputTreeFile\",\"$treeCut\"\)
	time root -l -q -b $macros/niffteTreePlots.C\+\(\"$inputTreeFile\",\"$treeCut\"\)
	wait

	cd $plotdir

done

rm comp_fitType_C*

