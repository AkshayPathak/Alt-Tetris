#ifndef TEST_LEVEL_H
#define TEST_LEVEL_H

#include <iostream>
#include <memory>
#include "Block.h"

using  namespace std;

class Level {

    vector<char> blockSequence;
    int blockPosition = 0;

    bool noRandom = true;

public:

    explicit Level(const vector<char> &blockSequence);

    virtual shared_ptr<Block> makeBlock() = 0;
    shared_ptr<Block> makeSequenceBlock();

    vector<shared_ptr<Cell>> makeIBlock();
    vector<shared_ptr<Cell>> makeJBlock();
    vector<shared_ptr<Cell>> makeLBlock();
    vector<shared_ptr<Cell>> makeOBlock();
    vector<shared_ptr<Cell>> makeSBlock();
    vector<shared_ptr<Cell>> makeZBlock();

    vector<shared_ptr<Cell>> makeTBlock();

    void setNoRandom(bool noRandom);

    bool isNoRandom() const;

    virtual int getLevel() = 0;
    virtual ~Level();

};

#endif //TEST_LEVEL_H
