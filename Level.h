#ifndef TEST_LEVEL_H
#define TEST_LEVEL_H

#include <iostream>
#include <memory>
#include "Block.h"

using  namespace std;

class Level {

public:
    virtual Block makeBlock() = 0;

    vector<vector<shared_ptr<Cell>>> makeIBlock();
    vector<vector<shared_ptr<Cell>>> makeJBlock();
    vector<vector<shared_ptr<Cell>>> makeLBlock();
    vector<vector<shared_ptr<Cell>>> makeOBlock();
    vector<vector<shared_ptr<Cell>>> makeSBlock();
    vector<vector<shared_ptr<Cell>>> makeZBlock();
    vector<vector<shared_ptr<Cell>>> makeTBlock();

    virtual ~Level();

};

#endif //TEST_LEVEL_H
