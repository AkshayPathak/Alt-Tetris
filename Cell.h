#ifndef TEST_CELL_H
#define TEST_CELL_H

#include <ostream>
#include "Observer.h"
#include "Subject.h"

class Cell : public Observer, Subject {

    int x;
    int y;
    char c;

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

};

#endif //TEST_CELL_H
