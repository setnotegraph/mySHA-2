/*
Auther: setnotegraph
Status: undone

Summary
    This is SHA-2 message block program. 

Reference 
    // SHA1 ~ SHA2 specification
    [FIPS180-4]: https://www.ietf.org/rfc/rfc1321.txt etc...
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mySHA2gen.h"

//endian: 0=big, 1=little
#define ENDIAN 0


//32bit
unsigned *makeMessage32(unsigned *data, int byte_size, int mode){
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
unsigned *string2message32(char *str, int str_size, int mode){
    int data_size= ((str_size)/4)+1;
    unsigned int data[data_size];

    //Init
    for(int i=0; i<data_size; i++) data[i] = 0;

    //Big Endian
    if(mode==0) for(int i=0; i<(str_size);i++) data[i/4] |= str[i]<<(24-(i%4)*8);
    //Little Endian
    else for(int i=0; i<(str_size);i++) data[i/4] |= str[i]<<((i%4)*8);
    
    //Make Message Block
    return makeMessage32(data, str_size, mode);
}

//32bit
unsigned *data2message32(unsigned *data, unsigned byte_size, int mode){
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
    return makeMessage32(fixData, byte_size, mode);
}


//64bit
unsigned long long *makeMessage64(unsigned long long *data, int byte_size, int mode){
    int data_size = (byte_size/8)+1;
    int Message_size = (((data_size+1)/16)*16)+16;
    unsigned long long *Message = malloc(sizeof(unsigned long long) * Message_size);
    //Init
    for(int i=0; i<Message_size; i++) Message[i] = 0;
    //Copy Data
    for(int i=0; i<data_size; i++) Message[i] = data[i];
    puts("");

    //Big Endian
    if(mode == 0) {
        // Append 1 bit 1.
        Message[(byte_size)/8] |= (unsigned long long)0x80<<(56-((byte_size)%8)*8);
        // Append Bit Length
        Message[Message_size-1] = (byte_size * 8);
    }
    //Little Endian
    else {
        // Append 1 bit 1.
        Message[(byte_size)/8] |= (unsigned long long)0x80<<(((byte_size)%8)*8);
        // Append Bit Length
        Message[Message_size-2] = (byte_size * 8);
    }
    return Message;
}

//64bit
unsigned long long *string2message64(char *str, int str_size, int mode){
    int data_size= ((str_size)/4)+1;
    unsigned long long data[data_size];

    //Init
    for(int i=0; i<data_size; i++) data[i] = 0;

    //Big Endian
    if(mode==0) for(int i=0; i<(str_size);i++) data[i/8] |= str[i]<<(56-(i%8)*8);
    //Little Endian
    else for(int i=0; i<(str_size);i++) data[i/8] |= str[i]<<((i%8)*8);
    
    //Make Message Block
    return makeMessage64(data, str_size, mode);
}

//64bit
unsigned long long *data2message64(unsigned long long *data, unsigned byte_size, int mode){
    int data_size= ((byte_size)/8)+1;
    unsigned long long fixData[data_size];

    //Init
    for(int i=0; i<data_size; i++) fixData[i] = 0;

    //Copy data
    if((byte_size%4)==0) for(int i=0; i<data_size-1; i++)     fixData[i] = data[i];
    else                 for(int i=0; i<(byte_size/8)+1; i++) fixData[i] = data[i];
    //Big Endian
    if(mode==0){
        if((byte_size%8) == 1)      fixData[data_size-1] = (fixData[data_size-1]<<56);
        else if((byte_size%8) == 2) fixData[data_size-1] = (fixData[data_size-1]<<48);
        else if((byte_size%8) == 3) fixData[data_size-1] = (fixData[data_size-1]<<40);
        else if((byte_size%8) == 4) fixData[data_size-1] = (fixData[data_size-1]<<32);
        else if((byte_size%8) == 5) fixData[data_size-1] = (fixData[data_size-1]<<24);
        else if((byte_size%8) == 6) fixData[data_size-1] = (fixData[data_size-1]<<16);
        else if((byte_size%8) == 7) fixData[data_size-1] = (fixData[data_size-1]<< 8);
    }
    //Make Message Block
    return makeMessage64(fixData, byte_size, mode);
}
