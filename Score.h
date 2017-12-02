#ifndef TEST_SCORE_H
#define TEST_SCORE_H

#include <memory>
#include "Level.h"

class Level;

class Score {
    struct ScoreImpl;

    std::unique_ptr<ScoreImpl> scoreImpl;

public:
    explicit Score(std::shared_ptr<Level> level);

    int getHiScore();

    int getCurrentScore();

    void updateScore();

};

#endif //TEST_SCORE_H
