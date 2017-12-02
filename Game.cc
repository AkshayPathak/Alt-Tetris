#include "Game.h"
#include "Grid.h"
#include "Block.h"
#include <iostream>
#include <fstream>
#include "Level0.h"

using namespace std;

struct Game::GameImpl {

    unique_ptr<Grid> grid = nullptr;
    unique_ptr<Level> level = nullptr;
    unique_ptr<Score> score = nullptr;
    unique_ptr<Interpreter> interpreter = make_unique<Interpreter>();
    shared_ptr<Observer> td = nullptr;                 // MUST MAKE TD AND GD AFTER GRID IS INITIALIZED... CAUSE ATTACHING TO IT, so put in initGame?
    shared_ptr<Observer> gd = nullptr;

    Block nextBlock;
    // TODO: grid is already dealt with through initGame, but maybe need constructor for interpreter, td and gd for sure (level score)?
};

Game::Game() : gameImpl{make_unique<GameImpl>()} {}

void Game::initInterpreter(int argc, char *argv[]) {
    gameImpl->interpreter->init(this, argc, argv);
}

void Game::initGame(int level, int seed, vector<char> blocksSequence, bool graphicalEnabled) {
    // making grid and interpreter
    gameImpl->grid = make_unique<Grid>(this);

    gameImpl->level = make_unique<Level0>(blocksSequence);
    getNextBlock() = gameImpl->level->makeBlock();
    // SHOULD ATTACH OBSERVERS HERE... assuming game already has SHARED pointers to td and gd
    gameImpl->grid->attach(gameImpl->td);
    gameImpl->grid->attach(gameImpl->gd);

    gameImpl->grid->init();
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


