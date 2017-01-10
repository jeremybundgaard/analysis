#!/bin/bash

root -q -b radiusCutsplotMaker.C\+\(\"$1\"\)



if [[ -d plots ]]; then
	mv *png plots
else
	mkdir plots
	mv *png plots
fi
./cleanup.sh

