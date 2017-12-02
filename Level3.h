#ifndef TEST_LEVEL3_H
#define TEST_LEVEL3_H

#include "Level.h"

class Block;

class Level3: public Level {
public:
    Level3();
    ~Level3();
    shared_ptr<Block> makeBlock() override;
    int getLevel() override;
};



#endif //TEST_LEVEL3_H
