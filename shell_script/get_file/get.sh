#!/bin/bash

# read config



# ssh login
ssh wanghb@10.3.3.60



# generate log patch file





# get patch file with ftp
ftp -n<<! 
open 10.3.3.108
user wanghb wanghb 
binary 
cd /DEVHome/wanghb/xbocs_run/bomcserver/log
lcd ./
prompt 
get BomcServer_20130508.log BomcServer_20130508.log
close 
bye 
!
