#include "Grid.h"
#include "Cell.h"
#include "Block.h"
#include "Game.h"
#include <algorithm>

using namespace std;

struct Grid::GridImpl {
    Game *game;
    int x;
    int y;
    vector<vector<shared_ptr<Cell>>> board;
    shared_ptr<Block> currentBlock;
    int lvl4Counter = 0;

    GridImpl(Game *game, int x, int y) :game{game}, x{x}, y{y},
        board{vector<vector<shared_ptr<Cell>>>(y)} {};
};

Grid::Grid(Game *game, int x, int y) : gridImpl{make_unique<GridImpl>(game, x, y)} {
    // Make the board
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            gridImpl->board.at(i).emplace_back(make_shared<Cell>(i, j));
        }
    }
}
void Grid::init() {
    gridImpl->lvl4Counter = 0;

    // Clears the board first
    for (int i = 0; i < gridImpl->board.size(); i++) {
        gridImpl->board.at(i).clear();
    }

    // Constructs empty board
    for (int i = 0; i < gridImpl->y; i++) {
        for (int j = 0; j < gridImpl->x; j++) {
            gridImpl->board.at(i).emplace_back(make_shared<Cell>(i, j));
        }
    }

    // Getting the next block from Game
    gridImpl->currentBlock = gridImpl->game->getNextBlock();
    numDown(3);

    // Creates Game's next block
    gridImpl->game->createBlock();

    // Changing the block so that textdisplay can print it correctly
    notifyObservers();
}


void Grid::transformLeft(bool performHeavy /* = false */) {
    Block copy = Block(gridImpl->currentBlock->getCells());
    copy.transformLeft();

    // Checking for invalid input
    if (invalidInput(copy)) return;

    // Checking if overlapping with anything
    if (overlap(copy)) return;

    gridImpl->currentBlock = make_shared<Block>(Block(copy));

    if (performHeavy) {
        transformDown();
    } else {
        notifyObservers();
    }
}

void Grid::transformRight(bool performHeavy /* = false */) {
    Block copy = Block(gridImpl->currentBlock->getCells());
    copy.transformRight();

    // Checking for invalid input
    if (invalidInput(copy)) return;

    // Checking if overlapping with anything
    if (overlap(copy)) return;

    gridImpl->currentBlock = make_shared<Block>(Block(copy));

    if (performHeavy) {
        transformDown();
    } else {
        notifyObservers();
    }
}

void Grid::transformDown() {
    Block copy = Block(gridImpl->currentBlock->getCells());
    copy.transformDown();

    // Checking for invalid input
    if (invalidInput(copy)) return;

    // Checking if overlapping with anything
    if (overlap(copy)) return;

    gridImpl->currentBlock = make_shared<Block>(Block(copy));
    notifyObservers();
}

void Grid::transformClockwise(bool performHeavy /* = false */) {
    Block copy = Block(gridImpl->currentBlock->getCells());
    copy.transformClockwise();

    // Checking for invalid input
    if (invalidInput(copy)) return;

    // Checking if overlapping with anything
    if (overlap(copy)) return;

    gridImpl->currentBlock = make_shared<Block>(Block(copy));

    if (performHeavy) {
        transformDown();
    } else {
        notifyObservers();
    }
}

void Grid::transformCounterClockwise(bool performHeavy /* = false */) {
    Block copy = Block(gridImpl->currentBlock->getCells());
    copy.transformCounterClockwise();

    // Checking for invalid input
    if (invalidInput(copy)) return;

    // Checking if overlapping with anything
    if (overlap(copy)) return;

    gridImpl->currentBlock = make_shared<Block>(Block(copy));

    if (performHeavy) {
        transformDown();
    } else {
        notifyObservers();
    }
}

/* 1. will drop as many times as it can
 * 2. setpiece when can no longer drop-->already calls fullRow, which calls shiftBoard
 */
void Grid::transformDrop() {
    bool keepDropping = true;
    while(keepDropping) {
        Block copy = Block(gridImpl->currentBlock->getCells());
        copy.transformDown();
        if (invalidInput(copy)) {
            keepDropping = false;
            break;
        }
        if (overlap(copy)) {
            keepDropping = false;
            break;
        }
        if (keepDropping) gridImpl->currentBlock = make_shared<Block>(Block(copy));
    }
    setBlock();
}

