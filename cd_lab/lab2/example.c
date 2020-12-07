#include<stdio.h>
#include<stdlib.h>
int main()
{
	printf("this is a sample program \n");
	int k = 5;
	while(k--)
	{
		printf("%d \n", k);
		if(k == 2)
		{
			break;
		}
	}
	return 0;
}