default: main

main: main.o Date.o Address.o Person.o
	g++ -o main main.o Date.o Address.o Person.o

Address.o: Address.cpp Address.h
	g++ -g -c Address.cpp

Date.o: Date.cpp Date.h
	g++ -g -c Date.cpp

Person.o: Person.cpp Person.h Address.h Date.h
	g++ -g -c Person.cpp

main.o: main.cpp Address.h Date.h Person.h
	g++ -g -c main.cpp

clean:
	rm -f *.o
	rm -f main