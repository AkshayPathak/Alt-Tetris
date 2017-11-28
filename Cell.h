#ifndef TEST_CELL_H
#define TEST_CELL_H

#include <ostream>
#include "Observer.h"
#include "Subject.h"

class Cell : public Observer, Subject {

    struct CellImpl;
    std::unique_ptr<CellImpl> cellImpl;

public:

    Cell(int x, int y, char c = ' ');

    Cell();

    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);

    char getC() const;

    void setC(char c);

    friend std::ostream &operator<<(std::ostream &os, const Cell &cell);

    virtual ~Cell();

};

#endif //TEST_CELL_H
