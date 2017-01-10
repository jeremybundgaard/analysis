#!/bin/bash

radAna=$1

nEvents=-1
if [[ $# -gt 1 ]]; then
	nEvents=$2
fi

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

	echo $myana/anahists/cuts/radius/$radAna $nEvents $radMin $radMax
	$myana/anahists/cuts/radius/$radAna $nEvents $radMin $radMax;sleep 5
done

./cleanup.sh
