#include <iostream>
#include <fstream>
#include <string>
#include "logic.h"

using std::cout, std::endl, std::ifstream, std::string;

/**
 * TODO: Student implement this function
 * Load representation of the dungeon level from file into the 2D map.
 * Calls createMap to allocate the 2D array.
 * @param   fileName    File name of dungeon level.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference to set starting position.
 * @return  pointer to 2D dynamic array representation of dungeon map with player's location., or nullptr if loading fails for any reason
 * @updates  maxRow, maxCol, player
 */
char** loadLevel(const string& fileName, int& maxRow, int& maxCol, Player& player) {

    ifstream filez(fileName);

    if(!filez.is_open())
    {
        return nullptr;
    }

    filez >> maxRow; // gather row numbers'
    
    if(filez.fail() || maxRow < 1)
    {
        return nullptr;
    }

    
    filez >> maxCol;
    
    if(filez.fail() || maxCol < 1)
    {
        return nullptr;
    }

    if(maxCol > INT32_MAX / maxRow)
    {
        return nullptr;
    }

 
    filez >> player.row; // row based on players move 
    
    if(filez.fail() || player.row < 0 || player.row >= maxRow)
    {
        return nullptr;
    }

    filez >> player.col; //col based on players move
    
    if(filez.fail() || player.col >= maxCol || player.col < 0)
    {
        return nullptr;
    }
  
    char** dungeon = createMap(maxRow,maxCol);
    char tile = '\0';
    bool exit_out = false;

    for(int i = 0; i < maxRow; i++){
        for(int j = 0; j < maxCol; j++)
        {
            filez >> tile; 

                if(filez.fail()){
                    deleteMap(dungeon,maxRow);
                    return nullptr;
                }

                if(tile == TILE_EXIT){
                    dungeon[i][j] = tile;
                    exit_out = true;
                }
                else if(tile == TILE_DOOR)
                {
                    dungeon[i][j] = tile;
                    exit_out = true;
                }
                else if(tile == TILE_PLAYER){
                    dungeon[i][j] = tile;
                }
                else if(tile == TILE_MONSTER){
                    dungeon[i][j] = tile;
                }
                else if(tile == TILE_PILLAR){
                    dungeon[i][j] = tile;
                }
                else if(tile == TILE_AMULET){
                    dungeon[i][j] = tile;
                }
                else if(tile == TILE_TREASURE)
                {
                    dungeon[i][j] = tile;
                }
                else if(tile == TILE_OPEN)
                {
                    dungeon[i][j] = tile;
                }
                else{
                    deleteMap(dungeon,maxRow);
                    return nullptr;
                }
            
            }
        }  
        //check for too many cells
        filez >> tile;
        
        if(!filez.fail()){ 
            deleteMap(dungeon,maxRow);
            return nullptr;
        }  
        // if exit door found should reset
        if(exit_out == false)
        {
            deleteMap(dungeon,maxRow);
            return nullptr;
        }

    dungeon [player.row][player.col] = TILE_PLAYER;
    return dungeon;
}


/**
 * TODO: Student implement this function
 * Translate the character direction input by the user into row or column change.
 * That is, updates the nextRow or nextCol according to the player's movement direction.
 * @param   input       Character input by the user which translates to a direction.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @updates  nextRow, nextCol
 * 
 */
void getDirection(char input, int& nextRow, int& nextCol) {

    if(input == MOVE_UP)
    {
        --nextRow;
    }
    if(input == MOVE_DOWN){
        ++nextRow;
    }
    if(input == MOVE_LEFT){
        --nextCol;
    }
    if(input == MOVE_RIGHT){
        ++nextCol;
    }

}

/**
 * TODO: [suggested] Student implement this function
 * Allocate the 2D map array.
 * Initialize each cell to TILE_OPEN.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @return  2D map array for the dungeon level, holds char type.
 */
