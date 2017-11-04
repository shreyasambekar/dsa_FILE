#include <stdlib.h>
#include "FILE.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

/*The  function FILE2 *fopen(const char *filename, const char *mode) opens the filename pointed to, by filename using the given mode.
 * This function returns a FILE pointer.
 *  Otherwise, NULL is returned and the global variable errno is set to indicate the error.*/
 
FILE2 *fopen2(const char *filename, const char *mode) {
	FILE2 *fp;
	int fd;
	static int max = 0;
	struct stat st;				//Structure to get the length of file
	if(max == 1) {				//Maximum possible no. of files are opened in the program
		return NULL;
	}
	fp = (FILE2 *)malloc(sizeof(FILE2));
	if(strcmp(mode, "r") == 0) {
		fd = open(filename, O_RDONLY);
		fp->flag = RBUF;
		fp->pos = 0;
		if(fd == -1) {
			return NULL;
		}
	}
	else if(strcmp(mode, "w") == 0) {
		fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
		fp->flag = WRBUF;
		fp->pos = 0;
		if(fd == -1) {
			return NULL;
		}
	}
	else if(strcmp(mode, "a") == 0) {
		fd = open(filename, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
		fp->flag = APPBUF;
		if(fd == -1) {
			return NULL;
		}
   		stat(filename, &(st));
		fp->pos = st.st_size;		
		lseek(fd, 0, SEEK_END);		//Set the file position to the end
	}
	else if(strcmp(mode, "r+") == 0) {
		fd = open(filename, O_RDWR);
		fp->flag = RWRBUF;
		fp->pos = 0;
		if(fd == -1) {
			return NULL;
		}
	}
	else if(strcmp(mode, "w+") == 0) {
		fd = open(filename, O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
		fp->flag = WRRBUF;
		fp->pos = 0;
		if(fd == -1) {
			return NULL;
		}
	}
	else if(strcmp(mode, "a+") == 0) {
		fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
		fp->flag = RAPPBUF;
   		stat(filename, &(st));
		if(fd == -1) {
			return NULL;
		}
		fp->pos = st.st_size;		
   		lseek(fd, 0, SEEK_END);		//Set the file position to the end
	}
	else {
		return NULL;
	}
	if(fd > 13) {
		max = 1;			//Maximum files opened
	}
	fp->fd = fd;
	fp->rcnt = 0;	
	fp->wcnt = 0;
	fp->rbuf = (char *) malloc(BUFSIZE);
	fp->wbuf = (char *) malloc(BUFSIZE);	
	fp->rptr = fp->rbuf;
	fp->wptr = fp->wbuf;
	return fp;
}

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
		ret = write(fp->fd, fp->wbuf, fp->wcnt);	//Flushes the buffer
	}
	if(ret == -1) {
		return -1;
	}
	free(fp->wbuf);						//Frees the memory allocatef for write buffer
	free(fp->rbuf);						//Frees the memory allocated for read buffer
	ret = close(fp->fd);
	free(fp);
	if(ret == -1) {
		return -1;
	}
	return 0;
}

/* The function int fread(void *ptr, size_t size, size_t nmemb, FILE2 *stream) reads data from the given stream into the array pointed to, 
 * by ptr.
 * The total number of elements successfully read are returned as int. If this number differs from the nmemb parameter,
 * then either an error had occurred or the End Of File was reached.
 * ferror() and feof() must be used to distinguish between error and EOF condition.*/

