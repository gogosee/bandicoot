

READ_REALLY_SIZE_RECORD=/home/hiram/bandicoot/shell_script/ftp/really_size.record


while read line 
do
#	echo $line
	FILE_SIZE=`echo $line`
	echo $FILE_SIZE
done < $READ_REALLY_SIZE_RECORD

