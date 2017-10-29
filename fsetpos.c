#include <stdlib.h>
#include "FILE.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

/* The fsetpos() function shall set the file position and state indicators for 
 * the stream pointed to by stream according to the value of the object pointed to by pos,
 * which the application shall ensure is a value obtained from an earlier call to fgetpos() on the same stream.
 * The fsetpos() function shall return 0 if it succeeds; otherwise, it shall return a non-zero value and set errno to indicate the error.
 */

int fsetpos2(FILE2 *fp, const fpos_t2 *pos) {
	int lret, ret;
	if(fp->fd > 13 || fp->fd < 0) {
		write(1, "Not a valid file descriptor, read operation failed\n", 51);
		return 0;
	}
	if(fp->wcnt != 0) {
		ret = write(fp->fd, fp->wbuf, fp->wcnt);
	}
	if(ret == -1) {
		return -1;
	}
	free(fp->wbuf);
	free(fp->rbuf);
	fp->wbuf = (char *)malloc(sizeof(BUFSIZE));
	fp->rbuf = (char *)malloc(sizeof(BUFSIZE));
	fp->rptr = fp->rbuf;
	fp->wptr = fp->wbuf;
	fp->rcnt = fp->wcnt = 0;
	if(fp->flag == EOF2) {
		fp->flag = fp->flagbackup;
	}
	lret = lseek(fp->fd, pos->position, SEEK_SET);
	fp->pos = pos->position;
	if(lret == -1) {
		return -1;
	}
	return 0;
}
