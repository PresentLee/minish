#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>


#define BUFF_SIZE 100

char file01[BUFF_SIZE];
char file02[BUFF_SIZE];

void ls()
{
//	printf("start \n");
    DIR *dp;
    struct dirent *ep;
	int fd;
	off_t sz_file;

	int i=0;

	dp = opendir("./");
   
	if(dp != NULL)
	{
	//	printf("write \n");
		while((ep = readdir(dp)) != NULL )
		{
		//	printf("%d",i);
			i++;
			fd = open(ep->d_name,O_RDONLY);
			sz_file =lseek(fd, 0, SEEK_END);
			printf("%-20s\t %ld\n",ep->d_name, sz_file);
			close(fd);
		}
//		printf("%d",i);
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
	int inputFd, outputFd, openFlags;
	mode_t filePerms;
	ssize_t numRead;
	char buf[BUFF_SIZE];

	inputFd = open(argv, O_RDONLY);
	if (inputFd == -1)
		printf("opening file %s", argv);

	openFlags = O_CREAT | O_WRONLY | O_TRUNC;
	filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; 

		outputFd = open(argv2, openFlags, filePerms);
	if (outputFd == -1)
		printf("opening file %s", argv2);

	while ((numRead = read(inputFd, buf, BUFF_SIZE)) > 0)
	{
		if (write(outputFd, buf, numRead) != numRead)
			printf("couldn't write whole buffer");
		if (numRead == -1)
			printf("read");
		if (close(inputFd) == -1)
			printf("close input");
		if (close(outputFd) == -1)
			printf("close output");
	}							    
		return 0;

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


