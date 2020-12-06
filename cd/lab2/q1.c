// remove all the tabs and blank spaces from the file
#include<stdio.h>
#include<stdlib.h>
int main()
{
	FILE *f1, *f2;
	char c;
	
	f1 = fopen("ip.txt", "r");
	f2 = fopen("op.txt", "w");
	
	while(c != EOF)
	{
		c = getc(f1);
		if(c == ' ')
		{
			putc(c, f2);
			c = getc(f1);
			while(c == ' ')
			{
				c = getc(f1);
			}	
			putc(c, f2);
		}
		else if(c == '\t')
		{
			continue;
		}
		else
		{
			putc(c, f2);
		}
		
	}
	
	fclose(f1);
	fclose(f2);
	return 0;
}
