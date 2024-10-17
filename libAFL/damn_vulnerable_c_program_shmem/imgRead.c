/*
Author: Hardik Shah
Email: hardik05@gmail.com
Web: http://hardik05.wordpress.com
*/

//a vulnerable c program to explain common vulnerability types
//fuzz with AFL

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//shared memory testcase fuzzing
__AFL_FUZZ_INIT();
//end share memory testcase

struct Image
{
	char header[4];
	int width;
	int height;
	char data[10];
};


int ProcessImage(char* filename){
	FILE *fp;
	char ch;
	struct Image* img;
	int bufsize;

	//shared memory data will be inside buff
	unsigned char *shmem_buf = __AFL_FUZZ_TESTCASE_BUF;
	bufsize =strlen(shmem_buf); 
	if(bufsize<=12){
		return 0;
	}
	img = (struct Image*)shmem_buf;
	printf("input: %s\n", shmem_buf);


	//integer overflow 0x7FFFFFFF+1=0
	//0x7FFFFFFF+2 = 1
	//will cause very large/small memory allocation.
	int size1 = img->width + img->height;
	//		printf("%d",size1);
	//		abort();
	char* buff1=(char*)malloc(size1);

	//heap buffer overflow
	memcpy(buff1,img->data,sizeof(img->data));
	free(buff1);
	//double free	
	if (size1%3==0){
		free(buff1);
	}
	else{
		//use after free
		if(size1%2 == 0){
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

	if(size3%5==0){
		//memory leak here
		buff4=0;
	}
	else{
		free(buff4);
	}

	free(buff2);

	return 0;
}

int main(int argc,char **argv)
{
	ProcessImage(argv[1]);
}
