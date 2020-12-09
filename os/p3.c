#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
int main(int argc, char* argv[])
{
	char ch = 'A';
	char* name = "John";
	char age = 25;
	float height = 6.2;
	printf("char = %c, string = %s, int = %d, float = %f \n",ch, name, age, height);
	printf("hex for INT: %x \n", age);
	errno = EPERM;
	printf("error is: %m \n");
}	
