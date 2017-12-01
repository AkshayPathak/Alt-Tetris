#ifndef TEST_LEVEL_H
#define TEST_LEVEL_H

#include <iostream>
#include <memory>
#include "Block.h"

class Level {
public:
    virtual ~Level()=0;
    virtual Block &makeBlock()=0;
    virtual int getLevel()=0;
    void setLevel(int newLevel);
};

#endif //TEST_LEVEL_H
