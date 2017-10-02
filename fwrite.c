#include "FILE.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

/* The function int fwrite(const void *ptr, int size, int nmemb, FILE2 *stream) writes data from the array pointed to, by ptr to the given
 * stream.
 * This function writtenurns the total number of elements successfully writtenurned as a int. 
 * If this number differs from the nmemb parameter, it will show an error.*/

int fwrite2(const void *ptr, int size, int nmemb, FILE2 *fp) {
	long int bytes, j, count = 0, written;
	bytes = size * nmemb;
	char *cp = (char *) ptr;
	while(1) {
		for(j = 0; j < bytes; j++) {
			*(fp->wptr++) = *(cp++);
			fp->wcnt++;
			if(fp->wcnt == BUFSIZE) {
				written = write(fp->fd, fp->wbuf, BUFSIZE);	//Writes to the file if the buffer is full
				if(written != BUFSIZE) {
					fp->wcnt = fp->wcnt - written;
					count = count + written;	
					return count / size;
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
	return count / size;
}
