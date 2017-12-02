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

public:

    Game();

    void initInterpreter(int argc, char *argv[]);

    void initGame(int level, int seed, vector<char> blocksSequence, bool graphicalEnabled);

    void createBlock();

    // Basic Commands
    void left();
    void right();
    void clockwise();
    void counterClockwise();
    void down();
    void drop();
    void levelUp();
    void levelDown();
    void I();
    void J();
    void L();
    void O();
    void S();
    void Z();
    void T();
    void restart();
    void hint();

    // Getters and setter
    shared_ptr<Block> getNextBlock() const;    // cant be reference or else pointer to the stack

    //friend class TextDisplay;
    // getters and setters used by textdisplay
    int getLevel();
    int getScore();
    int getHiScore();
    int getWidth();
    int getHeight();
    shared_ptr<Block> getCurrentBlock();
    vector<vector<shared_ptr<Cell>>> *getBoard();

    virtual ~Game();
};

#endif //TEST_GAME_H
