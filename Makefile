test: main.o project test_suite
	cc main.o project test_suite -o test
main.o: FILE.h main.c
	cc -c main.c
project: FILE.h fopen.o fclose.o fread.o fwrite.o fgetpos.o fsetpos.o feof.o ftell.o fseek.o
	cc fopen.o fclose.o fread.o fwrite.o fgetpos.o fsetpos.o feof.o ftell.o fseek.o -o project
fopen.o: FILE.h fopen.c
	cc -c fopen.c
fclose.o: FILE.h fclose.c
	cc -c fclose.c
fread.o: FILE.h fread.c
	cc -c fread.c
fwrite.o: FILE.h fwrite.c
	cc -c fwrite.c
fgetpos.o: FILE.h fgetpos.c
	cc -c fgetpos.c
fsetpos.o: FILE.h fsetpos.c
	cc -c fsetpos.c
feof.o: FILE.h feof.c
	cc -c feof.c
ftell.o: FILE.h ftell.c
	cc -c ftell.c
fseek.o: FILE.h fseek.c
	cc -c fseek.c
