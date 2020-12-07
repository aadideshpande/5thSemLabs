// recognize all the keywords and print them in uppercase
// Aadi Shantanu Deshpande
// A - 46 (B2)
// 180905402

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
int main()
{
	FILE *fptr1, *fptr2;
	char filename[100];
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

   char keyword[32][10]={
      "auto","double","int","struct","break","else","long",
      "switch","case","enum","register","typedef","char",
      "extern","return","union","const","float","short",
      "unsigned","continue","for","signed","void","default",
      "goto","sizeof","voltile","do","if","static","while"
   } ;

	char c = getc(fptr1), cb;
	while(c != EOF)
	{
		// we check for every string in the array
		for(int i = 0; i <= 31; i++)
		{
			//printf("inside loop1 \n");
			bool flag = 0;
			char ans[10];
			int m = 0;
			for(int j = 0; keyword[i][j] != '\0'; j++)
			{
				//printf("inside loop2 \n");
				if(c == keyword[i][j])
				{
					ans[m++] = toupper(c);
					c = getc(fptr1);
					//printf("%c ", c);
				}
				// if the character does not match with given character, 
				//we seek the pointer to the beginning an check with the next keyword
				else	
				{
					fseek(fptr1, -j, SEEK_CUR);
					c = getc(fptr1);
					break;
				}

				if(keyword[i][j + 1] == '\0')
				{
					flag = true;
				}
			}
			if(flag)
			{
				putc('\n', fptr2);
				for(int i = 0; ans[i] != '\0'; i++)
				{
					//printf("inside loop3\n");
					putc(ans[i], fptr2);
					printf("%c", ans[i]);
				}
				printf("\n");
			}
		}

	}

	fclose(fptr1);
	fclose(fptr2);
	return 0;
}
