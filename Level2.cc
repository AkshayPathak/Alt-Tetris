#include "Level2.h"

Level2::Level2(const vector<char> &blockSequence) : Level(blockSequence) {}

shared_ptr<Block> Level2::makeBlock() {

    if (isNoRandom()) {
        return makeSequenceBlock();
    }

    shared_ptr<Block> block;

    int num = rand() % 7;

    if(!num) {
        block = make_shared<Block>(makeSBlock());
    } else if(num == 1) {
        block = make_shared<Block>(makeZBlock());
    } else if(num == 2) {
        block = make_shared<Block>(makeIBlock());
    } else if(num == 3) {
        block = make_shared<Block>(makeJBlock());
    } else if(num == 4) {
        block = make_shared<Block>(makeLBlock());
    } else if(num == 5) {
        block = make_shared<Block>(makeOBlock());
    } else if(num == 6) {
        block = make_shared<Block>(makeTBlock());
    }

    return block;
}

int Level2::getLevel() {
    return 2;
}

Level2::~Level2() = default;