char** createMap(int maxRow, int maxCol) {

    //check errors
    if(maxRow < 0 || maxCol < 0 )
    {
        return nullptr;
    }

    char** dungeon = new char* [maxRow]; // create the 2d array for the map

    for(int row = 0; row < maxRow; row++){ // just to get row
        dungeon[row] = new char[maxCol];
        for(int col = 0; col < maxCol; col++)
        {
            dungeon[row][col] = TILE_OPEN; // intialize to the tile
        }
    }
    return dungeon;
}

/**
 * TODO: Student implement this function
 * Deallocates the 2D map array.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @return None
 * @update map, maxRow
 */
void deleteMap(char**& map, int& maxRow) {


   if(map != nullptr){
        for(int x = 0;  x < maxRow; x++)
        {
            delete[] map[x];
            map[x] = nullptr; 
        }
        delete[] map;
        map = nullptr; 
   }

    maxRow = 0; 
    
}

/**
 * TODO: Student implement this function
 * Resize the 2D map by doubling both dimensions.
 * Copy the current map contents to the right, diagonal down, and below.
 * Do not duplicate the player, and remember to avoid memory leaks!
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height), to be doubled.
 * @param   maxCol      Number of columns in the dungeon table (aka width), to be doubled.
 * @return  pointer to a dynamically-allocated 2D array (map) that has twice as many columns and rows in size.
 * @update maxRow, maxCol
 */
char** resizeMap(char** map, int& maxRow, int& maxCol) {

    if(map == nullptr){

        return nullptr;
    }
    
    if(maxRow < 1 || maxCol < 1){
         return nullptr;
    }

    if(maxRow > INT32_MAX / maxCol)
    {
        return nullptr;
    }


    int row2 = maxRow; 
    char** temp_array = new char*[row2*2]; // new arry to double the dimensions

    for(int i = 0; i < row2*2; ++i)
    {
        temp_array[i] = new char[maxCol*2];
    }

    //copy to map
    // for(int i = 0; i < maxRow; i++){
    //     for(int j = 0; j < maxCol; j++)
    //     {
    //         temp_array[i][j] = map[i][j];
    //     }
    // }

    for(int i = 0; i < row2; i++)
    {
        for(int j = 0; j < maxCol; j++)
        {
            temp_array[i][j] = map[i][j];
            
            if(temp_array[i][j] == TILE_PLAYER)
            {
                temp_array[i][j + maxCol] = TILE_OPEN;
                temp_array[i + row2][j + maxCol] = TILE_OPEN;
                temp_array[i + row2][j] = TILE_OPEN;
            }
            else{
                 temp_array[i][j + maxCol] = map[i][j];
                 temp_array[i + row2][j + maxCol] = map[i][j];
                 temp_array[i + row2][j] = map[i][j];
            }


            
        }
    }
 

    deleteMap(map,row2);

    maxRow *= 2;
    maxCol *= 2;

    return temp_array;
}

/**
 * TODO: Student implement this function
 * Checks if the player can move in the specified direction and performs the move if so.
 * Cannot move out of bounds or onto TILE_PILLAR or TILE_MONSTER.
 * Cannot move onto TILE_EXIT without at least one treasure. 
 * If TILE_TREASURE, increment treasure by 1.
 * Remember to update the map tile that the player moves onto and return the appropriate status.
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object to by reference to see current location.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @return  Player's movement status after updating player's position.
 * @update map contents, player
 */
