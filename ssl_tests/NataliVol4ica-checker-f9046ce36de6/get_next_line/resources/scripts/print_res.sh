total=`cat $1/total_temp | wc -l | sed "s/ //g"`
ok=`cat $1/total_temp | grep "OK" | wc -l | sed "s/ //g"`
if [ "$total" -eq "$ok" ]
then
	echo '\033[0;32m'"   [$ok/$total]"'\033[0m'
else
	echo '\033[0;31m'"   [$ok/$total]"'\033[0m'
fi