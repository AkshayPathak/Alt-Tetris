#include "Grid.h"
#include "Cell.h"
#include "Block.h"

using namespace std;

struct Grid::GridImpl {
    vector<vector<shared_ptr<Cell>>> board;  // not sure if this should be shared pointer

    Block currentBlock;

    void shiftBoard();
};

// deletes a bottom row, adds top row, changes index of every single Cell
void Grid::GridImpl::shiftBoard() {
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
Grid::Grid() : gridImpl{new GridImpl{}} {
    for (size_t i = 0; i < 18; i++) {
        for (size_t j = 0; j < 11; j++) {
            gridImpl->board.at(i).emplace_back(make_shared(new Cell(i,j)));
        }
    }
}

Grid::~Grid() = default;

void Grid::init() {
    // clears the board first
    for (size_t i = 0; i < gridImpl->board.size(); i++) {
        gridImpl->board.at(i).clear();
    }

    // constructs empty board
    for (size_t i = 0; i < 18; i++) {
        for (size_t j = 0; j < 11; j++) {
            gridImpl->board.at(i).emplace_back(make_shared(new Cell(i,j)));
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

void Grid::transformLeft() {
    // TODO Make a copy and perform transformation on that
    gridImpl->currentBlock.transformLeft();
}

void Grid::transformRight() {
    gridImpl->currentBlock.transformRight();
}

void Grid::transformDown() {
    gridImpl->currentBlock.transformDown();
}

void Grid::transformDrop() {
    gridImpl->currentBlock.transformDrop();
}

void Grid::transformClockwise() {
    gridImpl->currentBlock.transformClockwise();
}

void Grid::transformCounterClockwise() {
    gridImpl->currentBlock.transformCounterClockwise();
}
