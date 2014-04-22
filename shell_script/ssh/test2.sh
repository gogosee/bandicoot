
#!/bin/bash
ip1="10.3.3.60"
command1="ssh -l wanghb $ip1"
expect -c "
	spawn $command1;
	expect {
		\"10.3.3.60's password:\" {send \"aa\r\"; exp_continue}
		\"wanghb@\" {send \"df -h\r exit\r\"; exp_continue}
	}
"
