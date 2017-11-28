#include "Cell.h"

struct Cell::CellImpl {
    int x;
    int y;
    char c;

    CellImpl() : x{0}, y{0}, c{' '} {}

    CellImpl(int x, int y, char c) : x{x}, y{y}, c{c} {}
};

Cell::Cell(int x, int y, char c /* = ' ' */) : cellImpl{new CellImpl{x, y, c}} {}

Cell::Cell() : cellImpl{new CellImpl{}} {}

int Cell::getX() const {
    return cellImpl->x;
}

void Cell::setX(int x) {
    cellImpl->x = x;
}

int Cell::getY() const {
    return cellImpl->y;
}

void Cell::setY(int y) {
    cellImpl->y = y;
}

char Cell::getC() const {
    return cellImpl->c;
}

void Cell::setC(char c) {
    cellImpl->c = c;
}

std::ostream &operator<<(std::ostream &os, const Cell &cell) {
    os << cellImpl->c;
    return os;
}

Cell::~Cell() {

}
