#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FILE.h"
#include <errno.h>

int main(int argc, char *argv[]) {
	FILE *fp;
	FILE2 *fp2;
	char ptr[128], ptr2[128];
	int ret, ret2, len;
	
	printf("Test case 1: \n");
	/* Using standard functions. */
	/* We first open the file in 'r' mode using standard library functions.
	   Then read some no. of bytes into one array. And close the file.
	   We repeat the same procedure for functions implemented for the same file and same no. of bytes.
	   If the data read is same, fread works. Also, fopen is tested in 'r' mode. */
	fp = fopen("testfile1", "r");
	if(fp == NULL) {
		printf("Unable to open the file\n");
		return errno;
	}
	ret = fread(ptr, 4, 1, fp);
	ptr[4] = '\0';
	fclose(fp);
	/* Using functions implemented. */
	fp2 = fopen2("testfile1", "r");
	if(fp2 == NULL) {
		printf("Unable to open the file\n");
		return errno;
	}
	ret2 = fread2(ptr2, 4, 1, fp2);
	ptr2[4] = '\0';
	fclose2(fp2);
	if((strcmp(ptr, ptr2) == 0) && ret == ret2) {
		printf("fread tested and fopen tested in 'r' mode\n\n");
	}
	
	printf("Test case 2: \n");
	/* We open the file in 'a' mode. Use ftell(standard).
	   Then open the same file using functions implemented and use ftell2(implemented).
	   If return valued are same, fopen in 'a' mode and ftell is tested. */
	/* Using standard functions */
	fp = fopen("testfile1", "a");
	if(fp == NULL) {
		printf("Unable to open the file\n");
		return errno;
	}
	ret = ftell(fp);
	fclose(fp);
	/*Using functions implemeted*/
	fp2 = fopen2("testfile1", "a");
	if(fp2 == NULL) {
		printf("Unable to open the file");
		return errno;
	}
	ret2 = ftell2(fp2);
	fclose2(fp2);
	if(ret == ret2) {
		printf("ftell tested and fopen tested in 'a' mode. Also fclose tested as we have opened the same file close in case1\n\n");
	}
	
	printf("Test case 3: \n");
	/* We first fwrite some no. of bytes using function implemented in the file opened in 'w' mode.
	   We store the value returned by fwrite in an integer 'ret'.
	   We read the 'ret' no. of bytes from the same file using standard fread function.
	   If the data written and read is same, fwrite is tested and fopen is tested in 'w' mode. */
	fp2 = fopen2("testfile2", "w");
	if(fp2 == NULL) {
		printf("Unable to open the file\n");
		return errno;
	}
	printf("Enter the data to be written in the file\n");
	scanf("%[^\n]s", ptr2);
	ret2 = fwrite2(ptr2, 1, strlen(ptr2), fp2);
	fclose2(fp2);
	fp = fopen("testfile2", "r");
	if(fp == NULL) {
		printf("Unable to open the file\n");
		return errno;
	}
	fread(ptr, ret2, 1, fp);
	fclose(fp);
	if((strcmp(ptr, ptr2) == 0)) {
		printf("fwrite tested and fopen tested in 'w' mode\n\n");
	}
	
	printf("Test case 4: \n");
	/* We first open the file in 'w+' mode.
	   Get the file position using fgetpos.
	   Then write some data to file.
	   We do fsetpos to the position obtained using fgetpos and again write some data. It will overwrite the previous data.
	   Then we fseek to the start.
	   Finally we read the data to make sure the data was overwritten. */
	fpos_t2 position;
	fp2 = fopen2("testfile2", "w+");
	if(fp2 == NULL) {
		return errno;
	}
	fgetpos2(fp2, &position);
	fwrite2("Hello", 5, 1, fp2);
	fsetpos2(fp2, &position);
	len = strlen("Overwritten");
	fwrite2("Overwritten", len, 1, fp2);
	fseek2(fp2, 0, SEEK_SET2);
	fread2(ptr2, len, 1, fp2);
	ptr2[len] = '\0';
	if((strcmp(ptr2, "Overwritten") == 0)) {
		printf("fopen in 'w+' mode, fgetpos, fsetpos, fseek to the start tested\n\n");
	}
	fclose2(fp2);
	
	printf("Test case 4: \n");
	/* Initially testfile3 and testfile4 are same.
	   We first open the testfile3 in 'r+' mode, use some sequence of fseek and fwrite using standard library functions.
	   Then open the testfile4 and use same sequence of fseek and fwrite implemented by me.
	   Then see if testfile3 and testfile4 are same using shell script. */
	/* Using standard functions */
	fp = fopen("testfile3", "r+");
	fseek(fp, -5, SEEK_END);
	fwrite("good.", 5, 1, fp);
	fseek(fp, 0, SEEK_SET);
	fwrite("VJTI", 4, 1, fp);
	fseek(fp, 5, SEEK_CUR);
	fwrite("nice", 4, 1, fp);
	fclose(fp);
	/* Using functions implemented */
	fp2 = fopen2("testfile4", "r+");
	fseek2(fp2, -5, SEEK_END2);
	fwrite2("good.", 5, 1, fp2);
	fseek2(fp2, 0, SEEK_SET2);
	fwrite2("VJTI", 4, 1, fp2);
	fseek2(fp2, 5, SEEK_CUR2);
	fwrite2("nice", 4, 1, fp2);
	fclose2(fp2);
	system("cmp --silent testfile3 testfile4 && echo '### SUCCESS: Files Are Identical! ###' || echo '### WARNING: Files Are Different! ###'");
	printf("fopen in 'r+' mode works and fseek tested with all possible arguments\n\n");
	
	printf("Test case 5: \n");
	/* Here we open the file in 'r' mode.
	   Then, we try to read the greater no. of bytes than actually present in file.
	   If EOF file is tested, feof will be tested. */
	fp2 = fopen2("testfile1", "r");
	fread2(ptr, 14, 1, fp2);
	ret2 = feof2(fp2);
	if(ret2 > 0) {
		printf("feof tested\n\n");
	}
	return 0;
}
