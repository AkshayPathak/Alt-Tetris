#ifndef TEST_GRID_H
#define TEST_GRID_H

#include <iostream>
#include <vector>
#include <memory>
#include "Subject.h"
#include "Cell.h"

using namespace std;

class Game;

class Block;

class Grid : public Subject {

    struct GridImpl;
    unique_ptr<GridImpl> gridImpl;

public:

    Grid(Game *game, int x = 11, int y = 18);

    /**
     * Initializes the grid to empty cells
     */
    void init();

    /**
     * Puts the current block on the board permanently
     */
    void setBlock();

    /**
     * Transforms the current block one unit to the left
     * @param performHeavy True to move the block one unit down
     */
    void transformLeft(bool performHeavy = false);

    /**
     * Transforms the current block one unit to the right
     * @param performHeavy True to move the block one unit down
     */
    void transformRight(bool performHeavy = false);

    /**
     * Transforms the current block one unit down
     */
    void transformDown();

    /**
     * Transforms the current block one unit to the left
     */
    void transformDrop();

    /**
     * Transforms the current block 90 degrees clockwise
     * @param performHeavy
     */
    void transformClockwise(bool performHeavy = false);

    /**
     * Transforms the current block 90 degrees counterclockwise
     * @param performHeavy
     */
    void transformCounterClockwise(bool performHeavy = false);

    /**
     * Get the width of the board
     */
    int getWidth();

    /**
     * Get the height of the board
     */
    int getHeight();

    /**
     * Get the block that is currently in play
     */
    shared_ptr<Block> getBlock();

    /**
     * Get the board
     */
    vector<vector<shared_ptr<Cell>>> *getBoard();

    /**
     * Change the current block to the newBlock
     */
    void setCurrentBlock(shared_ptr<Block> newBlock);

    /**
     * Transform the block down by n units without printing the board
     * @param n
     */
    void numDown(int n);

    /**
     * Transform the block right by n units without printing the board
     * @param n
     */
    void numRight(int n);

    ~Grid();

private:

    /**
     * Check if the transformed block is in a valid position on the board
     */
    bool invalidInput(const Block &);

    /**
     * Check if the transformed block is overlapping another block on the board
     * @return
     */
    bool overlap(const Block &);

    /**
     * Check if the entire row is full
     */
    bool fullRow(int row) ;

    /**
     * Delete the given row and move the board down
     */
    void shiftBoard(int row);
};

#endif
