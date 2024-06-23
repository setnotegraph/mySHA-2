/*
	Author: setnotegraph
	Status: done
*/

/*SHA256.h*/

// Prevent duplication header files
#ifndef mySHA256_H
#define mySHA256_H
// Prevent duplication header files
#pragma once

// Define Functions
unsigned int rol(unsigned int x, int n);
unsigned int ror(unsigned int x, int n);

unsigned int mySHA256ch(unsigned int x, unsigned int y, unsigned int z);
unsigned int mySHA256maj(unsigned int x, unsigned int y, unsigned int z);

unsigned int mySHA256fS0(unsigned int x);
unsigned int mySHA256fS1(unsigned int x);
unsigned int mySHA256fs0(unsigned int x);
unsigned int mySHA256fs1(unsigned int x);

unsigned int conv(unsigned int x);
unsigned int mySHA256(unsigned *M, int src_size, unsigned *O);

//Temp


#endif
