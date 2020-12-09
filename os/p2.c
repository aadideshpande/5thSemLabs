#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
int main(int argc, char* argv[])
{
	int a = open(argv[1], O_RDONLY);
	char buffer[128];
	int line_count = 0;
	int i = 0;
	char ch;
	//char op[21][128];
	while(read(a, &ch, sizeof(ch)) > 0)
	{
		if(ch == '\n')
		{
			buffer[i++] = ch;
			buffer[i] = '\0';
			i = 0;
			line_count++;
			//printf("linecount is: %d \n", line_count);
			printf("%s", buffer);
			if(line_count == 20)
			{
				line_count = 0;
				printf("20 lines done, press any key to continue \n");	
				getchar();
			}
			
		}
		else
		{
			buffer[i++] = ch;
		}
	}
		
}
