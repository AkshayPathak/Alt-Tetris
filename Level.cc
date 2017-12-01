#include "Level.h"


struct LevelImpl {
    int lvl;
};

Block &Level::makeBlock() {

}


int Level::getLevel() {
    return levelImpl->lvl;
}


int Level::setLevel(int newLevel) {
    levelImpl->lvl = newLevel;
}

