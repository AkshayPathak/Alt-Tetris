#include "Block.h"
#include "Cell.h"
#include <iostream>

void Block::swap(Block &other) {
    using std::swap;
    swap(cells, other.cells);
}

Block::Block() {}


Block &Block::operator=(const Block &other) {
    Block b{other};    // TODO: can't make this cause block doesn't have a copy constructor... so referencing deleted function
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

// For transformClockwise:

struct Posn {
    int x,y;
};

Posn Block::lowerLeft() {
    int minX, minY;
    int len = cells.size();
    for(int i=0; i < len; ++i) {
        if(!i) {
            minX = cells.at(i)->getX();
            minY = cells.at(i)->getY();
            continue;
        }
        if(cells.at(i)->getX() < minX) {
            minX = cells.at(i)->getX();
        }
        if(cells.at(i)->getY() < minY) {
            minY = cells.at(i)->getY();
        }
    }
    Posn p{minX,minY};
    return p;
}

Posn Block::upperRight() {
    int maxX, maxY;
    int len = cells.size();
    for(int i=0; i < len; ++i) {
        if(!i) {
            maxX = cells.at(i)->getX();
            maxY = cells.at(i)->getY();
            continue;
        }
        if(cells.at(i)->getX() > maxX) {
            maxX = cells.at(i)->getX();
        }
        if(cells.at(i)->getY() > maxY) {
            maxY = cells.at(i)->getY();
        }
    }
    Posn p{maxX,maxY};
    return p;
}


void Block::transformClockwise() {
    Posn bottomLeft = lowerLeft();
    Posn topRight = upperRight();
    int len = cells.size();

    for(int i=0; i < len; ++i) {
        int oldX = cells.at(i)->getX();
        int oldY = cells.at(i)->getY();
        cells.at(i)->setX(bottomLeft.x + oldY - bottomLeft.y);
        cells.at(i)->setY(bottomLeft.y - oldX + topRight.x);
    }
    int shift_up = topRight.y - upperRight().y;
    for(int i=0; i < len; ++i) {
        cells.at(i)->setY(cells.at(i)->getY()+shift_up);
        //std::cout << "(" << cells.at(i)->getX() << "," << cells.at(i)->getY() << ")" << std::endl;
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

// TODO: you didn't have copy ctors in cell... AND... you would be getting a copy of the pointers not the values
// sort of copy ctor... not another block tho
Block::Block(std::vector<std::shared_ptr<Cell>> c) {
    cells = std::vector<std::shared_ptr<Cell>>(c.size());
    for(int i = 0; i < c.size(); i++) {
        cells.at(i) = std::make_shared<Cell>(*(c.at(i)));
    }
}

// copy ctor i wrote this before... dunno if still need
Block::Block(const Block &b) {
    cells = std::vector<std::shared_ptr<Cell>>(b.getCells().size());
    for(int i = 0; i < b.getCells().size(); i++) {
        cells.at(i) = std::make_shared<Cell>(*(b.getCells().at(i)));
    }
}
