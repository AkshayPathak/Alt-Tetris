#include "Level1.h"
#include "Level.h"
#include "Level1.h"

shared_ptr<Block> Level1::makeBlock() {

    if (isNoRandom()) {
        return makeSequenceBlock();
    }

    shared_ptr<Block> block;

    int num = std::rand() % 12;

    if(!num) {
        block = make_shared<Block>(makeSBlock());
    } else if(num == 1) {
        block = make_shared<Block>(makeZBlock());
    } else if(num == 2 || num == 3) {
        block = make_shared<Block>(makeIBlock());
    } else if(num == 4 || num == 5) {
        block = make_shared<Block>(makeJBlock());
    } else if(num == 6 || num == 7) {
        block = make_shared<Block>(makeLBlock());
    } else if(num == 8 || num == 9) {
        block = make_shared<Block>(makeOBlock());
    } else if(num == 10 || num == 11) {
        block = make_shared<Block>(makeTBlock());
    }

    return block;
}

int Level1::getLevel() {
    return 1;
}

Level1::Level1(const vector<char> &blockSequence) : Level{blockSequence} {}

Level1::~Level1() {}

