#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

/*
S -> UVW
U -> (S) | aSb | d
V -> aV | eps
W -> cW | eps
*/



int curr = 0;
char str[100];

void S();
void U();
void V();
void W();

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
	U();
	V();
	W();
}

void U()
{
	if(str[curr] == '(')
	{
		curr++;
		S();
		if(str[curr] == ')')
		{
			curr++;
		}
		else
		{
			invalid();
			exit(0);
		}
	}
	else if(str[curr] == 'a')
	{
		curr++;
		S();
		if(str[curr] == 'b')
		{
			curr++;
		}
		else
		{
			invalid();
			exit(0);
		}
	}
	else if(str[curr] == 'd')
	{
		curr++;
	}
	else
	{
		invalid();
		exit(0);
	}
}
void V()
{
	if(str[curr] == 'a')
	{
		curr++;
		V();
	}
}

void W()
{
	if(str[curr] == 'c')
	{
		curr++;
		W();
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