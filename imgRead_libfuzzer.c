/*
Author: Hardik Shah
Email: hardik05@gmail.com
Web: http://hardik05.wordpress.com
*/

//a vulnerable C program to explain common vulnerability types
//fuzz with libfuzzer

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
struct Image
{
	char header[4];
	int width;
	int height;
	char data[10];
};

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size){
if(size<=12){
return 0;
}
	struct Image *img;
	img = (struct Image*)data;
		//integer overflow 0x7FFFFFFF+1=0
		//0x7FFFFFFF+2 = 1
		//will cause very large/small memory allocation.
		int size1 = img->width + img->height;
		char* buff1=(char*)malloc(size1);

		//heap buffer overflow
		memcpy(buff1,img->data,sizeof(img->data));
		free(buff1);
		//double free	
		if (size1/3==0){
			free(buff1);
		}
		else{
			//use after free
			if(size1/20 == 0){
				buff1[0]='a';
			}
		}


		//integer underflow 0-1=-1
		//negative so will cause very large memory allocation
		int size2 = img->width - img->height+100;
		//printf("Size1:%d",size1);
		char* buff2=(char*)malloc(size2);

		//heap buffer overflow
		memcpy(buff2,img->data,sizeof(img->data));

		//divide by zero
		int size3= img->width/img->height;
		//printf("Size2:%d",size3);

		char buff3[10];
		char* buff4 =(char*)malloc(size3);
		memcpy(buff4,img->data,sizeof(img->data));

		//stack OOBR read bytes past buffer
		char OOBR_stack = buff3[size3];

		char OOBR_heap = buff4[size1];

		//stack OOBW write bytes past buffer
		buff3[size3]='c';
		buff4[size1]='c';

		if(size3/5==0){
			//memory leak here
			buff4=0;
		}
		else{
			free(buff4);
		}

		free(buff2);


}

