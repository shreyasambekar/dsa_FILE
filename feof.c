#include "FILE.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/* The function int feof(FILE *stream) tests the end-of-file indicator for the given stream.
 * Return Value
 * This function returns a non-zero value when End-of-File indicator associated with the stream is set
 *, else zero is returned. */

int feof2(FILE2 *fp) {
	if(fp->fd < 0 || fp->fd > 13) }{
		write(1, "Not a valid file descriptor\n", 28);
		return 0;
	}
	if(fp->flag == EOF2) {
		return 1;
	}
	return ;
}
