#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	FILE *fp1, *fp2;

	//choose file to read from 
	fp1 = fopen("sample.txt", "rb");

	//choose/create a file to write to
	fp2 = fopen("output.txt", "wb+");

	char ch;
	while((ch = fgetc(fp1)) != EOF)
	{
		fputc(ch, fp2);
	}
	printf("successfuly executed \n");

	close(fp1);
	close(fp2);
}