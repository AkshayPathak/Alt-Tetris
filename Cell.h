#ifndef TEST_CELL_H
#define TEST_CELL_H

#include <ostream>
#include "Observer.h"
#include "Subject.h"
#include "window.h"
#include <memory>



class Cell {

    struct CellImpl;
    std::unique_ptr<CellImpl> cellImpl;

public:

    Cell(int x, int y, char c = ' ');

    Cell(const Cell &);

    Cell();

    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);

    char getC() const;

    void setC(char c);

    void draw(std::unique_ptr<Xwindow> w, int x, int y, int width, int height);

    // undraw function??

    friend std::ostream &operator<<(std::ostream &os, const Cell &cell);

    ~Cell();

};

#endif //TEST_CELL_H
