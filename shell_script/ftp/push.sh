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

	# ����ļ�����޸�ʱ�䣬5ͳ��������
	if [ "$timedelta" -le $COLLECT_CYCLE ];then
		echo $line
	fi
done








# ��ȡ�����ļ���С


# ��ȡ�ϴ��ļ���С





# ��ȡ��������
tail -c 100000000 a.xml > t.xml

# �ϴ������ļ���ftp server
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

# ɾ�������ļ�
rm -rf t.xml

# ��¼��ǰ�ļ���С
