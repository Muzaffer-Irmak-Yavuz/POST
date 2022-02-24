CC = gcc
CFLAGS = -g -Wall

Dir += src/

Source += ${Dir}help.c 
Source += ${Dir}socket.c 

build : ${Dir}main.c
	${CC} -o post.out ${Dir}main.c ${Source} ${CFLAGS}
	