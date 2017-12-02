#ifndef TEST_LEVEL_H
#define TEST_LEVEL_H

#include <iostream>
#include <memory>
#include "Block.h"

using  namespace std;

class Level {

public:
    virtual Block makeBlock() = 0;

    vector<shared_ptr<Cell>> makeIBlock();
    vector<shared_ptr<Cell>> makeJBlock();
    vector<shared_ptr<Cell>> makeLBlock();
    vector<shared_ptr<Cell>> makeOBlock();
    vector<shared_ptr<Cell>> makeSBlock();
    vector<shared_ptr<Cell>> makeZBlock();
    vector<shared_ptr<Cell>> makeTBlock();

    virtual int getLevel() = 0;
    virtual ~Level();

};

#endif //TEST_LEVEL_H
