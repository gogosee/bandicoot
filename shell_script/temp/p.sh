#!/bin/bash 
FTP_SERVER=10.3.3.108 
FTP_USER=wanghb
FTP_PASS=wanghb
FTP_DEST_DIR=/DEVHome/wanghb/xbocs_run/bomcserver/log
LOCAL_DIR=/home/hiram/bandicoot/shell_script/ftp
LS_SEARCH_FILE="DataProc_*"
PUT_FILE_NAME=t.xml
DEST_FILE_NAME=t.xml
COLLECT_CYCLE=3000


# 获取指定文件中的增量数据
processLine()
{ 
	filename="$@" 
	#F1=$(echo $filename | awk '{ print $1 }') 

	#echo $filename
}   


UPDATE_FILES="123"

handleAllLog()
{
ls -l $LS_SEARCH_FILE | awk '{print $NF}' | while read line
do
	# 获取文件最后修改时间
	filedate=`stat $line | grep Modify | awk '{print $2}'`
	#echo $filedate
	filetime=`stat $line | grep Modify | awk '{split($3,var,".");print var[1]}'`
	#echo $filetime
	file_datetime=`date -d "$filedate $filetime" +%s`
	#echo $file_datetime

	# 获取当前时间
	current_datetime=`date +%s`
	#echo $current_datetime

	# 当前时间 - 文件最修改时间
	timedelta=`expr $current_datetime - $file_datetime`
	#echo $timedelta

	# 如果文件最后修改时间，在统计周期内,获取数据
	if [ "$timedelta" -le $COLLECT_CYCLE ];then
		processLine $line 
		UPDATE_FILES=${UPDATE_FILES}${line}
#		echo $line
	fi
done
}


firstTimeRecordLogsInfo()
{
	echo "first time.."	
}


#handleAllLog
echo $UPDATE_FILES

THIS_SCRIPT_CONFIG=./log.config
if [ ! -f "$THIS_SCRIPT_CONFIG" ]; then  
	touch $THIS_SCRIPT_CONFIG
	firstTimeRecordLogsInfo
else
#	echo $THIS_SCRIPT_CONFIG	
	source $THIS_SCRIPT_CONFIG
	handleAllLog
fi  






