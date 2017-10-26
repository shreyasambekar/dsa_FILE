#include "FILE.h"
#include <string.h>
#include <stdio.h>
int main(int argc, char *argv[]) {
	FILE2 *fp;
	int i;
	fp = fopen2("data.txt", "a");
	char ptr[8];
	while(((scanf("%s", ptr)) != -1)) {
		printf("hii\n");
		fwrite2(ptr, strlen(ptr), 1, fp);
	}
	/*fread2(ptr2, 1, 6, fp);*/
	printf("\n");
	/*fseek2(fp, 3, SEEK_CUR2);
	int ret = fseek2(fp, -31, SEEK_CUR2);
	ret = fseek2(fp, 3, SEEK_CUR2);*/
	int ret = fseek2(fp, -5, SEEK_CUR2);
	printf("ret: %d\n", ret);
	scanf("%s", ptr);
	fwrite2(ptr, strlen(ptr), 1, fp);
	/*for(i = 0; i < 6; i++) {
		printf("%c", ptr2[i]);*/
	fclose2(fp);
	return 0;
}
