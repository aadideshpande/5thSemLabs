// count number of lines and characters in the file

#include<stdio.h>
#include<stdlib.h>
int main()
{
	FILE *fptr1;
	char filename[100], c;
	int cnt = 0;
	int line_num = 0;
	printf("Enter the filename to open for reading: \n");
	scanf("%s", filename);
	fptr1 = fopen(filename, "r"); // Open one file for reading
	if (fptr1 == NULL)
	{
		printf("Cannot open file %s \n", filename);
		//perror(fptr1);
		exit(0);
	}
	
	c = fgetc(fptr1); // Read contents from file
	
	while (c != EOF)
	{
		if(c == '\n')
		{
			line_num++;
		}
		cnt++;
		c = fgetc(fptr1);
	}

	printf("the number of characters and lines are %d %d \n", cnt, line_num);
	fclose(fptr1);
	return 0;
}

