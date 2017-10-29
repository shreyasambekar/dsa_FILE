#include <unistd.h>
#include <fcntl.h>
#include "FILE.h"
#include <string.h>
#include <stdio.h>
int main(int argc, char *argv[]) {
	FILE2 *fp;
	int i = 0, arr[20], j, ret, pos;
	fp = fopen2("data.txt", "r+");
	char ptr[38], ptr2[8], ch;
	for(i = 0; i < 1; i++) {
		ret = fread2(ptr, 8, 3, fp);
		pos = ftell2(fp);
		printf("ret: %d\tpos: %d\n", ret, pos);
	}
		ret = fread2(ptr, 8, 2, fp);
		pos = ftell2(fp);
		printf("ret: %d\tpos: %d\n", ret, pos);
/*	int ret = fwrite2(ptr, 7, 4, fp);
	printf("ret: %d\n", ret);*/
	/*for(i = 0; i < 8; i++) {
		fread2(ptr2, 7, 1, fp);
		ptr2[7] = '\0';
		printf("%s\n", ptr2);
	}*/
	/*fseek2(fp, 7, SEEK_CUR2);
	fread2(ptr, 11, 1, fp);
	*(ptr + 11) = '\0';
	printf("%s\n", ptr);
	fseek2(fp, 7, SEEK_CUR2);*/
	/*while(((scanf("%s", ptr)) != -1)) {
		arr[i++] = strlen(ptr);	
		fwrite2(ptr, strlen(ptr), 1, fp);
	}*/
	/*printf("\n");
	fseek2(fp, -(strlen("shyamprasad") + strlen("ambekar")), SEEK_END);
	fread2(ptr, 11, 1, fp);
	*(ptr + 11) = '\0';
	printf("%s\n", ptr);
	fread2(ptr, 7, 1, fp);
	*(ptr + 7) = '\0';
	printf("%s\n", ptr);*/
	
/*	i = arr[0] + arr[1] + arr[2];
	j = fseek2(fp, (-1) * i, SEEK_CUR2);
	printf("ret: %d\n" ,j);
	while(((scanf("%s", ptr)) != -1)) {
		fwrite2(ptr, strlen(ptr), 1, fp);
	}*/
	/*printf("sum: %d\n", arr[0] + arr[1] + arr[2]);
	read(fp->fd, ptr, 5);
	ptr[4] = '\0';
	printf("see: %s\n", ptr);*/
	/*for(i = 0; i < 3; i++) {
		fread2(ptr, arr[i + 3], 1, fp);
		*(ptr + arr[i]) = '\0';
		printf("%s\n", ptr);
	}*/

	/*j = i;
	fseek2(fp, 0, SEEK_SET2);
	for(i = 0; i < j; i++) {
		fread2(ptr2, arr[i], 1, fp);
		*(ptr2 + arr[i]) = '\0';
		printf("%s\t", ptr2);
	}
	printf("\n");*/
	fclose2(fp);
	return 0;
}
