#include "Level.h"
#include "Cell.h"

struct Level::LevelImpl {
    vector<char> blockSequence;
    int blockPosition = 0;
    bool noRandom = true;

    explicit LevelImpl(const vector<char> &blockSequence) : blockSequence(blockSequence) {}
};

Level::Level(const vector<char> &blockSequence) : levelImpl{make_unique<LevelImpl>(blockSequence)} {}

vector<shared_ptr<Cell>> Level::makeIBlock() {
    vector<shared_ptr<Cell>> cells;

    cells.emplace_back(make_shared<Cell>(0, 0, 'I'));
    cells.emplace_back(make_shared<Cell>(1, 0, 'I'));
    cells.emplace_back(make_shared<Cell>(2, 0, 'I'));
    cells.emplace_back(make_shared<Cell>(3, 0, 'I'));

    return cells;
}

vector<shared_ptr<Cell>> Level::makeJBlock() {
    vector<shared_ptr<Cell>> cells;

    cells.emplace_back(make_shared<Cell>(0, 1, 'J'));
    cells.emplace_back(make_shared<Cell>(1, 1, 'J'));
    cells.emplace_back(make_shared<Cell>(2, 1, 'J'));
    cells.emplace_back(make_shared<Cell>(2, 0, 'J'));

    return cells;
}

vector<shared_ptr<Cell>> Level::makeLBlock() {
    vector<shared_ptr<Cell>> cells;

    cells.emplace_back(make_shared<Cell>(0, 0, 'L'));
    cells.emplace_back(make_shared<Cell>(0, 1, 'L'));
    cells.emplace_back(make_shared<Cell>(1, 1, 'L'));
    cells.emplace_back(make_shared<Cell>(2, 1, 'L'));

    return cells;
}

vector<shared_ptr<Cell>> Level::makeOBlock() {
    vector<shared_ptr<Cell>> cells;

    cells.emplace_back(make_shared<Cell>(0, 0, 'O'));
    cells.emplace_back(make_shared<Cell>(1, 0, 'O'));
    cells.emplace_back(make_shared<Cell>(0, 1, 'O'));
    cells.emplace_back(make_shared<Cell>(1, 1, 'O'));

    return cells;}

vector<shared_ptr<Cell>> Level::makeSBlock() {
    vector<shared_ptr<Cell>> cells;

    cells.emplace_back(make_shared<Cell>(2, 0, 'S'));
    cells.emplace_back(make_shared<Cell>(1, 0, 'S'));
    cells.emplace_back(make_shared<Cell>(1, 1, 'S'));
    cells.emplace_back(make_shared<Cell>(0, 1, 'S'));

    return cells;
}

vector<shared_ptr<Cell>> Level::makeZBlock() {
    vector<shared_ptr<Cell>> cells;

    cells.emplace_back(make_shared<Cell>(0, 0, 'Z'));
    cells.emplace_back(make_shared<Cell>(1, 0, 'Z'));
    cells.emplace_back(make_shared<Cell>(1, 1, 'Z'));
    cells.emplace_back(make_shared<Cell>(2, 1, 'Z'));

    return cells;
}

vector<shared_ptr<Cell>> Level::makeTBlock() {
    vector<shared_ptr<Cell>> cells;

    cells.emplace_back(make_shared<Cell>(0, 0, 'T'));
    cells.emplace_back(make_shared<Cell>(1, 0, 'T'));
    cells.emplace_back(make_shared<Cell>(2, 0, 'T'));
    cells.emplace_back(make_shared<Cell>(1, 1, 'T'));

    return cells;
}

shared_ptr<Block> Level::makeABlock() {
    vector<shared_ptr<Cell>> cells;

    cells.emplace_back(make_shared<Cell>(0, 0, '*'));

    return make_shared<Block>(cells);
}

void Level::resetBlockSequence() {
    levelImpl->blockPosition = 0;
}

void Level::setNoRandom(bool noRandom) {
    levelImpl->noRandom = noRandom;
}

bool Level::isNoRandom() const {
    return levelImpl->noRandom;
}

shared_ptr<Block> Level::makeSequenceBlock() {
    if (levelImpl->blockPosition == levelImpl->blockSequence.size()) {
        levelImpl->blockPosition = 0;
    }

    shared_ptr<Block> block;

    switch (levelImpl->blockSequence.at(levelImpl->blockPosition)) {
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

    levelImpl->blockPosition++;
    return block;
}

Level::~Level() {}
