#ifndef TEST_GRID_H
#define TEST_GRID_H

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Grid {
    struct gridImpl;
    unique_ptr<gridImpl> pImpl;
public:

    Grid();

    ~Grid();

    void init();     // creates board, empties it if there is already a board, will add observers to the Cells, don't know if it should tho

    friend ostream &operator<<(ostream &, Grid &);

    void setBlock();
};



#endif
