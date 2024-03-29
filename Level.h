#ifndef QUADRIS_LEVEL_H
#define QUADRIS_LEVEL_H

#include <iostream>
#include <memory>
#include "Block.h"

using namespace std;

class Level {

    struct LevelImpl;
    unique_ptr<LevelImpl> levelImpl;

public:

    explicit Level(const vector<char> &blockSequence);

    /**
     * Makes a block depending on the level
     */
    virtual shared_ptr<Block> makeBlock() = 0;

    /**
     * Make a block from the sequence file
     */
    shared_ptr<Block> makeSequenceBlock();

    vector<shared_ptr<Cell>> makeIBlock();

    vector<shared_ptr<Cell>> makeJBlock();

    vector<shared_ptr<Cell>> makeLBlock();

    vector<shared_ptr<Cell>> makeOBlock();

    vector<shared_ptr<Cell>> makeSBlock();

    vector<shared_ptr<Cell>> makeZBlock();

    vector<shared_ptr<Cell>> makeTBlock();

    /**
     * Creates a block of 1 cell
     */
    shared_ptr<Block> makeABlock();

    /**
     * Resets the block sequence to start from the beginning
     */
    void resetBlockSequence();

    /**
     * Set if block should be randomly generated or from the sequence file (not applicable for level 0)
     * @param noRandom True if block should be created from file, false if random
     */
    void setNoRandom(bool noRandom);

    /**
     * Check if random is enabled
     * @return True if random is disabled, false if enabled
     */
    bool isNoRandom() const;

    /**
     * Get the current level
     * @return
     */
    virtual int getLevel() = 0;

    virtual ~Level();

};

#endif //QUADRIS_LEVEL_H
