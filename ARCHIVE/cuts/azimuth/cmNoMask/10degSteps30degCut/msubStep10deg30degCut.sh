#!/bin/bash
#MSUB -l walltime=48:00:00
#MSUB -q pbatch
#MSUB -r y

nEvents=-1

if [[ $# -gt 0 ]]; then
	nEvents=$1
fi





	echo msub $myana/anahists/cuts/azimuth/azCuts.cmNoMask.anaHistMaker.sh $nEvents $azMin $azMax
	srun $myana/anahists/cuts/azimuth/azCuts.cmNoMask.anaHistMaker.sh $nEvents $azMin $azMax


