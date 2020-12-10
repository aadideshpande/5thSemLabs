#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

/*
S -> a | > | (T)
T -> T,S | S

after removing left recursion

S -> a | > | (T)
T -> ST'
T' -> ,ST'|eps

*/



int curr = 0;
char str[100];

void S();
void T();
void T_prime();

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
	}
	else if(str[curr] == '>')
	{
		curr++;
	}
	else if(str[curr] == '(')
	{
		curr++;
		T();
		if(str[curr] == ')')
		{
			curr++;
		}
	}
}

void T()
{
	//T -> ST'
	S();
	T_prime();
}

void T_prime()
{
	//T' -> ,ST'|eps
	if(str[curr] == ',')
	{
		curr++;
		S();
		T_prime();
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