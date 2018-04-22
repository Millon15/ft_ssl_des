./$1 > $2/E_ans
diff $2/E_cor $2/E_ans > temp
num=`wc -l < temp`
rm temp
echo "        main3.c : " >> $2/total
if [ "$num" -eq "0" ]
then
	echo "OK :)" >> $2/total_temp
	echo "          OK :)" >> $2/total
else
	echo "KO :(" >> $2/total_temp
	echo "          KO :(" >> $2/total
	echo " [Correct answer]: " >> $2/total
	cat $2/E_cor >> $2/total
	echo " [Your answer]: " >> $2/total
	cat $2/E_ans >> $2/total
fi