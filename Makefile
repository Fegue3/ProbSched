CC = gcc
CFLAGS = -Wall -g
OBJ = main.o process.o utils.o scheduler_FCFS.o

all: simulator

simulator: $(OBJ)
	$(CC) $(CFLAGS) -o simulator $(OBJ)

main.o: main.c process.h utils.h scheduler_FCFS.h
	$(CC) $(CFLAGS) -c main.c

process.o: process.c process.h utils.h
	$(CC) $(CFLAGS) -c process.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

scheduler_FCFS.o: scheduler_FCFS.c scheduler_FCFS.h process.h
	$(CC) $(CFLAGS) -c scheduler_FCFS.c

clean:
	rm -f *.o simulator