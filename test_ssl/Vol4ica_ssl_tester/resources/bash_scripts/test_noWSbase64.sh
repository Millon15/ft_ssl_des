key=$1
iv=$2
plaintext=./resources/files/plaintext
res=./resources/results
sc=./resources/bash_scripts

# base64 enc
./ft_ssl base64 -i $plaintext -o $res/my_base64_e -e
base64 -in $plaintext -out $res/ssl_base64_e
diff $res/my_base64_e $res/ssl_base64_e > temp
sh $sc/diff_check.sh "base64 encryption" differ

# base64 dec
./ft_ssl base64 -i $res/ssl_base64_e -o $res/my_base64_d -d
openssl base64 -in $res/ssl_base64_e -out $res/ssl_base64_d -d
diff $res/my_base64_d $res/ssl_base64_d > temp
sh $sc/diff_check.sh "base64 decryption" differ

# des-ecb enc
./ft_ssl des-ecb -i $plaintext -o $res/my_desecb_enc -k $key -e
openssl des-ecb -in $plaintext -out $res/ssl_desecb_enc -K $key -e
diff $res/my_desecb_enc $res/ssl_desecb_enc > temp
sh $sc/diff_check.sh "des-ecb encryption" differ

# des-ecb dec
./ft_ssl des-ecb -i $res/ssl_desecb_enc -o 	$res/my_desecb_dec -k $key
openssl des-ecb -in $res/ssl_desecb_enc -out	$res/ssl_desecb_dec -K $key
diff $res/my_desecb_dec $res/ssl_desecb_dec > temp
sh $sc/diff_check.sh "des-ecb decryption" differ

# des-cbc enc
./ft_ssl des-cbc -i $plaintext -o $res/my_descbc_enc -k $key -v $iv -e
openssl des-cbc -in $plaintext -out $res/ssl_descbc_enc -K $key -iv $iv -e
diff $res/my_descbc_enc $res/ssl_descbc_enc > temp
sh $sc/diff_check.sh "des-cbc encryption" differ

# des-cbc dec
./ft_ssl des-cbc -i $res/ssl_descbc_enc -o $res/my_descbc_dec -k $key -v $iv -d
openssl des-cbc -in $res/ssl_descbc_enc -out $res/ssl_descbc_dec -K $key -iv $iv -d
diff $res/my_descbc_dec $res/ssl_descbc_dec > temp
sh $sc/diff_check.sh "des-cbc decryption" differ

# des-ecb base64 enc
./ft_ssl des-ecb -i $plaintext -o $res/my_desecb_enc -k $key -e -a
openssl des-ecb -in $plaintext -K $key -e | base64 -out $res/ssl_desecb_enc
diff $res/my_desecb_enc $res/ssl_desecb_enc > temp
sh $sc/diff_check.sh "des-ecb encryption" differ
openssl des-ecb -in $plaintext -out $res/ssl_desecb_enc -K $key -e -a

# des-ecb base64 dec
./ft_ssl des-ecb -i $res/ssl_desecb_enc -o 	$res/my_desecb_dec -k $key -a
openssl des-ecb -in $res/ssl_desecb_enc -out	$res/ssl_desecb_dec -K $key -a
diff $res/my_desecb_dec $res/ssl_desecb_dec > temp
sh $sc/diff_check.sh "des-ecb decryption" differ

# des-cbc base64 enc
./ft_ssl des-cbc -i $plaintext -o $res/my_descbc_enc -k $key -v $iv -e -a
openssl des-cbc -in $plaintext -K $key -iv $iv -e | base64 -out $res/ssl_descbc_enc
diff $res/my_descbc_enc $res/ssl_descbc_enc > temp
sh $sc/diff_check.sh "des-cbc encryption" differ
openssl des-cbc -in $plaintext -out $res/ssl_descbc_enc -K $key -iv $iv -e -a

# des-cbc base64 dec
./ft_ssl des-cbc -i $res/ssl_descbc_enc -o $res/my_descbc_dec -k $key -v $iv -d -a
openssl des-cbc -in $res/ssl_descbc_enc -out $res/ssl_descbc_dec -K $key -iv $iv -d -a
diff $res/my_descbc_dec $res/ssl_descbc_dec > temp
sh $sc/diff_check.sh "des-cbc decryption" differ

