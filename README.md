# mySHA-2
This repository is my SHA-2 implementation.

## Status: undone

## probrem
If String is nothing, causes segmentation fault.

"""bash
./mySHA2 [SHA***] [-f] ["Nothing"]
"""

## Functions
* string2messageblock
* mySHA224
* mySHA256
* mySHA384
* mySHA512
* mySHA512/224
* mySHA512/256

## string2messageblock
Input : char array  
Output: 256*n or 512*n padding message block

## mySHA224
Input : 256*n bit message block  
Output: 224 bit message digest

## mySHA256
Input : 256*n bit message block  
Output: 256 bit message digest

## mySHA384
Input : 512*n bit message block  
Output: 384 bit message digest

## mySHA512
Input : 512*n bit message block  
Output: 512 bit message digest

## mySHA512/224
Input : 512*n bit message block  
Output: 224 bit message digest

## mySHA512/256
Input : 512*n bit message block  
Output: 256 bit message digest

## How to use
```shell
./mySHA2 "SHA***" "~"
```
