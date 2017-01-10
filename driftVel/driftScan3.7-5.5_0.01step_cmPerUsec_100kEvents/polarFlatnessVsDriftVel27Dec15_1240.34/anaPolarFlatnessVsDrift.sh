
if [[ $# != 0 ]]; then
	echo $#
	echo "USAGE: ./anaPolarFlatnessVsDrift.sh"
	exit
fi

preamp=$1
drfitVel=$2
treeFileDir=$3

plotdir=`pwd`/polarFlatnessVsDriftVel`date +%d%b%y_%H%M.%S`
mkdir $plotdir
cd $plotdir
cp $thesisData/drift/anaPolarFlatnessVsDrift.{sh,C} $plotdir

echo root -l -q -b anaPolarFlatnessVsDrift.C\+
time root -l -q -b anaPolarFlatnessVsDrift.C\+
wait

rm anaPolarFlatnessVsDrift_C*

cd -