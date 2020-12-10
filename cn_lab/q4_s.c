#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<netdb.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<time.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/wait.h>
#include<signal.h>
#define PORT 8080

void servfunc(int sockfd)
{
	char ttime[100], buff[100];
	int process_id;
	while(1)
	{
		read(sockfd, buff, sizeof(buff));
		process_id = getpid();
		write(sockfd, &process_id, sizeof(process_id));
		time_t raw_time;
		struct tm* timeinfo;
		time(&raw_time);
		timeinfo = localtime(&raw_time);
		strcpy(ttime, asctime(timeinfo));
		write(sockfd, ttime, sizeof(ttime));
	}	
}


int main()
{
	int sockfd, connfd;
	unsigned int len;
	struct sockaddr_in server, client;
	// create and verify socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0); //tcp
	if(sockfd == -1)
	{
		printf("creation failed \n");
		exit(0);
	}
	else
	{
		printf("creation successful \n");
	}
	
	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(PORT);
	
	// binding and verification
	if(bind(sockfd, (struct sockaddr*)&server, sizeof(server)) != 0)
	{
		printf("socket binding failed \n");
	}
	else
	{
		printf("socket successfully binded \n");
	}
	
	// server ready to listen
	if(listen(sockfd, 5) != 0)
	{
		printf("listening failed \n");
	}
	else
	{
		printf("server now listening \n");
	}
	
	len = sizeof(client);
	
	// accept packet from client
	connfd = accept(sockfd, (struct sock_addr*)&client, &len);
	if(connfd < 0)
	{
		printf("accept failed \n");
		exit(0);
	}
	else
	{
		printf("server has accepted the client \n");
	}
	servfunc(connfd);
	close(sockfd);
}
