#include "Level0.h"

shared_ptr<Block> Level0::makeBlock() {
    return makeSequenceBlock();
}

Level0::~Level0() {}

Level0::Level0(vector<char> fileSequence) : Level{fileSequence} {}

int Level0::getLevel() {
    return 0;
}
