#include "Game.h"

/* Initialize static member of class Game which tracks number of robots in the game and is the size of robotArray */
/* This is different than the robotCounter in Robot because that counter doesn't change when a robot is removed */
int Game::RobotsNumber = 0;

/* Game constructor with two given maps */
Game::Game(const int *coords1, const int *coords2)
{
    this->_map1 = new Map(coords1, 1);
    this->_map2 = new Map(coords2, 2);
    this->_robotArray = nullptr;
}

/* Accepts coords of new robot and map number to add it to and adds a new robot to game in specified map and location */
/* Addition is only possible if location isn't a wall or out of bounds. Returns add action status */
status Game::addRobotToGame(int x, int y, int map)
{
    // Check that x,y is within map
    if (x < 0 || y < 0 || x >= _map1->getSize() || y >= _map1->getSize()){
        cout << "Invalid location\n";
        return BadArgs;
    }
    // Check that x,y is not a wall on map
    Map* temp_map = nullptr;
    bool wallTest;
    if (map == 1){
        temp_map = _map1;
        wallTest = _map1->isWall(x, y);
    }
    else{
        temp_map = _map2;
        wallTest = _map2->isWall(x, y);
    }
    
    if (wallTest == true){
        cout << "Invalid location\n";
        return BadArgs;
    }
    // Allocate memory for first robot if array is empty
    if (this->_robotArray == NULL){
        this->_robotArray = (Robot**) malloc(sizeof(Robot*));
        if (this->_robotArray == NULL)
            return BadMemoryAllocation;
        this->_robotArray[0] = new Robot(temp_map, x, y);
        if (this->_robotArray[0] == NULL)
            return BadMemoryAllocation;
    }
    
    else    // Allocate memory for current number of robots pointers + 1
    {
        Robot** temp_array = (Robot**) malloc((RobotsNumber + 1) * sizeof(Robot*));
        if (temp_array == NULL)
            return BadMemoryAllocation;
        
        for (int i=0; i < RobotsNumber; i++)
            temp_array[i] = this->_robotArray[i];
        
        free(this->_robotArray);
        this->_robotArray = temp_array;
        this->_robotArray[RobotsNumber] = new Robot(temp_map, x, y);
        if (this->_robotArray[RobotsNumber] == NULL)
            return BadMemoryAllocation;
    }
    RobotsNumber++;
    return success;
}

/* Accepts RobotSerial number, deletes it from robot dynamic array and free memory allocated to it */
/* Output delete message if print == true and Returns deletion status */
status Game::deleteRobotFromGame(int robotSerial, bool print)
{
    // Verify robot array is not empty
    if (this->_robotArray == NULL)
        return BadArgs;
    
    // search for robot with matching serial number
    for (int i=0; i < RobotsNumber; i++){
        if (this->_robotArray[i]->_serialNumber == robotSerial){
            
            // output delete message if needed and delete
            if (print == true)
                cout << "Robot deleted: " << this->_robotArray[i]->_serialNumber << " MAP: " << this->_robotArray[i]->_map->getMapN() << " GPS: " << this->_robotArray[i]->_xPos << "," << this->_robotArray[i]->_yPos << endl;
            delete this->_robotArray[i];
            
            // iterate remaining array and shift left before reallocating memory
            for (int j=i; j < (RobotsNumber - 1); j++)
                this->_robotArray[j] = this->_robotArray[j+1];
            
            // reallocated memory for robot array
            this->_robotArray = (Robot**) realloc(this->_robotArray, (RobotsNumber - 1) * sizeof(Robot*));
            if (this->_robotArray == NULL && RobotsNumber > 1)
                return BadMemoryAllocation; 
            RobotsNumber--;
            return success;
        }
    }
    return BadArgs;     // Serial Number was not found 
}

/* Accepts RobotSerial number and Move direction, finds matching robot and moves it */
/* Return status on move action */
status Game::moveRobot(int robotSerial, char* direction)const
{
    // Verify robot array is not empty
    if (this->_robotArray == NULL || direction == NULL)
        return BadArgs;
    
    status stat;
    // search for robot with matching serial number
    for (int i=0; i < RobotsNumber; i++){
        if (this->_robotArray[i]->_serialNumber == robotSerial){
            stat = this->_robotArray[i]->moveRobot(direction);
            return stat;
        }
    }
    return BadArgs;     // Serial Number was not found
}

/* Use map + operator and display robots on the new map if they fit. Does not save the new map */
void Game::addMaps()const
{
    Map res = *_map1 + *_map2;
    cout << res;
    if (this->_robotArray != NULL){   
        for (int i=0; i < RobotsNumber; i++){ 
            // If robot is lost skip it
            if (this->_robotArray[i]->_map == NULL)
                continue;
            if ((res).isWall(this->_robotArray[i]->_xPos, this->_robotArray[i]->_yPos) == false)
                cout << "Robot: " << this->_robotArray[i]->_serialNumber << " GPS: " << this->_robotArray[i]->_xPos << "," << this->_robotArray[i]->_yPos << endl;
        }
    }
}


