
####�ѱ���/home/databachup/a.sh up ftp /home/databackup ��####

#!/bin/bash 

ftp -n<<! 
open 192.168.1.171
user guest 123456 
binary 
cd /home/data 
lcd /home/databackup 
prompt 
put a.sh a.sh 
close 
bye 
!

