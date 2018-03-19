#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <libc.h>

int		main()
{
	int		len;
	char	*str;
	char	*key;
	char	*iv;
	FILE	*plaintext;
	FILE	*keyf;
	FILE	*ivf;

	plaintext = fopen("./resources/files/plaintext", "w");
	keyf = fopen("./resources/files/key", "w");
	ivf = fopen("./resources/files/iv", "w");

	// ======= GENERATING RANDOM STRING ==========
	srand(time(NULL));
	len = arc4random_uniform(1024) + 1;
	str = (char*)malloc(sizeof(char) * (len + 1));
	for (int i = 0; i < len; i++)
	{
		str[i] = arc4random_uniform(15);
		if (str[i] == 0)
			str[i] = arc4random_uniform(2) == 0 ? '\t' : '\n';
		else
			str[i] = arc4random_uniform(95) + 32;
	}
	str[len] = '\0';
	fprintf(plaintext, "%s", str);
	
	// ========== BASE64 =============

	//fprintf(script, "./ft_ssl base64 -i plaintext -o ./results/my_base64_e\n");
	//fprintf(script, "openssl base64 -in plaintext -out ./results/ssl_base64_e\n");
	//fprintf(script, "diff ./results/my_base64_e ./results/ssl_base64_e\n");
	//fprintf(script, "./ft_ssl base64 -i ./results/ssl_base64_e -o ./results/my_base64_d\n");
	//fprintf(script, "openssl base64 -in ./results/ssl_base64_e -out ./results/ssl_base64_d\n");
	//fprintf(script, "diff ./results/my_base64_d ./results/ssl_base64_d\n");

	// ========== GENERATING RANDOM KEY ============
	len = arc4random_uniform(48) + 1;
	key = (char*)malloc(sizeof(char) * (len + 1));
	key[len] = '\0';
	for (int i = 0; i < len; i++)
	{
		key[i] = arc4random_uniform(16);
		key[i] = key[i] < 10 ? key[i] + '0' : key[i] - 10 + 'A' + arc4random_uniform(2) * ('a' - 'A');
	}
	fprintf(keyf, "%s", key);
	//fprintf(script, "./ft_ssl des-ecb -i plaintext -o ./results/my_desecb_enc -k %s\n", key);
	//fprintf(script, "openssl des-ecb -in plaintext -out ./results/ssl_desecb_enc -K %s\n", key);
	//fprintf(script, "diff ./results/my_desecb_enc ./results/ssl_desecb_enc\n");
	//fprintf(script, "./ft_ssl des-ecb -i ./results/ssl_desecb_enc -o ./results/my_desecb_dec -k %s\n", key);
	//fprintf(script, "openssl des-ecb -in ./results/ssl_desecb_enc -out ./results/ssl_desecb_dec -K %s\n", key);
	//fprintf(script, "diff ./results/my_desecb_dec ./results/ssl_desecb_dec\n");

	// ========= GENERATING IV ============
	len = arc4random_uniform(16) + 1;
	iv = (char*)malloc(sizeof(char) * (len + 1));
	iv[len] = '\0';
	for (int i = 0; i < len; i++)
	{
		iv[i] = arc4random_uniform(16);
		iv[i] = iv[i] < 10 ? iv[i] + '0' : iv[i] - 10 + 'A' + arc4random_uniform(2) * ('a' - 'A');
	}
	fprintf(ivf, "%s", iv);
	//fprintf(script, "./ft_ssl des-cbc -i plaintext -o ./results/my_descbc_enc -k %s -v %s\n", key, iv);
	//fprintf(script, "openssl des-cbc -in plaintext -out ./results/ssl_descbc_enc -K %s -iv %s\n", key, iv);
	//fprintf(script, "diff ./results/my_descbc_enc ./results/ssl_descbc_enc\n");
	//fprintf(script, "./ft_ssl des-cbc -i ./results/ssl_descbc_enc -o ./results/my_descbc_dec -k %s -v %s\n", key, iv);
	//fprintf(script, "openssl des-cbc -in ./results/ssl_descbc_enc -out ./results/ssl_descbc_dec -K %s -iv %s\n", key, iv);
	//fprintf(script, "diff ./results/my_descbc_dec ./results/ssl_descbc_dec\n");
	//fclose(script);

	fclose(plaintext);
	fclose(keyf);
	fclose(ivf);
	return (0);
}