int fread2(void *ptr, size_t size, size_t nmemb, FILE2 *fp) {	
	long int bytes = size * nmemb, j = 0, count = 0, i, ret;		
	char *cp = (char *) ptr;				
	if(fp->fd > 13 || fp->fd < 0) {				
		write(1, "Not a valid file descriptor, read operation failed\n", 51);
		return 0;
	}
	if(fp->wcnt != 0) {				//If call to fwrite is made before, to write the remaining data in buffer
		ret = write(fp->fd, fp->wbuf, fp->wcnt);	
		if(ret == -1) {
			return 0;
		}
		free(fp->wbuf);
		fp->wbuf = (char *)malloc(BUFSIZE);
		fp->wptr = fp->wbuf;
		fp->wcnt = 0;
	}
	while(1) {
		if(fp->rcnt == 0) {
			fp->rcnt = read(fp->fd, fp->rbuf, BUFSIZE);
			if(fp->rcnt == -1) {
				return 0;
			}
			fp->rptr = fp->rbuf;
			if(fp->rcnt < BUFSIZE) {
				fp->flagbackup = fp->flag;
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
		i = fp->rcnt;
		for(j = 0; j < i; j++) {
			*(cp++) = *(fp->rptr++);
			count++;			
			fp->rcnt--;
		}
		bytes = bytes - j;
		if(fp->flag == EOF2) {
			break;
		}
	}
	fp->pos = fp->pos + count;			//To advance the file position
	return (count / size);				//Returns the no. of elements read
}

/* The function int fwrite(const void *ptr, int size, int nmemb, FILE2 *stream) writes data from the array pointed to, by ptr to the given
 * stream.
 * This function returns the total number of elements successfully written as a int. 
 * If this number differs from the nmemb parameter, it will show an error.*/

int fwrite2(const void *ptr, size_t size, size_t nmemb, FILE2 *fp) {
	long int bytes, j, count = 0, written, ret;
	bytes = size * nmemb;
	char *cp = (char *) ptr;
	if(fp->fd > 13 || fp->fd < 0) {
		write(1, "Not a valid file descriptor, write operation failed\n", 52);
		return 0;
	}
	if(fp->rcnt != 0) {				//If call to fread is made before, to write the remaining data in buffer
		ret = lseek(fp->fd, -(fp->rcnt), SEEK_CUR);	
		if(ret == -1) {
			return 0;
		}
		free(fp->rbuf);
		fp->rbuf = (char *)malloc(BUFSIZE);
		fp->rptr = fp->wbuf;
		fp->rcnt = 0;
	}
	while(1) {
		for(j = 0; j < bytes; j++) {		
			*(fp->wptr++) = *(cp++);
			fp->wcnt++;
			if(fp->wcnt == BUFSIZE) {
				written = write(fp->fd, fp->wbuf, BUFSIZE);	//Writes to the file if the buffer is full
				if(written == -1) {
					return 0;
				}
				if(written != BUFSIZE) {
					fp->wcnt = fp->wcnt - written;
					fp->wptr = fp->wbuf + fp->wcnt; 
					count = count + written;	
					fp->pos = fp->pos + count;		
					return (count / size);
				}
				fp->wcnt = 0;	
				break;
			}
		}
		if(fp->wcnt != 0) {
			written = j;	
		}
		count = count + written;
		if(fp->wcnt == 0) {
			bytes = bytes - j - 1;
			fp->wptr = fp->wbuf;
		}
		else {
			bytes = bytes - j;
		}
		if(bytes == 0) {
			break;
		}
	}	
	fp->pos = fp->pos + count;			//Advances the file position
	return (count / size);				//Returns the no. of elements written
}

/* The C library function long int ftell(FILE *stream) returns the current file position of the given stream.
 * This function returns the current value of the position indicator. 
 * If an error occurs, -1L is returned. */

long int ftell2(FILE2 *fp) {
	if(fp->fd > 13 || fp->fd < 0) {				//Not a standard file descriptor
		write(1, "Not a valid file descriptor\n", 28);
		return -1L;
	}
	return fp->pos;
}

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
			if((-1) * offset < fp->rptr - fp->rbuf) {	//Only changing the buffer index
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

/* The function int fgetpos(FILE *stream, fpos_t *pos) gets the current file position of the stream and writes it to pos.
 * This function returns zero on success, else non-zero value in case of an error.*/

int fgetpos2(FILE2 *fp, fpos_t2 *pos) {
	if(fp->fd < 0 || fp->fd > 13) {	
		write(1, "Not a valid file decriptor\n", 28);
		return 1;
	}
	pos->position = fp->pos;		//Copies position in fpos_t structure member which can be later used by fsetpos
	return 0;
}

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

/* The function int feof(FILE *stream) tests the end-of-file indicator for the given stream.
 * Return Value
 * This function returns a non-zero value when End-of-File indicator associated with the stream is set
 *, else zero is returned. */

int feof2(FILE2 *fp) {
	if(fp->fd < 0 || fp->fd > 13) {
		write(1, "Not a valid file descriptor\n", 28);
		return 0;
	}
	if(fp->flag == EOF2) {
		return 1;
	}
	return 0;
}
