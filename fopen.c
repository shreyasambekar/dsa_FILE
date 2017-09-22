#include <FILE.h> 
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
FILE2 *fopen(const char *filename, const char *mode) {
	FILE2 *fp;
	int fd;
	printf("%d" , i);
/*	if(strcmp(mode, "r") == 0) {
		fd = open(filename, O_RDONLY);
		fp->flag = RBUF;
		if(fd == -1) {
			return NULL;
		}
	}
	else if(strcmp(mode, "w") == 0) {
		fd = open(filename, O_WRDONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
		fp->flag = WBUF;
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
		fd = open(filename, O_RDONLY | O_WRDONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
		fp->flag = WRRRBUF;
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
*/
}
