#include "Game.h"
#include "Grid.h"
#include "Block.h"
#include "Level.h"
#include "Level0.h"
#include "Score.h"
#include "TextDisplay.h"
#include "GraphicsDisplay.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "Level1.h"
#include "Interpreter.h"
#include <iostream>
#include <fstream>

using namespace std;

struct Game::GameImpl {
    unique_ptr<Grid> grid = nullptr;
    unique_ptr<Level> level = nullptr;
    unique_ptr<Score> score = nullptr;
    unique_ptr<Interpreter> interpreter = nullptr;
    shared_ptr<Observer> td = nullptr;
    shared_ptr<Observer> gd = nullptr;

    shared_ptr<Block> nextBlock;
    vector<char> blockSequence;
};

Game::Game() : gameImpl(make_unique<GameImpl>()) {}

void Game::initInterpreter(int argc, char *argv[]) {
    gameImpl->interpreter = make_unique<Interpreter>();
    gameImpl->interpreter->init(this, argc, argv);
}

void Game::initGame(int level, int seed, const vector<char> &blocksSequence, bool graphicalEnabled, int highscore) {

    // Seed the random number generator
    srand(seed);

    gameImpl->blockSequence = blocksSequence;

    // making grid and interpreter
    gameImpl->grid = make_unique<Grid>(this);

    // Create the score object
    gameImpl->score = make_unique<Score>();
    gameImpl->score->setHiScore(highscore);

    // Make the appropriate level
    switchLevel(level);

    // Create the first next block
    gameImpl->nextBlock = gameImpl->level->makeBlock();

    // Create the text display
    gameImpl->td = make_shared<TextDisplay>(this);

    // Attach TextDisplay as an observer to Grid
    gameImpl->grid->attach(gameImpl->td);

    // If graphicsDisplay should be enabled, create it and add as an observer to Grid
    if (graphicalEnabled) {
        gameImpl->gd = make_shared<GraphicsDisplay>(this);
        gameImpl->grid->attach(gameImpl->gd);
    }

    gameImpl->grid->init();
}

void Game::left() {
    gameImpl->grid->transformLeft(checkHeavy());
}

void Game::right() {
    gameImpl->grid->transformRight(checkHeavy());
}

void Game::clockwise() {
    gameImpl->grid->transformClockwise(checkHeavy());
}

void Game::counterClockwise() {
    gameImpl->grid->transformCounterClockwise(checkHeavy());
}

void Game::down() {
    gameImpl->grid->transformDown();
}

void Game::drop() {
    gameImpl->grid->transformDrop();
}

bool Game::checkHeavy() {
    return gameImpl->level->getLevel() >= 3;
}

void Game::levelUp() { // Needs Level.h
    switchLevel(gameImpl->level->getLevel() + 1);
}

void Game::levelDown() {  // Needs Level.h
    switchLevel(gameImpl->level->getLevel() - 1);
}

void Game::switchLevel(int newLevel) {
    switch (newLevel) {
        case 0:
            gameImpl->level = make_unique<Level0>(gameImpl->blockSequence);
            break;
        case 1:
            gameImpl->level = make_unique<Level1>(gameImpl->blockSequence);
            break;
        case 2:
            gameImpl->level = make_unique<Level2>(gameImpl->blockSequence);
            break;
        case 3:
            gameImpl->level = make_unique<Level3>(gameImpl->blockSequence);
            break;
        case 4:
            gameImpl->level = make_unique<Level4>(gameImpl->blockSequence);
    }
    gameImpl->grid->notifyObservers();
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
    // Reset the blocks sequence to start from beginning
    gameImpl->level->resetBlockSequence();
    // Generate new block
    gameImpl->nextBlock = gameImpl->level->makeBlock();
    gameImpl->grid->init();
}

void Game::random(bool noRandom) {
    gameImpl->level->setNoRandom(noRandom);
}
void Game::createBlock() {
    gameImpl->nextBlock = gameImpl->level->makeBlock();
}

shared_ptr<Block> Game::getNextBlock() const {
    return gameImpl->nextBlock;
}

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


shared_ptr<Block> Game::getABlock() {
    return gameImpl->level->makeABlock();
}

vector<vector<shared_ptr<Cell>>> *Game::getBoard() {
    return gameImpl->grid->getBoard();
}

void Game::incrementPointsByLinesDeleted(int numberOfLinesDeleted) {
    gameImpl->score->updateScore((numberOfLinesDeleted + gameImpl->level->getLevel()) *
                                 (numberOfLinesDeleted + gameImpl->level->getLevel()));
}

Game::~Game() {}

