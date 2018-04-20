#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>

ssize_t read(int fd, void*buf, size_t nbytes)
{
	time_t current_time;
	struct tm *times;

	current_time = time(NULL);
	times = localtime(&current_time);
	printf("%2d:%2d:%2d %-6s %d %p %ld \n", times->tm_hour,times->tm_min,times->tm_sec,"read",fd,buf,nbytes);

	ssize_t (*original_read)(int fd, void *bur, size_t nbytes);
	original_read = dlsym(RTLD_NEXT,"read");
	return (*original_read)(fd,buf,nbytes);
}

ssize_t write(int fd, const void *buf, size_t n)
{
	time_t current_time;
	struct tm *times;

	current_time = time(NULL);
	times = localtime(&current_time);
	printf("%2d:%2d:%2d %-6s %d %p %ld \n", times->tm_hour,times->tm_min,times->tm_sec,"write",fd, buf,n);

	ssize_t (*original_write)(int fd,const void *buf, size_t n);
	original_write = dlsym(RTLD_NEXT,"write");
	return (*original_write)(fd,buf,n);
}

int unlink(const char *path)
{
	time_t current_time;
	struct tm *times;

	current_time = time(NULL);
	times = localtime(&current_time);
	printf("%2d:%2d:%2d %-6s %s \n", times->tm_hour,times->tm_min,times->tm_sec,"unlink",path);

	int (*original_unlink)(const char *path);
	original_unlink = dlsym(RTLD_NEXT,"unlink");
	return (*original_unlink)(path);
}

int open (const char *pathname, int flags, mode_t MODE)
{
	time_t current_time;
	struct tm *times;

	current_time = time(NULL);
	times = localtime(&current_time);
	printf("%2d:%2d:%2d %-6s %s %d \n", times->tm_hour,times->tm_min,times->tm_sec,"open",pathname,MODE);
	
	int (*original_open)(const char *pathname, int flags, mode_t MODE);
	original_open = dlsym(RTLD_NEXT, "open");
	return (*original_open)(pathname,flags, MODE);
}

int close(int fd)
{
	time_t current_time;
	struct tm *times;

	time( &current_time);
	times = localtime(&current_time);
	printf("%2d:%2d:%2d %-6s %d \n", times->tm_hour,times->tm_min,times->tm_sec,"close",fd);

	int (*original_close)(int fd);
	original_close = dlsym(RTLD_NEXT,"close");
	return (*original_close)(fd);
}
