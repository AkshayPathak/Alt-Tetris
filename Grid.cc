#include "Grid.h"
#include "Cell.h"
#include "Block.h"
#include "Game.h"

using namespace std;

struct Grid::GridImpl {
    shared_ptr<Game> game;
    vector<vector<shared_ptr<Cell>>> board;
    int x;
    int y;
    Block currentBlock;

    // Methods
    GridImpl(shared_ptr<Game> game, int x, int y) :game{game}, x{x}, y{y} {};
};

//--------------------------------------------------------------------------------
// Public
// ctor
// TODO: CHECK THE CTOR AND INIT FUNCTIONS
Grid::Grid(shared_ptr<Game> game, int x = 11, int y = 18) : gridImpl{new GridImpl{game, x, y}} {
    // makes the board
    for (size_t i = 0; i < y; i++) {
        for (size_t j = 0; j < x; j++) {
            gridImpl->board.at(i).emplace_back(make_shared(new Cell(i,j)));
        }
    }
    // gets the first current block
    gridImpl->currentBlock = gridImpl->game->getNextBlock();   // changing grid's currentBlock
    gridImpl->game->createBlock();      // creates Game's next block
}

Grid::~Grid() = default;

void Grid::init() {
    // clears the board first
    for (size_t i = 0; i < gridImpl->board.size(); i++) {
        gridImpl->board.at(i).clear();
    }

    // constructs empty board
    for (size_t i = 0; i < gridImpl->y; i++) {
        for (size_t j = 0; j < gridImpl->x; j++) {
            gridImpl->board.at(i).emplace_back(make_shared(new Cell(i,j)));
        }
    }

    gridImpl->currentBlock = gridImpl->game->getNextBlock();   // changing grid's currentBlock
    gridImpl->game->createBlock();      // creates Game's next block
}

// ONLY DROP CALLS THIS METHOD RIGHT NOW, maybe should make it private
void Grid::setBlock() {
    // puts currentBlock on the board
    for (size_t i = 0; i < gridImpl->currentBlock.getCells().size(); i++) {
        int x = gridImpl->currentBlock.getCells().at(i)->getX();
        int y = gridImpl->currentBlock.getCells().at(i)->getY();
        char c = gridImpl->currentBlock.getCells().at(i)->getC();
        gridImpl->board.at(y).at(x)->setC(c);
    }

    if (fullBoard()) shiftBoard();    // maybe change to full row

    notifyObservers();
    gridImpl->currentBlock = gridImpl->game->getNextBlock();   // changing grid's currentBlock
    gridImpl->game->createBlock();      // creates Game's next block
}

void Grid::transformLeft() {
    Block copy = gridImpl->currentBlock;    // block has big 5
    copy.transformLeft();

    // checking for invalid input
    if (invalidInput(copy)) return;

    // checking if overlapping with anything
    if (overlap(copy)) return;

    gridImpl->currentBlock = copy;
    notifyObservers();
}

void Grid::transformRight() {
    Block copy = gridImpl->currentBlock;
    copy.transformRight();

    // checking for invalid input
    if (invalidInput(copy)) return;

    // checking if overlapping with anything
    if (overlap(copy)) return;

    gridImpl->currentBlock = copy;
    notifyObservers();
}

void Grid::transformDown() {
    Block copy = gridImpl->currentBlock;
    copy.transformDown();

    // checking for invalid input
    if (invalidInput(copy)) return;

    // checking if overlapping with anything
    if (overlap(copy)) return;

    gridImpl->currentBlock = copy;
    notifyObservers();
}

void Grid::transformClockwise() {
    Block copy = gridImpl->currentBlock;
    copy.transformClockwise();

    // checking for invalid input
    if (invalidInput(copy)) return;

    // checking if overlapping with anything
    if (overlap(copy)) return;

    gridImpl->currentBlock = copy;
    notifyObservers();
}

void Grid::transformCounterClockwise() {
    Block copy = gridImpl->currentBlock;
    copy.transformCounterClockwise();

    // checking for invalid input
    if (invalidInput(copy)) return;

    // checking if overlapping with anything
    if (overlap(copy)) return;

    gridImpl->currentBlock = copy;
    notifyObservers();
}



void Grid::transformDrop() {
    // TODO: IMPLEMENT
}




//Private
//TODO: IMPLEMENT
bool Grid::fullBoard() const {
    return false;
}

bool Grid::invalidInput(const Block &copy) {
    for (size_t i = 0; i < copy.getCells().size(); i++) {
        int x = copy.getCells().at(i)->getX();
        int y = copy.getCells().at(i)->getY();
        if (x < 0) return true;
        if (x >= gridImpl->x) return true;
        if (y < 0) return true;
        if (y >= gridImpl->y) return true;
    }
    return false;
}

bool Grid::overlap(const Block &copy) {
    for (size_t i = 0; i < copy.getCells().size(); i++) {
        int x = copy.getCells().at(i)->getX();
        int y = copy.getCells().at(i)->getY();
        if (gridImpl->board.at(y).at(x)->getC() != ' ') return true;
    }
    return false;
}


// TODO: make it for any row that is completely filled, not just the bottom
// deletes a bottom row, adds top row, changes index of every single Cell
void Grid::shiftBoard() {
    gridImpl->board.pop_back();
    vector<shared_ptr<Cell>> first = vector<shared_ptr<Cell>>(11);
    for(size_t i = 0, j = 0; i < 11; i++) {
        first.at(i) = make_shared(new Cell(i, j));
    }
    gridImpl->board.insert(gridImpl->board.begin(), first);

    // switching every cell after the first row
    for (size_t i = 1; i < 18; i++) {
        for (size_t j = 0; j < 11; j++) {
            gridImpl->board.at(i).at(j)->setX(j);
            gridImpl->board.at(i).at(j)->setY(i);
        }
    }
}


