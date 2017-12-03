#ifndef TEST_INTERPRETER_H
#define TEST_INTERPRETER_H

#include <iostream>
#include <vector>
#include <memory>
#include "Game.h"

using namespace std;

class Game;

class Interpreter {

    int level = 0;
    int seed = 123;
    bool graphicsEnabled = true;
    string scriptFileName = "sequence.txt";
    vector<char> blockSequence;

    typedef void (Game::*GameFunction)();

    void interpretCommandLineArgs(int argc, char *const *argv);

    void parseSequenceFile();

    int getMultiplier(string &cmd);

    void multiplierFunction(Game *game, int multiplier, GameFunction function);

    string matchCommand(const string &cmd);

public:

    void init(Game *game, int argc, char *argv[]);
};

#endif //TEST_INTERPRETER_H
