#include "Score.h"

struct Score::ScoreImpl {
    int hiScore;
    int currentScore;

    ScoreImpl(): hiScore{0}, currentScore{0} {}
};

Score::Score(): scoreImpl{std::make_unique<ScoreImpl>()} {}


int Score::getHiScore() {
    return scoreImpl->hiScore;
}

void Score::setHiScore(int hiScore) {
    scoreImpl->hiScore = hiScore;
};


int Score::getScore() {
    return scoreImpl->currentScore;
}

void Score::updateScore(int increment) {
    scoreImpl->currentScore += increment;
    if(scoreImpl->currentScore > scoreImpl->hiScore) scoreImpl->hiScore = scoreImpl->currentScore;
}

void Score::resetScore() {
    scoreImpl->currentScore = 0;
}

Score::~Score() {}

