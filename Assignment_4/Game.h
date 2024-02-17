#ifndef GAME_H_
#define GAME_H_

#include "Robot.h"
#include "Map.h"

using namespace std;

/* The Game module is the main module used by the manu user-facing program */
/* an instance of Game holds a dynamic array of robots and two maps */

class Game
{
private:
    Robot** _robotArray;
    Map *_map1, *_map2;
    static int RobotsNumber;

public:
    /* Initialize game given two coordinate arrays of {0,1} to create maps from */
    Game(const int *coords1, const int *coords2);
    /* Add a robot to this Game instance - print error message if (x,y) indicate a well or out-of-bounds */
    status addRobotToGame(int x, int y, int map);
    /* Remove a robot from the game based on serial Number */
    status deleteRobotFromGame(int robotSerial, bool print);
    /* Move robot on the board one tile in give direction */
    status moveRobot(int robotSerial, char* direction)const;
    /* AddMaps and move robots */
    void addMaps()const;
    /* AddEqualMaps and move robots */
    void addEqualMaps(int nMap);
    /* Map assign make one map equal to the other */
    void mapAssign(int nMap);
    /* Destructor - clears all robots and maps in game when called */
    ~Game();
    status printMap(int map)const;
    /* RunGame - prints menu and calls appropriate functions based on input */
    void runGame();

};

#endif /* GAME_H_ */