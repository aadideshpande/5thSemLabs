//merges lines alternatively from 2 files and store it in 3rd file
#include<stdio.h>
#include<stdlib.h>
int main()
{
	FILE *fptr1, *fptr2, *fptr3;
	char f1[100], f2[100], f3[100];
	printf("enter the 1st file name: ");
	scanf("%s", f1);
	printf("enter the 2nd file name: ");
	scanf("%s", f2);
	
	fptr1 = fopen(f1, "r");
	fptr2 = fopen(f2, "r");
	
	printf("Enter the filename to open for writing: \n");
	scanf("%s", f3);
	fptr3 = fopen(f3, "w");
	
	FILE *temp = fptr1;
	
	char c1 = fgetc(temp);
	int lin_cnt = 0;
	while(c1 != EOF)
	{
		if(c1 == '\n')
		{
			lin_cnt++;
		}
		c1 = fgetc(temp);
	}
	
	rewind(fptr1);
	//printf("the no. of lines are: %d \n", lin_cnt);

	while(lin_cnt--)
	{
		char c = fgetc(fptr1);
		while(c != '\n')
		{
			fputc(c, fptr3);
			c = fgetc(fptr1);
		}
		//c = fgetc(fptr1);
		
		char c2 = fgetc(fptr2);
		while(c2 != '\n')
		{
			fputc(c2, fptr3);
			c2 = fgetc(fptr2);
		}
		//c2 = fgetc(fptr2);
		fputc('\n', fptr3);	
	}
		fclose(fptr1);
		fclose(fptr2);
		fclose(fptr3);
}
