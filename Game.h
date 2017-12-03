#ifndef TEST_GAME_H
#define TEST_GAME_H

#include <memory>
#include <iostream>
#include <vector>
#include "Interpreter.h"
#include "Block.h"

using namespace std;

class Grid;
class Cell;
class Block;
class Level;
class Level0;
class Score;
class GraphicsDisplay;
class TextDisplay;
class Interpreter;

class Game {
    struct GameImpl;
    unique_ptr<GameImpl> gameImpl;

    /**
     * Changes the level to the given integer
     * @param newLevel
     */
    void switchLevel(int newLevel);

    /**
     * Checks if the a heavy operation is supposed to be performed based on the level
     * @return Returns true if heavy
     */
    bool checkHeavy();

public:

    Game();

    // Initializer methods
    /**
     * Create the interpreter to parse the command line args, and listen to user commands
     * @param argc The number of command line args
     * @param argv The array of command line args
     */
    void initInterpreter(int argc, char *argv[]);

    /**
     * Initializes all aspects of the game including level and grid
     * @param level The level to start at
     * @param seed The seed for the random number generator
     * @param blocksSequence The sequence of blocks from the file
     * @param graphicalEnabled True if graphical UI should be shown
     * @param highscore The highscore that was read from the saved file
     */
    void initGame(int level, int seed, const vector<char> &blocksSequence, bool graphicalEnabled, int highscore);

    void createBlock();
    // Basic Commands
    /**
     * Transforms the current block one unit to the left
     */
    void left();
    /**
     * Transforms the current block one unit to the right
     */
    void right();
    /**
     * Transforms the current block one 90 degrees clockwise
     */
    void clockwise();
    /**
     * Transforms the current block one 90 degrees counterclockwise
     */
    void counterClockwise();
    /**
     * Transforms the current block one unit down
     */
    void down();
    /**
     * Moves the current block down as far as it can go and switches to the next block
     */
    void drop();
    /**
     * Increase the current level by 1
     */
    void levelUp();
    /**
     * Decrease the current level by 1
     */
    void levelDown();

    /**
     * Change the current block to the one specified
     */
    void I();
    void J();
    void L();
    void O();
    void S();
    void Z();
    void T();

    /**
     * Restart the game
     */
    void restart();

    /**
     * Set if the block should be randomly generated or read from a file (not applicable for level 0)
     * @param noRandom True to read from a file, false to randomly generate
     */
    void random(bool noRandom);

    /**
     * Increment the current score given the number of lines removed
     * @param numberOfLinesDeleted
     */
    void incrementPointsByLinesDeleted(int numberOfLinesDeleted);

    void hint();

    /**
     * Get the current level
     */
    int getLevel();

    /**
     * Get the current score
     */
    int getScore();

    /**
     * Get the current Hi Score
     */
    int getHiScore();

    /**
     * Get the width of the board
     */
    int getWidth();

    /**
     * Get the height of the board
     */
    int getHeight();

    /**
     * Get the current block that is being played
     */
    shared_ptr<Block> getCurrentBlock();

    /**
     * Get the next block
     */
    shared_ptr<Block> getNextBlock() const;

    /**
     * Get a block that is 1x1
     */
    shared_ptr<Block> getABlock();

    /**
     * Get the board
     */
    vector<vector<shared_ptr<Cell>>> *getBoard();

    virtual ~Game();
};

#endif //TEST_GAME_H
