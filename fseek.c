#include <stdlib.h>
#include "FILE.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

/* The C library function int fseek(FILE *stream, long int offset, int whence) 
 * sets the file position of the stream to the given offset.
 * This function returns zero if successful, or else it returns a non-zero value.*/

int fseek2(FILE2 *fp, long int offset, int whence) {
	int lret;
	if(fp->fd > 13 || fp->fd < 0) {
		write(1, "Not a valid file descriptor, read operation failed\n", 51);
		return 0;
	}
	if(whence != SEEK_CUR2) {	
		free(fp->rbuf);	
		fp->rbuf = (char *)malloc(BUFSIZE);
		fp->rptr = fp->rbuf;	
		if(fp->wcnt != 0) {
			write(fp->fd, fp->wbuf, fp->wcnt);
		}
		free(fp->wbuf);
		fp->wbuf = (char *)malloc(BUFSIZE);
		fp->wptr = fp->wbuf;
		fp->wcnt = 0;
		fp->rcnt = 0;
		if(whence == SEEK_SET2) {
			lret = lseek(fp->fd, offset, SEEK_SET);
			if(lret == -1) {
				return -1;
			}
			return 0;
		}
		else {
			lret = lseek(fp->fd, offset, SEEK_END);
			if(lret == -1) {
				return -1;
			}
			return 0;
		}
	}
	else {
		if(fp->wcnt != 0) {
			write(fp->fd, fp->wbuf, fp->wcnt);
			free(fp->wbuf);
			fp->wbuf = (char *)malloc(BUFSIZE);
			fp->wptr = fp->wbuf;
			fp->wcnt = 0;
		}
		if(offset < 0) {	
			if((-1) * offset < /*BUFSIZE - fp->rcnt*/fp->rptr - fp->rbuf) {		//check
				fp->pos = fp->pos + offset;
				fp->rptr = fp->rptr + offset;
				fp->rcnt = fp->rcnt - offset;
				return 0;
			}
			else if((-1) * offset >= /*BUFSIZE - fp->rcnt*/fp->rptr - fp->rbuf) {	//check
				lret = lseek(fp->fd, -(fp->rptr - fp->rbuf + fp->rcnt/*BUFSIZE*/), SEEK_CUR);
				if(lret == -1) {
					return -1;
				}
				offset = offset + fp->rptr - fp->rbuf/* + fp->rcnt*/;	//see if it works	
				free(fp->rbuf);
				fp->rbuf = (char *)malloc(BUFSIZE);
				fp->rptr = fp->rbuf;
				fp->rcnt = 0;	
			}
		}		
		else if(offset > 0) {
			if(fp->rcnt > offset) {
				fp->pos = fp->pos + offset;
				fp->rptr = fp->rptr + offset;
				fp->rcnt = fp->rcnt - offset;
				return 0;
			}
			else if(offset > fp->rcnt) {
				offset = offset - fp->rcnt;
				free(fp->rbuf);
				fp->rbuf = (char *)malloc(BUFSIZE);
				fp->rptr = fp->rbuf;
				fp->rcnt = 0;	
			}
		}
	}
	lret = lseek(fp->fd, offset, SEEK_CUR);
	if(lret == -1) {
		return -1;
	}
	return 0;
}
