# mySHA-2
This repository is my SHA-2 implementation.

## Status
|Target       |Status|
|:------------|:----:|
|ALL SHA-2    |X     |
|SHA-256      |O     |
|SHA-512      |X     |
|SHA-224      |X     |
|SHA-384      |X     |
|SHA-512/224  |X     |
|SHA-512/256  |X     |
|Handle File  |X     |
|Handle String|O     |
|No Defects   |X     |

## Probrem
If String is nothing, causes segmentation fault.

```bash
./mySHA2 [SHA***] [-f] ["Nothing"]
```

## Functions
* string2messageblock
* mySHA224
* mySHA256
* mySHA384
* mySHA512
* mySHA512/224
* mySHA512/256

### string2messageblock
Input : char array  
Output: 256*n or 512*n padding message block

### mySHA224
Input : 256*n bit message block  
Output: 224 bit message digest

### mySHA256
Input : 256*n bit message block  
Output: 256 bit message digest

### mySHA384
Input : 512*n bit message block  
Output: 384 bit message digest

### mySHA512
Input : 512*n bit message block  
Output: 512 bit message digest

### mySHA512/224
Input : 512*n bit message block  
Output: 224 bit message digest

### mySHA512/256
Input : 512*n bit message block  
Output: 256 bit message digest

### How to use
```shell
./mySHA2 [SHA***] [option] [file or string]
```
