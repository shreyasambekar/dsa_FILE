#include <stdlib.h>
#define BUFSIZE 1024
#define MAX 10
typedef struct file {
	int cnt;		//Characters left
	char *ptr;		//Next character position
	char *base;		//Location of buffer
	int flag;		//Mode of file access
	int fd;			//File descriptor
}FILE2;

/*Some more flags to add for appending, combined reading and buffered etc. options*/
enum flags {	
	RBUF = 1,		//File open for reading and is buffered, the file must exist
	WBUF = 2, 		//File open for writing and is buffered, empty file is created
	APPBUF = 3,  		//File open for appending and is buffered, created if not exist
	RWRBUF = 4,		//File open for reading and writing and is buffered, the file must exist	
	WRRBUF = 5,		//File open for reading and writing and is buffered, empty file is created
	RAPPBUF = 6,		//File open for reading and appending and is buffered, created if not exist
	ERR = 7,		//Error has occured on file
};

FILE2 *arr[MAX];
int i = 0;
