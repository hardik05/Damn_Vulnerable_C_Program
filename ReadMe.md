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

**How to generate input for AFL?**

just create a sample input file as following and rest AFL will take care:

echo "IMG" >input/1.txt

AFL will automatically generate new test cases and discover most of the vulnerabilities mentioned above. thats the beauty of AFL :)

**Why you created this?**

It takes lot of time for new comers and even experianced people to understand different types of vulnerabilities. i have faced this problem myself and decided to share what i learned.
If you learn something from it, send me a thnak you note. that all i need.

**Author?**

**Email:** hardik05@gmail.com

**web:** http://hardik05.wordpress.com


**Feedback?**

suggestions and comments are always welcomed. if you find any issue or have a fix or a new feature send pull request.

