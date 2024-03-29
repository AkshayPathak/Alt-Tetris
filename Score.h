#ifndef QUADRIS_SCORE_H
#define QUADRIS_SCORE_H

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
     * Set the highscore
     */
    void setHiScore(int hiScore);

    ~Score();

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

};

#endif //QUADRIS_SCORE_H
