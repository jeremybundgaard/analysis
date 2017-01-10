
if [[ $# != 2 ]]; then
	echo "USAGE: $macros/fragRate.sh <cm244|cf252> <int preamp>"
	exit
fi

actinide=$1
preamp=$2

echo root -l -q -b $macros/fragRate.C\+\(\"$actinide\",$preamp\)
time root -l -q -b $macros/fragRate.C\+\(\"$actinide\",$preamp\)
wait

rm $macros/fragRate_C*

