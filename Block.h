#ifndef TEST_BLOCK_H
#define TEST_BLOCK_H

#include <vector>
#include <memory>

class Cell;

class Block {

    std::vector<std::shared_ptr<Cell>> cells;

    void swap(Block &other);

public:

    Block();

    Block(const Block &other);

    Block &operator=(const Block &other);

    Block &operator=(Block &&other);


    // getter
    std::vector<std::shared_ptr<Cell>> getCells() const;

    void transformLeft();

    void transformRight();

    void transformDown();

    void transformClockwise();

    void transformCounterClockwise();
};


#endif //TEST_BLOCK_H
