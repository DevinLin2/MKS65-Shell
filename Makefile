all: main.o bashcommands.o parse.o
	gcc -o program main.o parse.o bashcommands.o
main.o: main.c bashcommands.h parse.h
	gcc -c main.c
bashcommands.o: bashcommands.c
	gcc -c bashcommands.c
parse.o: parse.c
	gcc -c parse.c
run:
	./program
