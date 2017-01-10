for file in radCut*;
do
    mv "$file" polarCut"${file#radCut}"
done