# ===== BONUS =======

# des3-ecb enc
./ft_ssl des3-ecb -i $plaintext -o $res/my_des3ecb_enc -k $key -e
openssl des-ede3 -in $plaintext -out $res/ssl_des3ecb_enc -K $key -e
diff $res/my_des3ecb_enc $res/ssl_des3ecb_enc > temp
sh $sc/diff_check.sh "des3-ecb encryption" differ_bonus

# des3-ecb dec
./ft_ssl des3-ecb -i $res/ssl_des3ecb_enc -o 	$res/my_des3ecb_dec -k $key -d
openssl des-ede3 -in $res/ssl_des3ecb_enc -out	$res/ssl_des3ecb_dec -K $key -d
diff $res/my_des3ecb_dec $res/ssl_des3ecb_dec > temp
sh $sc/diff_check.sh "des3-ecb decryption" differ_bonus

#des3-cbc enc
./ft_ssl des3-cbc -i $plaintext -o $res/my_des3cbc_enc -k $key -v $iv -e
openssl des3 -in $plaintext -out $res/ssl_des3cbc_enc -K $key -iv $iv -e
diff $res/my_des3cbc_enc $res/ssl_des3cbc_enc > temp
sh $sc/diff_check.sh "des3-cbc encryption" differ_bonus

# des3-cbc dec
./ft_ssl des3-cbc -i $res/ssl_des3cbc_enc -o $res/my_des3cbc_dec -k $key -v $iv -d
openssl des3 -in $res/ssl_des3cbc_enc -out $res/ssl_des3cbc_dec -K $key -iv $iv -d
diff $res/my_des3cbc_dec $res/ssl_des3cbc_dec > temp
sh $sc/diff_check.sh "des3-cbc decryption" differ_bonus


# des3-ecb base64 enc
./ft_ssl des3-ecb -i $plaintext -o $res/my_des3ecb_enc_base -k $key -e -a
openssl des-ede3 -in $plaintext -K $key -e | base64 -out $res/ssl_des3ecb_enc_base
diff $res/my_des3ecb_enc_base $res/ssl_des3ecb_enc_base > temp
sh $sc/diff_check.sh "des3-ecb base64 encryption" differ_bonus
openssl des-ede3 -in $plaintext -out $res/ssl_des3ecb_enc_base -K $key -e -a

# des3-ecb base64 dec
./ft_ssl des3-ecb -i $res/ssl_des3ecb_enc_base -o 	$res/my_des3ecb_dec_base -k $key -a -d
openssl des-ede3 -in $res/ssl_des3ecb_enc_base -out	$res/ssl_des3ecb_dec_base -K $key -a -d
diff $res/my_des3ecb_dec_base $res/ssl_des3ecb_dec_base > temp
sh $sc/diff_check.sh "des3-ecb base64 decryption" differ_bonus

# des3-cbc base64 enc
./ft_ssl des3-cbc -i $plaintext -o $res/my_des3cbc_enc_base -k $key -v $iv -e -a
openssl des3 -in $plaintext -K $key -iv $iv -e | base64 -out $res/ssl_des3cbc_enc_base
diff $res/my_des3cbc_enc_base $res/ssl_des3cbc_enc_base > temp
sh $sc/diff_check.sh "des3-cbc base64 encryption" differ_bonus
openssl des3 -in $plaintext -out $res/ssl_des3cbc_enc_base -K $key -iv $iv -e -a

# des3-cbc base64 dec
./ft_ssl des3-cbc -i $res/ssl_des3cbc_enc_base -o $res/my_des3cbc_dec_base -k $key -v $iv -d -a
openssl des3 -in $res/ssl_des3cbc_enc_base -out $res/ssl_des3cbc_dec_base -K $key -iv $iv -d -a
diff $res/my_des3cbc_dec_base $res/ssl_des3cbc_dec_base > temp
sh $sc/diff_check.sh "des3-cbc base64 decryption" differ_bonus


