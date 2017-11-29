#include "Grid.h"
#include "Cell.h"

using namespace std;

struct Grid::gridImpl {
    vector<vector<shared_ptr<Cell>>> board;  // not sure if this should be shared pointer
    void shiftBoard();
};

// deletes a bottom row, adds top row, changes index of every single Cell
void Grid::gridImpl::shiftBoard() {
    board.pop_back();
    vector<shared_ptr<Cell>> first = vector<shared_ptr<Cell>>(11);
    for(size_t i = 0, j = 0; i < 11; i++) {
        first.at(i) = make_shared(new Cell(i, j));
    }
    board.insert(board.begin(), first);

    // switching every cell after the first row
    for (size_t i = 1; i < 18; i++) {
        for (size_t j = 0; j < 11; j++) {
            board.at(i).at(j)->setX(j);
            board.at(i).at(j)->setY(i);
        }
    }
}


//--------------------------------------------------------------------------------
// Public
Grid::Grid() : pImpl{new gridImpl{}} {
    for (size_t i = 0; i < 18; i++) {
        for (size_t j = 0; j < 11; j++) {
            pImpl->board.at(i).emplace_back(make_shared(new Cell(i,j)));
        }
    }
}

Grid::~Grid() = default;

void Grid::init() {
    // clears the board first
    for (size_t i = 0; i < pImpl->board.size(); i++) {
        pImpl->board.at(i).clear();
    }

    // constructs empty board
    for (size_t i = 0; i < 18; i++) {
        for (size_t j = 0; j < 11; j++) {
            pImpl->board.at(i).emplace_back(make_shared(new Cell(i,j)));
        }
    }

    // add Textdisplay to Cell's observers
    // add GridDisplay to Cell's observers

}

ostream &operator<<(ostream &, Grid &) {
// should this class have this method?
}

void Grid::setBlock() {
// not really sure about this method
}
