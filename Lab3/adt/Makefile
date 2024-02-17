# This a Makefile for Lab3
# Author: Or Gindes

default: lab3

lab3: main.o GenDict.o Student.o
	gcc main.o GenDict.o Student.o -o main.out

GenDict.o: GenDict.c GenDict.h
	gcc -g -c GenDict.c

Student.o: Student.c Student.h GenDict.h
	gcc -g -c Student.c

main.o: main.c Student.h
	gcc -g -c main.c

clean:
	rm -f *.o
	rm -f main.out