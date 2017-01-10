#!/bin/bash

if [[ $# -ne 1 ]]; then
	echo "USAGE: $macros/calcRunTimes.sh /p/lscratche/jerbundg/analysis/ratio/runTime/cm244.runLogs"
	echo "USAGE: $macros/calcRunTimes.sh /p/lscratche/jerbundg/analysis/ratio/runTime/cf252.runLogs"
fi

actinide=`basename $1 .runLogs`
echo $actinide

runtimeOutputDir=/p/lscratche/jerbundg/analysis/ratio/runTime/
if [ -d "$runtimeOutputDir" ]; then
	echo "test"
fi
find $1 -type d -a -name "*Preamp" | while read rundir;
do
	runtype=$rundir
	runtype=${runtype%/2ndPreamp}
	runtype=${runtype%/1stPreamp}

	preamp=`basename $rundir`
	preamp=${preamp%stPreamp}
	preamp=${preamp%ndPreamp}
	runtype=$actinide.`basename $runtype`$preamp.runtime
	echo $runtype
	timeTally=0

	for runlog in `find $rundir -name "*runtimes" | sort`
	do
		runNumber=`grep "runNumber" $runlog`
		runNumber=${runNumber:10}
		if [[ $runNumber != "100001995" ]] || [[ "$runNumber" != "100001962" ]]; then
			runtime=`grep "runTime" $runlog`
			runtime=${runtime:8}
			timeTally=$((timeTally + runtime))
			# echo $timeTally
			echo $runNumber $runtime $timeTally
		fi
	done
	echo $timeTally
	echo $timeTally > $runtype
	echo
	echo 
done

