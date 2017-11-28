#ifndef TEST_GRID_H
#define TEST_GRID_H

#include <iostream>
#include <vector>

using namespace std;

class Cell;
class Block;
class Level;
class Score;
class GraphicsDisplay;
class TextDisplay;

class Grid {
    vector<vector<Cell>> board;
    Level *level = nullptr;
    Score *score = nullptr;
    TextDisplay *td = nullptr;
    GraphicsDisplay *gd = nullptr;
public:
    Block &nextBlock();
    Block &currentBlock();
    friend ostream &operator<<(ostream &, Grid &);
    // should i create an init fucntion.. make new Textdisplay inside grid's init, or should i take in a parameterized constructor...
    void init();
};



#endif
