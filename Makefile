test: main.o project
	cc main.o project -o test
main.o: FILE.h main.c
	cc -c main.c
project: FILE.h project.c
	cc -c project.c -o project
