#ifndef TEST_SCORE_H
#define TEST_SCORE_H

#include <memory>



class Score {
    struct ScoreImpl;

    std::unique_ptr<ScoreImpl> scoreImpl;

public:
    Score();
    ~Score();

    int getHiScore();

    int getScore();

    void updateScore(int increment);

    void resetScore();

};

#endif //TEST_SCORE_H
