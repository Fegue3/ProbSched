CC = gcc
CFLAGS = -Wall

OBJS = main.o process.o utils.o

all: test

test: $(OBJS)
	$(CC) $(CFLAGS) -o test $(OBJS)

main.o: main.c process.h
process.o: process.c process.h utils.h
utils.o: utils.c utils.h

clean:
	rm -f *.o test
