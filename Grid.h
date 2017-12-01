#ifndef TEST_GRID_H
#define TEST_GRID_H

#include <iostream>
#include <vector>
#include <memory>
#include "Subject.h"

using namespace std;

class Game;
class Block;

class Grid : public Subject{
    struct GridImpl;
    unique_ptr<GridImpl> gridImpl;
public:

    Grid(Game *game, int x = 11, int y = 18);

    ~Grid();

    void init();     // call when want to clear board

    void setBlock();

    void transformLeft();

    void transformRight();

    void transformDown();

    void transformDrop();

    void transformClockwise();

    void transformCounterClockwise();
private:
    bool invalidInput(const Block &);

    bool overlap(const Block &);

    bool fullRow(int row) const;

    void shiftBoard(int row);
};

#endif
