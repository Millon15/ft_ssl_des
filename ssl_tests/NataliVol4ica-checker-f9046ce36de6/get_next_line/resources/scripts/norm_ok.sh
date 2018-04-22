err=`wc -l < norm2`
if [ "$err" -eq "0" ]
then
	echo '\033[0;32m'"OK :)"'\033[0m'
fi