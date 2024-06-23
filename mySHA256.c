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

// Declear Variables
const static unsigned int mySHA256IV[8] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

const static unsigned int mySHA256KT[64] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
                                            0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
                                            0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
                                            0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
                                            0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
                                            0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
                                            0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
                                            0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

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

