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
	static int max = 0;
	struct stat st;						//Structure to get the length of file
	if(max == 1) {						//Maximum possible no. of files are opened in the program
		return NULL;
	}
	fp = (FILE2 *)malloc(sizeof(FILE2));
	if(strcmp(mode, "r") == 0) {
		fd = open(filename, O_RDONLY);
		fp->flag = RBUF;
		fp->pos = 0;
		if(fd == -1) {
			return NULL;
		}
	}
	else if(strcmp(mode, "w") == 0) {
		fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
		fp->flag = WRBUF;
		fp->pos = 0;
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
   		stat(filename, &st);
		fp->pos = st.st_size;		//Addition by 1 may be necessary
		lseek(fd, 0, SEEK_END);		//Set the file position to the end
	}
	else if(strcmp(mode, "r+") == 0) {
		fd = open(filename, O_RDWR);
		fp->flag = RWRBUF;
		fp->pos = 0;
		if(fd == -1) {
			return NULL;
		}
	}
	else if(strcmp(mode, "w+") == 0) {
		fd = open(filename, O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
		fp->flag = WRRBUF;
		fp->pos = 0;
		if(fd == -1) {
			return NULL;
		}
	}
	else if(strcmp(mode, "a+") == 0) {
		fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
		fp->flag = RAPPBUF;
		if(fd == -1) {
			return NULL;
		}
   		stat(filename, &st);
		fp->pos = st.st_size;		//Addition by 1 may be necessary
   		lseek(fd, 0, SEEK_END);		//Set the file position to the end
	}
	else {
		return NULL;
	}
	if(fd > 13) {
		max = 1;			//Maximum files opened
	}
	fp->fd = fd;
	fp->rcnt = 0;	
	fp->wcnt = 0;
	fp->rbuf = (char *) malloc(BUFSIZE);
	fp->wbuf = (char *) malloc(BUFSIZE);	
	fp->rptr = fp->rbuf;
	fp->wptr = fp->wbuf;
	return fp;
}
