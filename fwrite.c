#include "FILE.h"
#include <stdlib.h>
#include <stddef.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

/* The function int fwrite(const void *ptr, int size, int nmemb, FILE2 *stream) writes data from the array pointed to, by ptr to the given
 * stream.
 * This function returns the total number of elements successfully written as a int. 
 * If this number differs from the nmemb parameter, it will show an error.*/

int fwrite2(const void *ptr, size_t size, size_t nmemb, FILE2 *fp) {
	long int bytes, j, count = 0, written, ret;
	bytes = size * nmemb;
	char *cp = (char *) ptr;
	if(fp->fd > 13 || fp->fd < 0) {
		write(1, "Not a valid file descriptor, write operation failed\n", 52);
		return 0;
	}
	if(fp->rcnt != 0) {				//If call to fread is made before, to write the remaining data in buffer
		ret = lseek(fp->fd, -(fp->rcnt), SEEK_CUR);	
		if(ret == -1) {
			return 0;
		}
		free(fp->rbuf);
		fp->rbuf = (char *)malloc(BUFSIZE);
		fp->rptr = fp->wbuf;
		fp->rcnt = 0;
	}
	while(1) {
		for(j = 0; j < bytes; j++) {		
			*(fp->wptr++) = *(cp++);
			fp->wcnt++;
			if(fp->wcnt == BUFSIZE) {
				written = write(fp->fd, fp->wbuf, BUFSIZE);	//Writes to the file if the buffer is full
				if(written == -1) {
					return 0;
				}
				if(written != BUFSIZE) {
					fp->wcnt = fp->wcnt - written;
					fp->wptr = fp->wbuf + fp->wcnt; 
					count = count + written;	
					fp->pos = fp->pos + count;		
					return (count / size);
				}
				fp->wcnt = 0;	
				break;
			}
		}
		if(fp->wcnt != 0) {
			written = j;	
		}
		count = count + written;
		if(fp->wcnt == 0) {
			bytes = bytes - j - 1;
			fp->wptr = fp->wbuf;
		}
		else {
			bytes = bytes - j;
		}
		if(bytes == 0) {
			break;
		}
	}	
	fp->pos = fp->pos + count;			//Advances the file position
	return (count / size);				//Returns the no. of elements written
}
