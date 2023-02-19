CC = gcc
FLAGS = -Wall -Wextra -g

.PHONY: build

build: main

main: main.o utils.o trees.o commands.o
	$(CC) $(FLAGS) -o $@ $^
	
main.o: main.c
	$(CC) $(FLAGS) -o $@ -c $<

utils.o: utils.c utils.h
	$(CC) $(FLAGS) -o $@ -c $<

trees.o: trees.c trees.h
	$(CC) $(FLAGS) -o $@ -c $<

commands.o: commands.c commands.h
	$(CC) $(FLAGS) -o $@ -c $<

.PHONY: clean
clean:
	rm -rf *.o main