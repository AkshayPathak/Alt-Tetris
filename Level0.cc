#include "Level0.h"

shared_ptr<Block> Level0::makeBlock() {

    switch (fileSequence.at(position)) {
        case 'I':
            return make_shared<Block>(makeIBlock());
        case 'J':
            return make_shared<Block>(makeJBlock());
        case 'L':
            return make_shared<Block>(makeLBlock());
        case 'O':
            return make_shared<Block>(makeOBlock());
        case 'S':
            return make_shared<Block>(makeSBlock());
        case 'Z':
            return make_shared<Block>(makeZBlock());
        case 'T':
            return make_shared<Block>(makeTBlock());
    }



}

Level0::~Level0() {}

Level0::Level0(vector<char> fileSequence) : fileSequence{fileSequence} {}

int Level0::getLevel() {
    return 0;
}
