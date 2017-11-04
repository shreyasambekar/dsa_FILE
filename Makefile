test: main.o project
	cc main.o project -o test
main.o: FILE.h main.c
	cc -c main.c
project: FILE.h fopen.o fclose.o fread.o fwrite.o fgetpos.o fsetpos.o feof.o ftell.o fseek.o
	cc -shared -rdynamic fopen.o fclose.o fread.o fwrite.o fgetpos.o fsetpos.o feof.o ftell.o fseek.o -o project
fopen.o: FILE.h fopen.c
	cc -c -fPIC fopen.c
fclose.o: FILE.h fclose.c
	cc -c -fPIC fclose.c
fread.o: FILE.h fread.c
	cc -c -fPIC fread.c
fwrite.o: FILE.h fwrite.c
	cc -c -fPIC fwrite.c
fgetpos.o: FILE.h fgetpos.c
	cc -c -fPIC fgetpos.c
fsetpos.o: FILE.h fsetpos.c
	cc -c -fPIC fsetpos.c
feof.o: FILE.h feof.c
	cc -c -fPIC feof.c
ftell.o: FILE.h ftell.c
	cc -c -fPIC ftell.c
fseek.o: FILE.h fseek.c
	cc -c -fPIC fseek.c
