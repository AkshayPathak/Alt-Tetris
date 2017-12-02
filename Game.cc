#include "Game.h"
#include "Grid.h"
#include "Block.h"
#include "Level.h"
#include "Level0.h"
#include "TextDisplay.h"
#include <iostream>
#include <fstream>

using namespace std;

struct Game::GameImpl {
    unique_ptr<Grid> grid = nullptr;
    unique_ptr<Level> level = nullptr;
    //unique_ptr<Score> score = nullptr;
    unique_ptr<Interpreter> interpreter = make_unique<Interpreter>();
    shared_ptr<Observer> td = nullptr;                 // MUST MAKE TD AND GD AFTER GRID IS INITIALIZED... CAUSE ATTACHING TO IT, so put in initGame?
    shared_ptr<Observer> gd = nullptr;

    Block nextBlock;
};

void Game::initInterpreter(int argc, char *argv[]) {
    gameImpl->interpreter->init(this, argc, argv);
}

void Game::initGame(int level, int seed, vector<char> blocksSequence, bool graphicalEnabled) {
    // making grid and interpreter
    gameImpl->grid = make_unique<Grid>(this);

    // TODO: Implement different levels that you start with
    gameImpl->level = make_unique<Level0>(blocksSequence);   // like this just for testing
    gameImpl->nextBlock = gameImpl->level->makeBlock();   // makes the first block
    gameImpl->grid->init();             // good that this is after make block

    gameImpl->td = make_shared<TextDisplay>(this);
    //make gd here too


    gameImpl->grid->attach(gameImpl->td);    // attaching observers
    //gameImpl->grid->attach(gameImpl->gd);      // attaching observers

}

void Game::left() {
    gameImpl->grid->transformLeft();
}

void Game::right() {
    gameImpl->grid->transformRight();
}

void Game::clockwise() {
    gameImpl->grid->transformClockwise();
}

void Game::counterClockwise() {
    gameImpl->grid->transformCounterClockwise();
}

void Game::down() {
    gameImpl->grid->transformDown();
}

void Game::drop() {
    gameImpl->grid->transformDrop();
}

void Game::levelUp() { // Needs Level.h
    //int newLevel = gameImpl->level->getLevel() + 1;
    //newLevel = newLevel > 4 ? 4 : newLevel;
    //gameImpl->level->setLevel(newLevel);
}

void Game::levelDown() {  // Needs Level.h
    //int newLevel = gameImpl->level->getLevel() - 1;
    //newLevel = newLevel >= 0 ? newLevel : 0;
    //gameImpl->level->setLevel(newLevel);
}

void Game::I() {

}

void Game::J() {

}

void Game::S() {

}

void Game::Z() {

}

void Game::L() {

}

void Game::O() {

}

void Game::T() {

}

void Game::restart() {

}

void Game::hint() {

}

void Game::createBlock() {
    gameImpl->nextBlock = gameImpl->level->makeBlock();
}

Block Game::getNextBlock() const {
    return gameImpl->nextBlock;
}

Game::~Game() {

}
// THE 5 GETTERS I GUESS... STILL DUNNO WHY FRIEND DOESNT WORK

int Game::getLevel() {
    return gameImpl->level->getLevel();
}

int Game::getScore() {
    // return gameImpl->score->getScore(); TODO: Make the score class
}

int Game::getHiScore() {
    //return gameImpl->score->getHiScore();      TODO: Make the score class
}

int Game::getWidth() {
    return gameImpl->grid->getWidth();
}

int Game::getHeight() {
    return gameImpl->grid->getHeight();
}

Block Game::getCurrentBlock() {
    return gameImpl->grid->getBlock();
}

vector<vector<shared_ptr<Cell>>> *Game::getBoard() {
    return gameImpl->grid->getBoard();
}



