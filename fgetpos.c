#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include "FILE.h"

/* The function int fgetpos(FILE *stream, fpos_t *pos) gets the current file position of the stream and writes it to pos.
 * This function returns zero on success, else non-zero value in case of an error.*/

int fgetpos2(FILE2 *fp, fpos_t2 *pos) {
	if(fp->fd < 0 || fp->fd > 13) {	
		write(1, "Not a valid file decriptor\n", 28);
		return 1;
	}
	pos->position = fp->position;		//Copies position in fpos_t structure member which can be later used by fsetpos
	return 0;
}
