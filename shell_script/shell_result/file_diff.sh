
if diff a.txt b.txt > /dev/null; then
	echo "same"
else
	echo "diff"
fi 
