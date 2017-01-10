infile="$1"
outFile=$2


find . -name $infile -exec grep "Length of run = " {} \;  | while read line; do prefixCut=${line#I-NiffteCalibManager.cxx-LoadCalibData: Length of run = }; runtime=${prefixCut%.000000 seconds}; ((sum += runtime));echo $sum > $2 ;done