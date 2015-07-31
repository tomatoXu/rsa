#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <string.h>
#include "rsa.h"

#define BUFSIZE 1024

struct option opts[] = {
        {"plain", 1, NULL, 'p'},
        {"cipher", required_argument, NULL, 'c'},
        {"pub", 1, NULL, 'b'},
        {"pri", 1, NULL, 'i'},
        {"help", 0, NULL, 'h'},
        {"version", 0, NULL, 'v'}
};

int main(int argc, char **argv)
{
        rsa_context ctx;
        rsa_pubkey pub_key;
        rsa_crt_prikey pri_key;
        unsigned char *plain = "";
        unsigned char *cipher = "";
        unsigned char *pubkey = "";
        unsigned char *privkey = "";
        mpi n,e,d;
        int opt = 0;
        while ((opt = getopt_long(argc, argv, "p:k:hv", opts, NULL)) != -1) {
                switch (opt) {
                case 'p':
                        strncpy(plain, optarg, sizeof(plain)-1);
                        break;
                case 'c':
                        strncpy(cipher, optarg, sizeof(cipher)-1);
                        break;
                case 'b':
                        memcpy(pubkey, optarg, 8);
                        strcpy(pub_key.N,pubkey);
                        break;
                case 'i':
                        memcpy(privkey, optarg, 8);
                        break;
                case 'v':
                        printf("version 1.0.0\n");
                        break;
                case 'h':
                        printf("Usage: ./desencrypt -p plaintext -k deskey [-hv]\n");
                        printf(" -p --plain plaintext\n");
                        printf(" -k --key 8 Bytes key\n");
                        printf(" -h --help help information\n");
                        printf(" -v --version version information\n");
                        break;
                default:
                        printf("Usage: ./desencrypt -p plaintext -k deskey [-hv]\n");
                        printf(" -p --plain plaintext\n");
                        printf(" -k --key 8 Bytes key\n");
                        printf(" -h --help help information\n");
                        printf(" -v --version version information\n");
                        return -1;
                }
        }
        unsigned char input[128];
        unsigned char output[128];
        unsigned char finput[128];
        memset(input,0,sizeof(input));
        memset(output,0,sizeof(output));
        memset(finput,0,sizeof(finput));
        int i=0;
//	strcpy(input,"wangweihua11234567889");
        
        mpi_read_string(&ctx.N, pubkey, sizeof(pubkey)/8);
        mpi_read_string(&ctx.E, (unsigned char*)"\x00\x01\x00\x01", 4);
                
        //RSA_Generate_keys(&pub_key,&pri_key);
/*	for(i=0; i<256; i++)
	{
                pub_key.N[i]=key[i];
		printf("%x ", pub_key.N[i]);
		if((i+1)%16==0) printf("\n");
	}*/
        printf("plain:%s\n",plain);

        RSA_Encrypt(&pub_key,plain,output);
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
