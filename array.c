#include <stdio.h>
#include <string.h>

#define buff_size 100

main(int argc, char ** argv)
{
	char input[buff_size];
	char trash[buff_size];
	char get_mode[buff_size][buff_size];
	int i,j,k;
	int size;
	
	i = 0;
	j = 0;
	k = 0;

	while(1)
	{
		memset(input, 0, sizeof(input));
		memset(get_mode, 0, sizeof(get_mode));
		scanf("%[^\n]s", &input);
		scanf("%c",&trash);
		size = strlen(input);

		for(k=0; k<size; k++)
		{
			if(k==0)
			{
				get_mode[i][j] = input[k];
				j++;
				printf("1");
			}
			else
			{
				if(strcmp(input[k],"\0")==0)
				{
					get_mode[i][j] = "\0";
					i++;
					j=0;
					printf("2");
				}
				else
				{
					get_mode[i][j] = input[k];
					j++;
					printf("3");
				}
			}

		}

	printf("%s %d",input,size);
	printf("%s %s %s",get_mode[0],get_mode[1],get_mode[2]);
	
	}

return 0;
}
