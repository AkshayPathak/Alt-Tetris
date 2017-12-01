#ifndef TEST_LEVEL_H
#define TEST_LEVEL_H

#include <iostream>
#include <memory>
#include "Block.h"

class Level {
    struct LevelImpl;
    std::unique_ptr<LevelImpl> levelImpl;
public:
    Block &makeBlock();
    int getLevel();
    int setLevel(int newLevel);
};

#endif //TEST_LEVEL_H
