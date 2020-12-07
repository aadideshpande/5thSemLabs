// remove blanks and tabs from the given file
// Aadi Shantanu Deshpande
// A - 46 (B2)
// 180905402

#include<stdio.h>
#include<stdlib.h>
int main()
{
	FILE *f1, *f2;
	char filename[100], c;
	printf("enter the input file name: \n");
	scanf("%s", filename);
	f1 = fopen(filename, "r");

	if(f1 == NULL)
	{
		printf("file not found \n");
		exit(0);
	}

	printf("enter the output file name: \n");
	scanf("%s", filename);
	f2 = fopen(filename, "w+");
	
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
			putc(' ', f2);
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