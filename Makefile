# Makefile for t9/trie.h/trie.c
# Chiho Kim
# CSE 374 Homework 5

# default target
t9: main.o trie.o
	gcc -Wall -g -std=c11 -o t9 main.o trie.o

# source files
trie.o: trie.c trie.h
	gcc -Wall -g -std=c11 -c trie.c

main.o: main.c trie.h
	gcc -Wall -g -std=c11 -c main.c

# "phony" target to remove built files and backups
clean:
	rm -f *.o t9 *~
