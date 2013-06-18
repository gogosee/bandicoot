#!/bin/bash 
FTP_SERVER=10.3.3.108 
FTP_USER=wanghb
FTP_PASS=wanghb
FTP_DEST_DIR=/DEVHome/wanghb/xbocs_run/bomcserver/log/ftp2

LOG_DIR=/DEVHome/wanghb/inc_log
LS_SEARCH_FILE="*.log"
INCREMENT_FILE_NAME="log_Inc"
INCREMENT_FILE_DIR=/DEVHome/wanghb/inc_log/inc_log

COLLECT_CYCLE=300
IS_SAVE_INC=y


#############################################################################################
#############################################################################################

FIRST_TIME=no
SHELL_WORK_DIR=`pwd`
THIS_SCRIPT_CONFIG=$SHELL_WORK_DIR/log.config
THIS_SCRIPT_CONFIG_TMP=$SHELL_WORK_DIR/log.config.tmp
SYSTEM_OS=`uname -a | awk '{print $1}'`

if [ $SYSTEM_OS = "SunOS" ]; then
	PATH=$PATH:$SHELL_WORK_DIR/bin
#	TAIL=/usr/xpg4/bin/tail
#else
#	TAIL=tail
fi
TAIL=$SHELL_WORK_DIR/bin/wtail


### ��ȡ ���������ļ���
CUR_SYS_TIME=`date +'%Y%m%d%H%M%S'`
INCREMENT_FILE_NAME=$INCREMENT_FILE_NAME"."$HOSTNAME"."$CUR_SYS_TIME
INCREMENT_FILE_PATH=$INCREMENT_FILE_DIR/$INCREMENT_FILE_NAME
DEST_INCREMENT_FILE_TMPNAME=$INCREMENT_FILE_NAME".temp"
REALLY_READ_SIZE_RECORD=$SHELL_WORK_DIR/.really_read_size.record
#echo $INCREMENT_FILE_NAME


### ��ȡָ���ļ��е���������
getIncrementData()
{ 
	filename="$@" 
	cfg_filesize="-1";

	# �������ļ��ж�ȡ�ļ���С
	while read line	
	do
		cfg_filename=`echo $line|awk -F'|' '{print $1}'`
		if [ $cfg_filename = $filename ]; then
			cfg_filesize=`echo $line|awk -F'|' '{print $2}'`
			#echo $cfg_filename $cfg_filesize
		fi
	done < $THIS_SCRIPT_CONFIG

	# ��ȡ�������ݣ�д�������ļ�
	if [ $cfg_filesize = "-1" ]; then
		# �����ļ����޼�¼��˵�����������ļ��������ļ�����ȫ����Ϊ��������
		cat $filename >> $INCREMENT_FILE_PATH

		# ��¼�ļ���Ϣ���µ������ļ�
		FILE_SIZE=$(ls -l $filename | awk '{print $5}')
		echo $filename"|"$FILE_SIZE >> $THIS_SCRIPT_CONFIG_TMP
	else
		## ��ȡ����������Ϊ
		# ��ȡ��ǰ�ļ���С
		cur_filesize=$(ls -l $filename | awk '{print $5}')
		# ��ȡ�������ݴ�С
		increment_size=`expr $cur_filesize - $cfg_filesize`		
		# echo "increment_size:"$increment_size
		# ��ȡ��������, д�������ļ�
		#$TAIL -c $increment_size $filename >> $INCREMENT_FILE_PATH
		$TAIL -e -f $filename -t $cfg_filesize -s $increment_size -r $REALLY_READ_SIZE_RECORD >> $INCREMENT_FILE_PATH

		# ��ȡ�µ��ļ���Ϣ�����Ҽ�¼�ļ���Ϣ���µ������ļ�
		#FILE_SIZE=$(ls -l $filename | awk '{print $5}')
		while read line 
		do
			READ_SIZE=`echo $line`
		done < $REALLY_READ_SIZE_RECORD
		# �����ļ������õ��ļ���С + ��ǰ������������ == ��ǰ�ļ���С
		FILE_SIZE=`expr ${cfg_filesize} + ${READ_SIZE}`

		#echo $increment_size
		#echo $cfg_filesize
		#echo $READ_SIZE
		#echo $FILE_SIZE

		echo $filename"|"$FILE_SIZE >> $THIS_SCRIPT_CONFIG_TMP
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
	echo $filename"|"$FILE_SIZE >> $THIS_SCRIPT_CONFIG
#	echo "get file" $filename "info"
}  


### ��ȡָ���ļ���Ϣ
getNoUpdateInfo()
{ 
	filename="$@" 

	# ��ȡ�ļ���С
	FILE_SIZE=$(ls -l $filename | awk '{print $5}')
	# echo $FILE_SIZE

	# ��¼�ļ���С�������ļ�
	echo $filename"|"$FILE_SIZE >> $THIS_SCRIPT_CONFIG_TMP
#	echo "get file" $filename "info"
}  


### ������־�ļ�Ŀ¼
cd $LOG_DIR

### �Ƿ��ǵ�һ�����д�shell, ���ñ�־FIRST_TIME
if [ ! -f "$THIS_SCRIPT_CONFIG" ]; then  
	# ���������ļ�
	touch $THIS_SCRIPT_CONFIG
	FIRST_TIME=yes
else
	# ���������ļ�
	touch $INCREMENT_FILE_PATH
	# ������ʱ�����ļ�
	touch $THIS_SCRIPT_CONFIG_TMP
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

	# ��ȡ�ļ�����޸�ʱ��
	if [ $SYSTEM_OS = "Linux" ]; then
		file_datetime=`date -d "$filedate $filetime" +%s`
	elif [ $SYSTEM_OS = "SunOS" ]; then
		file_datetime=`wdate "$filedate $filetime"`
	else
		echo "NO Support System OS, update this script first please! exit."
		exit
	fi
	#echo $file_datetime

	# ��ȡ��ǰʱ��
	if [ $SYSTEM_OS = "Linux" ]; then
		current_datetime=`date +%s`
	elif [ $SYSTEM_OS = "SunOS" ]; then
		current_datetime=`wdate -c`
	else
		echo "NO Support System OS, update this script first please! exit."
		exit
	fi
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
	# ����ͳ�������ڣ���Ҫ��¼�ļ���С
	else
		if [ $FIRST_TIME = "yes" ]; then
			getFileInfo $line
		else
			getNoUpdateInfo $line
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
cd $INCREMENT_FILE_DIR
ftp -n<<! 
open $FTP_SERVER
user $FTP_USER $FTP_PASS
binary 
cd $FTP_DEST_DIR
lcd $INCREMENT_FILE_DIR
prompt 
put $INCREMENT_FILE_NAME $DEST_INCREMENT_FILE_TMPNAME
rename $DEST_INCREMENT_FILE_TMPNAME $INCREMENT_FILE_NAME
close 
bye 
!

# ɾ�������ļ�
if [ $IS_SAVE_INC = "n" ]; then
	rm $INCREMENT_FILE_PATH
fi

fi

cd $SHELL_WORK_DIR








