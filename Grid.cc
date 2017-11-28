#include "Grid.h"

using namespace std;

struct Grid::GridImpl {
    vector<vector<shared_ptr<Cell>>> board;  // not sure if this should be shared pointer
    unique_ptr<Level> level = nullptr;
    unique_ptr<Score> score = nullptr;
    unique_ptr<TextDisplay> td = nullptr;
    unique_ptr<GraphicsDisplay> gd = nullptr;
};

// Private
void shiftBoard() {
    // need Block.h
}

// gets level to create a block, just returns reference to that block
Block &makeBlock() {
    // need Level
}

void setBlock() {

}
//--------------------------------------------------------------------------------
// Public
Block &Grid::nextBlock() {

}

Block &Grid::currentBlock() {

}

ostream &operator<<(ostream &, Grid &) {

}

void Grid::init() {

}
