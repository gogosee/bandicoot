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


# ��ȡָ���ļ��е���������
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
	# ��ȡ�ļ�����޸�ʱ��
	filedate=`stat $line | grep Modify | awk '{print $2}'`
	#echo $filedate
	filetime=`stat $line | grep Modify | awk '{split($3,var,".");print var[1]}'`
	#echo $filetime
	file_datetime=`date -d "$filedate $filetime" +%s`
	#echo $file_datetime

	# ��ȡ��ǰʱ��
	current_datetime=`date +%s`
	#echo $current_datetime

	# ��ǰʱ�� - �ļ����޸�ʱ��
	timedelta=`expr $current_datetime - $file_datetime`
	#echo $timedelta

	# ����ļ�����޸�ʱ�䣬��ͳ��������,��ȡ����
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






