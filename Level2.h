#ifndef TEST_LEVEL2_H
#define TEST_LEVEL2_H

#include "Level.h"

class Block;

class Level2 : public Level {

public:
    explicit Level2(const vector<char> &blockSequence);

    shared_ptr<Block> makeBlock() override;

    int getLevel() override;

    ~Level2() override;
};


#endif //TEST_LEVEL2_H
