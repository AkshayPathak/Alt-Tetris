#include "Level0.h"

shared_ptr<Block> Level0::makeBlock() {

    shared_ptr<Block> block;

    switch (fileSequence.at(position)) {
        case 'I':
            block = make_shared<Block>(makeIBlock());
            break;
        case 'J':
            block = make_shared<Block>(makeJBlock());
            break;
        case 'L':
            block = make_shared<Block>(makeLBlock());
            break;
        case 'O':
            block = make_shared<Block>(makeOBlock());
            break;
        case 'S':
            block = make_shared<Block>(makeSBlock());
            break;
        case 'Z':
            block = make_shared<Block>(makeZBlock());
            break;
        case 'T':
            block = make_shared<Block>(makeTBlock());
            break;
    }

    position++;
    return block;

}

Level0::~Level0() {}

Level0::Level0(vector<char> fileSequence) : fileSequence{fileSequence} {}

int Level0::getLevel() {
    return 0;
}
