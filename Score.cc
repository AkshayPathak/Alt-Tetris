#include "Score.h"

struct Score::ScoreImpl {
    int hiScore;
    int currentScore;

    ScoreImpl(): hiScore{0}, currentScore{0} {}
};

Score::Score(): scoreImpl{std::make_unique<ScoreImpl>()} {}

Score::~Score() {};

int Score::getHiScore() {
    return scoreImpl->hiScore;
}

int Score::getScore() {
    return scoreImpl->currentScore;
}


void Score::updateScore(int increment) {
    scoreImpl->currentScore += increment;
    if(scoreImpl->currentScore > scoreImpl->hiScore) scoreImpl->hiScore = scoreImpl->currentScore;
}
