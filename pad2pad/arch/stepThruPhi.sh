#!/bin/bash

radAna=$1
inputlist=$2
nEvents=-1

if [[ $# -gt 2 ]]; then
	nEvents=$3
fi

printf "\n\n";echo "∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑" 
echo "usage: ./stepThruPhi.sh <anaShellScript.sh> <inputListtextfile> <number of events>"
echo "∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑ ∑";printf "\n"

radStep=0.4
for i in {0..18}; do
	radMin=$( echo "$i*$radStep" | bc -l)
	radMax=$( echo "$radMin + $radStep" | bc -l)

	if (($(echo "$radMax < 1" |bc -l) )); then
		radMax=0$radMax
	fi
	if (($(echo "$radMin < 1" |bc -l) )); then
		radMin=0$radMin
	fi
	if [[ $i -eq 0 ]]; then
		radMin=0.0
	fi

	echo $myana/anahists/pad2pad/$radAna $inputlist $nEvents $radMin $radMax
	# $myana/anahists/pad2pad/$radAna $inputlist $nEvents $radMin $radMax
	# sleep 5

done

