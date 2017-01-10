
if [[ $# != 1 ]]; then
	echo "USAGE: $macros/runtimeCalc.sh <inputTreeFile.root>"
	exit
fi

inputTreeFile=$1

echo root -l -q -b $macros/runtimeCalc.C\+\(\"$inputTreeFile\",\)
time root -l -q -b $macros/runtimeCalc.C\+\(\"$inputTreeFile\",\)
wait

rm $macros/runtimeCalc_C*

