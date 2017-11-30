#ifndef TEST_GRID_H
#define TEST_GRID_H

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Grid {
    struct GridImpl;
    unique_ptr<GridImpl> gridImpl;
public:

    Grid();

    ~Grid();

    void init();     // creates board, empties it if there is already a board, will add observers to the Cells, don't know if it should tho

    void setBlock();

    void transformLeft();

    void transformRight();

    void transformDown();

    void transformDrop();

    void transformClockwise();

    void transformCounterClockwise();

    friend ostream &operator<<(ostream &, Grid &);
};



#endif
