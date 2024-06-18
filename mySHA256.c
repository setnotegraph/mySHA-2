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
        
        printf("Time %d:", i);
        for(int k=0; k<8; k++) printf("%08x ", O[k]);
        puts("");
    }
    return 0;
}

//32bit
unsigned *makeMessage(unsigned *data, int byte_size, int mode){
    int data_size = (byte_size/4)+1;
    int Message_size = (((data_size+1)/16)*16)+16;
    unsigned *Message = malloc(sizeof(unsigned) * Message_size);
    //Init
    for(int i=0; i<Message_size; i++) Message[i] = 0;
    //Copy Data
    for(int i=0; i<data_size; i++) Message[i] = data[i];
    puts("");

    //Big Endian
    if(mode == 0) {
        // Append 1 bit 1.
        Message[(byte_size)/4] |= 0x80<<(24-((byte_size)%4)*8);
        // Append Bit Length
        Message[Message_size-1] = (byte_size * 8);
    }
    //Little Endian
    else {
        // Append 1 bit 1.
        Message[(byte_size)/4] |= 0x80<<(((byte_size)%4)*8);
        // Append Bit Length
        Message[Message_size-2] = (byte_size * 8);
    }
    return Message;
}

//32bit
unsigned *string2message(char *str, int str_size, int mode){
    int data_size= ((str_size)/4)+1;
    unsigned int data[data_size];

    //Init
    for(int i=0; i<data_size; i++) data[i] = 0;

    //Big Endian
    if(mode==0) for(int i=0; i<(str_size);i++) data[i/4] |= str[i]<<(24-(i%4)*8);
    //Little Endian
    else for(int i=0; i<(str_size);i++) data[i/4] |= str[i]<<((i%4)*8);
    
    //Make Message Block
    return makeMessage(data, str_size, mode);
}

//32bit
unsigned *data2message(unsigned *data, unsigned byte_size, int mode){
    int data_size= ((byte_size)/4)+1;
    unsigned int fixData[data_size];

    //Init
    for(int i=0; i<data_size; i++) fixData[i] = 0;

    //Copy data
    if((byte_size%4)==0) for(int i=0; i<data_size-1; i++)     fixData[i] = data[i];
    else                 for(int i=0; i<(byte_size/4)+1; i++) fixData[i] = data[i];
    //Big Endian
    if(mode==0){
        if((byte_size%4) == 1)      fixData[data_size-1] = (fixData[data_size-1]<<24);
        else if((byte_size%4) == 2) fixData[data_size-1] = (fixData[data_size-1]<<16);
        else if((byte_size%4) == 3) fixData[data_size-1] = (fixData[data_size-1]<< 8);
    }
    //Make Message Block
    return makeMessage(fixData, byte_size, mode);
}

int main(void) {
    /*Test Text*/
    //char src[256] = "Visual Studio drives me crazy and I am suspecting I am doing something wrong. This is what I do: I installed Visual Studio(Pro '08) a long time ago, I installed the Windows SDK (Win 7 x64), someone emails me a project, it fails to build.";
    //char src[256] = "The quick brown fox jumps over the lazy dogs. This sentence is one of the English pangrams, and is often used for typing and computer keyboard tests.";
    //char src[256] = "Message";
    //char src[256] = "TEST";
    //char src[256] = "";
    //desired output:e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855
    //char src[256] = "a";
    // desired output:ca978112ca1bbdcafac231b39a23dc4da786eff8147c4e72b9807785afee48bb
    char src[256] = "abc";
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

#if 0
    SHA256_STEP V;
    init256STEP(&V);    
    for(int i=0;i<36;i++){
        printf("%08x ",V.a[i]);
        printf("%08x ",V.b[i]);
        printf("%08x ",V.c[i]);
        printf("%08x ",V.d[i]);
        printf("%08x ",V.e[i]);
        printf("%08x ",V.f[i]);
        printf("%08x ",V.g[i]);
        printf("%08x ",V.h[i]);
        puts("");
    }
#endif
    //SHA's test vector file
    //**Len: bit length**
    
    // unsigned int data[1] = {0x00};
    // int byte_size = 0;
    //desired output:e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855
    
    // unsigned int data[1] = {0xd3};
    // int byte_size = 1;
    // // desired output:28969cdfa74a12c82f3bad960b0b000aca2ac329deea5c2328ebc6f2ba9802c1

    // unsigned int data[4] = {0xde188941,0xa3375d3a,0x8a061e67,0x576e926d};
    // int byte_size = 16;
    // desired output:067c531269735ca7f541fdaca8f0dc76305d3cada140f89372a410fe5eff6e4d
    
    // unsigned int data[14] = {0xde188941,0xa3375d3a,0x8a061e67,0x576e926d,0xc71a7fa3,0xf0cceb97,0x452b4d32,0x27965f9e,0xa8cc7507,0x6d9fb9c5,0x417aa5cb,0x30fc2219,0x8b34982d,0xbb629e};
    // int byte_size = 55;
    //desired output:038051e9c324393bd1ca1978dd0952c2aa3742ca4f1bd5cd4611cea83892d382
    
    // unsigned int data[1] = {0x616263};
    // int byte_size = 3;
    // desired output:ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad 
    
    unsigned int data[14] = {0x61626364,0x62636465,0x63646566,0x64656667,0x65666768,0x66676869,0x6768696a,
                             0x68696a6b,0x696a6b6c,0x6a6b6c6d,0x6b6c6d6e,0x6c6d6e6f,0x6d6e6f70,0x6e6f7071};
    int byte_size = 56;
    //desired output:248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1
    
    int data_size;
    data_size = ((byte_size/4)+1);

    int dataMB_size = ((data_size+1)/16)*16+16;
    
    unsigned int *dataMB;
    dataMB = data2message(data, byte_size, ENDIAN);
    
    for(int i=0; i<dataMB_size; i++){
        if((i%16)==0) printf("\n%d\n",i/16);
        printf("0x%08x ", dataMB[i]);
    }
    puts("");

    unsigned int dataHash[8];
    mySHA256(dataMB,byte_size,dataHash);
    for(int i=0; i<8; i++) printf("%08x", dataHash[i]);
    puts("");
    free(dataMB);   

}
