default: main

main: main.o Creature.o Wolf.o Penguin.o Troll.o
	g++ -o main main.o Creature.o Wolf.o Penguin.o Troll.o

Creature.o: Creature.cpp Creature.h
	g++ -g -c Creature.cpp

Wolf.o: Wolf.cpp Wolf.h Creature.h
	g++ -g -c Wolf.cpp

Penguin.o: Penguin.cpp Penguin.h Creature.h
	g++ -g -c Penguin.cpp

Troll.o: Troll.cpp Troll.h Creature.h
	g++ -g -c Troll.cpp

main.o: main.cpp Wolf.h Penguin.h Troll.h
	g++ -g -c main.cpp

clean:
	rm -f *.o
	rm -f main