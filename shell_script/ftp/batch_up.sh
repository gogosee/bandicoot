####���ص�/home/databackup to ftp�������ϵ�/home/data####

#!/bin/bash 

ftp -n<<! 
open 192.168.1.171
user guest 123456 
binary 
hash
cd /home/data 
lcd /home/databackup 
prompt 
mput * 
close 
bye 
!

