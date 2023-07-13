/*
Author: Hardik Shah
Email: hardik05@gmail.com
Web: http://hardik05.wordpress.com
https://www.geeksforgeeks.org/socket-programming-cc/
*/

//a vulnerable c program to explain common vulnerability types
//fuzz with AFL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include<unistd.h>	//write

#include<pthread.h> //for threading , link with lpthread

//structure which holds our data
struct Image
{
	char header[4];
	int width;
	int height;
	char data[10];
};
int ProcessImage(char *buffer, size_t size);

int SetupServer(){
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
	char *hello = "Hello from server";

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
				&opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( 31337 );

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr *)&address, 
				sizeof(address))<0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
					(socklen_t*)&addrlen))<0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}
	valread = read( new_socket , buffer, 1024);
	printf("%s\n",buffer );
	ProcessImage(buffer,valread);
	return 0;
}

int ProcessImage(char* buffer, size_t size){
	if(size<=12){
		return 0;
	}

	struct Image *img;
	img = (struct Image*)buffer;



	printf("\n\tHeader\twidth\theight\tdata\t\r\n");

	printf("\n\t%s\t%d\t%d\t%s\r\n",img->header,img->width,img->height,img->data);


	//integer overflow 0x7FFFFFFF+1=0
	//0x7FFFFFFF+2 = 1
	//will cause very large/small memory allocation.
	int size1 = img->width + img->height;
	char* buff1=(char*)malloc(size1);

	//heap buffer overflow
	memcpy(buff1,img->data,sizeof(img->data));
	free(buff1);
	//double free	
	if (size1/2==0){
		free(buff1);
	}
	else{
		//use after free
		if(size1/3 == 0){
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

	//OOBR read bytes past stack/heap buffer
	char OOBR = buff3[size3];
	char OOBR_heap = buff4[size3];

	//OOBW write bytes past stack/heap buffer
	buff3[size3]='c';
	buff4[size3]='c';

	if(size3>10){
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
	//ProcessImage(argv[1]);
	SetupServer();

}
