// server side of the udp
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#define PORT 5000
#define MAXLINE 1000

int main()
{
	char buffer[100];
	struct sockaddr_in server, client;
	int servsockfd, n;
	unsigned int len;

	bzero(&server, sizeof(server));

	//create UDP socket 
	servsockfd = socket(AF_INET, SOCK_DGRAM, 0);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(PORT);
	server.sin_family = AF_INET;

	// bind the server addr. to the socket descriptor
	bind(servsockfd, (struct sockaddr*)&server, sizeof(server));


	// receive the datagram
	len = sizeof(client);
	n = recvfrom(servsockfd, buffer, sizeof(buffer),0, (struct sockaddr*)&client, &len);
	buffer[n] = '\0';
	puts(buffer);

	// echo the datagram back to the client
	sendto(servsockfd, buffer, n, 0, (struct sockaddr*)&client, sizeof(client));
	getchar();

	close(servsockfd);

}