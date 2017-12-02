#ifndef TEST_LEVEL1_H
#define TEST_LEVEL1_H

#include "Level.h"

using namespace std;

class Level0 : public Level {

    vector<char> fileSequence;
    int position = 0;

public:

    explicit Level0(vector<char> fileSequence);

    int getLevel() override;

    shared_ptr<Block> makeBlock() override;

    ~Level0() override;

};


#endif //TEST_LEVEL1_H
