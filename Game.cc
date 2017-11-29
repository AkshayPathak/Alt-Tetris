#include "Game.h"
#include "Grid.h"
#include "Block.h"
#include <iostream>
#include <fstream>

// #include "Level.h"

using namespace std;

struct Game::GameImpl {


    unique_ptr<Grid> grid = nullptr;
    unique_ptr<Level> level = nullptr;
    unique_ptr<Score> score = nullptr;
    unique_ptr<TextDisplay> td = nullptr;
    unique_ptr<GraphicsDisplay> gd = nullptr;

};

Game::Game(): gameImpl{new GameImpl{}}, inter{new Interpreter{}} {}

void Game::init(int argc, char *argv[]) {
    inter->init(this,argc,argv);
}

void Game::left() {
    gameImpl->grid->currentBlock().transformLeft();
}

void Game::right() {
    gameImpl->grid->currentBlock().transformRight();
}

void Game::clockwise() {
    gameImpl->grid->currentBlock().transformClockwise();
}

void Game::counterClockwise() {
    gameImpl->grid->currentBlock().transformCounterClockwise();
}

void Game::down() {
    gameImpl->grid->currentBlock().transformDown();
}

void Game::drop() {
    gameImpl->grid->currentBlock().transformDrop();
}

void Game::levelUp() { // Needs Level.h
    int newLevel = gameImpl->level->getLevel() + 1;
    newLevel = newLevel > 4 ? 4 : newLevel;
    gameImpl->level->setLevel(newLevel);
}

void Game::levelDown() {  // Needs Level.h
    int newLevel = gameImpl->level->getLevel() - 1;
    newLevel = newLevel >= 0 ? newLevel : 0;
    gameImpl->level->setLevel(newLevel);
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