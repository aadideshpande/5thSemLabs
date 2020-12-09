// LAB1, Q1


//Write a UDP client-server program where client sends rows of a matrix to the server combines
//them together as a two dimensional matrix and display the same.
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
	int mat[100][100];
	int row, col;
	printf("enter the number of rows and columns:\n");
	scanf("%d %d", &row, &col);
	printf("enter the numbers of the matrix: \n");
	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < col; j++)
		{
			scanf("%d", &mat[i][j]);
		}
	}

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


	// sending the number of rows and columns to the server
	int matdata[2] = {row, col};
	sendto(sockfd, matdata, MAXLINE, 0, (struct sockaddr*)&server, sizeof(server));
	len = sizeof(client);

	// sending the actual matrix to the server
	for(int i = 0; i < row; i++)
	{
		sendto(sockfd, mat[i], MAXLINE, 0, (struct sockaddr*)&server, sizeof(server));
	}
	// get the data back from the server
	//n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&client, &len);
	//buffer[n] = '\0';
	//printf("message sent was : %s \n", buffer);
	getchar();

	close(sockfd);

}