#include "Score.h"

struct Score::ScoreImpl {
    std::shared_ptr<Level> level;
    int hiScore;
    int currentScore;

    explicit ScoreImpl(std::shared_ptr<Level>): level{level}, hiScore{0}, currentScore{0} {}
};

Score::Score(std::shared_ptr<Level> level): scoreImpl{std::make_unique<ScoreImpl>} {}

int Score::getHiScore() {
    return scoreImpl->hiScore;
}

int Score::getCurrentScore() {
    return scoreImpl->currentScore;
}

int square(int x) {
    return x*x;
}

void Score::updateScore() {
    int addedScore = square(scoreImpl->level->getLevel() + 1);
    scoreImpl->currentScore += addedScore;
    if(scoreImpl->currentScore > scoreImpl->hiScore) scoreImpl->hiScore = scoreImpl->currentScore;
}