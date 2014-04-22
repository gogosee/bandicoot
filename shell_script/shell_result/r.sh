#!/bin/bash                                                                                                                                           

# FTP服务器配置
FTP_SERVER=10.3.3.108
FTP_USER=wanghb1
FTP_PASS=wanghb
FTP_DEST_DIR=/DEVHome/wanghb/xbocs_run/bomcserver/log/ftp

# 此shell脚本所在目录
# 待分析日志所在目录
# 需要分析的文件匹配模式，可以设定多个匹配模式，以|号分隔
# 增量日志前辍. 增量日志文件格式是： 日志前辍.主机名.时间
SHELL_WORK_DIR=/DEVHome/wanghb/app/log/inc
LOG_DIR=/DEVHome/wanghb/app/log
SEARCH_FILE_PATTERN="*.log|*.out|*.txt"
INCREMENT_FILE_NAME="log_Inc"

# 采集周期
# 是否保存增量日志在本地
# 增量日志在本地存放目录
COLLECT_CYCLE=300
IS_SAVE_INC=y
INCREMENT_FILE_DIR=/home/hiram/bandicoot/shell_script/shell_result

#############################################################################################


PrintLog()
{
	LogMsg="$@"
	echo $LogMsg
}

#rm a
#echo $?
#if [ $? -eq 0 ]; then
#	echo "ok"
#	PrintLog "ok"
#else
#	echo "fail"
#	PrintLog "fail"
#fi

cd $INCREMENT_FILE_DIR
if [ $? -eq 0 ]; then
	PrintLog "ok"
else
	PrintLog "fail"
fi


ftp -n 1>my.log 2>err.log <<! 
open $FTP_SERVER
user $FTP_USER $FTP_PASS
binary 
cd $FTP_DEST_DIR
lcd $INCREMENT_FILE_DIR
prompt 
put $INCREMENT_FILE_NAME 
close 
bye 
!

if [ $? -eq 0 ]; then
#	echo "ok"
PrintLog "ok"
else
#	echo "fail"
PrintLog "fail"
fi











