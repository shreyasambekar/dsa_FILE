#include "FILE.h"
#include <string.h>
#include <stdio.h>
int main(int argc, char *argv[]) {
	FILE2 *fp;
	int i;
	fp = fopen2("data.txt", "w");
	char ptr[8];
	while(((scanf("%s", ptr)) != -1)) {
		printf("hii\n");
		fwrite2(ptr, strlen(ptr), 1, fp);
	}
	/*fread2(ptr2, 1, 6, fp);*/
	printf("\n");
	/*for(i = 0; i < 6; i++) {
		printf("%c", ptr2[i]);*/
	fclose2(fp);
	return 0;
}
