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


### 获取 增量数据文件名
CUR_SYS_TIME=`date +'%Y%m%d%H%M%S'`
INCREMENT_FILE_NAME=$INCREMENT_FILE_NAME"."$HOSTNAME"."$CUR_SYS_TIME
INCREMENT_FILE_PATH=$INCREMENT_FILE_DIR/$INCREMENT_FILE_NAME
DEST_INCREMENT_FILE_TMPNAME=$INCREMENT_FILE_NAME".temp"
REALLY_READ_SIZE_RECORD=$SHELL_WORK_DIR/.really_read_size.record
#echo $INCREMENT_FILE_NAME


### 获取指定文件中的增量数据
getIncrementData()
{ 
	filename="$@" 
	cfg_filesize="-1";

	# 从配置文件中读取文件大小
	while read line	
	do
		cfg_filename=`echo $line|awk -F'|' '{print $1}'`
		if [ $cfg_filename = $filename ]; then
			cfg_filesize=`echo $line|awk -F'|' '{print $2}'`
			#echo $cfg_filename $cfg_filesize
		fi
	done < $THIS_SCRIPT_CONFIG

	# 读取增量数据，写入增量文件
	if [ $cfg_filesize = "-1" ]; then
		# 配置文件中无记录，说明是新生成文件，整个文件内容全部作为增量数据
		cat $filename >> $INCREMENT_FILE_PATH

		# 记录文件信息到新的配置文件
		FILE_SIZE=$(ls -l $filename | awk '{print $5}')
		echo $filename"|"$FILE_SIZE >> $THIS_SCRIPT_CONFIG_TMP
	else
		## 读取增量部份作为
		# 获取当前文件大小
		cur_filesize=$(ls -l $filename | awk '{print $5}')
		# 获取增量部份大小
		increment_size=`expr $cur_filesize - $cfg_filesize`		
		# echo "increment_size:"$increment_size
		# 读取增量部份, 写入增量文件
		#$TAIL -c $increment_size $filename >> $INCREMENT_FILE_PATH
		$TAIL -e -f $filename -t $cfg_filesize -s $increment_size -r $REALLY_READ_SIZE_RECORD >> $INCREMENT_FILE_PATH

		# 获取新的文件信息，并且记录文件信息到新的配置文件
		#FILE_SIZE=$(ls -l $filename | awk '{print $5}')
		while read line 
		do
			READ_SIZE=`echo $line`
		done < $REALLY_READ_SIZE_RECORD
		# 配置文件中配置的文件大小 + 当前读到的数据量 == 当前文件大小
		FILE_SIZE=`expr ${cfg_filesize} + ${READ_SIZE}`

		#echo $increment_size
		#echo $cfg_filesize
		#echo $READ_SIZE
		#echo $FILE_SIZE

		echo $filename"|"$FILE_SIZE >> $THIS_SCRIPT_CONFIG_TMP
	fi
}


### 获取指定文件信息
getFileInfo()
{ 
	filename="$@" 

	# 获取文件大小
	FILE_SIZE=$(ls -l $filename | awk '{print $5}')
	# echo $FILE_SIZE

	# 记录文件大小到配置文件
	echo $filename"|"$FILE_SIZE >> $THIS_SCRIPT_CONFIG
#	echo "get file" $filename "info"
}  


### 获取指定文件信息
getNoUpdateInfo()
{ 
	filename="$@" 

	# 获取文件大小
	FILE_SIZE=$(ls -l $filename | awk '{print $5}')
	# echo $FILE_SIZE

	# 记录文件大小到配置文件
	echo $filename"|"$FILE_SIZE >> $THIS_SCRIPT_CONFIG_TMP
#	echo "get file" $filename "info"
}  


### 进入日志文件目录
cd $LOG_DIR

### 是否是第一次运行此shell, 设置标志FIRST_TIME
if [ ! -f "$THIS_SCRIPT_CONFIG" ]; then  
	# 创建配置文件
	touch $THIS_SCRIPT_CONFIG
	FIRST_TIME=yes
else
	# 创建增量文件
	touch $INCREMENT_FILE_PATH
	# 创建临时配置文件
	touch $THIS_SCRIPT_CONFIG_TMP
	FIRST_TIME=no
fi  


### 遍历所有文件,查找出统计周期内更新过的文件, 并处理
ls -l $LS_SEARCH_FILE | awk '{print $NF}' | while read line
do
	# 获取文件最后修改时间
	filedate=`stat $line | grep Modify | awk '{print $2}'`
	#echo $filedate
	filetime=`stat $line | grep Modify | awk '{split($3,var,".");print var[1]}'`
	#echo $filetime

	# 获取文件最后修改时间
	if [ $SYSTEM_OS = "Linux" ]; then
		file_datetime=`date -d "$filedate $filetime" +%s`
	elif [ $SYSTEM_OS = "SunOS" ]; then
		file_datetime=`wdate "$filedate $filetime"`
	else
		echo "NO Support System OS, update this script first please! exit."
		exit
	fi
	#echo $file_datetime

	# 获取当前时间
	if [ $SYSTEM_OS = "Linux" ]; then
		current_datetime=`date +%s`
	elif [ $SYSTEM_OS = "SunOS" ]; then
		current_datetime=`wdate -c`
	else
		echo "NO Support System OS, update this script first please! exit."
		exit
	fi
	#echo $current_datetime

	# 当前时间 - 文件最修改时间
	timedelta=`expr $current_datetime - $file_datetime`
	#echo $timedelta

	# 如果文件最后修改时间，在统计周期内,获取数据
	if [ "$timedelta" -le $COLLECT_CYCLE ];then
		if [ $FIRST_TIME = "yes" ]; then
			getFileInfo $line
		else
			getIncrementData $line 
		fi
	# 不在统计周期内，需要记录文件大小
	else
		if [ $FIRST_TIME = "yes" ]; then
			getFileInfo $line
		else
			getNoUpdateInfo $line
		fi
	fi
done


### 非第一次运行，才执行如下操作：
### 1. 更新配置文件
### 2. ftp 增量数据记录文件 到 ftp serever
### 3. 删除 增量数据记录文件
if [ $FIRST_TIME = "no" ]; then

# 更新配置文件
rm $THIS_SCRIPT_CONFIG
mv $THIS_SCRIPT_CONFIG_TMP $THIS_SCRIPT_CONFIG

# ftp增量文件到ftp server
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

# 删除增量文件
if [ $IS_SAVE_INC = "n" ]; then
	rm $INCREMENT_FILE_PATH
fi

fi

cd $SHELL_WORK_DIR








