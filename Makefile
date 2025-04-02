#A Simple Example Makefile for soshell
#
# Syntax:
# Alvo: Dependencias
# tab Action 1
# tab Action 2
#
# Variaveis: compiler, compiler flags, libraries to link, names of the object files for the executable.
#
CC=cc
FLAGS=-c -Wall
LIBS=-lm
OBS= main.o process.o scheduler_FCFS.o algorithms.o scheduler_RR.o ps.o

#Alvo por defeito é o primeiro
all :  simulator

main.o : algorithms.h main.c
	$(CC) $(FLAGS) main.c

process.o : algorithms.h process.c
	$(CC) $(FLAGS) process.c

scheduler_FCFS.o : algorithms.h scheduler_FCFS.c
	$(CC) $(FLAGS) scheduler_FCFS.c

algorithms.o : algorithms.h algorithms.c
	$(CC) $(FLAGS) algorithms.c

scheduler_RR.o : algorithms.h scheduler_RR.c
	$(CC) $(FLAGS) scheduler_RR.c

ps.o : algorithms.h ps.c
	$(CC) $(FLAGS) ps.c

simulator : $(OBS)
	$(CC)  -o simulator  $(OBS) $(LIBS)
clean limpar:
	rm -f simulator *.o
	rm -f *~
	echo "Remover: Ficheiros executáveis, objetos e temporários."
