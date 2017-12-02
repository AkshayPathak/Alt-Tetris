#ifndef TEST_LEVEL2_H
#define TEST_LEVEL2_H

#include "Level.h"

class Block;

class Level2: public Level {
public:
    Level2();
    ~Level2();
    Block &makeBlock() override;
    int getLevel() override;
};



#endif //TEST_LEVEL2_H
