#include "Level0.h"

Block Level0::makeBlock() {

    switch (fileSequence.at(position)) {
        case 'I':
            return Block{makeIBlock()};
        case 'J':
            return Block{makeJBlock()};
        case 'L':
            return Block{makeLBlock()};
        case 'O':
            return Block{makeOBlock()};
        case 'S':
            return Block{makeSBlock()};
        case 'Z':
            return Block{makeZBlock()};
        case 'T':
            return Block{makeTBlock()};
    }



}

Level0::~Level0() {}

Level0::Level0(vector<char> fileSequence) : fileSequence{fileSequence} {}

int Level0::getLevel() {
    return 0;
}
