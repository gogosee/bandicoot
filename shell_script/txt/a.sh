#!/bin/bash 
# 译者:龙力勤 
# 最新更新:2009-08-16 
# 出自懒人运维:http://www.lazysa.com 
# Eamil:longkaty@sina.com 
# 用途:文本读取,文本分析 
# 描述:shell脚本按行读取文本文件,并对读取的行进行分析 # 更多关于此脚本的讨论，请参考:http://www.lazysa.com/2009/08/779.html 
# 用法:./readline myfile.txt 
# User define Function (UDF) 


processLine(){ 
line="$@" 
# get all args 
# just echo them, but you may need to customize it according to your need 
# for example, F1 will store first field of $line, see readline2 script # for more examples 
# F1=$(echo $line | awk '{ print $1 }') 
echo $line }   


### Main script stars here 
### # Store file name 
FILE=""   


# Make sure we get file name as command line argument 
# Else read it from standard input device 
if [ "$1" == "" ]; then 
     FILE="/dev/stdin" 
else 
     FILE="$1" 
# make sure file exist and readable 
     if [ ! -f $FILE ]; then 
      echo "$FILE : does not exists" 
      exit 1 
     elif [ ! -r $FILE ]; then 
          echo "$FILE: can not read" 
          exit 2 
     fi 
fi 
# read $FILE using the file descriptors   


# Set loop separator to end of line 
BAKIFS=$IFS 
IFS=$(echo -en "nb") 
exec 3<&0 
exec 0<$FILE 
while read line 
do 
   # use $line variable to process line in processLine() function 
   processLine $line 
done 
exec 0<&3   


# restore $IFS which was used to determine what the field separators are 
IFS=$BAKIFS 
exit 0
