#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
int main(int argc, char* argv[])
{
	// argv[1] is the file we have chosen to be searched
	// argv[2] is the keyword we have to search
	int n = open(argv[1], O_RDONLY);
	
	char buffer[256];
	char ch;
	int i = 0;
	int lin_num = 0;
	while(read(n, &ch, sizeof(ch)) > 0)
	{
		if(ch != '\n')
		{
			buffer[i++] = ch;
		}
		else
		{
			lin_num += 1;
			buffer[i] = '\0';
			i = 0;
			//printf("the buffer is %s \n", buffer);
			//char* ans = strstr(buffer, argv[2]);
			if(strstr(buffer, argv[2]))
			{
				printf("%d  %s \n",lin_num, buffer);
			}
		}
	}
	close(n);	
}
