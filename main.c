#include <unistd.h>
#include <fcntl.h>
#include "FILE.h"
#include <string.h>
#include <stdio.h>
int main(int argc, char *argv[]) {
	FILE2 *fp;
	int i = 0, arr[20], j;
	fp = fopen2("data.txt", "w+");
	char ptr[38], ptr2[8];
	while(((scanf("%s", ptr)) != -1)) {
		arr[i++] = strlen(ptr);	
		fwrite2(ptr, strlen(ptr), 1, fp);
	}
	printf("\n");
	j = i;
	fseek2(fp, 0, SEEK_SET2);
	for(i = 0; i < j; i++) {
		fread2(ptr2, arr[i], 1, fp);
		*(ptr2 + arr[i]) = '\0';
		printf("%s\t", ptr2);
	}
	printf("\n");
	fclose2(fp);
	return 0;
}
