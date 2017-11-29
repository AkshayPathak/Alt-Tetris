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
    unique_ptr<Interpreter> inter;

public:
    void init(int argc, char argv[]);

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
};


#endif //TEST_GAME_H
