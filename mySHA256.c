/*
Auther: setnotegraph
Status: done

Summary
    This is SHA-256 program. 

Reference 
    // SHA1 ~ SHA2 specification
    [FIPS180-4]: https://www.ietf.org/rfc/rfc1321.txt etc...
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mySHA256.h"

//endian: 0=big, 1=little
#define ENDIAN 0

unsigned int ror(unsigned int x, int n){
    return ((x << (32-n)) | (x>>n));
}

unsigned int mySHA256ch(unsigned int x, unsigned int y, unsigned int z) {
    return (( x & y )^( ~x & z ));
}

unsigned int mySHA256maj(unsigned int x, unsigned int y, unsigned int z) {
    return (( x & y ) ^ ( x & z ) ^ ( y & z ));
}

unsigned int mySHA256fS0(unsigned int x){
    return (ror(x,2)^ror(x,13)^ror(x,22));
}

unsigned int mySHA256fS1(unsigned int x){
    return (ror(x,6)^ror(x,11)^ror(x,25));
}

unsigned int mySHA256fs0(unsigned int x){
    return (ror(x,7)^ror(x,18)^(x>>3));
}

unsigned int mySHA256fs1(unsigned int x){
    return (ror(x,17)^ror(x,19)^(x>>10));
}

//Ver:Normal
unsigned int mySHA256(unsigned *M, int src_size, unsigned *O){
    //init
    O[0]= mySHA256IV[0];
    O[1]= mySHA256IV[1];
    O[2]= mySHA256IV[2];
    O[3]= mySHA256IV[3];
    O[4]= mySHA256IV[4];
    O[5]= mySHA256IV[5];
    O[6]= mySHA256IV[6];
    O[7]= mySHA256IV[7];
    
    unsigned int a;
    unsigned int b;
    unsigned int c;
    unsigned int d;
    unsigned int e;
    unsigned int f;
    unsigned int g;
    unsigned int h;
    
    unsigned int T1;
    unsigned int T2;

    int data_size =  ((src_size/4)+1);
    int Message_size = (((data_size+1)/16)*16+16);
    
    puts("");
    for(int i=0; i < (Message_size/16); i++){
        a = O[0];
        b = O[1];
        c = O[2];
        d = O[3];
        e = O[4];
        f = O[5];
        g = O[6];
        h = O[7];
        unsigned int W[64];
        for(int j=0; j<64 ;j++){
            if(j<16) W[j] = M[(j+(16*i))];
            else W[j] = mySHA256fs1(W[j-2]) + W[j-7] + mySHA256fs0(W[j-15]) + W[j-16];
        }

        for(int j=0; j < 64; j++){
            T1 = h + mySHA256fS1(e) + mySHA256ch(e,f,g) + mySHA256KT[j] + W[j];
            T2 = mySHA256fS0(a) + mySHA256maj(a,b,c);
            h=g, g=f, f=e, e=d+T1, d=c, c=b, b=a,a=T1+T2;
        }
        O[0] += a;
        O[1] += b;
        O[2] += c;
        O[3] += d;
        O[4] += e;
        O[5] += f;
        O[6] += g;
        O[7] += h;
    }
    return 0;
}

