#**************************************
#dman vulnerable imageReader
#Author: hardik shah
#email: hardik05@gmail.com
#website: http://hardik05.wordpress.com
#**************************************
 
 CC=afl-gcc  #compiler
 TARGET=imgRead #target file name
  
all:
	   AFL_HARDEN=1 $(CC) -fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined imgRead.c -o $(TARGET)
	     
clean:
	    rm $(TARGET)
