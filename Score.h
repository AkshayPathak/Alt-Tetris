#ifndef TEST_SCORE_H
#define TEST_SCORE_H

#include <memory>

class Score {
    struct ScoreImpl;

    std::unique_ptr<ScoreImpl> scoreImpl;

public:
    Score();

    /**
     * Get the high score that was set
     */
    int getHiScore();

    /**
     * Get the current score
     */
    int getScore();

    /**
     * Update the score by 'increment' points
     */
    void updateScore(int increment);

    /**
     * Reset the current score to 0
     */
    void resetScore();

    ~Score();

};

#endif //TEST_SCORE_H
