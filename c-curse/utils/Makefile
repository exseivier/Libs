

build-main: a.out

a.out: main.c libio.c libio.h
	gcc -g -Wall -lm --std=c99 main.c libio.c

build-manager: manager

manager: manager.c libio.c libio.h
	gcc -g -Wall -lm --std=c99 -o manager manager.c libio.c
