while read line; do
	name=`echo $line|awk -F '=' '{print $1}'`
	value=`echo $line|awk -F '=' '{print $2}'`
	case $name in "name")
		name=$value£»£»"pwd"£©
		pwd=$value£»£»"permission"£©
		permission=$value£»£»*£©
