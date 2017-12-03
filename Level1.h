#ifndef TEST_LEVEL1_H
#define TEST_LEVEL1_H

#include "Level.h"

class Block;

class Level1: public Level {
public:
    shared_ptr<Block> makeBlock() override;
    int getLevel() override;

    Level1();
    ~Level1() override;
};


#endif //TEST_LEVEL1_H
