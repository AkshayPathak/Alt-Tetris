#ifndef TEST_GRID_H
#define TEST_GRID_H

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Cell;
class Block;
class Level;
class Score;
class GraphicsDisplay;
class TextDisplay;

class Grid {
    struct GridImpl;
    unique_ptr<GridImpl> pImpl;
public:
    Grid() noexcept;
    Block &nextBlock() noexcept;
    Block &currentBlock() noexcept;
    void init() noexcept;
    friend ostream &operator<<(ostream &, Grid &) noexcept;
};



#endif
