#ifndef TEST_INTERPRETER_H
#define TEST_INTERPRETER_H

#include <iostream>
#include <vector>
#include <memory>
#include "Game.h"

using namespace std;

class Game;

class Interpreter {

public:
    void init(Game *game, int argc, char *argv[]);
};

#endif //TEST_INTERPRETER_H
