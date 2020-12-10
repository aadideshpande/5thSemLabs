#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

/*
S -> aAcBe
A -> Ab | b
B -> d

S -> aAcBe
A -> bA'
A' -> bA' | eps
B -> d

*/



int curr = 0;
char str[100];

void S();
void A();
void A_prime();
void B();

void invalid()
{
	printf("-----------------ERROR!----------------\n");
	exit(0);
}

void valid()
{
	printf("----------------SUCCESS!---------------\n");
	exit(0);
}


void S()
{
	if(str[curr] == 'a')
	{
		curr++;
		A();
		if(str[curr] == 'c')
		{
			curr++;
			B();
			if(str[curr] == 'e')
			{
				curr++;
			}
		}
	}
}

void A()
{
	//A -> bA'
	//A' -> bA' | eps
	if(str[curr] == 'b')
	{
		curr++;
		A_prime();
	}
}
void A_prime()
{
	if(str[curr] == 'b')
	{
		curr++;
		A_prime();
	}
}

void B()
{
	if(str[curr] == 'd')
	{
		curr++;
	}
}
int main()
{
	printf("Enter String: ");
	scanf("%s", str);
	S();
	if(str[curr] == '$')
	{
		valid();
	}
	else
	{// printf("%c\n", str[curr]);
		invalid();
	}
}