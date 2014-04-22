#! /bin/bash

var=`echo "aaa.txt,bbb,ccc" | awk   -F',' '{print $0} ' |  sed "s/,/ /g"`
for list in $var
do
	echo $list
done

