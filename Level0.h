#ifndef QUADRIS_LEVEL1_H
#define QUADRIS_LEVEL1_H

#include "Level.h"
#include <cstdlib>

using namespace std;

class Level0 : public Level {

public:

    explicit Level0(vector<char> fileSequence);

    int getLevel() override;

    shared_ptr<Block> makeBlock() override;

    ~Level0() override;

};


#endif //QUADRIS_LEVEL1_H
