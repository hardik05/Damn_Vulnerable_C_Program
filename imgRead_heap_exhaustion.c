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
		printf("\nCan't open file or file doesn't exist.\r\n");
		exit(0);
	}


	while(fread(&img,sizeof(img),1,fp)>0)
	{
		//if(strcmp(img.header,"IMG")==0)
		//{
		printf("\n\tHeader\twidth\theight\tdata\t\r\n");

		printf("\n\t%s\t%d\t%d\t%s\r\n",img.header,img.width,img.height,img.data);


		//integer overflow 0x7FFFFFFF+1=0
		//0x7FFFFFFF+2 = 1
		//will cause very large/small memory allocation.
		int size1 = img.width + img.height;
		char *buff1;
		if(size1/2==0){
			do{
				buff1=(char*)malloc(size1);
			}while(buff1);
		}
	}
	return 0;
	}

	int main(int argc,char **argv)
	{
		ProcessImage(argv[1]);
		return 0;
	}
