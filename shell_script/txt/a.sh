#!/bin/bash 
# ����:������ 
# ���¸���:2009-08-16 
# ����������ά:http://www.lazysa.com 
# Eamil:longkaty@sina.com 
# ��;:�ı���ȡ,�ı����� 
# ����:shell�ű����ж�ȡ�ı��ļ�,���Զ�ȡ���н��з��� # ������ڴ˽ű������ۣ���ο�:http://www.lazysa.com/2009/08/779.html 
# �÷�:./readline myfile.txt 
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
