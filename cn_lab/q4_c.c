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
#define MAX 80

void clifunc(int sockfd)
{
	int process_id;
	char ttime[100], buff[100];
	while(1)
	{
		strcpy(buff, "hey ");
		write(sockfd, buff, sizeof(buff));
		read(sockfd, &process_id, sizeof(process_id));
		read(sockfd, ttime, sizeof(ttime));
		printf("from server: process_id: %d, time: %s \n", process_id, ttime);
	}
}

int main()
{
	int sockfd, connfd;
	struct sockaddr_in server, client;
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
	{
		printf("creation failed \n");
		exit(0);
	}
	
	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(PORT);
	
	if(connect(sockfd, (struct sock_addr*)&server, sizeof(server)) != 0)
	{
		printf("connecting to server failed \n");
		exit(0);
	}
	
	clifunc(sockfd);
	close(sockfd);
}
