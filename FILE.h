#include <stdlib.h>
#include <stddef.h>
#define BUFSIZE 1024
#define MAX 10
#define SEEK_SET2 100
#define SEEK_CUR2 200
#define SEEK_END2 300

typedef struct file {
	int rcnt;		//Characters left to read from buffer
	int wcnt;		//Chracters to be written to file from buffer
	char *rptr;		//Next character position for read buffer
	char *wptr;		//Next character position for write buffer
	char *rbuf;		//Location of buffer for reading
	char *wbuf;		//Location of buffer for writing
	int flag;		//Mode of file access
	int flagbackup;		//To get the flag when EOF of file is removed
	int fd;			//File descriptor
	long int fpos;		//Current file position
}FILE2;

enum flags {	
	RBUF = 1,		//File open for reading and is buffered, the file must exist
	WRBUF,  		//File open for writing and is buffered, empty file is created
	APPBUF,  		//File open for appending and is buffered, created if not exist
	RWRBUF, 		//File open for reading and writing and is buffered, the file must exist	
	WRRBUF,			//File open for reading and writing and is buffered, empty file is created
	RAPPBUF,		//File open for reading and appending and is buffered, created if not exist
	ERR, 			//Error has occured on file
	EOF2 = 8		//End of file has reached on file
};

/* In the GNU C Library, fpos_t is an opaque data structure that contains internal data to represent file offset and conversion state 
 * information.
 * It may encode both a record offset within the file, and a character offset.
 * I am implementing a simple version of it.*/

typedef struct fpos_t2 {
	long int position;
}fpos_t2;

int fclose2(FILE2 *);
FILE2 *fopen2(const char *filename, const char *mode);
int fread2(void *ptr, size_t size, size_t nmemb, FILE2 *stream);	
int fwrite2(const void *ptr, size_t size, size_t nmemb, FILE2 *stream);
long int ftell2(FILE2 *stream);
int fseek2(FILE2 *stream, long int offset, int whence);
int feof2(FILE2 *stream);
int fsetpos2(FILE2 *stream, const fpos_t2 *pos);
int fgetpos2(FILE2 *stream, fpos_t2 *pos);
