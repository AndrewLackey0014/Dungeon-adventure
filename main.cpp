#include <iostream>
#include <fstream>
#include <string>
#include "helper.h"
using std::cin, std::cout, std::endl, std::string, std::ifstream;

/**
 * Creates internal representation of dungeon map.
 * @param   fileName    File name of dungeon map representation.
 * @param   width       Width of dungeon map.
 * @param   height      Height of dungeon map.
 * @param   currX       Player's starting x-position on dungeon map.
 * @param   currY       Player's starting y-position on dungeon map.
 * @return  2D dynamic array representation of dungeon map with player's location.
 */
// STEP 1: Write code for createMap(...) function here.
int** createMap(const string filename, int& width, int& height, int& currX, int& currY){
    // declare/define and open input file stream
    ifstream ifs (filename);
    // check if input stream opened successfully
    if (!ifs.is_open()) {
        cout << "ERROR: unable to open: " << filename << endl;
        ifs.close();
        return nullptr;
    }

    ifs >> width >> height;

    ifs >> currX >> currY;

  
    // Create a one dimensional array on the heap of pointers to places on the board 
    //    that has width elements (i.e. the number of columns)
    int** map = new int*[width];
  
    bool fail = false;
  
    for (int i=0; i < width; ++i) { // loop through each column
    // assign that column to a one dimensional array on the heap
    //  that has height elements (i.e. the number of rows)
        map[i] = new int[height];
    
        if (map[i] == nullptr) { // failed to allocate
        fail = true;
        }
    }
  
    if (fail) { // if any allocation fails, clean up and avoid memory leak
    // deallocate any arrays created in for loop
        for (int i=0; i < width; ++i) {
            delete [] map[i]; // deleting nullptr is not a problem
        }
        delete [] map; // delete array of pointers
        return nullptr;
    }
    // initialize cells
    for (int row=0; row<height; ++row) {
        for (int col=0; col<width; ++col) {
            map[col][row] = { 0 };
        }
    }
    int current_position;
    while (!ifs.eof()){
        for (int row=0; row<height; ++row){
            for (int col=0; col<width; ++col){
                ifs >> current_position;
                if (col == currX && row == currY){
                    map[currX][currY] = TILE_PLAYER;
                }
                else if (current_position == TILE_OPEN){
                    map[col][row] = TILE_OPEN;
                }
                else if (current_position == TILE_PILLAR){
                    map[col][row] = TILE_PILLAR;
                }
                else if (current_position == TILE_EXIT){
                    map[col][row] = TILE_EXIT;
                }
            }
        }
    }
        
    ifs.close();
    return map;

}
/**
 * Updates player's position and movement status for next turn. 
 * @param   map         Dungeon map.
 * @param   width       Width of dungeon map.
 * @param   height      Height of dungeon map.
 * @param   direction   User's keyboard input for player's dungeon map direction.
 * @param   currX       Player's current x-position on dungeon map.
 * @param   currY       Player's current y-position on dungeon map.
 * @param   nextX       Player's next x-position on dungeon map.
 * @param   nextY       Player's next y-position on dungeon map.
 * @return  Player's movement status after updating player's position for next turn.
 */
// STEP 2: Write code for updateNextPosition(...) function here.
void swap(int currX, int currY, int& nextX, int& nextY){
    nextX = currX;
    nextY = currY;
}
void add_subtract(char input, int& nextX,int& nextY){
    if (input == MOVE_UP){
        nextY -= 1;
    }
    else if (input == MOVE_DOWN){
        nextY += 1;
    }
    else if (input == MOVE_LEFT){
        nextX -= 1;
    }
    else if (input == MOVE_RIGHT){
        nextX += 1;
    }
}
void locate(int** map, int& tile, int& nextX, int& nextY){
    tile = map[nextX][nextY];
}

