#ifndef MAP_H_
#define MAP_H_

#include "Defs.h"

using namespace std;

/* This is a module of Map of boolean values of fixed size = 7 and dimensions size x size */
/* The map represents a maze where '1' are walls and '0' are passages in the maze */
/* The module defines operator between maps and facilitates usage of the map by other modules */

class Map
{
private:

    int data[49] = {0};
    int mapNumber;
    static const int size = 7;      // Map is a two-dim array of static size x size

public:
    // default constructor
    Map();
    // parameterized constructor
    Map(const int *data, int mapNumber);
    // Map '=' operator - first map will become a copy of second map without robots, robots occupying a new wall are deleted
    Map& operator=(const Map& other);
    // Destructor - nothing to destory as no memory is allocated
    ~Map(){};
    // Map addition - new map created by elementwise application of OR between two maps
    const Map operator+(const Map& other)const;
    // Map '+=' operator - add walls from other map to first map - delete robots in map1 who occupy new wall cells
    const Map& operator+=(const Map& other);
    // Map '==' operator - compare maps based on wall location (not robots) and return TRUE if there are equal
    bool operator==(const Map& other)const;
    // Map '<<' operator - output map info to stdout
    friend ostream& operator<<(ostream& out, const Map& map);
    // return mapNumber
    int getMapN() {return mapNumber;}
    // Function to check if location in map is a wall
    bool isWall(int col, int row)const;
    // Function to check if location is out-of-bounds of the map
    bool isOutofBounds(int col, int row)const;
    // return Map size
    static int getSize() {return size;}

};


#endif /* MAP_H_ */
    
