# -*- MakeFile -*-

CC = gcc
CFLAGS  = -g -Wall -Werror -Wextra -pedantic -std=c99

default: knapsack

knapsack: knapsack.o main.o helpers.o item.o string.o
	$(CC) $(CFLAGS) -o knapsack knapsack.o main.o helpers.o item.o string.o

knapsack.o: knapsack.c knapsack.h
	$(CC) $(CFLAGS) -c knapsack.c

string.o: string.c string.h
	$(CC) $(CFLAGS) -c string.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

helpers.o: helpers.c helpers.h
	$(CC) $(CFLAGS) -c helpers.c

item.o: item.c item.h
	$(CC) $(CFLAGS) -c item.c

clean:
	rm knapsack.o main.o helpers.o item.o knapsack string.o





