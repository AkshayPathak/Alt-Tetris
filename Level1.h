#ifndef TEST_LEVEL1_H
#define TEST_LEVEL1_H

#include "Level.h"

class Block;

class Level1: public Level {
public:
    Block makeBlock() override;
    int getLevel() override;
};


#endif //TEST_LEVEL1_H
