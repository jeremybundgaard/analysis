for i in {0..33}; do
	azMin=$(($i*10-180)) 
	azMax=$((azMin+30))
	echo $i
	echo $myana/anahists/cuts/azimuth/azCuts.cmNoMask.anaHistMaker.sh $1 $azMin $azMax
done
