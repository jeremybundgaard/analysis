
if [[ $# != 1 ]]; then
	echo "USAGE: $macros/fragCount.sh <inputTreeFile.root>"
	exit
fi

inputTreeFile=$1

echo root -l -q -b $macros/fragCount.C\+\(\"$inputTreeFile\"\)
time root -l -q -b $macros/fragCount.C\+\(\"$inputTreeFile\"\)
wait

rm $macros/fragCount_C*

