// lab1 q2

//Write a TCP client which sends a string to a server program. Server displays the string along with
//client IP and ephemeral port number. Server then responds to the client by echoing back the string
//in uppercase. The process continues until one of them types “QUIT”.
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include<unistd.h>
#include<ctype.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void clifunc(int sockfd)
{
	char buff[MAX];
	int n;
	for (;;) 
	{
		bzero(buff, sizeof(buff));
		printf("Enter the string : ");
		n = 0;
		while ((buff[n++] = getchar()) != '\n');
		if ((strncmp(buff, "quit", 4)) == 0) 
		{
			printf("Client Exit...\n");
			break;
		}
		write(sockfd, buff, sizeof(buff));
		bzero(buff, sizeof(buff));
		read(sockfd, buff, sizeof(buff));
		printf("From Server : %s", buff);
		if ((strncmp(buff, "quit", 4)) == 0) 
		{
			printf("Client Exit...\n");
			break;
		}
	}
}
int main()
{
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;
	// socket create and verification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) 
	{
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));
	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	/*
	// connect the client socket to server socket
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) 
	{
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("connected to the server..\n");
	*/
	connect(sockfd, (SA*)&servaddr, sizeof(servaddr));
	clifunc(sockfd);
	// function for clientclifunc(sockfd);
	// close the socket
	close(sockfd);
}
