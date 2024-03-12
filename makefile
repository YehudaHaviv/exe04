
CC=gcc
CFLAGS=-Wall -g -Wextra

all: digitcompress

digitcompress: encodemain.o libcompress.a
	${CC} ${CFLAGS} -o digitcompress encodemain.o libcompress.a

encodemain.o: encodemain.c libcompress.a
	${CC} ${CFLAGS} -c encodemain.c

libcompress.a: compress.o
	ar -rcs libcompress.a compress.o

compress.o: compress.c compress.h
	${CC} ${CFLAGS} -c compress.c

clean:
	rm -f *.o digitcompress libcompress.a

