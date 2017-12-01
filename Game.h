#ifndef TEST_GAME_H
#define TEST_GAME_H

#include <memory>
#include <iostream>
#include <vector>
#include "Interpreter.h"

using namespace std;

class Grid;
class Cell;
class Block;
class Level;
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

    void initGame(int level, int seed, vector<shared_ptr<Block>> blocksSequence, bool graphicalEnabled);

    void createBlock();

    Block getNextBlock() const;    // cant be reference or else pointer to the stack

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
    void random();
    void noRandom(string inFile);
    void sequence(string inFile);
    void restart();
    void hint();

    virtual ~Game();
};

#endif //TEST_GAME_H
