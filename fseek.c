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
	int lret, ret;
	if(fp->fd > 13 || fp->fd < 0) {
		write(1, "Not a valid file descriptor, read operation failed\n", 51);
		return 0;
	}
	if(fp->flag == EOF2) {
		fp->flag = fp->flagbackup;
	}
	if(whence != SEEK_CUR2) {	
		free(fp->rbuf);	
		fp->rbuf = (char *)malloc(BUFSIZE);
		fp->rptr = fp->rbuf;	
		if(fp->wcnt != 0) {
			ret = write(fp->fd, fp->wbuf, fp->wcnt);
			if(ret == -1) {
				return -1;
			}
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
			fp->pos = lret;
			return 0;
		}
		else {
			lret = lseek(fp->fd, offset, SEEK_END);
			if(lret == -1) {
				return -1;
			}
			fp->pos = lret;
			return 0;
		}
	}
	else {
		if(fp->wcnt != 0) {
			ret = write(fp->fd, fp->wbuf, fp->wcnt);
			if(ret == -1) {
				return -1;
			}
			free(fp->wbuf);
			fp->wbuf = (char *)malloc(BUFSIZE);
			fp->wptr = fp->wbuf;
			fp->wcnt = 0;
		}
		if(offset < 0) {	
			if((-1) * offset < fp->rptr - fp->rbuf) {		//Only changing the buffer index
				fp->pos = fp->pos + offset;
				fp->rptr = fp->rptr + offset;
				fp->rcnt = fp->rcnt - offset;
				return 0;
			}
			else if((-1) * offset >= fp->rptr - fp->rbuf) {	
				lret = lseek(fp->fd, -(fp->rptr - fp->rbuf + fp->rcnt), SEEK_CUR);
				if(lret == -1) {
					return -1;
				}
				fp->pos = fp->pos + offset;
				offset = offset + fp->rptr - fp->rbuf;
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
				fp->pos = fp->pos + offset;
				offset = offset - fp->rcnt;
				free(fp->rbuf);
				fp->rbuf = (char *)malloc(BUFSIZE);
				fp->rptr = fp->rbuf;
				fp->rcnt = 0;	
			}
		}
	}
	lret = lseek(fp->fd, offset, SEEK_CUR);			//Actually doing lseek if the no. of elements left in buffer is less
	if(lret == -1) {
		return -1;
	}
	return 0;
}
