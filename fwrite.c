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
	long int bytes, j, count = 0, written;
	bytes = size * nmemb;
	char *cp = (char *) ptr;
	if(fp->fd > 13 || fp->fd < 0) {
		write(1, "Not a valid file descriptor, write operation failed\n", 52);
		return 0;
	}
	if(fp->rcnt != 0) {				//If call to fread is made before, to write the remaining data in buffer
		lseek(fp->fd, -(fp->rcnt), SEEK_CUR);	//Handle the case if lseek fails later
		free(fp->rbuf);
		fp->rbuf = (char *)malloc(BUFSIZE);
		fp->rptr = fp->wbuf;
		fp->rcnt = 0;
	}
	while(1) {
		for(j = 0; j < bytes; j++) {				//Addition of 1 may be necessary to loop conditions
			*(fp->wptr++) = *(cp++);
			fp->wcnt++;
			if(fp->wcnt == BUFSIZE) {
				written = write(fp->fd, fp->wbuf, BUFSIZE);	//Writes to the file if the buffer is full
				if(written != BUFSIZE) {
					fp->wcnt = fp->wcnt - written;
					count = count + written;	
					fp->pos = fp->pos + count;		//Add 1 if necessary later
					return (count / size);
				}
				fp->wcnt = 0;	
				break;
			}
		}
		if(fp->wcnt != 0) {
			written = fp->wcnt;
		}
		count = count + written;
		if(fp->wcnt == 0) {
			bytes = bytes - BUFSIZE;
		}
		else {
			bytes = bytes - fp->wcnt;
		}
		if(bytes == 0) {
			break;
		}
	}	
	fp->pos = fp->pos + count;	
	return (count / size);
}
