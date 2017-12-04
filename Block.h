#ifndef QUADRIS_BLOCK_H
#define QUADRIS_BLOCK_H

#include <vector>
#include <memory>

class Cell;
struct Posn;

class Block {

    std::vector<std::shared_ptr<Cell>> cells;

    void swap(Block &other);

    // For transform Clockwise
    Posn lowerLeft();

    // For transform Clockwise
    Posn upperRight();

public:

    Block();

    Block(const Block &b);

    explicit Block(std::vector<std::shared_ptr<Cell>> cells);

    Block &operator=(const Block &other);

    Block &operator=(Block &&other);

    /**
     * Transforms all the cells associated with the block one unit left
     */
    void transformLeft();

    /**
     * Transforms all the cells associated with the block one unit right
     */
    void transformRight();

    /**
     * Transforms all the cells associated with the block one unit down
     */
    void transformDown();

    /**
     * Transforms all the cells associated with the block 90 degrees clockwise
     */
    void transformClockwise();

    /**
     * Transforms all the cells associated with the block 90 degrees counterclockwise
     */
    void transformCounterClockwise();

    /**
     * Get all the cells associated with the block
     */
    std::vector<std::shared_ptr<Cell>> getCells() const;
};

#endif //QUADRIS_BLOCK_H
