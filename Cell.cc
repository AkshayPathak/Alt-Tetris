#include "Cell.h"

Cell::Cell(int x, int y, char c /* = ' ' */) : x{x}, y{x}, c{c} {}

Cell::Cell() : x{0}, y{0}, c{'c'} {}

int Cell::getX() const {
    return x;
}

void Cell::setX(int x) {
    Cell::x = x;
}

int Cell::getY() const {
    return y;
}

void Cell::setY(int y) {
    Cell::y = y;
}

char Cell::getC() const {
    return c;
}

void Cell::setC(char c) {
    Cell::c = c;
}

std::ostream &operator<<(std::ostream &os, const Cell &cell) {
    os << cell.c;
    return os;
}
