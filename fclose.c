#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "FILE.h"
#include <stdlib.h>
int fclose2(FILE2 * fp) {
	int ret;
	free(fp->base);			//Frees the memory allocated for buffer
	fp->cnt = 0;
	fp->flag = 0;
	ret = close(fp->fd);
	if(ret == -1) {
		return -1;
	}
	i--;				//The no. of files opened in program is now less
	return 0;
}
