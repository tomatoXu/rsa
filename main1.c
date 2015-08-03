#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include "rsa.h"

#define BUFSIZE 1024

struct option opts[] = {
        {"plain", required_argument, NULL, 'p'},
        {"cipher", required_argument, NULL, 'c'},
        {"pub", required_argument, NULL, 'b'},
        {"pri", required_argument, NULL, 'i'},
        {"help", no_argument, NULL, 'h'},
        {"version", no_argument, NULL, 'v'}
};
/*
typedef union{
        struct {
                char low;
                char high;
        }twobyte;
        unsigned char key;
}KEY;
*/

unsigned long f(char str[2])
{
        unsigned long var = 0;
        unsigned long t;
        int len = strlen(str);
        if (var > 8)
                return -1;
        //strupr(str);
        if(str[0]>='a'&&str[0]<='z')
                str[0]-='a'-'A';
        if(str[1]>='a'&&str[1]<='z')
                str[1]-='a'-'A';
        for (;*str;str++){
                if (*str >= 'A'&&*str <='F')
                        t = *str-55;
                else
                        t = *str-48;
                var<<=4;
                var|=t;
        }
        return var;
}
int main(int argc, char **argv)
{
        rsa_context ctx;
        rsa_pubkey pub_key;
        rsa_crt_prikey pri_key;
        unsigned char plain[256];
        unsigned char cipher[256];
        char temp[512];
        unsigned char pubkey[256];
        unsigned char priv_p[256];
        unsigned char priv_q[256];
        unsigned char output[128];
        memset(temp,0,sizeof(temp));
        memset(pubkey,0,sizeof(pubkey));
        memset(plain,0,sizeof(plain));
        memset(priv_p,0,sizeof(priv_p));
        memset(priv_q,0,sizeof(priv_q));
        memset(output,0,sizeof(output));
        int i = 0;
        mpi n,e,d;
        int opt = 0;
        while ((opt = getopt_long(argc, argv, "p:c:b:i:hv", opts, NULL)) != -1) {
                switch (opt) {
                case 'p':
                        strncpy(plain, optarg, sizeof(plain)-1);
                        break;
                case 'c':
                        strncpy(cipher, optarg, sizeof(cipher)-1);
                        break;
                case 'b':
                        memcpy(temp, optarg, 512);
                        for(i=0;i<strlen(temp);i++){
                                if (temp[2*i]=='\0'||temp[2*i+1]=='\0') break;
                                char tmp[2];
                                tmp[0] = temp[2*i];
                                tmp[1] = temp[2*i+1];
                                pubkey[i] = f(tmp);
                        }
                        //printf("len:%d\n",strlen(pubkey));
                        break;
                case 'i':
                        memcpy(priv_p, optarg, 512);
                       /* printf("temp:%s\n",temp);
                        for(i=0;i<strlen(temp);i++){
                                if (temp[2*i]=='+'||temp[2*i+1]=='+') break;
                                char tmp[2];
                                tmp[0] = temp[2*i];
                                tmp[1] = temp[2*i+1];
                                printf("ss%s ",tmp);
                                priv_p[i] = f(tmp);
                        }
                        printf("i:%d\n",i);
                        i++;
                        int a = i;
                        for(i;i<strlen(temp);i++){
                                if (temp[2*i]=='\0'||temp[2*i+1]=='\0') break;
                                char tmp[2];
                                tmp[0] = temp[2*i];
                                tmp[1] = temp[2*i+1];
                                priv_q[i-a] = f(tmp);
                        }*/ 
                        break;
                case 'v':
                        printf("version 1.0.0\n");
                        break;
                case 'h':
                        printf("Usage: ./desencrypt -p plaintext -k deskey [-hv]\n");
                        printf(" -p --plain plaintext\n");
                        printf(" -c --cipher ciphertext\n");
                        printf(" -b|i --key 8 Bytes key\n");
                        printf(" -h --help help information\n");
                        printf(" -v --version version information\n");
                        break;
                default:
                        printf("Usage: ./desencrypt -p plaintext -k deskey [-hv]\n");
                        printf(" -p --plain plaintext\n");
                        printf(" -c --cipher ciphertext\n");
                        printf(" -b|i --key 8 Bytes key\n");
                        printf(" -h --help help information\n");
                        printf(" -v --version version information\n");
                        return -1;
                }
        }
        
       /* char *o = "ac";
        unsigned char y=f(o);
        printf("0x%02x\n",y);

*/
        RSA_Generate_keys(&pub_key,&pri_key);
	for(i=0; i<256; i++)
	{
        pub_key.N[i] = pubkey[i];
		printf("%02x ", pub_key.N[i]);
		if((i+1)%16==0) printf("\n");
	}
        printf("\nplain:%s\n",plain);
        RSA_Encrypt(&pub_key,plain,output);
        printf("\nthe encrypted message is:\n");
        
	for(i=0; i<strlen(output)-1; i++)
	{
		printf("%02x ", output[i]);
		if((i+1)%16==0) printf("\n");
      	}
	printf("\n");
        return 0;
}
