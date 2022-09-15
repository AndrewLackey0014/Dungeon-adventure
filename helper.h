#ifndef HELPER_H
#define HELPER_H

// constants for tile status
const int TILE_OPEN     = 0;    // blank tile
const int TILE_PLAYER   = 1;    // tile for player's current location
const int TILE_PILLAR   = 2;    // tile for unpassable pillar location
const int TILE_EXIT     = 3;    // tile for exit door out of dungeon

// constants for movement status flags 
const int STATUS_MOVE   = 0;    // flag indicating player has moved 
const int STATUS_STAY   = 1;    // flag indicating player has stayed still
const int STATUS_ESCAPE = 2;    // flag indicating player has stepped into exit door

// constants for user's keyboard inputs
const char MOVE_UP      = 'w';  // up movement
const char MOVE_LEFT    = 'a';  // left movement
const char MOVE_DOWN    = 's';  // down movement
const char MOVE_RIGHT   = 'd';  // right movement
const char INPUT_QUIT   = 'q';  // quit command

// constant value for tile width in console output
const int TILE_WIDTH    = 3;

// do not change
void deleteMap(int** board, int width);

// do not change
void outputMap(int** board, int width, int height);

// do not change
void outputStatus(int status, int currX, int currY);

#endif
