/*
  Auther: setnotegraph
  Status: Undone
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mySHA256.h"

#define ENDIAN 0
#define DEBUG  1


static char *Cond1 = "SHA224";
static char *Cond2 = "SHA256";
static char *Cond3 = "SHA384"; 
static char *Cond4 = "SHA512";
static char *Cond5 = "SHA512/224";
static char *Cond6 = "SHA512/256";

int main(int argc, char **argv){
    /**/
    if (argc == 1) { 
        printf("This program is my SHA-2 implementation.\n");
        exit(0);
    }
    
    if(strcmp(argv[1],Cond1)==0){
        fprintf(stderr,"Not ready function.\n");
        exit(1);

    }

    else if(strcmp(argv[1],Cond2)==0){
        printf("%s is ready.\n",argv[1]);    
    }
    
    else if(strcmp(argv[1],Cond3)==0){
        fprintf(stderr,"Not ready function.\n");
        exit(1);
    
    }
    
    else if(strcmp(argv[1],Cond4)==0){
        fprintf(stderr,"Not ready function.\n");
        exit(1);
    }

    else if(strcmp(argv[1],Cond5)==0){
        fprintf(stderr,"Not ready function.\n");
        exit(1);
    }
    
    else if(strcmp(argv[1],Cond6)==0){
        fprintf(stderr,"Not ready function.\n");
        exit(1);
    }

    else{
        fprintf(stderr,"Invalid command.\n");
        exit(1);
    }


    char src[256];
    //init
    for(int i=0; i<256; i++) src[i] = 0;

    /*Test Text*/
    //char src[256] = "Visual Studio drives me crazy and I am suspecting I am doing something wrong. This is what I do: I installed Visual Studio(Pro '08) a long time ago, I installed the Windows SDK (Win 7 x64), someone emails me a project, it fails to build.";
    //char src[256] = "The quick brown fox jumps over the lazy dogs. This sentence is one of the English pangrams, and is often used for typing and computer keyboard tests.";
    //char src[256] = "Message";
    //char src[256] = "TEST";
    //char src[256] = "";
    //desired output:e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855
    //char src[256] = "a";
    // desired output:ca978112ca1bbdcafac231b39a23dc4da786eff8147c4e72b9807785afee48bb
    //char src[256] = "abc";
    // desired output:ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad
    //char src[256] = "de188941a3375d3a8a061e67576e926d";
    //char src[256] = "It's my message, so check SHA256's hash value. check it ";
    //char src[256] = "It's my message, so check SHA256's hash value. check it out.";
    //char src[256] = "It's my message, so check SHA256's hash value. If you don't same value, your program it wrong.";
    //char src[256] = "abcd";
    //desired output:88d4266fd4e6338d13b845fcf289579d209c897823b9217da3e161936f031589
    //26+26+1234
    //char src[256] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234";
    // desired output:b1c20ba49d3374f82bd624b2896c2096b48e83192fa3d062c7e5716ceea7421c
    if(argc > 2) for(int i=0; i<256; i++) src[i] = argv[2][i];
    int src_s = strlen(src);
    
    unsigned int *stringMB;    
    int message_size = ((((src_s/4)+1)+1)/16)*16+16;
    stringMB = string2message(src, src_s, ENDIAN);

    for(int i=0; i<(message_size); i++){
        if((i%16)==0) printf("\n%d\n",i/16);
        printf("0x%08x ", stringMB[i]);
    }
    puts("");
    unsigned int H[8];
    mySHA256(stringMB,src_s,H);
    for(int i=0; i<8; i++) printf("%08x", H[i]);
    puts("");
    puts("");
    free(stringMB);

    puts("-------------------------------");
    return 0;
}
