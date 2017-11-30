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

Block &Block::operator=(Block &&other) noexcept {
    swap(other);
    return *this;
}

void Block::transformLeft() {
    for (auto &cell : cells) {
        cell->getX();
    }
}

void Block::transformRight() {
    // TODO: Implement this
}

void Block::transformDown() {
    // TODO: Implement this
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
