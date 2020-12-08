// client side of the udp

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#define PORT 5000
#define MAXLINE 1000

int main()
{
	char buffer[100];
	char *message = "hello user";
	struct sockaddr_in server, client;
	int sockfd, n;
	unsigned int len;

	bzero(&server, sizeof(server));

	//create UDP socket 
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(PORT);
	server.sin_family = AF_INET;

	// bind the server addr. to the socket descriptor
	bind(sockfd, (struct sockaddr*)&server, sizeof(server));


	// sending the data to the server
	sendto(sockfd, message, MAXLINE, 0, (struct sockaddr*)&server, sizeof(server));
	len = sizeof(client);

	// get the data back from the server
	n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&client, &len);
	buffer[n] = '\0';
	printf("message sent was : %s \n", buffer);
	getchar();

	close(sockfd);

}