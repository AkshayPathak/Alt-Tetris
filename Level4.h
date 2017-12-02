#ifndef TEST_LEVEL4_H
#define TEST_LEVEL4_H

#include "Level.h"

class Block;

class Level4: public Level {
public:
    Level4();
    ~Level4();
    Block &makeBlock() override;
    int getLevel() override;
};



#endif //TEST_LEVEL4_H
