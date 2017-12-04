#ifndef QUADRIS_CELL_H
#define QUADRIS_CELL_H

#include <ostream>
#include "Observer.h"
#include "Subject.h"
#include "window.h"
#include <memory>

class Cell {

    struct CellImpl;
    std::unique_ptr<CellImpl> cellImpl;

public:

    Cell(int x, int y, char c = ' ', bool pivot = false);

    Cell(const Cell &);

    Cell();

    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);

    char getC() const;

    void setC(char c);

    bool isPivot() const;

    void setPivot(bool pivot);

    void draw(std::shared_ptr<Xwindow> w, int x, int y, int width, int height);

    friend std::ostream &operator<<(std::ostream &os, const Cell &cell);

    ~Cell();

};

#endif //QUADRIS_CELL_H