int updateNextPosition(int** map, int width, int height, char input, int currX, int currY, int& nextX, int& nextY){
    swap(currX, currY, nextX, nextY);
    add_subtract(input, nextX, nextY);
    int tile;
    if (input == MOVE_UP){
        if (((currY - 1 + width) % width) == width - 1){
            swap(currX, currY, nextX, nextY);
            return STATUS_STAY;
        }
        locate(map, tile, nextX, nextY);
        if(tile == TILE_PILLAR){
            swap(currX, currY, nextX, nextY);
            return STATUS_STAY;
        }
        else if(tile == TILE_EXIT){
            return STATUS_ESCAPE;
        }else{
            return STATUS_MOVE;
        }
    }
    if (input == MOVE_DOWN){
        if (((currY + 1 + width) % width) == 0){
            swap(currX, currY, nextX, nextY);
            return STATUS_STAY;
        }
        locate(map, tile, nextX, nextY);
        if(tile == TILE_PILLAR){
            swap(currX, currY, nextX, nextY);
            return STATUS_STAY;
        }
        else if(tile == TILE_EXIT){
            return STATUS_ESCAPE;
        }else{
            return STATUS_MOVE;
        }
    }
    if (input == MOVE_LEFT){
        if (((currX - 1 + height) % height) == height - 1){
            swap(currX, currY, nextX, nextY);
            return STATUS_STAY;
        }
        locate(map, tile, nextX, nextY);
        if(tile == TILE_PILLAR){
            swap(currX, currY, nextX, nextY);
            return STATUS_STAY;
        }
        else if(tile == TILE_EXIT){
            return STATUS_ESCAPE;
        }else{
            return STATUS_MOVE;
        }
    }
    if (input == MOVE_RIGHT){
        if (((currX + 1 + height) % height) == 0){
            swap(currX, currY, nextX, nextY);
            return STATUS_STAY;
        }
        locate(map, tile, nextX, nextY);
        if(tile == TILE_PILLAR){
            swap(currX, currY, nextX, nextY);
            return STATUS_STAY;
        }
        else if(tile == TILE_EXIT){
            return STATUS_ESCAPE;
        }else{
            return STATUS_MOVE;
        }
    }
}


/**
 * Updates dungeon map representation with player's current position.
 * @param   currX       Player's current x-position on dungeon map.
 * @param   currY       Player's current y-position on dungeon map.
 * @param   nextX       Player's next x-position on dungeon map.
 * @param   nextY       Player's next y-position on dungeon map.  
 */
// STEP 3: Write code for updateMap(...) function here.

void updateMap(int** map, int& currX, int& currY, int nextX, int nextY){
    map[currX][currY] = TILE_OPEN;
    currX = nextX;
    currY = nextY;
    map[currX][currY] = TILE_PLAYER;
}


int main() {

    // declare variables
    int width, height, currX, currY, nextX, nextY;
    string fileName;

    // prompt user to enter dungeon file name
    cout << "Please enter dungeon map file: ";
    cin >> fileName;

    // --- UNCOMMENT THE FOLLOWING LINES AFTER COMPLETING STEP 1 ---
    // create map, or quit if map load error
    
    int** map = createMap(fileName, width, height, currX, currY);
        if (map == nullptr) {
        cout << "This dungeon map does not exist. ";
        cout << "Returning you back to the real word, adventurer!" << endl;
        return 1;
    }
    

    // display greeting message
    cout << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "Good day, adventurer! Your goal is to escape the dungeon!" << endl;
    cout << " --- SYMBOLS ---"                                          << endl;
    cout << " o          : That is you, the adventurer!"                << endl;
    cout << " x, -, |    : These are unpassable obstacles."             << endl;
    cout << " !          : That is the door to escape the dungeon."     << endl;
    cout << " --- CONTROLS ---"                                         << endl;
    cout << " w, a, s, d : Keys for moving up, left, down, and right."  << endl;
    cout << " q          : Key for abandoning your quest."              << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << endl;
    
    // --- UNCOMMENT THE FOLLOWING LINES AFTER COMPLETING STEP 1 ---
    // // display map

    outputMap(map, width, height);
    

    // move player
    char input;
    int status;
    while (true) {
        // get user input
        cout << "Enter command (w,a,s,d: move, q: quit): ";
        cin >> input;

        // quit game if user inputs quit
        if (input == INPUT_QUIT) {
            cout << "Thank you for playing!" << endl;
            break;
        }

        // skip turn if user inputs 
        if (input !=  MOVE_UP && input != MOVE_LEFT && input != MOVE_DOWN && input != MOVE_RIGHT) {
            cout << "I did not understand your command, adventurer!" << endl;
            continue;
        }

    
        // --- UNCOMMENT THE FOLLOWING LINES AFTER COMPLETING STEP 2 ---
        // // move player, if possible, and get map status
        status = updateNextPosition(map, width, height, input, currX, currY, nextX, nextY);
    

    
        // --- UNCOMMENT THE FOLLOWING LINES AFTER COMPLETING STEP 3 ---
        // // update map
        
        if (status == STATUS_MOVE || status == STATUS_ESCAPE) {
            updateMap(map, currX, currY, nextX, nextY);
        }
        
        
        // // display map and status
        outputMap(map, width, height);
        outputStatus(status, currX, currY);
        
        // // quit game if user escapes
        if (status == STATUS_ESCAPE) {
            break;
        }
    }

    
    // --- UNCOMMENT THE FOLLOWING LINES AFTER COMPLETING STEP 1 ---
    // // delete map
    deleteMap(map, width);
    

    return 0;
    
}
