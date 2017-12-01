#include "Game.h"
#include "Grid.h"
#include "Block.h"
#include <iostream>
#include <fstream>

using namespace std;

struct Game::GameImpl {

    unique_ptr<Grid> grid = nullptr;
//    unique_ptr<Level> level = nullptr;
//    unique_ptr<Score> score = nullptr;
    unique_ptr<Interpreter> interpreter = make_unique<Interpreter>();
//    unique_ptr<TextDisplay> td = nullptr;
//    unique_ptr<GraphicsDisplay> gd = nullptr;

    Block nextBlock;

};

Game::Game() : gameImpl{make_unique<GameImpl>()} {}

void Game::initInterpreter(int argc, char *argv[]) {
    gameImpl->interpreter->init(this, argc, argv);
}

void Game::initGame(int level, int seed, vector<shared_ptr<Block>> blocksSequence, bool graphicalEnabled) {
    // making grid and interpreter
    gameImpl->grid = make_unique<Grid>(this);
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

void Game::random() {

}

void Game::noRandom(string inFile) {

}

void Game::sequence(string inFile) {

}

void Game::restart() {

}

void Game::hint() {

}

void Game::createBlock() {
    //...
}

Block Game::getNextBlock() const {
    // shouldn't replace nextblock in here because it won't know if other classes use it, currently it does cause grid will always take it
    // but other classes might not
}

Game::~Game() {

}
