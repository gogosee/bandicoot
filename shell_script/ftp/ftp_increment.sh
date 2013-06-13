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


### 获取 增量数据文件名
CUR_SYS_TIME=`date +'%Y%m%d%H%M%S'`
INCREMENT_FILE_NAME=$INCREMENT_FILE_NAME"."$CUR_SYS_TIME
#echo $INCREMENT_FILE_NAME


### 获取指定文件中的增量数据
getIncrementData()
{ 
	filename="$@" 
	cfg_filesize="-1";

	# 从配置文件中读取文件大小
	while read line	
	do
		cfg_filename=`echo $line|awk -F ':::' '{print $1}'`
		if [ $cfg_filename = $filename ]; then
			cfg_filesize=`echo $line|awk -F ':::' '{print $2}'`
			#echo $cfg_filename $cfg_filesize
		fi
	done < $THIS_SCRIPT_CONFIG

	# 读取增量数据，写入增量文件
	if [ $cfg_filesize = "-1" ]; then
		# 配置文件中无记录，说明是新生成文件，整个文件内容全部作为增量数据
		cat $filename >> $INCREMENT_FILE_NAME

		# 记录文件信息到新的配置文件
		FILE_SIZE=$(ls -l $filename | awk '{print $5}')
		echo $filename":::"$FILE_SIZE >> $THIS_SCRIPT_CONFIG_TMP
	else
		## 读取增量部份作为
		# 获取当前文件大小
		cur_filesize=$(ls -l $filename | awk '{print $5}')
		# 获取增量部份大小
		increment_size=`expr $cur_filesize - $cfg_filesize`		
		# echo "increment_size:"$increment_size
		# 读取增量部份, 写入增量文件
		tail -c $increment_size $filename >> $INCREMENT_FILE_NAME

		# 记录文件信息到新的配置文件
		FILE_SIZE=$(ls -l $filename | awk '{print $5}')
		echo $filename":::"$FILE_SIZE >> $THIS_SCRIPT_CONFIG_TMP
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
	echo $filename":::"$FILE_SIZE >> $THIS_SCRIPT_CONFIG
#	echo "get file" $filename "info"
}  


### 是否是第一次运行此shell, 设置标志FIRST_TIME
if [ ! -f "$THIS_SCRIPT_CONFIG" ]; then  
	touch $THIS_SCRIPT_CONFIG
	FIRST_TIME=yes
else
#	source $THIS_SCRIPT_CONFIG
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
		if [ $FIRST_TIME = "yes" ]; then
			getFileInfo $line
		else
			getIncrementData $line 
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

# 删除增量文件
rm $INCREMENT_FILE_NAME

fi







