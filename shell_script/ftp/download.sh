####ftp服务器上下载/home/data/a.sh to local /home/databackup####
#!/bin/bash 
ftp -n<<! 
open 10.3.3.108
user wanghb wanghb 
binary 
cd /DEVHome/wanghb
lcd ./
prompt 
get log.tar b.tar
close 
bye 
!

