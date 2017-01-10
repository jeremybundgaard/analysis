for i in {0..35}; do
	azMin=$(($i*10-180)) 
	azMax=$((azMin+30))
	echo $i
	echo $myana/anahists/cuts/azimuth/autoradiograph/azCuts.autoradiograph.anaHistMaker.sh $1 $azMin $azMax
	$myana/anahists/cuts/azimuth/autoradiograph/azCuts.autoradiograph.anaHistMaker.sh $1 $azMin $azMax
done
