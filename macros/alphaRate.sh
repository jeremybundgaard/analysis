
if [[ $# != 1 ]]; then
	echo "USAGE: $macros/alphaRate.sh <cm244|cf252>"
	exit
fi

actinide=$1
preamp=1
echo root -l -q -b $macros/alphaRate.C\+\(\"$actinide\",$preamp\)
time root -l -q -b $macros/alphaRate.C\+\(\"$actinide\",$preamp\)
wait

actinide=$1
preamp=2
echo root -l -q -b $macros/alphaRate.C\+\(\"$actinide\",$preamp\)
time root -l -q -b $macros/alphaRate.C\+\(\"$actinide\",$preamp\)
wait

hadd alphaRate_cm244.trees.root alphaRate1.trees.root alphaRate2.trees.root

rm $macros/alphaRate_C*

