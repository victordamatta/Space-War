CC=gcc
CFLAGS=-Wall -g

main: main.c bibfis.c nave.c projetil.c planeta.c
	${CC} ${CFLAGS} -o main $^ -lm

