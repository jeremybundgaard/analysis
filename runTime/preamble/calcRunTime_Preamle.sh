#!/bin/bash

if [[ $# -ne 1 ]]; then
	echo "USAGE: $macros/runTimeCalcNIFFTEPreamle.sh /p/lscratche/jerbundg/analysis/ratio/runTime/cm244.runlog"
	echo "USAGE: $macros/runTimeCalcNIFFTEPreamle.sh /p/lscratche/jerbundg/analysis/ratio/runTime/cf252.runlog"
fi

actinide=`basename $1 .runlog`
echo $actinide

outdir=/p/lscratche/jerbundg/analysis/ratio/runTime/preamble/runtimes
if [ ! -d "$outdir" ]; then
	mkdir $outdir
fi

allRunTimesFile=$outdir/$actinide.allRunTimes
find $1 -type d -a -name "*Preamp" | while read rundir;
do
	runtype=$rundir
	runtype=${runtype%/2ndPreamp}
	runtype=${runtype%/1stPreamp}

	preamp=`basename $rundir`
	preamp=${preamp%stPreamp}
	preamp=${preamp%ndPreamp}
	outfile=$actinide.`basename $runtype`$preamp.runtime
	echo $outfile
	timeTally=0

	for runlog in `find $rundir -name "*runtimes" | sort`
	do
		runNumber=`grep "runNumber" $runlog`
		runNumber=${runNumber:10}
		if [[ $runNumber != "100001995" ]] || [[ "$runNumber" != "100001962" ]]; then
			runtime=`grep "runTime" $runlog`
			runtime=${runtime:8}
			echo "$runNumber,$runtime" >> $allRunTimesFile
			timeTally=$((timeTally + runtime))
			# echo $timeTally
			# echo $runNumber $runtime $timeTally
		fi

	done
	echo $timeTally
	echo $timeTally > $outdir/$outfile
	echo
	
done

