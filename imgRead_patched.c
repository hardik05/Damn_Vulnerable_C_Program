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
	unsigned int width;
	unsigned int height;
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
		unsigned int size1 = img.width + img.height;
		if(size1>0xFFFF)
		{
			printf("Error!Large value of size1 detected!");
			return 0;
		}

		char* buff1=(char*)malloc(size1);
		if(buff1==NULL)
		{
			printf("error! buffer alocation failed!");
			return 0;
		}
		if(sizeof(img.data)> size1)
		{
			printf("Error!, not eough memory to copy data");
			return 0;
		}
		//heap buffer overflow
		memcpy(buff1,img.data,sizeof(img.data));
		free(buff1);
		buff1=NULL;

		//double free	
		if (size1/2==0){
			free(buff1);
		}
		else{
			//use after free
			if(size1/3 == 0){
				if(buff1==NULL){
					printf("Error! Buffer is already freed!");
						return 0;

				}
				else
				{
					buff1[0]='a';
				}
			}
		}


		//integer underflow 0-1=-1
		//negative so will cause very large memory allocation
		unsigned int size2 = img.width - img.height+100;
		//printf("Size1:%d",size1);
		char* buff2=(char*)malloc(size2);
		if(buff2==NULL)
		{
			printf("Error! Memory allocation failed!");
			return 0;
		}
		if(sizeof(img.data)>size2)
		{
			printf("Errr!, not enugh emmory to copy data!");
			return 0;
		}

		//heap buffer overflow
		memcpy(buff2,img.data,sizeof(img.data));

		//divide by zero
		if(img.height==0)
		{
			printf("Error! Image Height is zero!");
			return 0;
		}

		int size3= img.width/img.height;
		//printf("Size2:%d",size3);

		char buff3[10];
		char* buff4 =(char*)malloc(size3);
		if(buff4==NULL)
		{
			printf("Error!, Memory allocation failed.");
			return 0;
		}
		if(sizeof(img.data) >size3){
			printf("Error!, not enouggh memoy to copy data!");
			return 0;
		}
		memcpy(buff4,img.data,sizeof(img.data));

		//OOBR read bytes past stack/heap buffer
		if(size3>9)
		{
			printf("Error! memory acess beynd allowed size detected!");
			return 0;
		}

		else
		{
			char OOBR = buff3[size3];
			buff3[size3]='c';

		}
		int size4 = size3+100;
		if(size4> size3)
		{
			printf("Error! memory acess beyond alowed size detected!");
			return 0;
		}
		else
		{
			char OOBR_heap = buff4[size4];
			buff4[size4]='c';

		}

		//OOBW write bytes past stack/heap buffer

		if(size3>10){
			//memory leak here
			free(buff4);
			buff4=0;
		}
		else{
			free(buff4);
		}

		free(buff2);
		//}
		//else
		//	printf("invalid header\r\n");

	}
	fclose(fp);

	return 0;
}

int main(int argc,char **argv)
{
	ProcessImage(argv[1]);

}
