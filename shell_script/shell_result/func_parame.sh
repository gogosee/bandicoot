
NUM1=0


function add()
{
	#"NUM"$1=`expr $"NUM"$1 + 1`;	
	#"NUM"$1=`echo "a"`
	# NUM1=0
#	echo "TNUM"$TNUM
	NUM1=`expr $NUM1 + 1`;	
}

add 1

echo $NUM1



