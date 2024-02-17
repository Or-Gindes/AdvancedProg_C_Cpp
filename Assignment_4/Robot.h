#ifndef ROBOT_H_
#define ROBOT_H_

#include "Defs.h"
#include "Map.h"

using namespace std;

/* This module represents a robot with coordinates on a map (provided by the map module) and a serial number identifying the robots */
/* The robot can only occupy 'passage' (i.e. 0) spots on the map */
/* The module faciliates usage of Robot by Game module including creating and moving robots around the map and tracking their numbers */

class Robot
{
    Map* _map;
    int _xPos;
    int _yPos;
    int _serialNumber;
    static int _robotCount;

public:
    // default / parameterized constructor
    Robot(Map* map=nullptr, int x=0, int y=0);
    // copy constructor
    Robot(const Robot &other);
    // Destructor
    ~Robot(){};
    // Move robot in given direction from options - {Up,Down,Left,Right}
    status moveRobot(char* direction);
    // Define a robot << operator
    friend ostream& operator<<(ostream& out, const Robot& robot);
    // define Game as a friend class which can use and access private Robot variables to account
    friend class Game;
    static int getNumberOfRobots() {return _robotCount;}
};

#endif /* ROBOT_H_ */