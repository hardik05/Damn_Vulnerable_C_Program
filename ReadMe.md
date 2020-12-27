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

`echo "IMG" >input/1.txt`

AFL will automatically generate new test cases and discover most of the vulnerabilities mentioned above. thats the beauty of AFL :)

**How to fuzz it using AFL?**

**1. First compile this program using following command:**

`afl-gcc -g -fsanitize=address imgRead.c -o imgread`

**2. run this command:** 

`afl-fuzz -i input -o output -m none -- ./imgRead @@`

**How to fuzz it using honggfuzz**

**1. First compile this program using following command:**

`hfuzz-gcc -g -fsanitize=address imgRead.c -o imgread`

**2. run this command:** 

`hongfuzz -i input -- ./imgread ___FILE___`

 **How to fuzz using libfuzzer**
 
You need to modify the C code, you can get the updated code from here: https://github.com/hardik05/Damn_Vulnerable_C_Program/blob/master/imgRead_libfuzzer.c

**1. Compile the program using following command:**

`clang -fsanitize=fuzzer,address,undefined -g imgRead_libfuzzer.c -o imgRead_libfuzzer`

**2. run this command to fuzz:

`./imgRead_libfuzzer`


you can see the video tutorials here:

**Complete Fuzzing Playlist:**

https://www.youtube.com/watch?v=r7ucv2kN4j4&list=PLHGgqcJIME5kYhOSdJjvtVS4b4_OXDqM-

individual videos below:

**Linux**

**AFL**

**[Fuzzing with AFL] How to install AFL on Ubuntu**-> https://www.youtube.com/watch?v=r7ucv2kN4j4

**[Fuzzing with AFL] Fuzzing a simple C program with AFL** -> https://www.youtube.com/watch?v=NiGC1jxFx78&t=66s

**[Fuzzing with AFL] Finding different types of vulnerabilities with AFL** -> https://www.youtube.com/watch?v=m1RkShHzx_8&t=151s

**[Fuzzing with AFL] Triaging crashes with crashwalk and finding root cause with GDB** -> https://www.youtube.com/watch?v=5R2gPkCXZkM

**Honggfuzz**

**[Fuzzing with honggfuzz] Fuzzing a simple C program with HongFuzz** -> https://www.youtube.com/watch?v=6OBXJtEe-d8

**[Fuzzing with honggfuzz] Hongfuzz,checksec(pwntools),ASAN** -> https://www.youtube.com/watch?v=Lr8pLQRTHac 

**Libfuzzer**

**[Fuzzing with libfuzzer] How to fuzz a simple C program using LibFuzzer** -> https://www.youtube.com/watch?v=hFva8kJQwnc&list=PLHGgqcJIME5m7HaHfACayoyN0TRe2PHRp

**[Fuzzing with libfuzzer,AFL] How to fuzz libfuzzer harness program using AFL** -> https://www.youtube.com/watch?v=HfEqm3TrfwM&list=PLHGgqcJIME5m7HaHfACayoyN0TRe2PHRp&index=2

**Radamsa**

**[Fuzzing with Radamsa] Fuzzing a simple C program with Radamsa** -> https://youtu.be/1FRsXVNpynQ

**Windows**

**WinAFL**

**[Fuzzing with WinAFL] Fuzzing a simple C program with WinAFL** -> https://www.youtube.com/watch?v=Va_Wtxf3DMc

**[Fuzzing with WinAFL] What is a fuzzing function, how to make sure everything is working fine?** -> https://www.youtube.com/watch?v=HLORLsNnPzo

**I need more windows harness to fuzz with winafl**

sure, check here -> https://github.com/hardik05/winafl-harness

**i want to try something different may be some different mutators than winafl default ones..**

yep, you can try this -> https://github.com/hardik05/winafl-powermopt

more will be uploaded as i create them.


**Why you created this?**

It takes lot of time for new comers and even experianced people to understand different types of vulnerabilities. i have faced this problem myself and decided to share what i learned.

If you learn something from it, send me a thnak you note. thats all i need.

**Author?**

**Twitter:** https://twitter.com/hardik05 

**Email:** DM me on twitter :)

**web:** http://hardik05.wordpress.com

**my youtube channel:** https://www.youtube.com/user/MrHardik05/featured?view_as=subscriber


**Feedback?**

suggestions and comments are always welcomed. if you find any issue or have a fix or a new feature send pull request.

