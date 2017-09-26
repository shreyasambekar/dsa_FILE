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
	free(fp->wbuf);			//Yet to write the code for writing the data in buffer to file before freeing it
	free(fp->rbuf);			//Frees the memory allocated for buffer
	fp->cnt = 0;
	fp->flag = 0;
	ret = close(fp->fd);
	if(ret == -1) {
		return -1;
	}
	i--;				//The no. of files opened in program is now less
	return 0;
}
