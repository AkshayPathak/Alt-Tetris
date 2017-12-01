#include "Grid.h"
#include "Cell.h"
#include "Block.h"
#include "Game.h"
#include <algorithm>

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
Grid::Grid(shared_ptr<Game> game, int x /* = 11 */, int y /* = 18 */) : gridImpl{new GridImpl{game, x, y}} {
    // makes the board
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            gridImpl->board.at(i).emplace_back(make_shared<Cell>(new Cell{i, j}));
        }
    }
}

Grid::~Grid() = default;

void Grid::init() {
    // clears the board first
    for (int i = 0; i < gridImpl->board.size(); i++) {
        gridImpl->board.at(i).clear();
    }

    // constructs empty board
    for (int i = 0; i < gridImpl->y; i++) {
        for (int j = 0; j < gridImpl->x; j++) {
            gridImpl->board.at(i).emplace_back(make_shared(Cell{i,j}));
        }
    }

    gridImpl->currentBlock = gridImpl->game->getNextBlock();   // changing grid's currentBlock
    gridImpl->game->createBlock();      // creates Game's next block
    notifyObservers();
}

// only drop calls this
void Grid::setBlock() {
    // puts currentBlock on the board
    for (int i = 0; i < gridImpl->currentBlock.getCells().size(); i++) {
        int x = gridImpl->currentBlock.getCells().at(i)->getX();
        int y = gridImpl->currentBlock.getCells().at(i)->getY();
        char c = gridImpl->currentBlock.getCells().at(i)->getC();
        gridImpl->board.at(y).at(x)->setC(c);
    }
    notifyObservers();

    // getting a vector of x values
    vector<int> y_values(gridImpl->currentBlock.getCells().size());
    for (int i = 0; i < gridImpl->currentBlock.getCells().size(); i++) {
        y_values.at(i) = gridImpl->currentBlock.getCells().at(i)->getY();
    }
    sort(y_values.begin(), y_values.end());
    y_values.erase(unique( y_values.begin(), y_values.end()), y_values.end());

    for(int i = 0; i < y_values.size(); i++) {
        if (fullRow(y_values.at(i))) shiftBoard(y_values.at(i));
    }

    gridImpl->currentBlock = gridImpl->game->getNextBlock();   // changing grid's currentBlock
    gridImpl->game->createBlock();      // creates Game's next block
    notifyObservers();
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


/* 1. will drop as many times as it can
 * 2. setpiece when can no longer drop-->already calls fullRow, which calls shiftBoard
 */
void Grid::transformDrop() {
    bool keepDropping = true;
    while(keepDropping) {
        Block copy = gridImpl->currentBlock;
        copy.transformDown();
        if (invalidInput(copy)) keepDropping = false;
        if (overlap(copy)) keepDropping = false;
        gridImpl->currentBlock = copy;
        notifyObservers();
    }
    setBlock();
}

//Private
// row is an index
bool Grid::fullRow(int row) const {
    for(int i = 0; i < gridImpl->x; i++) {
        // if it is space, then there is an empty character there
        if (gridImpl->board.at(row).at(i)->getC() == ' ') {
            return false;
        }
    }
    return true;
}

bool Grid::invalidInput(const Block &copy) {
    for (int i = 0; i < copy.getCells().size(); i++) {
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
    for (int i = 0; i < copy.getCells().size(); i++) {
        int x = copy.getCells().at(i)->getX();
        int y = copy.getCells().at(i)->getY();
        if (gridImpl->board.at(y).at(x)->getC() != ' ') return true;
    }
    return false;
}



// calls notifyObservers --- SHOULDN'T ---- just call at the end of all the deletions
// deletes a row, adds top row, changes index of every single Cell up until deleted row
void Grid::shiftBoard(int row) {
    // delete the row that is full
    gridImpl->board.erase(gridImpl->board.begin() + row - 1);

    // changes all the indexes until hits row
    for (int i = 1; i < row; i++) {
        for (int j = 0; j < gridImpl->x; j++) {
            gridImpl->board.at(i).at(j)->setY(gridImpl->board.at(i).at(j)->getY() + 1);
        }
    }

    // adds in first top row of new empty Cells
    vector<shared_ptr<Cell>> first = vector<shared_ptr<Cell>>(gridImpl->x);
    for(int i = 0, j = 0; i < gridImpl->x; i++) {
        first.at(i) = make_shared<Cell>(new Cell{i, j});
    }
    gridImpl->board.insert(gridImpl->board.begin(), first);
}


