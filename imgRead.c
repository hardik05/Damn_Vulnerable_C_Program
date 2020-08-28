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
	struct Image img;

	fp = fopen(filename,"r");            //Statement   1

	if(fp == NULL)
	{
		printf("\nCan't open file or file doesn't exist.");
		exit(0);
	}

	printf("\n\tHeader\twidth\theight\tdata\t\r\n");

	while(fread(&img,sizeof(img),1,fp)>0){
		printf("\n\t%s\t%d\t%d\t%s\r\n",img.header,img.width,img.height,img.data);

		//integer overflow 0x7FFFFFFF+1=0
		//0x7FFFFFFF+2 = 1
		//will cause very large/small memory allocation.
		int size1 = img.width + img.height;
		char* buff1=(char*)malloc(size1);

		//heap buffer overflow
		memcpy(buff1,img.data,sizeof(img.data));
		free(buff1);
		//double free	
		if (size1/2==0){
			free(buff1);
		}
		else{
			//use after free
			if(size1 == 123456){
				buff1[0]='a';
			}
		}


		//integer underflow 0-1=-1
		//negative so will cause very large memory allocation
		int size2 = img.width - img.height+100;
		//printf("Size1:%d",size1);
		char* buff2=(char*)malloc(size2);

		//heap buffer overflow
		memcpy(buff2,img.data,sizeof(img.data));

		//divide by zero
		int size3= img.width/img.height;
		//printf("Size2:%d",size3);

		char buff3[10];
		char* buff4 =(char*)malloc(size3);
		memcpy(buff4,img.data,sizeof(img.data));

		//OOBR read bytes past buffer
		char OOBR = buff3[size3];

		//OOBW write bytes past buffer
		buff3[size3]='c';

		if(size3>10){
			//memory leak here
			buff4=0;
		}
		else{
			free(buff4);
		}

		free(buff2);


	}
	fclose(fp);


}

int main(int argc,char **argv)
{
	ProcessImage(argv[1]);


}
