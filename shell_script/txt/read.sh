#!/bin/bash 

processLine()
{ 
line="$@" 
# get all args 
# just echo them, but you may need to customize it according to your need 
# for example, F1 will store first field of $line, see readline2 script # for more examples 
F1=$(echo $line | awk '{ print $1 }') 
echo $line
}   


### Main script stars here 
### # Store file name 
FILE=""   


# Make sure we get file name as command line argument 
# Else read it from standard input device 
if [ "$1" == "" ]; then 
	FILE="/dev/stdin" 
else 
	FILE="$1" 
	echo $FILE
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

#tac $FILE | awk '{print $1,$3}'
tac $FILE | while read line
do
	echo $line
done


exit 0


