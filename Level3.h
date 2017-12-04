#ifndef QUADRIS_LEVEL3_H
#define QUADRIS_LEVEL3_H

#include "Level.h"

class Block;

class Level3 : public Level {

public:

    Level3(const vector<char> &blockSequence);

    shared_ptr<Block> makeBlock() override;

    int getLevel() override;

    ~Level3() override;
};


#endif //QUADRIS_LEVEL3_H
