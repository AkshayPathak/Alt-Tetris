#ifndef TEST_LEVEL_H
#define TEST_LEVEL_H

#include <iostream>
#include "Block.h"

class Level {
    int lvl;
public:
    Block &makeBlock();
    int getLevel();
    int setLevel(int newLevel);
};


#endif //TEST_LEVEL_H
