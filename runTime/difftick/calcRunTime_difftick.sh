#!/bin/bash

actinide=cm244
# echo $actinide

outdir=/p/lscratche/jerbundg/analysis/ratio/runTime/difftick/runtimes
if [ ! -d "$outdir" ]; then
	mkdir $outdir
fi

allRunTimesFile=$outdir/cm244.allRunTimes
find /p/lscratche/jerbundg/analysis/ratio/runTime/difftick/ -type d -a -name "*Preamp" | while read rundir;
do
	runtype=$rundir
	runtype=${runtype%/2ndPreamp}
	runtype=${runtype%/1stPreamp}

	preamp=`basename $rundir`
	preamp=${preamp%stPreamp}
	preamp=${preamp%ndPreamp}
	runtype=$actinide.`basename $runtype`$preamp.difftick
	echo $runtype
	timeTally=0

	for runlog in `find $rundir -name "*.difftick" | sort`
	do
		# cat $runlog
		runNumber=`basename $runlog .difftick`
		# if [[ $runNumber != "100001995" ]] || [[ "$runNumber" != "100001962" ]]; then
		runtime=`grep "runtime = " $runlog`
		runtime=${runtime:10}
		echo "$runNumber,$runtime" >> $allRunTimesFile
		timeTally=`echo $timeTally + $runtime |bc`
		# echo $runNumber $runtime $timeTally
		# fi
	done
	echo $timeTally
	echo $timeTally > $outdir/$runtype
	echo 
done

