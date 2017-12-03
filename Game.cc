#include "Game.h"
#include "Grid.h"
#include "Block.h"
#include "Level.h"
#include "Level0.h"
#include "Score.h"
#include "TextDisplay.h"
#include <iostream>
#include <fstream>

using namespace std;

struct Game::GameImpl {
    unique_ptr<Grid> grid = nullptr;
    unique_ptr<Level> level = nullptr;
    unique_ptr<Score> score = nullptr;
    unique_ptr<Interpreter> interpreter = make_unique<Interpreter>();
    shared_ptr<Observer> td = nullptr;                 // MUST MAKE TD AND GD AFTER GRID IS INITIALIZED... CAUSE ATTACHING TO IT, so put in initGame?
//    shared_ptr<Observer> gd = nullptr;

    shared_ptr<Block> nextBlock;
};

void Game::initInterpreter(int argc, char *argv[]) {
    gameImpl->interpreter->init(this, argc, argv);
}

void Game::initGame(int level, int seed, vector<char> blocksSequence, bool graphicalEnabled) {

    // making grid and interpreter
    gameImpl->grid = make_unique<Grid>(this);

    // TODO: Implement different levels that you start with
    gameImpl->score = make_unique<Score>();
    gameImpl->level = make_unique<Level0>(blocksSequence);   // like this just for testing
    gameImpl->nextBlock = gameImpl->level->makeBlock();   // makes the first block
    gameImpl->td = make_shared<TextDisplay>(this);
    gameImpl->grid->attach(gameImpl->td);    // attaching observers
    //gameImpl->grid->attach(gameImpl->gd);      // attaching observers
    gameImpl->grid->init();             // good that this is after make block

    //make gd here too

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
    int rightShift = (gameImpl->grid->getBlock()->getCells().at(0)->getX());
    int downShift = (gameImpl->grid->getBlock()->getCells().at(0)->getY()) - 3;
    gameImpl->grid->setCurrentBlock(make_shared<Block>(gameImpl->level->makeIBlock()));
    gameImpl->grid->numDown(downShift);
    gameImpl->grid->numRight(rightShift);
    gameImpl->grid->notifyObservers();
}

void Game::J() {
    int rightShift = (gameImpl->grid->getBlock()->getCells().at(0)->getX());
    int downShift = (gameImpl->grid->getBlock()->getCells().at(0)->getY()) - 3;
    gameImpl->grid->setCurrentBlock(make_shared<Block>(gameImpl->level->makeJBlock()));
    gameImpl->grid->numDown(downShift);
    gameImpl->grid->numRight(rightShift);
    gameImpl->grid->notifyObservers();
}

void Game::S() {
    int rightShift = (gameImpl->grid->getBlock()->getCells().at(0)->getX());
    int downShift = (gameImpl->grid->getBlock()->getCells().at(0)->getY()) - 3;
    gameImpl->grid->setCurrentBlock(make_shared<Block>(gameImpl->level->makeSBlock()));
    gameImpl->grid->numDown(downShift);
    gameImpl->grid->numRight(rightShift);
    gameImpl->grid->notifyObservers();
}

void Game::Z() {
    int rightShift = (gameImpl->grid->getBlock()->getCells().at(0)->getX());
    int downShift = (gameImpl->grid->getBlock()->getCells().at(0)->getY()) - 3;
    gameImpl->grid->setCurrentBlock(make_shared<Block>(gameImpl->level->makeZBlock()));
    gameImpl->grid->numDown(downShift);
    gameImpl->grid->numRight(rightShift);
    gameImpl->grid->notifyObservers();
}

void Game::L() {
    int rightShift = (gameImpl->grid->getBlock()->getCells().at(0)->getX());
    int downShift = (gameImpl->grid->getBlock()->getCells().at(0)->getY()) - 3;
    gameImpl->grid->setCurrentBlock(make_shared<Block>(gameImpl->level->makeLBlock()));
    gameImpl->grid->numDown(downShift);
    gameImpl->grid->numRight(rightShift);
    gameImpl->grid->notifyObservers();
}

void Game::O() {
    int rightShift = (gameImpl->grid->getBlock()->getCells().at(0)->getX());
    int downShift = (gameImpl->grid->getBlock()->getCells().at(0)->getY()) - 3;
    gameImpl->grid->setCurrentBlock(make_shared<Block>(gameImpl->level->makeOBlock()));
    gameImpl->grid->numDown(downShift);
    gameImpl->grid->numRight(rightShift);
    gameImpl->grid->notifyObservers();
}

void Game::T() {
    int rightShift = (gameImpl->grid->getBlock()->getCells().at(0)->getX());
    int downShift = (gameImpl->grid->getBlock()->getCells().at(0)->getY()) - 3;
    gameImpl->grid->setCurrentBlock(make_shared<Block>(gameImpl->level->makeTBlock()));
    gameImpl->grid->numDown(downShift);
    gameImpl->grid->numRight(rightShift);
    gameImpl->grid->notifyObservers();
}

void Game::restart() {
    gameImpl->score->resetScore();
    gameImpl->grid->init();
}

void Game::hint() {
// TODO
}

void Game::createBlock() {
    gameImpl->nextBlock = gameImpl->level->makeBlock();
}

shared_ptr<Block> Game::getNextBlock() const {
    return gameImpl->nextBlock;
}

Game::~Game() {

}
// THE 5 GETTERS I GUESS... STILL DUNNO WHY FRIEND DOESNT WORK

int Game::getLevel() {
    return gameImpl->level->getLevel();
}

int Game::getScore() {
     return gameImpl->score->getScore();
}

int Game::getHiScore() {
    return gameImpl->score->getHiScore();
}

int Game::getWidth() {
    return gameImpl->grid->getWidth();
}

int Game::getHeight() {
    return gameImpl->grid->getHeight();
}

shared_ptr<Block> Game::getCurrentBlock() {
    return gameImpl->grid->getBlock();
}

vector<vector<shared_ptr<Cell>>> *Game::getBoard() {
    return gameImpl->grid->getBoard();
}

void Game::incrementPointsByLinesDeleted(int numberOfLinesDeleted) {
    gameImpl->score->updateScore((numberOfLinesDeleted + gameImpl->level->getLevel()) *
                                 (numberOfLinesDeleted + gameImpl->level->getLevel()));
}

Game::Game() : gameImpl(make_unique<GameImpl>()) {}

