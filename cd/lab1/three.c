// reverse contents of the file and store it in new file
// display the size of the file

#include<stdio.h>
#include<stdlib.h>

long count(FILE *f) 
{
    fseek(f, -1L, 2);
    long last_pos = ftell(f); // returns the position of the last element of the file
    last_pos++;
    return last_pos;
}

int main()
{
	FILE *fptr1, *fptr2;
	char filename[100], c;
	printf("enter the name of the file \n");
	scanf("%s", filename);
	fptr1 = fopen(filename, "r");
	
	if (fptr1 == NULL)
	{
		printf("Cannot open file %s \n", filename);
		//perror(fptr1);
		exit(0);
	}
	
	printf("Enter the filename to open for writing: \n");
	scanf("%s", filename);
	fptr2 = fopen(filename, "w+"); 
	int cnt = count(fptr1);
	
	// pointer points to the last character in the file
	fseek(fptr1, 0L, SEEK_END); 
	
	while(cnt)
	{
		c = fgetc(fptr1);
		printf("%c", c);
		fputc(c, fptr2);
		fseek(fptr1, -1L, SEEK_CUR);
		cnt--;
	}
	
	printf("reverse copy done \n");
	fclose(fptr1);
	fclose(fptr2);
	return 0;
}
