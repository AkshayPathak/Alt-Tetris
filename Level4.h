#ifndef TEST_LEVEL4_H
#define TEST_LEVEL4_H

#include "Level.h"

class Block;

class Level4 : public Level {

public:

    Level4(const vector<char> &blockSequence);

    ~Level4() override;

    shared_ptr<Block> makeBlock() override;

    int getLevel() override;
};


#endif //TEST_LEVEL4_H
