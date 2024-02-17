/* Assignment 4 - 04.01.23 */

#include "Game.h"

int main()
{
    // Maps are defined outside of main because we might want to have different instances of the Game with different maps
    int zone1[49] = {
        1, 0, 0, 1, 1, 0, 1,    // row 6
        1, 1, 0, 0, 0, 0, 1,    // row 5
        0, 1, 0, 1, 1, 1, 0,    // row 4
        0, 0, 0, 1, 1, 1, 0,    // row 3
        1, 0, 1, 1, 0, 1, 0,    // row 2
        1, 0, 1, 0, 0, 1, 0,    // row 1
        1, 0, 0, 0, 0, 0, 0,    // row 0
    };

    int zone2[49] = {
        1, 1, 0, 0, 0, 1, 1,    // row 6
        1, 1, 0, 1, 1, 1, 1,    // row 5
        1, 1, 0, 0, 0, 1, 1,    // row 4
        0, 1, 1, 1, 0, 1, 1,    // row 3
        0, 0, 0, 0, 0, 1, 1,    // row 2
        1, 1, 0, 1, 1, 1, 0,    // row 1
        1, 0, 1, 0, 0, 0, 0,    // row 0
    };

    Game game = Game(zone1, zone2);
    game.runGame();

    return 0;
}
