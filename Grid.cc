#include "Grid.h"
#include "Cell.h"
#include "Block.h"
#include "Game.h"
#include <algorithm>

using namespace std;

struct Grid::GridImpl {
    Game * game;
    int x;
    int y;
    vector<vector<shared_ptr<Cell>>> board;
    shared_ptr<Block> currentBlock;

    // Methods
    GridImpl(Game *game, int x, int y) :game{game}, x{x}, y{y},
        board{vector<vector<shared_ptr<Cell>>>(y)} {};
};

//--------------------------------------------------------------------------------
// Public
// ctor
Grid::Grid(Game *game, int x, int y) : gridImpl{make_unique<GridImpl>(game, x, y)} {
    // makes the board
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            gridImpl->board.at(i).emplace_back(make_shared<Cell>(i, j));
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
            gridImpl->board.at(i).emplace_back(make_shared<Cell>(i, j));
        }
    }

//    printBoard();

    gridImpl->currentBlock = gridImpl->game->getNextBlock();   // changing grid's currentBlock
    numDown(3);
    gridImpl->game->createBlock();      // creates Game's next block
    // changing the block so that textdisplay can print it correctly
    notifyObservers();
}

void Grid::transformLeft(bool performHeavy /* = false */) {
    Block copy = Block(gridImpl->currentBlock->getCells());
    copy.transformLeft();

    // checking for invalid input
    if (invalidInput(copy)) return;

    // checking if overlapping with anything
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

    // checking for invalid input
    if (invalidInput(copy)) return;

    // checking if overlapping with anything
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

    // checking for invalid input
    if (invalidInput(copy)) return;

    // checking if overlapping with anything
    if (overlap(copy)) return;

    gridImpl->currentBlock = make_shared<Block>(Block(copy));
    notifyObservers();
}

void Grid::transformClockwise(bool performHeavy /* = false */) {
    Block copy = Block(gridImpl->currentBlock->getCells());
    copy.transformClockwise();

    // checking for invalid input
    if (invalidInput(copy)) return;

    // checking if overlapping with anything
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

    // checking for invalid input
    if (invalidInput(copy)) return;

    // checking if overlapping with anything
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

//Private
// row is an index
bool Grid::fullRow(int row) {
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

// only drop calls this
void Grid::setBlock() {
    // puts currentBlock on the board
    bool restart = false;
    for (int i = 0; i < gridImpl->currentBlock->getCells().size(); i++) {
        int x = gridImpl->currentBlock->getCells().at(i)->getX();
        int y = gridImpl->currentBlock->getCells().at(i)->getY();
        if (y <= 3) restart = true;
        char c = gridImpl->currentBlock->getCells().at(i)->getC();
        gridImpl->board.at(y).at(x)->setC(c);
    }
    if (restart) gridImpl->game->restart();

    // getting a vector of x values
    vector<int> yValues(gridImpl->currentBlock->getCells().size());
    for (int i = 0; i < gridImpl->currentBlock->getCells().size(); i++) {
        yValues.at(i) = gridImpl->currentBlock->getCells().at(i)->getY();
    }
    sort(yValues.begin(), yValues.end());
    yValues.erase(unique( yValues.begin(), yValues.end()), yValues.end());

//    int numLinesErased = 0;
//    for(int i = 0; i < yValues.size(); i++) {
//        if (fullRow(yValues.at(i)) == true) {
//            shiftBoard(yValues.at(i));
//            numLinesErased++;
//        }
//    }
//    gridImpl->game->incrementPointsByLinesDeleted(numLinesErased);
    int numLinesErased = 0;
    for(int i = 0; i < yValues.size(); i++) {
        if (fullRow(yValues.at(i))) {
            shiftBoard(yValues.at(i));
            numLinesErased++;
        }
    }
    if (numLinesErased!= 0) gridImpl->game->incrementPointsByLinesDeleted(numLinesErased);

    gridImpl->currentBlock = gridImpl->game->getNextBlock();   // changing grid's currentBlock
    numDown(3);
    gridImpl->game->createBlock();      // creates Game's next block

    if (overlap(*(gridImpl->currentBlock))) gridImpl->game->restart();

    notifyObservers();     // prints with the piece at the bottom
}

// deletes a row, adds top row, changes index of every single Cell up until deleted row
void Grid::shiftBoard(int row) {

    // delete the row that is full
    gridImpl->board.erase(gridImpl->board.begin() + row);

    // changes all the indexes until hits row
    for (int i = 1; i < row; i++) {
        for (int j = 0; j < gridImpl->x; j++) {
            gridImpl->board.at(i).at(j)->setY(gridImpl->board.at(i).at(j)->getY() + 1);
        }
    }

    // adds in first top row of new empty Cells
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

//void Grid::printBoard() {
//    for (auto &i : gridImpl->board) {
//        for (auto &j : i) {
//            cout << j->getC();
//        }
//        cout << endl;
//    }
//}

void Grid::setCurrentBlock(shared_ptr<Block> newBlock) {
    gridImpl->currentBlock = newBlock;
    numDown(3);
    //notifyObservers();
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

//void Grid::numRight(int n) {
//    for(int i = 0; i < gridImpl->currentBlock->getCells().size(); i++) {
//        cout << i << endl;
//        cout << "old coords: " << gridImpl->currentBlock->getCells().at(0)->getX() << ", " << gridImpl->currentBlock->getCells().at(0)->getY() << endl;
//        gridImpl->currentBlock->getCells().at(i)->setX(gridImpl->currentBlock->getCells().at(i)->getX() + n);
//        cout << "new coords: " << gridImpl->currentBlock->getCells().at(0)->getX() << ", " << gridImpl->currentBlock->getCells().at(0)->getY() << endl;
//    }
//}


