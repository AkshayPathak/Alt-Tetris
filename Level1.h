#ifndef QUADRIS_LEVEL5_H
#define QUADRIS_LEVEL5_H

#include "Level.h"

class Block;

class Level1 : public Level {

public:
    explicit Level1(const vector<char> &blockSequence);

    shared_ptr<Block> makeBlock() override;

    int getLevel() override;

    ~Level1() override;
};
#endif //QUADRIS_LEVEL5_H