/* Use map += operator and and delete robots that no longer have space */
/* Uses map number provided to determine which map is overwritten */
void Game::addEqualMaps(int map)
{
    Map* temp_map = nullptr;
    if (map == 1){
        *_map1 += *_map2;
        temp_map = _map1;
    }
    else if (map == 2){
        *_map2 += *_map1;
        temp_map = _map2;
    }
    else
        cout << "Invalid MAP number\n";
    
    if (this->_robotArray != NULL){   
        for (int i=0; i < RobotsNumber; i++){ 
            // If robot is lost skip it
            if (this->_robotArray[i]->_map == NULL)
                continue;
            if (this->_robotArray[i]->_map->getMapN() == map){
                if (temp_map->isWall(this->_robotArray[i]->_xPos, this->_robotArray[i]->_yPos) == true){
                    deleteRobotFromGame(this->_robotArray[i]->_serialNumber, false);
                    i--;
                }
            }
        }
    }
}

/* Use map = operator and delete robots that no longer have space */
/* Uses map number provided to determine which map is overwritten */
void Game::mapAssign(int map)
{
    Map* temp_map = nullptr;
    if (map == 1){
        *_map1 = *_map2;
        temp_map = _map1;
    }
    else if (map == 2){
        *_map2 = *_map1;
        temp_map = _map2;
    }
    else
        cout << "Invalid MAP number";
    cout << "\n";
    if (this->_robotArray != NULL){   
        for (int i=0; i < RobotsNumber; i++){ 
            // If robot is lost skip it
            if (this->_robotArray[i]->_map == NULL)
                continue;
            if (this->_robotArray[i]->_map->getMapN() == map){
                if (temp_map->isWall(this->_robotArray[i]->_xPos, this->_robotArray[i]->_yPos) == true){
                    deleteRobotFromGame(this->_robotArray[i]->_serialNumber, false);
                    i--;
                }
            }
        }
    }
}


/* Destructor for Game in charge of clearing Robot memory and freeing memory dynamically allocated to robot array */
Game::~Game()
{
    if (this->_robotArray != NULL){   
        for (int i=0; i < RobotsNumber; i++){
            delete this->_robotArray[i];
        }
        free(this->_robotArray);
    }
    delete this->_map1;
    delete this->_map2;
}

/* Function accepts number of map and prints map and robot information if its on the map */
/* Returns status enum indicating printing success or failure */
status Game::printMap(int map)const
{
    Map* temp_map = nullptr;
    if (map == 1){
        temp_map = _map1;
        cout << *_map1;
    }
    else if (map == 2){
        temp_map = _map2;
        cout << *_map2;
    }
    else
        return BadArgs;
    
    for (int i=0; i < RobotsNumber; i++)
        if (this->_robotArray[i]->_map == temp_map)
            cout << *this->_robotArray[i];

    return success;
}

void Game::runGame()
{
        char buffer[300];
    char direction[1];
    int choice, nMap, x, y, nRobot;
    status stat;

    do {
        cout << "Robot Control Menu \n"
        << "1. Add Robot \n"
        << "2. Delete Robot \n"
        << "3. Move Robot \n"
        << "4. Operator + \n"
        << "5. Operator += \n"
        << "6. Operator = \n"
        << "7. Operator == \n"
        << "8. Operator << \n"
        << "9. Quit \n"
        << "Input your option: \n";
        cin >> buffer;
        choice = atoi(buffer);
        switch (choice)
        {
            case 1: // Add Robot
                cout << "Enter MAP number: \n";
                cin >> buffer;
                nMap = atoi(buffer);
                if (nMap != 1 && nMap != 2){
                    cout << "Invalid Map \n";
                    break;
                }
                cout << "Enter Coordinates (X,Y): \n";
                cin >> x >> y;
                stat = this->addRobotToGame(x, y, nMap);
                if (stat == BadMemoryAllocation)
                    return;
                break;

            case 2: // Delete Robot
                cout << "Enter Robot number: \n";
                cin >> buffer;
                nRobot = atoi(buffer);
                stat = this->deleteRobotFromGame(nRobot, true);
                if (stat == BadMemoryAllocation)
                    return;
                break;

            case 3: // Move Robot
                cout << "Enter Robot number: \n";
                cin >> buffer;
                nRobot = atoi(buffer);
                cout << "Enter Direction: \n";
                cin >> direction;
                stat = this->moveRobot(nRobot, direction);
                if (stat == BadMemoryAllocation)
                    return;
                break;

            case 4: // Operator +
                this->addMaps();
                break;

            case 5: // Operator +=
                cout << "Override MAP number: \n\n";
                cin >> buffer;
                nMap = atoi(buffer);
                this->addEqualMaps(nMap);
                break;

            case 6: // Operator =
                cout << "Override MAP number: \n";
                cin >> buffer;
                nMap = atoi(buffer);
                this->mapAssign(nMap);
                break;

            case 7: // Operator ==
                if ((_map1 == _map2) == true)
                    cout << "TRUE \n";
                else
                    cout << "FALSE \n";
                break;

            case 8:
                cout << "Please enter MAP number: \n";
                cin >> nMap;
                stat = this->printMap(nMap);
                if (stat != success)
                    cout << nMap << " is not a valid Map Number \n";
                break;

            case 9:
                break;

            default:
                cout << "Invalid input \n";
                break;
        }

    }while (choice !=9);
}