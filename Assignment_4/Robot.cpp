#include "Robot.h"

// Initialize static member of class Robot
int Robot::_robotCount = 0;

/* param Constructor - accepts a pointer to map and robot location */
Robot::Robot(Map* map, int x, int y)
{
    _map = map;
    _xPos = x;
    _yPos = y;
    _robotCount++;
    _serialNumber = _robotCount;
    cout << "New Robot: " << _serialNumber << "  MAP: " << _map->getMapN() << "  GPS: " << _xPos << "," << _yPos << endl;
}

/* Copy constructor - accepts another Robot and becomes a copy of it */
Robot::Robot(const Robot &other)
{
    _map = other._map;
    _xPos = other._xPos;
    _yPos = other._yPos;
    _robotCount++;
    _serialNumber = _robotCount;
    cout << "New Robot: " << _serialNumber << "  MAP: " << _map->getMapN() << "  GPS: " << _xPos << "," << _yPos << endl;
}

/* Adjust robot position based on 'direction' input unless out of reach (-1, -1) or running into a wall in which case position won't change */
/* Return status of move action */
status Robot::moveRobot(char* direction)
{
    if (direction == NULL)
        return BadArgs;
    if (_xPos == -1 && _yPos == -1)
        return failure;
    int x = _xPos;
    int y = _yPos;
    if (strcmp(direction, "U") == 0)
        y += 1;
    else if (strcmp(direction, "D") == 0)
        y -= 1;
    else if (strcmp(direction, "L") == 0)
        x -= 1;
    else if (strcmp(direction, "R") == 0)
        x += 1;

    // move robot if its not running into a wall, check if robot fell out of bounds and set new position
    if (_map->isWall(x, y) == false){
        if (_map->isOutofBounds(x, y) == true){
            _xPos = -1;
            _yPos = -1;
            return failure;
        }
        else{
            _xPos = x;
            _yPos = y;            
        }  
    }
    cout << "Robot: " << _serialNumber;
    if (_map != NULL)
        cout << " MAP: " << _map->getMapN();
    cout << " GPS: " << _xPos << "," << _yPos << endl;
    return success;
}

/* Map '<<' operator - output map info to stdout */
ostream& operator<<(ostream& out, const Robot& bot)
{
    cout << "Robot: " << bot._serialNumber;
    if (bot._map != NULL)
        cout << " Map: " << bot._map->getMapN();
    cout << " GPS: " << bot._xPos << "," << bot._yPos << endl;
    return out;
}
