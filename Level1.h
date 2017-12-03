#ifndef TEST_LEVEL5_H
#define TEST_LEVEL5_H

#include "Level.h"

class Block;

class Level1 : public Level {

public:
    explicit Level1(const vector<char> &blockSequence);

    shared_ptr<Block> makeBlock() override;

    int getLevel() override;

    ~Level1() override;
};
#endif //TEST_LEVEL5_H
