CC = gcc
CFLAGS = -Wall -g
OBJ = main.o process.o utils.o scheduler.o

all: simulator

simulator: $(OBJ)
	$(CC) $(CFLAGS) -o simulator $(OBJ)

main.o: main.c process.h utils.h scheduler.h
	$(CC) $(CFLAGS) -c main.c

process.o: process.c process.h utils.h
	$(CC) $(CFLAGS) -c process.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

scheduler.o: scheduler.c scheduler.h process.h
	$(CC) $(CFLAGS) -c scheduler.c

clean:
	rm -f *.o simulator