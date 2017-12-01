
#ifndef TEST_LEVEL0_H
#define TEST_LEVEL0_H

#include "Level.h"

class Block;

class Level0: public Level {
public:
    Level0();
    ~Level0();
    Block &makeBlock() override;
    int getLevel() override;
};

#endif //TEST_LEVEL0_H
