#include "Map.h"


/* default constructor */
Map::Map()
{
    for (int i=0; i < (this->size * this->size) ; i++)
        this->data[i] = 0;
    this->mapNumber = -1;
}

/* param Constructor - accepts map data and map number to create a new map instance */
Map::Map(const int *data, int mapNumber)
{
    for (int i=0; i < (this->size * this->size) ; i++)
        this->data[i] = data[i];
    this->mapNumber = mapNumber;
}

/* Copy constructor - accepts another instace of Map to become a copy of */
Map& Map::operator=(const Map& other)
{
    for (int i=0; i < (this->size * this->size) ; i++)
        this->data[i] = other.data[i];
    return *this;
}

/* Map Addition - return new map that has walls from both maps, i.e. elementwise OR operation */
const Map Map::operator+(const Map& other)const
{
    Map res;
    for (int i=0; i < (this->size * this->size) ; i++)
        res.data[i] = (this->data[i] || other.data[i]);

    return res;
}

/* Map '+=' operator - add walls from other map to first map. use previously define '=' and '+' map operators */
const Map& Map::operator+=(const Map& other)
{
    *this = *this + other;
    return *this;
}

/*  Map '==' operator - compare maps based on wall location and return TRUE if there are equal */
bool Map::operator==(const Map& other)const
{
    bool isEqual = true;
    for (int i=0; i < (this->size * this->size) ; i++){
        isEqual = (this->data[i] == other.data[i]);
        if (isEqual == false)
            return isEqual;
    }
    return isEqual;
}

/* Map '<<' operator - output map info to stdout */
ostream& operator<<(ostream& out, const Map& map)
{
    out << "\n";
    for (int i=0; i < (map.size * map.size) ; i++){
        if (i % map.size == 0)
            out << "[";
        out << map.data[i];
        if (i % map.size == map.size - 1)
            out << "]\n";
        else
            out << " ";
    }
    out << "\n";
    return out;
}

/* Support function to determin if coordinates on map are a wall or passage. for out of bounds values false will be returned because robot can fall off map */
bool Map::isWall(int col, int row)const
{
    if (col < 0 || row < 0 || col >= size || row >= size)
        return false;
    return (bool) data[(size - 1 - row) * size + col];
}

/* Support function to determin if coordinates are outside of map */
bool Map::isOutofBounds(int col, int row)const
{
    if (col < 0 || row < 0 || col >= size || row >= size)
        return true;
    return false;
}
