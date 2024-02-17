# This a Makefile for Assignment 3 - C Second
# Author: Or Gindes

default: JerryBoreeMain

JerryBoreeMain: JerryBoreeMain.o LinkedList.o KeyValuePair.o HashTable.o MultiValueHashTable.o Jerry.o
	gcc JerryBoreeMain.o LinkedList.o KeyValuePair.o HashTable.o MultiValueHashTable.o Jerry.o -o JerryBoree

LinkedList.o: LinkedList.c LinkedList.h Defs.h
	gcc -g -c LinkedList.c

KeyValuePair.o: KeyValuePair.c KeyValuePair.h Defs.h
	gcc -g -c KeyValuePair.c

HashTable.o: HashTable.c HashTable.h Defs.h KeyValuePair.h LinkedList.h
	gcc -g -c HashTable.c

MultiValueHashTable.o: MultiValueHashTable.c MultiValueHashTable.h Defs.h HashTable.h LinkedList.h
	gcc -g -c MultiValueHashTable.c

Jerry.o: Jerry.c Jerry.h Defs.h
	gcc -g -c Jerry.c

JerryBoreeMain.o: JerryBoreeMain.c Jerry.h Defs.h MultiValueHashTable.h HashTable.h LinkedList.h
	gcc -g -c JerryBoreeMain.c

clean:
	rm -f *.o
	rm -f JerryBoreeMain