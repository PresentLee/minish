#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>


#define BUFF_SIZE 100
#define BUF_SIZE 100

char file01[BUFF_SIZE];
char file02[BUFF_SIZE];

void ls()
{
	printf("start \n");
    DIR *dp;
    struct dirent *ep;
	dp = opendir("./");

    if(dp != NULL)
	{
		printf("write \n");
		while((ep = readdir(dp)) != NULL )
		{
       		puts (ep->d_name);
		}
		closedir(dp);
	}
	else
	{
		perror ("couldn't open the directory");
	}
	if(closedir(dp) == -1)
	{
		perror("file doesn't close");
	}

return;

}

int cp(char *argv, char *argv2)
{
	int argc;
	int inputFd, outputFd, openFlags;
	mode_t filePerms;
	ssize_t numRead;
	char buf[BUF_SIZE];

	if (argc != 3 || strcmp(argv[1], "--help") == 0)
		usageErr("%s old-file new-file\n", argv[0]);
		inputFd = open(argv[1], O_RDONLY);
	if (inputFd == -1)
		errExit("opening file %s", argv[1]);
		openFlags = O_CREAT | O_WRONLY | O_TRUNC;
		filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; 

		outputFd = open(argv[2], openFlags, filePerms);
	if (outputFd == -1)
		errExit("opening file %s", argv[2]);

	while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0)
		if (write(outputFd, buf, numRead) != numRead)
			fatal("couldn't write whole buffer");
		if (numRead == -1)
			errExit("read");
		if (close(inputFd) == -1)
			errExit("close input");
		if (close(outputFd) == -1)
			errExit("close output");
								    
		exit(EXIT_SUCCESS);

}

int rm(char *argv)
{
	if (-1 == remove(argv))
		printf("fail");
	return 0;
}


int main(int argc, char **argv)
{
	char mode[BUFF_SIZE];

    while(1)
    {
        printf("> ");   
	    memset(mode, 0, sizeof(mode));
	    memset(file01, 0, sizeof(file01));
	    memset(file02, 0, sizeof(file02));
		
		scanf("%s", mode);
		/*
		*ptr = strtok(mode," ");
		ptr = strtok(NULL, " ");
		ptr = strtok(NULL, " ");
		strcpy(file01,ptr);
		ptr = strtok(NULL," ");
		strcpy(file02 ,ptr);
*/
        	if(mode[0] == 'l' && mode[1] =='s' )
        	{
				ls();
        	}
        	if(mode[0] == 'c'&& mode[1]=='p')
        	{
				scanf("%s %s", file01, file02);
            	cp(file01,file02);
        	}
			if(mode[0] == 'r'&& mode[1]=='m')
        	{
				scanf("%s", file01);
            	rm(file01);
        	}
			if(strcmp(mode, "exit")==0)
			{
				exit(1);

			}
		
    }

return 0;
}


