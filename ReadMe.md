**What it is?**

This is a simple C program, i coded to explain common types of vulnerabilities like:
1. integer overflow
2. integer underflow
3. Out of bound Read
4. Out of bound Write
5. Double Free
6. Use After Free
7. Memory leaks

This C program contains vulenrable code of all of the above vulnerabilities and then users can fuzz it using AFL or hongfuzz or anything else they want. 

**How to Compile **

just type "make" on the command prompt. Makefile is included with it.

**How to generate input for AFL?**

just create a sample input file as following and rest AFL will take care:

echo "IMG" >input/1.txt

AFL will automatically generate new test cases and discover most of the vulnerabilities mentioned above. thats the beauty of AFL :)

**How to fuzz it using AFL?**

**run this command:** afl-fuzz -i input -o output -m none -- ./imgRead @@

you can see the video tutorials here:

**Linux**

**[Fuzzing with AFL] How to install AFL on Ubuntu**-> https://www.youtube.com/watch?v=r7ucv2kN4j4

**[Fuzzing with AFL] Fuzzing a simple C program with AFL** -> https://www.youtube.com/watch?v=NiGC1jxFx78&t=66s

**[Fuzzing with AFL] Finding different types of vulnerabilities with AFL** -> https://www.youtube.com/watch?v=m1RkShHzx_8&t=151s

**[Fuzzing with AFL] Triaging crashes with crashwalk and finding root cause with GDB** -> https://www.youtube.com/watch?v=5R2gPkCXZkM

**[Fuzzing with honggfuzz] Fuzzing a simple C program with HongFuzz** -> https://www.youtube.com/watch?v=6OBXJtEe-d8
**[Fuzzing with honggfuzz] Hongfuzz,checksec(pwntools),ASAN** -> https://www.youtube.com/watch?v=Lr8pLQRTHac 

**Windows**
**[Fuzzing with WinAFL] Fuzzing a simple C program with WinAFL** -> https://www.youtube.com/watch?v=Va_Wtxf3DMc
**[Fuzzing with WinAFL] What is a fuzzing function, how to make sure everything is working fine?** -> https://www.youtube.com/watch?v=HLORLsNnPzo

more will be uploaded as i create them.


**Why you created this?**

It takes lot of time for new comers and even experianced people to understand different types of vulnerabilities. i have faced this problem myself and decided to share what i learned.

If you learn something from it, send me a thnak you note. thats all i need.

**Author?**

**Twitter:** https://twitter.com/hardik05 

**Email:** DM me on twitter :)

**web:** http://hardik05.wordpress.com


**Feedback?**

suggestions and comments are always welcomed. if you find any issue or have a fix or a new feature send pull request.

