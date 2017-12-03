#include "Level4.h"

Level4::Level4() = default;

Level4::~Level4() = default;

shared_ptr<Block> Level4::makeBlock() {
    shared_ptr<Block> block;

    int num = rand() % 9;

    if(!num || num == 1) {
        block = make_shared<Block>(makeSBlock());
    } else if(num == 2 || num == 3) {
        block = make_shared<Block>(makeZBlock());
    } else if(num == 4) {
        block = make_shared<Block>(makeIBlock());
    } else if(num == 5) {
        block = make_shared<Block>(makeJBlock());
    } else if(num == 6) {
        block = make_shared<Block>(makeLBlock());
    } else if(num == 7) {
        block = make_shared<Block>(makeOBlock());
    } else if(num == 8) {
        block = make_shared<Block>(makeTBlock());
    }

    return block;
}


int Level4::getLevel() {
    return 4;
}

