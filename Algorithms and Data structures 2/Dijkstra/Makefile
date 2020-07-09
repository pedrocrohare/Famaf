# -*- MakeFile -*-

CC = gcc
CFLAGS  = -g -Wall -Werror -Wextra -pedantic -std=c99

default: dijkstra

dijkstra: dijkstra.o main.o graph.o cost.o set.o
	$(CC) $(CFLAGS) -o dijkstra dijkstra.o main.o graph.o cost.o set.o

dijkstra.o: dijkstra.c dijkstra.h
	$(CC) $(CFLAGS) -c dijkstra.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c graph.c

cost.o: cost.c cost.h
	$(CC) $(CFLAGS) -c cost.c

clean:
	rm cost.o graph.o main.o dijkstra.o dijkstra *~





