project: main.o project.o
	cc main.o project.o -o project
main.o: FILE.h main.c
	cc -c main.c
project.o: FILE.h project.c
	cc -c project.c
