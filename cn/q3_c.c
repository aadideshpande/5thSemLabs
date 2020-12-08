// client program
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
	int sd,nd,n,len,reult,n1;
	struct sockaddr_in seraddress, cliaddr;
	char buf[256], buf1[256];
	sd=socket(AF_INET, SOCK_STREAM,0);
	seraddress.sin_family=AF_INET;
	seraddress.sin_addr.s_addr=INADDR_ANY;
	seraddress.sin_port=htons(10200);
	len=sizeof(seraddress);
	connect(sd,(struct sockaddr*)&seraddress,len);

	int a, b;
	printf("enter 2 numbers: \n");
	scanf("%d %d", &a, &b);
	char op;
	printf("enter the operator: \n");
	scanf("%c", &op);

	int ans
	n = write(sd,a,sizeof(a));
	n = write(sd, b, sizeof(b));
	n = write(sd, c, sizeof(c));
	n1=read(sd,ans,sizeof(ans));
	printf("message from server %d \n",ans);
	getchar();
}