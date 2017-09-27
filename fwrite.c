#include "FILE.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

/* The function int fwrite(const void *ptr, int size, int nmemb, FILE2 *stream) writes data from the array pointed to, by ptr to the given
 * stream.
 * This function returns the total number of elements successfully returned as a int. 
 * If this number differs from the nmemb parameter, it will show an error.*/

int fwrite2(const void *ptr, int size, int nmemb, FILE2 *fp) {
	long int bytes, j, count = 0, ret;
	bytes = size * nmemb;
	char *cp = (char *) ptr;
	while(1) {
		for(j = 0; j < bytes; j++) {
			*(fp->wptr++) = *(cp++);
			fp->wcnt++;
			if(fp->wcnt == BUFSIZE) {
				ret = write(fp->fd, fp->wbuf, j);	//Writes to the file if the buffer is full
				fp->wcnt = 0;
				break;
			}
		}
		if(fp->wcnt != 0) {
			ret = j;
		}
		fp->wptr = fp->wbuf + fp->wcnt;
		count = count + ret;
		bytes = bytes - j;
		if(bytes == 0) {
			break;
		}
	}	
	return count/size;
}
