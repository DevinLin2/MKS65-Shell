all: main.o bashcommands.o parse.o redirect.o semicolon.o
	gcc -o program main.o parse.o bashcommands.o redirect.o semicolon.o
main.o: main.c bashcommands.h parse.h redirect.h semicolon.h
	gcc -c main.c
bashcommands.o: bashcommands.c
	gcc -c bashcommands.c
redirect.o: redirect.c
	gcc -c redirect.c
parse.o: parse.c
	gcc -c parse.c
semicolon.o: semicolon.c
	gcc -c semicolon.c
run:
	./program
