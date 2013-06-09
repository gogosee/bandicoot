#!/bin/bash 
FTP_SERVER=10.3.3.108 
FTP_USER=wanghb
FTP_PASS=wanghb
FTP_DEST_DIR=/DEVHome/wanghb/xbocs_run/bomcserver/log
LOCAL_DIR=/home/hiram/bandicoot/shell_script/ftp
LS_SEARCH_FILE="*.xml"
PUT_FILE_NAME=t.xml
DEST_FILE_NAME=t.xml
COLLECT_CYCLE=3000


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

	# 如果文件最后修改时间，5统计周期内
	if [ "$timedelta" -le $COLLECT_CYCLE ];then
		echo $line
	fi
done








# 获取现在文件大小


# 读取上次文件大小





# 截取增量部份
tail -c 100000000 a.xml > t.xml

# 上传增量文件到ftp server
ftp -n<<! 
open $FTP_SERVER
user $FTP_USER $FTP_PASS
binary 
cd $FTP_DEST_DIR
lcd $LOCAL_DIR
prompt 
put $PUT_FILE_NAME $DEST_FILE_NAME
close 
bye 
!

# 删除增量文件
rm -rf t.xml

# 记录当前文件大小
