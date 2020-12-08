// LAB1, Q1
// 
// Aadi Shantanu Deshpande
// 180905402
// A - 46 (B2)

//Write a UDP client-server program where client sends rows of a matrix to the server combines
//them together as a two dimensional matrix and display the same.

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


	// receive the number of rows and columns from the client
	int dim[2];
	len = sizeof(client);
	n = recvfrom(servsockfd, dim, sizeof(dim),0, (struct sockaddr*)&client, &len);
	printf("the dimensions of the matrix are: %d * %d \n", dim[0], dim[1]);

	// receive the actual matrix from the client
	int row = dim[0];
	int col = dim[1];
	int matrix[row][col];

	for(int i = 0; i < row; i++)
	{
		n = recvfrom(servsockfd, matrix[i], sizeof(matrix), 0, (struct sockaddr*)&client, &len);
	}

	// now we print the matrix
	printf("the matrix is: \n");
	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < col; j++)
		{
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}

	// echo the datagram back to the client
	//sendto(servsockfd, dim, n, 0, (struct sockaddr*)&client, sizeof(client));
	getchar();

	close(servsockfd);

}