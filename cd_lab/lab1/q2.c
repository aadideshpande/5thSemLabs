// remove the preprocessor directives from the given input C file


#include<stdio.h>
#include<stdlib.h>
int main()
{
	FILE *fptr1, *fptr2;
	char filename[100], c;
	printf("enter the input file name: \n");
	scanf("%s", filename);
	fptr1 = fopen(filename, "r");

	if(fptr1 == NULL)
	{
		printf("file not found \n");
		exit(0);
	}

	printf("enter the output file name: \n");
	scanf("%s", filename);
	fptr2 = fopen(filename, "w+");

	char ca = getc(fptr1), cb;
	while(ca != EOF)
	{
		if(ca == '#')
		{
			//ca = getc(fptr1);
			while(ca != EOF && ca != '\n')
			{
				ca = getc(fptr1);
				//printf("inside loop 1\n");
			}
			ca = getc(fptr1);
			//printf("after loop 1\n");
			if(ca == EOF)
			{
				break;
			}
		}
		else
		{
			do
			{
				putc(ca, fptr2);
				ca = getc(fptr1);
				//printf("inside loop2\n");
				if(ca == EOF)
				{
					break;
				}
			}while(ca != '\n');
		}
		//ca = getc(fptr1);
	}
	printf("program done \n");
	fclose(fptr1);
	fclose(fptr2);

	return 0;
}