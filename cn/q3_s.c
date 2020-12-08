// server side program
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include<ctype.h>
int main()
{
	int sd,nd,n,reult;
	unsigned int len;
	struct sockaddr_in seraddress, cliaddr;
	char buf[256];
	sd=socket(AF_INET, SOCK_STREAM,0);seraddress.sin_family=AF_INET;
	seraddress.sin_addr.s_addr=INADDR_ANY;
	seraddress.sin_port=htons(10200);
	bind(sd,(struct sockaddr*)&seraddress,sizeof(seraddress));
	listen(sd,5);
	len=sizeof(cliaddr);
	while(1)
	{
		int x, y;
		char op;
		nd=accept(sd,(struct sockaddr*)&cliaddr,&len);
		if (fork()==0)
		{
			close(sd);
		}
		n=read(nd,x,sizeof(x));
		n = read(nd, y, sizeof(y));
		n = read(nd, op, sizeof(op));

		printf("message from client %d %c %d \n",x, op, y);
		//getchar();
	
	}
	close(nd);
}