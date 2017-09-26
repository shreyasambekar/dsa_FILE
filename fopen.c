#include <stdlib.h>
#include "FILE.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

/*The  function FILE2 *fopen(const char *filename, const char *mode) opens the filename pointed to, by filename using the given mode.
 * This function returns a FILE pointer.
 *  Otherwise, NULL is returned and the global variable errno is set to indicate the error.*/
 
FILE2 *fopen2(const char *filename, const char *mode) {
	FILE2 *fp;
	int fd;
	if(i == MAX) {						//Maximum possible no. of files are opened in the program
		return NULL;
	}
	if(strcmp(mode, "r") == 0) {
		fd = open(filename, O_RDONLY);
		fp->flag = RBUF;
		if(fd == -1) {
			return NULL;
		}
	}
	else if(strcmp(mode, "w") == 0) {
		fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
		fp->flag = WRBUF;
		if(fd == -1) {
			return NULL;
		}
	}
	else if(strcmp(mode, "a") == 0) {
		fd = open(filename, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
		fp->flag = APPBUF;
		if(fd == -1) {
			return NULL;
		}
   		lseek(fd, 0, SEEK_END);		//Set the file position to the end
	}
	else if(strcmp(mode, "r+") == 0) {
		fd = open(filename, O_RDONLY | O_WRONLY);
		fp->flag = RWRBUF;
		if(fd == -1) {
			return NULL;
		}
	}
	else if(strcmp(mode, "w+") == 0) {
		fd = open(filename, O_RDONLY | O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
		fp->flag = WRRBUF;
		if(fd == -1) {
			return NULL;
		}
	}
	else if(strcmp(mode, "a+") == 0) {
		fd = open(filename, O_RDONLY | O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
		fp->flag = RAPPBUF;
		if(fd == -1) {
			return NULL;
		}
   		lseek(fd, 0, SEEK_END);		//Set the file position to the end
	}
	else {
		return NULL;
	}
	fp->fd = fd;
	fp->cnt = 0;	
	fp->rbuf = (char *) malloc(BUFSIZE);
	fp->wbuf = (char *) malloc(BUFSIZE);	
	fp->rptr = fp->rbuf;
	i++;					//Increases the counter that keeps record of no. of opened files
	return fp;
}
