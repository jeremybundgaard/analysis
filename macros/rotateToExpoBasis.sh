#!/bin/bash



plotdir2ndPreamp=rotateToExpoBasis.`date +%d%b%y_%H%M.%S`
mkdir $plotdir2ndPreamp
cp $macros/rotateToExpoBasis.C $plotdir2ndPreamp
cd $plotdir2ndPreamp
root -l -q -b rotateToExpoBasis.C\+ 
