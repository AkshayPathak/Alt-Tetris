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

    // Getters and setter
    void switchLevel(int newLevel);

public:

    Game();

    void initInterpreter(int argc, char *argv[]);

    void initGame(int level, int seed, const vector<char> &blocksSequence, bool graphicalEnabled);

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
    void random(bool noRandom);

    void hint();

    shared_ptr<Block> getNextBlock() const;    // cant be reference or else pointer to the stack
    //friend class TextDisplay;
    // getters and setters used by textdisplay
    int getLevel();
    int getScore();
    int getHiScore();
    int getWidth();
    int getHeight();
    void incrementPointsByLinesDeleted(int numberOfLinesDeleted);
    shared_ptr<Block> getCurrentBlock();

    vector<vector<shared_ptr<Cell>>> *getBoard();

    virtual ~Game();

    bool checkHeavy();
};

#endif //TEST_GAME_H
