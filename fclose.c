#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "FILE.h"
#include <stdlib.h>

/*The function int fclose(FILE2 *stream) closes the stream. 
 *The memory allocated for buffers is freed. 
 *If any data is remaining to write in the buffer, it is written before freeing the buffer.
 *This method returns zero if the stream is successfully closed. On failure, EOF is returned. */

int fclose2(FILE2 * fp) {
	int ret;
	if(fp->fd > 13 || fp->fd < 0) {
		write(1, "Not a valid file descriptor\n", 28);
		return -1;
	}
	if(fp->wcnt != 0) {
		write(fp->fd, fp->wbuf, fp->wcnt);	//Flushes the buffer
	}
	free(fp->wbuf);			//Frees the memory allocatef for write buffer
	free(fp->rbuf);			//Frees the memory allocated for read buffer
	ret = close(fp->fd);
	free(fp);
	if(ret == -1) {
		return -1;
	}
	return 0;
}
