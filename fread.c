#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include "FILE.h"

/*The function int fread(void *ptr, int size, int nmemb, FILE2 *stream) reads data from the given stream into the array pointed to, by ptr.
 *The total number of elements successfully read are returned as int. If this number differs from the nmemb parameter,
 *then either an error had occurred or the End Of File was reached.
 *ferror() and feof() must be used to distinguish between error and EOF condition.*/

int fread2(void *ptr, int size, int nmemb, FILE2 *fp) {
	long int bytes = size * nmemb, j, count = 0;
	char *cp = (char *) ptr;
	while(1) {
		if(fp->rcnt == 0) {
			fp->rcnt = read(fp->fd, fp->rbuf, BUFSIZE);
			fp->rptr = fp->rbuf;
			if(fp->rcnt < BUFSIZE) {
				fp->flag = EOF2;
			}
		}
		if(fp->rcnt >= bytes) {
			for(j = 0; j < bytes; j++) {
				*(cp++) = *(fp->rptr++);
				count++;
				fp->rcnt--;
			}
			break;
		}
		bytes = bytes - fp->rcnt;
		for(j = 0; j < fp->rcnt; j++) {
			*(cp++) = *(fp->rptr++);
			count++;
			fp->rcnt--;
		}
		if(fp->flag == EOF2) {
			break;
		}
	}
	return count/size;
}
