#!/bin/bash                                                                                                                                           

# FTP����������
FTP_SERVER=10.3.3.108
FTP_USER=wanghb1
FTP_PASS=wanghb
FTP_DEST_DIR=/DEVHome/wanghb/xbocs_run/bomcserver/log/ftp

# ��shell�ű�����Ŀ¼
# ��������־����Ŀ¼
# ��Ҫ�������ļ�ƥ��ģʽ�������趨���ƥ��ģʽ����|�ŷָ�
# ������־ǰ�. ������־�ļ���ʽ�ǣ� ��־ǰ�.������.ʱ��
SHELL_WORK_DIR=/DEVHome/wanghb/app/log/inc
LOG_DIR=/DEVHome/wanghb/app/log
SEARCH_FILE_PATTERN="*.log|*.out|*.txt"
INCREMENT_FILE_NAME="log_Inc"

# �ɼ�����
# �Ƿ񱣴�������־�ڱ���
# ������־�ڱ��ش��Ŀ¼
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











