// remove single and multiline comments from the .c program
#include<stdio.h>
#include<stdlib.h>

int main()
{
	FILE *fa, *fb;
	char ca, cb;
	
	fa = fopen("hello.c", "r");
	
	if(fa == NULL)
	{
		printf("cannot open file \n");
		exit(0);
	}
	
	fb = fopen("answer.c", "w");
	ca = getc(fa);
	
	while(ca != EOF)
	{
		if(ca == ' ')
		{
			putc(ca, fb);	// if only single space present
			
			while(ca == ' ')
			{
				ca = getc(fa);
			}	
		}
		
		if(ca == '/')
		{
			cb = getc(fa);
			if(cb == '/') // single line comment
			{
				while(ca != '\n')
				{
					ca = getc(fa);
				}
			}
			else if(cb == '*') // for multiline comment
			{
				do
				{
					while(ca != '*')
					{
						ca = getc(fa);
					}
					ca = getc(fa);
				}while(ca != '/');
			}
			else
			{
				putc(ca, fb);
				putc(cb,  fb);
			}
		}
		else
		{
			putc(ca, fb);
		}
		ca = getc(fa);
	}
	
	fclose(fa);
	fclose(fb);
	return 0;
}