int doPlayerMove(char** map, int maxRow, int maxCol, Player& player, int nextRow, int nextCol) {

    if(nextRow < 0 || nextRow >= maxRow || nextCol < 0 || nextCol >= maxCol)
    {
        return STATUS_STAY; // impossible to move since out of bounds 
    }


    else if(map[nextRow][nextCol] == TILE_MONSTER || map[nextRow][nextCol] == TILE_PILLAR)
    {
        return STATUS_STAY; // can't pass through the pillars and monsters thereofore no movement
    }

    else if(map[nextRow][nextCol] == TILE_TREASURE){

        map[player.row][player.col] = TILE_OPEN; // update to open position
        player.row = nextRow; // preprae to take spot
        player.col = nextCol;
        ++player.treasure; // update the tressure
        map[player.row][player.col] = TILE_PLAYER;
        
        return STATUS_TREASURE;
    }

    else if(map[nextRow][nextCol] == TILE_AMULET)
    {
        map[player.row][player.col] = TILE_OPEN;
        player.row = nextRow;
        player.col = nextCol;
        map[player.row][player.col] = TILE_PLAYER; 

        return STATUS_AMULET;

    }

    else if(map[nextRow][nextCol] == TILE_DOOR)
    {
        map[player.row][player.col] = TILE_OPEN;
        player.row = nextRow;
        player.col = nextCol;
        map[player.row][player.col] = TILE_PLAYER;

        return STATUS_LEAVE;
    }

    else if(map[nextRow][nextCol] == TILE_EXIT)
    {
        if(player.treasure){
            map[player.row][player.col] = TILE_OPEN;
            player.row = nextRow;
            player.col = nextCol;
            map[player.row][player.col] = TILE_PLAYER;
            return STATUS_ESCAPE;
        }
        else{
            return STATUS_STAY;
        }
    }

    else if(map[nextRow][nextCol] == TILE_OPEN)
    {
        map[player.row][player.col] = TILE_OPEN;
        player.row = nextRow;
        player.col = nextCol;
        map[player.row][player.col] = TILE_PLAYER;
        return STATUS_MOVE;
    }

   return STATUS_STAY;
}

/**
 * TODO: Student implement this function
 * Update monster locations:
 * We check up, down, left, right from the current player position.
 * If we see an obstacle, there is no line of sight in that direction, and the monster does not move.
 * If we see a monster before an obstacle, the monster moves one tile toward the player.
 * We should update the map as the monster moves.
 * At the end, we check if a monster has moved onto the player's tile.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference for current location.
 * @return  Boolean value indicating player status: true if monster reaches the player, false if not.
 * @update map contents
 */
bool doMonsterAttack(char** map, int maxRow, int maxCol, const Player& player) {

    bool defeated = false;


    //comming from the top
    for(int i = player.row - 1; i > -1 ; i--)
    {
        if(map[i][player.col] == TILE_PILLAR)
        {
             break; 
        }
        else if(map[i][player.col] == TILE_MONSTER)
        {
                //move the monster colser to the players and check
                map[i][player.col] = TILE_OPEN;
                map[i+1][player.col] = TILE_MONSTER;
                if(i + 1 == player.row)
                {
                    defeated = true;
                }
            }
    }

    //checking pa bajo --- down 
    for(int j = player.row + 1; j < maxRow; j++)
    {
        if(map[j][player.col] == TILE_PILLAR)
        {
            break;
        }
        else if(map[j][player.col] == TILE_MONSTER)
        {
            map[j][player.col] = TILE_OPEN;
            map[j - 1][player.col] = TILE_MONSTER;
            if(j - 1 == player.row)
            {
                defeated = true;
            }
        }
    }
    //izquieda left 
    for(int k = player.col - 1; k >= 0; k--)
    {
        if(map[player.row][k] == TILE_PILLAR){
            break;
        }
        else if(map[player.row][k] == TILE_MONSTER)
        {
            map[player.row][k] = TILE_OPEN;
            map[player.row][k + 1] = TILE_MONSTER;
            if(k + 1 == player.col){
               defeated = true; 
            }
        }
        
    }

    //derecha right 
    for(int h = player.col + 1; h < maxCol; h++){

        if(map[player.row][h] == TILE_PILLAR){
            break;
        }
        else if(map[player.row][h] == TILE_MONSTER)
        {
            map[player.row][h] = TILE_OPEN;
            map[player.row][h - 1] = TILE_MONSTER;
            if(h - 1 == player.col)
            {
                defeated = true;
            } 
        }
    }

    return defeated;
}
