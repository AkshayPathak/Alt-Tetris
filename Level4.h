#ifndef QUADRIS_LEVEL4_H
#define QUADRIS_LEVEL4_H

#include "Level.h"

class Block;

class Level4 : public Level {

public:

    Level4(const vector<char> &blockSequence);

    ~Level4() override;

    shared_ptr<Block> makeBlock() override;

    int getLevel() override;
};


#endif //QUADRIS_LEVEL4_H
