#include "Block.h"
#include "Cell.h"

void Block::swap(Block &other) {
    using std::swap;
    swap(cells, other.cells);
}

Block::Block() {}

Block::Block(const Block &other) : cells{other.cells} {}

Block &Block::operator=(const Block &other) {
    Block b{other};
    swap(b);
    return *this;
}

Block &Block::operator=(Block &&other) {
    swap(other);
    return *this;
}

void Block::transformLeft() {
    for (auto &cell : cells) {
        cell->setX(cell->getX() - 1);
    }
}

void Block::transformRight() {
    for (auto &cell : cells) {
        cell->setX(cell->getX() + 1);
    }
}

void Block::transformDown() {
    for (auto &cell : cells) {
        cell->setY(cell->getY() + 1);
    }
}

void Block::transformClockwise() {
    // TODO: Implement this
}

void Block::transformCounterClockwise() {
    // TODO: Implement this
}

std::vector<std::shared_ptr<Cell>> Block::getCells() const{
    return cells;
}
