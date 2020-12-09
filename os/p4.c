#include<stdio.h>
int main(int argc, char* argv[])
{
	FILE *fp1 = fopen(argv[1], "r");
	FILE *fp2 = fopen("sample_output.txt", "w");
	
	char c;
	while((c = fgetc(fp1)) != EOF)
	{
		fputc(c, fp2);
	}
	fclose(fp1);
	fclose(fp2);
}
