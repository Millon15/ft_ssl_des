err=`wc -l < temp`
if  ! [ "$err" -eq "0" ]
then
	echo "\t"$1 >> $2
fi