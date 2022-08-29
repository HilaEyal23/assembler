# *assembler*

*The final project of the C course (20465) at The Open University.<br />
Note: the computer model for this project and the given assembly language are imaginary.*

### *Double Pass Model:*
*The assembler is based on three steps: preprocess and two passes: <br />
**Preprocessor** - replaces macros with the corresponding code fragments. <br />
**First Pass** - parses the input and detectes syntax errors. <br />
**Second Pass** - encodes the parsed lines in binary (according to the following method) and converts it to 32 base (more details below). At the end it outputs .ob file and .ext \ .ent files if there are .extern and .entry declaretions.* 

### *The Computer Hardware:*
*The computer in this project consists of a processor (a CPU), 8 registers, and RAM (Random Access Memory).
A word's size in memory is 10 bits. The RAM size is 256 words while part of the memory is used as a stack. In addition, each register stores a single word.
The computer works with integers, both positive and negative. There is no support for real numbers. Arithmetically, it works using the 2's completement method, and it supports characters that are represented in ascii code.*


### *Encoding Method:*
*There are two main types of lines which encodes words: instructions and directives. <br /> <br />
**Instructions Encoding:** <br />
Each instruction usualy encodes a few word to the memory in the range of 1 to 4, while the first word consists of command and operands adderssing methods and the following words relates to the operands. <br />
The first word sructure is as the following:*

| opcode        | src addressing method | dest addressing method | A,R,E  |
| :-------------: |:-------------:|:-------------:| -----:|
| 9 - 6 | 5 - 4 | 3 - 2  | 1 - 0 |

*command's opcode: <br />*
| opcode (decimal)        | command |
| :-------------: |:-------------:|
| 0        | mov |
| 1        | cmp |
| 2        | add |
| 3        | sub |
| 4        | not |
| 5        | clr |
| 6        | lea |
| 7        | inc |
| 8        | dec |
| 9        | jmp |
| 10       | bne |
| 11       | get |
| 12       | prn |
| 13       | jsr |
| 14       | rts |
| 15       | hlt |

*addressing methods: <br />*
| method's number (decimal)        | method's name |
| :-------------: |:-------------:|
| 0        | immediate |
| 1        | drect |
| 2        | relative |
| 3        | struct |

*A, R, E: <br />*
| method's number (decimal)        | method's name |
| :-------------: |:-------------:|
| 0        | Absolute |
| 1        | Relocate |
| 2        | External |

*<br /> <br />
 **Directives Encoding:** <br /> 
 There are 5 main types of directives: .data, .string, .struct, .entry and .extern. <br /> <br />
 **.data** is a declaration of integers array. Each integer encodes a single word to the memory according to the following structure: <br />*
 
 | value (binary) | A,R,E |
| :-------------: |:-------------:|
| 9 - 2 | 1 - 0 |

*<br />
**.string** is a declaration of characters array. Each charcter encodes a single word to the memory according to the following structure: <br />*
 
 | ascii code (binary) | A,R,E |
| :-------------: |:-------------:|
| 9 - 2 | 1 - 0 |

*In addition, each string encodes '\0' at it's end, which is acctualy 0-word. <br />*
*<br />
**.struct** is a declaration of struct. Each structure consist of two fields: a number and a string. The declaration ".struct" encodes to the memory a single integer word (as described above) and a string sequence of words (described above as well). <br />*

*<br />
**.entry** is a declaration of a lable which is defined in the currend file but may be used in anothers. Entry declaretion does not encodes to the memory but does make the program output `.ent` file as well. <br />*

*<br />
**.extern** is a declaration of a label which isn't defined in the currend file but in diffrent one. Extern declaretion does not encodes to the memory but does make the program output `.ext` file as well <br />*

*<br />*
### *32 Base:*
 
 *As mentioned above, the final output files are written in 32-Base. The converting is according to the following table: <br />*
| decimal       | 32 Base |
| :-------------: |:-------------:|
| 0        | ! |
| 1        | @ |
| 2        | # |
| 3        | $ |
| 4        | % |
| 5        | ^ |
| 6        | & |
| 7        | * |
| 8        | < |
| 9        | > |
| 10       | a |
| 11       | b |
| 12       | c |
| 13       | d |
| 14       | e |
| 15       | f |


### *How To Use?*
*First downlode the project and make some assembly files with an `.as` extension. Then open the terminal and use the commans "make" in order to complie the project:*
```C
> make
```
*<br /> Once compilation succseed, you may run the program on your assembly files by using this command in the terminal:*
```C
> ./assembler fileName
```
*In case you want to run more than one file, you may write:*
```C
> ./assembler fileName1 fileName2 fileName3
```
*Note: `.as` is **not** a part of the file's name.*

*If everything went well, `.am` and `.ob` files will appeare to each file you gave the program. The `.am` file is the preprocessed file and the `.ob` file is the assemblered file. Otherwise, errors should be printed due the standart output. <br />
<br />Note: there is a limitation on line's length, if you get "core dumped" you better check you haven't crossed the limit. Moreover "core dumped" may appraer in case the given file wasn't found*
