
#include <stdio.h>
#include <string.h>

#include "rsa.h"

#define BUFSIZE  1024



 main(void)
{

    unsigned char input[128];
    unsigned char output[128];
    unsigned char finput[128];
    memset(input,0,sizeof(input));
    memset(output,0,sizeof(output));
    memset(finput,0,sizeof(finput));
        int i=0;
//	strcpy(input,"wangweihua11234567889");
    input[0]='w';
    input[1]='w';
    input[2]='w';
    input[3]='w';
    input[4]='w';
	input[5]='w';
//	strcpy((char *)input,"yaolong1");
	rsa_crt_prikey pri_key;
    rsa_pubkey pub_key;
    RSA_Generate_keys(&pub_key,&pri_key);

	for(i=0; i<256; i++)
	{
		printf("%x ", pub_key.N[i]);
		if((i+1)%16==0) printf("\n");
	}
    printf("input:%s\n",input);

    RSA_Encrypt(&pub_key,input,output);
printf("\n");

	for(i=0; i<21; i++)
	{
		printf("%x ", output[i]);
		if((i+1)%32==0) printf("\n");
      	}
	RSA_Decrypt(&pri_key,output,finput);
printf("\n");
	for(i=0; i<21; i++)
	{
		printf("%c ", finput[i]);
		if((i+1)%32==0) printf("\n");
	}
	printf("\n");
return 0;                                                 
}



