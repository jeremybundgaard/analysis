#MSUB -l walltime=48:00:00
#MSUB -q pbatch
#MSUB -r y

nEvents=-1

if [[ $# -gt 0 ]]; then
	nEvents=$1
fi

for i in {0..35}; do
	azMin=$(($i*10-180)) 
	azMax=$((azMin+30))
	echo $myana/anahists/cuts/azimuth/azCuts.cmNoMask.anaHistMaker.sh $nEvents $azMin $azMax
	# $myana/anahists/cuts/azimuth/azCuts.cmNoMask.anaHistMaker.sh $nEvents $azMin $azMax 
done
$myana/cleanup.sh
