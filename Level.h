#ifndef TEST_LEVEL_H
#define TEST_LEVEL_H

#include <iostream>
#include <memory>
#include "Block.h"

using namespace std;

class Level {

    vector<char> blockSequence;
    int blockPosition = 0;
    bool noRandom = true;

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

#endif //TEST_LEVEL_H
