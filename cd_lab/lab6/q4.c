#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

/*
S -> (L) | a
L -> L,S | s

S -> (L) | a
L -> sL'
L' -> ,SL' | eps

*/



int curr = 0;
char str[100];

void S();
void L();
void L_prime();

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
	if(str[curr] == '(')
	{
		curr++;
		L();
		if(str[curr] == ')')
		{
			curr++;
		}
	}
	else if(str[curr] == 'a')
	{
		curr++;
	}
}

void L()
{
	//L -> sL'
	//L' -> ,SL' | eps
	if(str[curr] == 's')
	{
		curr++;
		L_prime();
	}
}

void L_prime()
{
	if(str[curr] == ',')
	{
		curr++;
		S();
		L_prime();
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
	{
		invalid();
	}
}