#ifndef TEST_BLOCK_H
#define TEST_BLOCK_H

#include <vector>
#include <memory>

class Cell;

class Block {

    std::vector<std::unique_ptr<Cell>> cells;

    void swap(Block &other);

public:

    Block();

    Block(const Block &other);

    Block &operator=(const Block &other);

    Block &operator=(Block &&other);

    void transformLeft();

    void transformRight();

    void transformDown();

    void transformDrop();

    void transformClockwise();

    void transformCounterClockwise();
};


#endif //TEST_BLOCK_H
