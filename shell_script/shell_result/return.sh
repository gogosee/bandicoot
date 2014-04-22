


PrintLog()
{
	LogMsg="$@"
	echo $LogMsg
}

rm a
#echo $?
if [ $? -eq 0 ]; then
#	echo "ok"
	PrintLog "ok"
else
#	echo "fail"
	PrintLog "fail"
fi


