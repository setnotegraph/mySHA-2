/*
	Author: setnotegraph
	Status: done
*/

/*SHA256.h*/
// Prevent duplication header files
#ifndef mySHA2gen_H
#define mySHA2gen_H
// Prevent duplication functions
#pragma once

// Define Fucntions

unsigned *makeMessage32(unsigned *data, int byte_size, int mode);
unsigned *string2message32(char *str, int str_size, int mode);
unsigned *data2message32(unsigned *data, unsigned byte_size, int mode);

unsigned long long *makeMessage64(unsigned long long *data, int byte_size, int mode);
unsigned long long *string2message64(char *str, int str_size, int mode);
unsigned long long *data2message64(unsigned long long *data, unsigned byte_size, int mode);


unsigned int mySHA2message32();
unsigned long long mySHA2message64();


#endif
