./$1 $2/$3 $2/$4 $2/$5 > $2/B_ans
diff $2/B_cor $2/B_ans > temp
num=`wc -l < temp`
rm temp
echo "        $3 $4 $5 main4.c:" >> $2/total
if [ "$num" -eq "0" ]
then
	echo "OK :)" >> $2/total_temp
	echo "          OK :)" >> $2/total
else
	echo "KO :(" >> $2/total_temp
	echo "          KO :(" >> $2/total
	echo " [Correct answer]: " >> $2/total
	cat $2/B_cor >> $2/total
	echo " [Your answer]: " >> $2/total
	cat $2/B_ans >> $2/total
fi