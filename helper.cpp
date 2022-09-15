#include <iostream>
#include "helper.h"
using std::cout, std::endl;

void deleteMap(int** map, int width) {

    for (int x = 0; x < width; ++x) {
        delete[] map[x];
    }

    delete[] map;
}

void outputMap(int** map, int width, int height) {

    // output top border
    cout << "+";
    for (int x = 0; x < width * TILE_WIDTH; ++x) {
        cout << "-";
    }
    cout << "+";
    cout << endl;
    
    for (int y = 0; y < height; ++y) {

        // output left border
        cout << "|";

        // output inner blocks
        for (int x = 0; x < width; ++x) {
            // output current block
            cout << " ";
            if      (map[x][y] == TILE_OPEN)     { cout << " "; }
            else if (map[x][y] == TILE_PLAYER)   { cout << "o"; }
            else if (map[x][y] == TILE_PILLAR)   { cout << "x"; }
            else if (map[x][y] == TILE_EXIT)     { cout << "!"; }
            cout << " ";
        }

        // output right border
        cout << "|";
        cout << endl;
    }
    
    // output bottom border
    cout << "+";
    for (int x = 0; x < width * TILE_WIDTH; ++x) {
        cout << "-";
    }
    cout << "+";
    cout << endl;
}

void outputStatus(int status, int currX, int currY) {

    switch (status) {
        case STATUS_MOVE :
            cout << "You have moved to location: (" << currX << ", " << currY << ")" << endl;
            break;
        case STATUS_STAY :
            cout << "An obstacle blocks your path." << endl;
            break;
        case STATUS_ESCAPE :
            cout << "Congratulations, adventurer! You have escaped the dungeon!" << endl;
            break;
    }
    cout << endl;
}
