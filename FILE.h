#include <stdlib.h>
#include <stddef.h>
#define BUFSIZE 1024
#define MAX 10

typedef struct file {
	int rcnt;		//Characters left to read from buffer
	int wcnt;		//Chracters to be written to file from buffer
	char *rptr;		//Next character position for read buffer
	char *wptr;		//Next character position for write buffer
	char *rbuf;		//Location of buffer for reading
	char *wbuf;		//Location of buffer for writing
	int flag;		//Mode of file access
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

int i = 0;			//Variable that stores no. of simultaneously opened files
int fclose2(FILE2 *);
FILE2 *fopen2(const char *filename, const char *mode);
int fread2(void *ptr, size_t size, size_t nmemb, FILE2 *stream);	
int fwrite2(const void *ptr, size_t size, size_t nmemb, FILE2 *stream);
long int ftell(FILE2 *);
