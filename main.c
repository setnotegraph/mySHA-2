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

int main(int argc, char **argv){
    if (argc == 1) { 
        printf("This program is my SHA-2 implementation.\n");
        exit(0);
    }
    /**/
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

    /*File option*/
    /*
    if(argv[2][0] == '-'){
        switch((argv[2][1])){
            case 'f':
                
                break;
            case 'v':

                break;
            default:
                fprintf(stderr,"Option Error.\n");
                exit(1);
        }
            
    }
    
    */

    char src[256];
    //init
    for(int i=0; i<256; i++) src[i] = 0;

    if(argc > 2) for(int i=0; i<256; i++) src[i] = argv[2][i];
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
}