bool Grid::fullRow(int row) {
    // Row is an index on the board
    bool value = true;
    for(int i = 0; i < gridImpl->x; i++) {
        // if it is space, then there is an empty character there
        if (gridImpl->board.at(row).at(i)->getC() == ' ') {
            value = false;
            break;
        }
    }
    return value;
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

void Grid::setBlock() {
    // Puts currentBlock on the board
    bool restart = false;
    for (int i = 0; i < gridImpl->currentBlock->getCells().size(); i++) {
        int x = gridImpl->currentBlock->getCells().at(i)->getX();
        int y = gridImpl->currentBlock->getCells().at(i)->getY();
        if (y <= 3) restart = true;
        char c = gridImpl->currentBlock->getCells().at(i)->getC();
        gridImpl->board.at(y).at(x)->setC(c);
    }
    if (restart) gridImpl->game->restart();

    // Get a vector of x values
    vector<int> yValues(gridImpl->currentBlock->getCells().size());
    for (int i = 0; i < gridImpl->currentBlock->getCells().size(); i++) {
        yValues.at(i) = gridImpl->currentBlock->getCells().at(i)->getY();
    }
    sort(yValues.begin(), yValues.end());
    yValues.erase(unique( yValues.begin(), yValues.end()), yValues.end());

    int numLinesErased = 0;
    for(int i = 0; i < yValues.size(); i++) {
        if (fullRow(yValues.at(i))) {
            shiftBoard(yValues.at(i));
            numLinesErased++;
        }
    }
    if (numLinesErased!= 0) {
        gridImpl->game->incrementPointsByLinesDeleted(numLinesErased);
        gridImpl->lvl4Counter = 0;
    } else {   // erase no lines
        if (gridImpl->currentBlock->getCells().size() == 1) {
             return;
        }
        gridImpl->lvl4Counter += 1;
        if (gridImpl->lvl4Counter == 5 && gridImpl->game->getLevel() == 4) {
            setCurrentBlock(gridImpl->game->getABlock());
            numRight(5);
            numDown(3);
            transformDrop();
            gridImpl->lvl4Counter = 0;
        }
    }

    // Get the next block from Game
    gridImpl->currentBlock = gridImpl->game->getNextBlock();
    numDown(3);
    // Make Game's next block
    gridImpl->game->createBlock();

    if (overlap(*(gridImpl->currentBlock))) gridImpl->game->restart();

    // Print with the piece at the bottom
    notifyObservers();
}

void Grid::shiftBoard(int row) {
    // Deletes a row, adds top row, changes index of every single Cell up until deleted row

    // Delete the row that is full
    gridImpl->board.erase(gridImpl->board.begin() + row);

    // Changes all the indexes until hits row
    for (int i = 1; i < row; i++) {
        for (int j = 0; j < gridImpl->x; j++) {
            gridImpl->board.at(i).at(j)->setY(gridImpl->board.at(i).at(j)->getY() + 1);
        }
    }

    // Adds in first top row of new empty Cells
    vector<shared_ptr<Cell>> first = vector<shared_ptr<Cell>>(gridImpl->x);
    for(int i = 0, j = 0; i < gridImpl->x; i++) {
        first.at(i) = make_shared<Cell>(i, j);
    }
    gridImpl->board.insert(gridImpl->board.begin(), first);
}

int Grid::getWidth() {
    return gridImpl->x;
}

int Grid::getHeight() {
    return gridImpl->y;
}

shared_ptr<Block> Grid::getBlock() {
    return gridImpl->currentBlock;
}

vector<vector<shared_ptr<Cell>>> *Grid::getBoard() {
    return &(gridImpl->board);
}

void Grid::setCurrentBlock(shared_ptr<Block> newBlock) {
    gridImpl->currentBlock = newBlock;
    numDown(3);
}

void Grid::numDown(int n) {
    for(int i = 0; i < gridImpl->currentBlock->getCells().size(); i++) {
        gridImpl->currentBlock->getCells().at(i)->setY(gridImpl->currentBlock->getCells().at(i)->getY() + n);
    }
}

void Grid::numRight(int n) {
    for(int i = 0; i < gridImpl->currentBlock->getCells().size(); i++) {
        gridImpl->currentBlock->getCells().at(i)->setX(gridImpl->currentBlock->getCells().at(i)->getX() + n);
    }
}

Grid::~Grid() {};
