#!/bin/bash 
FTP_SERVER=10.3.3.108 
FTP_USER=wanghb
FTP_PASS=wanghb
FTP_DEST_DIR=/DEVHome/wanghb/xbocs_run/bomcserver/log
LOCAL_DIR=/opt/wanghb/Run/BomcServer/log
LS_SEARCH_FILE="*"
INCREMENT_FILE_NAME=bomcserver_log
#PUT_FILE_NAME=increment_0.log
#DEST_FILE_NAME=increment_0.log
COLLECT_CYCLE=300


#############################################################################################
#############################################################################################

FIRST_TIME=no
THIS_SCRIPT_CONFIG=./log.config
THIS_SCRIPT_CONFIG_TMP=./log.config.tmp


### ��ȡ ���������ļ���
CUR_SYS_TIME=`date +'%Y%m%d%H%M%S'`
INCREMENT_FILE_NAME=$INCREMENT_FILE_NAME"."$CUR_SYS_TIME
#echo $INCREMENT_FILE_NAME


### ��ȡָ���ļ��е���������
getIncrementData()
{ 
	filename="$@" 
	cfg_filesize="-1";

	# �������ļ��ж�ȡ�ļ���С
	while read line	
	do
		cfg_filename=`echo $line|awk -F ':::' '{print $1}'`
		if [ $cfg_filename = $filename ]; then
			cfg_filesize=`echo $line|awk -F ':::' '{print $2}'`
			#echo $cfg_filename $cfg_filesize
		fi
	done < $THIS_SCRIPT_CONFIG

	# ��ȡ�������ݣ�д�������ļ�
	if [ $cfg_filesize = "-1" ]; then
		# �����ļ����޼�¼��˵�����������ļ��������ļ�����ȫ����Ϊ��������
		cat $filename >> $INCREMENT_FILE_NAME

		# ��¼�ļ���Ϣ���µ������ļ�
		FILE_SIZE=$(ls -l $filename | awk '{print $5}')
		echo $filename":::"$FILE_SIZE >> $THIS_SCRIPT_CONFIG_TMP
	else
		## ��ȡ����������Ϊ
		# ��ȡ��ǰ�ļ���С
		cur_filesize=$(ls -l $filename | awk '{print $5}')
		# ��ȡ�������ݴ�С
		increment_size=`expr $cur_filesize - $cfg_filesize`		
		# echo "increment_size:"$increment_size
		# ��ȡ��������, д�������ļ�
		tail -c $increment_size $filename >> $INCREMENT_FILE_NAME

		# ��¼�ļ���Ϣ���µ������ļ�
		FILE_SIZE=$(ls -l $filename | awk '{print $5}')
		echo $filename":::"$FILE_SIZE >> $THIS_SCRIPT_CONFIG_TMP
	fi
}   


### ��ȡָ���ļ���Ϣ
getFileInfo()
{ 
	filename="$@" 

	# ��ȡ�ļ���С
	FILE_SIZE=$(ls -l $filename | awk '{print $5}')
	# echo $FILE_SIZE

	# ��¼�ļ���С�������ļ�
	echo $filename":::"$FILE_SIZE >> $THIS_SCRIPT_CONFIG
#	echo "get file" $filename "info"
}  


### �Ƿ��ǵ�һ�����д�shell, ���ñ�־FIRST_TIME
if [ ! -f "$THIS_SCRIPT_CONFIG" ]; then  
	touch $THIS_SCRIPT_CONFIG
	FIRST_TIME=yes
else
#	source $THIS_SCRIPT_CONFIG
	FIRST_TIME=no
fi  


### ���������ļ�,���ҳ�ͳ�������ڸ��¹����ļ�, ������
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
		if [ $FIRST_TIME = "yes" ]; then
			getFileInfo $line
		else
			getIncrementData $line 
		fi
	fi
done


### �ǵ�һ�����У���ִ�����²�����
### 1. ���������ļ�
### 2. ftp �������ݼ�¼�ļ� �� ftp serever
### 3. ɾ�� �������ݼ�¼�ļ�
if [ $FIRST_TIME = "no" ]; then

# ���������ļ�
rm $THIS_SCRIPT_CONFIG
mv $THIS_SCRIPT_CONFIG_TMP $THIS_SCRIPT_CONFIG

# ftp�����ļ���ftp server
ftp -n<<! 
open $FTP_SERVER
user $FTP_USER $FTP_PASS
binary 
cd $FTP_DEST_DIR
lcd $LOCAL_DIR
prompt 
put $INCREMENT_FILE_NAME
close 
bye 
!

# ɾ�������ļ�
rm $INCREMENT_FILE_NAME

fi







