#include "Level.h"

class Level0;
class Level1;
class Level2;
class Level3;
class Level4;


Level::~Level() {}

void Level::setLevel(int newLevel) {
    Level *theNewLevel;
    if(newLevel == 0) {
        theNewLevel = new Level0{};
    } else if(newLevel == 1) {
        theNewLevel = new Level1{};
    } else if(newLevel == 2) {
        theNewLevel = new Level2{};
    } else if(newLevel == 3) {
        theNewLevel = new Level3{};
    } else if(newLevel == 4) {
        theNewLevel = new Level4{};
    }
    std::swap(theNewLevel,this);
}
