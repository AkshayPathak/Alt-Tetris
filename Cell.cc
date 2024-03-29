#include "Cell.h"
#include <memory>

using namespace std;

struct Cell::CellImpl {
    int x;
    int y;
    char c;
    bool pivot;

    CellImpl() : x{0}, y{0}, c{' '}, pivot{false} {}

    CellImpl(int x, int y, char c, bool pivot) : x{x}, y{y}, c{c}, pivot{pivot} {}
};

Cell::Cell(int x, int y, char c, bool pivot) : cellImpl{std::make_unique<CellImpl>(x, y, c, pivot)} {}

Cell::Cell() : cellImpl{std::make_unique<CellImpl>()} {}

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

bool Cell::isPivot() const {
    return cellImpl->pivot;
}

void Cell::setPivot(bool pivot) {
    cellImpl->pivot = pivot;
}

std::ostream &operator<<(std::ostream &os, const Cell &cell) {
    os << cell.cellImpl->c;
    return os;
}

// copy ctor
Cell::Cell(const Cell &c) : cellImpl{make_unique<CellImpl>()} {
    setX(c.getX());
    setY(c.getY());
    setC(c.getC());
    setPivot(c.isPivot());
}

// for Graphics
void Cell::draw(shared_ptr<Xwindow> w, int x, int y,int width, int height) {
    if (cellImpl->c == ' ') {
        w->fillRectangle(x, y, width, height, Xwindow::Black);
    } else if (cellImpl->c == 'I') {
        w->fillRectangle(x, y, width, height, Xwindow::Red);
    } else if (cellImpl->c == 'J') {
        w->fillRectangle(x, y, width, height, Xwindow::Green);
    } else if (cellImpl->c == 'L') {
        w->fillRectangle(x, y, width, height, Xwindow::Blue);
    } else if (cellImpl->c == 'O') {
        w->fillRectangle(x, y, width, height, Xwindow::Cyan);
    } else if (cellImpl->c == 'Z') {
        w->fillRectangle(x, y, width, height, Xwindow::Yellow);
    } else if (cellImpl->c == 'S') {
        w->fillRectangle(x, y, width, height, Xwindow::Magenta);
    } else if (cellImpl->c == 'T') {
        w->fillRectangle(x, y, width, height, Xwindow::Orange);
    } else if (cellImpl->c == '*') {
        w->fillRectangle(x, y, width, height, Xwindow::Brown);
    }
}

Cell::~Cell() {}
