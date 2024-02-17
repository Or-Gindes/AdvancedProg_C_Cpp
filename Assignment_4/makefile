default: Ass4

Ass4: main.o Robot.o Map.o Game.o
	g++ -o Ass4 main.o Robot.o Map.o Game.o

Robot.o: Robot.cpp Robot.h Defs.h
	g++ -g -c Robot.cpp

Map.o: Map.cpp Map.h Defs.h
	g++ -g -c Map.cpp

Game.o: Game.cpp Game.h Robot.h Map.h
	g++ -g -c Game.cpp

main.o: main.cpp Robot.h Map.h Game.h
	g++ -g -c main.cpp

clean:
	rm -f *.o
	rm -f Ass4