#include "Block.h"
#include "Cell.h"
#include <iostream>

void Block::swap(Block &other) {
    using std::swap;
    swap(cells, other.cells);
}

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

    int pivotX;
    int pivotY;

    // Finding the pivot
    for (int i = 0; i < getCells().size(); i++) {
        if (getCells().at(i)->isPivot()) {
            pivotX = getCells().at(i)->getX();
            pivotY = getCells().at(i)->getY();
            break;
        }
    }

    // Getting each piece relative to the pivot
    for (int i = 0; i < getCells().size(); i++) {
        if (getCells().at(i)->isPivot()) {
            continue;
        } else {
            // 2nd piece first piece (pivot)
            int relativeX = getCells().at(i)->getX() - pivotX;
            int relativeY = getCells().at(i)->getY() - pivotY;
            int newRelativeX = -relativeY;
            int newRelativeY = relativeX;

            getCells().at(i)->setX(pivotX + newRelativeX);
            getCells().at(i)->setY(pivotY + newRelativeY);
        }
    }
}


void Block::transformCounterClockwise() {
    transformClockwise();
    transformClockwise();
    transformClockwise();
}

std::vector<std::shared_ptr<Cell>> Block::getCells() const{
    return cells;
}

Block::Block(std::vector<std::shared_ptr<Cell>> c) {
    cells = std::vector<std::shared_ptr<Cell>>(c.size());
    for(int i = 0; i < c.size(); i++) {
        cells.at(i) = std::make_shared<Cell>(*(c.at(i)));
    }
}

Block::Block(const Block &b) {
    cells = std::vector<std::shared_ptr<Cell>>(b.getCells().size());
    for(int i = 0; i < b.getCells().size(); i++) {
        cells.at(i) = std::make_shared<Cell>(*(b.getCells().at(i)));
    }
}

Block::Block() {}