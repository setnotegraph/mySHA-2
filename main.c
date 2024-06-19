/*
  Auther: setnotegraph
  Status: Undone
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mySHA256.h"
#include "mySHA2gen.h"

#define ENDIAN 0
#define DEBUG  0


static char *Cond1 = "SHA224";
static char *Cond2 = "SHA256";
static char *Cond3 = "SHA384"; 
static char *Cond4 = "SHA512";
static char *Cond5 = "SHA512/224";
static char *Cond6 = "SHA512/256";

/*trigger*/
static char Mode = 0;
static char Word = 0; /*0: 32bit, 1: 64bit*/
static char File = 0;
/*Argument adjustment*/
static char argind= 0;


int main(int argc, char **argv){
    if (argc == 1) { 
        printf("This program is my SHA-2 implementation.\n");
        exit(0);
    }
    
    if(strcmp(argv[1],Cond1)==0){
        fprintf(stderr,"Not ready function.\n");
        exit(1);
        Word = 0;

    }

    else if(strcmp(argv[1],Cond2)==0){
        printf("%s is ready.\n",argv[1]);
        Mode = 2;
        Word = 0;
    }
    
    else if(strcmp(argv[1],Cond3)==0){
        fprintf(stderr,"Not ready function.\n");
        exit(1);
        Word = 1;
    }
    
    else if(strcmp(argv[1],Cond4)==0){
        fprintf(stderr,"Not ready function.\n");
        exit(1);
        Word = 1;
    }

    else if(strcmp(argv[1],Cond5)==0){
        fprintf(stderr,"Not ready function.\n");
        exit(1);
        Word = 1;
    }
    
    else if(strcmp(argv[1],Cond6)==0){
        fprintf(stderr,"Not ready function.\n");
        exit(1);
        Word = 1;
    }

    else{
        fprintf(stderr,"Invalid command.\n");
        exit(1);
        Word = 1;
    }

    /*Option*/
    while(1){    
        if(argv[2+argind][0] == '-'){
            argind +=1;
            switch((argv[2][1])){
                /*f: file*/
                case 'f':
                    File = 1;
                    break;
                /*v: version(or vision)*/
                case 'v':

                    break;
                default:
                    fprintf(stderr,"Option Error.\n");
                    exit(1);
            }
        }
        else break;
    }
    
    /*src: input data, MB:message size*/
    char src[256];
    int src_s;
    unsigned int *MB;
    

    /*Read File*/
    if(File==1){
       fprintf(stderr, "Sorry, Not make yet.\n");
       exit(1);
    }
    /*Read Argument String*/
    else{
        for(int i=0; i<256; i++) src[i] = 0;
        for(int i=0; i<256; i++) src[i] = argv[2+argind][i];
        src_s = strlen(src);
    }
    
    switch (Mode) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            MB = string2message32(src, src_s, ENDIAN);
            unsigned int H[8];
            mySHA256(MB, src_s, H);
            for(int i=0; i<8; i++) printf("%08x", H[i]);
            printf("\n");
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        default:
            fprintf(stderr, "Invalid Mode Value.\n");
            exit(1);
    }
    free(MB);
    return 0;
#if 0
    char src[256];
    //init
    for(int i=0; i<256; i++) src[i] = 0;

    if(argc > 2) for(int i=0; i<256; i++) src[i] = argv[2+argind][i];
    int src_s = strlen(src);
    
    unsigned int *stringMB;    
    int message_size = ((((src_s/4)+1)+1)/16)*16+16;
    stringMB = string2message32(src, src_s, ENDIAN);
#if DEBUG
    for(int i=0; i<(message_size); i++){
        if((i%16)==0) printf("\n%d\n",i/16);
        printf("0x%08x ", stringMB[i]);
    }
    puts("");
#endif
    unsigned int H[8];
    mySHA256(stringMB,src_s,H);
    for(int i=0; i<8; i++) printf("%08x", H[i]);
    puts("");
    free(stringMB);
    return 0;
#endif
}
