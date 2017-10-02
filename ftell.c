#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include "FILE.h"

/* The C library function long int ftell(FILE *stream) returns the current file position of the given stream.
 * This function returns the current value of the position indicator. 
 * If an error occurs, -1L is returned. */

long int ftell(FILE2 *fp) {
	if(fp->fd > 13) {		//Not a standard file descriptor
		write(1, "Not a standard file descriptor\n", 31);
		return -1L;
	}
	return fp->pos;
}
