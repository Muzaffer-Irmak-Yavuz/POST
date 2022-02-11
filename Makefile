CC = gcc
CFLAGS = -g -Wall


build : main.c
	${CC} -o post main.c ${CFLAGS}
	