#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include "FILE.h"

/*The function int fread(void *ptr, int size, int nmemb, FILE2 *stream) reads data from the given stream into the array pointed to, by ptr.
 *The total number of elements successfully read are returned as int. If this number differs from the nmemb parameter,
 *then either an error had occurred or the End Of File was reached.
 *ferror() and feof() must be used to distinguish between error and EOF condition.*/

int fread(void *ptr, int size, int nmemb, FILE2 *fp) {
	long int bytes = size * nmemb, i, count = 0;
	static int rddata;
	char *cp = (char *) ptr;
	while(1) {
		if(fp->cnt == 0) {
			rddata = read(fp->fd, fp->rbuf, BUFSIZE)
			fp->rptr = fp->rbuf;
			if(rddata < BUFSIZE) {
				fp->flag = EOF2;
			}
		}
		else {
			rddata = fp->base + rddata - fp->ptr;
			fp->cnt = 0;
		}
		if(rddata >= bytes) {
			for(i = 0; i < bytes, i++) {
				*(cp++) = *(fp->ptr++);
				count++;
			}
			fp->cnt = rddata - bytes;
			break;
		}
		bytes = bytes - BUFSIZE;
		for(i = 0; i < rddata; i++) {
			*(cp++) = *(fp->ptr++)
			count++;
		}
		if(fp->flag == EOF2) {
			break;
		}
	}
	return count/size;
}
