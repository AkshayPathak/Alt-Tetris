#include <sstream>
#include "GraphicsDisplay.h"
#include "Game.h"
#include "window.h"
#include "Cell.h"

using namespace std;

struct GraphicsDisplay::GraphicsDisplayImpl {
    Game *game;
    shared_ptr<Xwindow> xw;

    explicit GraphicsDisplayImpl(Game *game) : game{game}, xw{make_shared<Xwindow>()} {}
};

GraphicsDisplay::GraphicsDisplay(Game *game)
        : graphicsDisplayImpl{make_unique<GraphicsDisplayImpl>(game)} {}

// the print function
void GraphicsDisplay::notify() {
    // MATH LOGIC:
    int yMultiplier = 25;
    int xMultiplier = 25;


    stringstream lvl;
    stringstream score;
    stringstream hiScore;

    lvl << "Level: " << graphicsDisplayImpl->game->getLevel();
    score << "Score: " << graphicsDisplayImpl->game->getScore();
    hiScore << "Hi Score: " << graphicsDisplayImpl->game->getHiScore();


    graphicsDisplayImpl->xw->drawBigString(60, 100, "Quadris");

    graphicsDisplayImpl->xw->fillRectangle(0, 100, 225, 100, Xwindow::White);

    graphicsDisplayImpl->xw->drawString(70, 125, lvl.str());
    graphicsDisplayImpl->xw->drawString(70, 150, score.str());
    graphicsDisplayImpl->xw->drawString(70, 175, hiScore.str());


    graphicsDisplayImpl->xw->drawBigString(30, 300, "Next Block: ", Xwindow::Black);

    shared_ptr<Block> bb = graphicsDisplayImpl->game->getNextBlock();
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            bool printBlock = false;
            for (int k = 0; k < bb->getCells().size(); k++) {
                if (bb->getCells().at(k)->getX() == j && bb->getCells().at(k)->getY() == i) {
                    bb->getCells().at(k)->draw(graphicsDisplayImpl->xw, j * xMultiplier + 60, i * yMultiplier + 350,
                                               xMultiplier - 1, yMultiplier - 1);
                    printBlock = true;
                    break;
                }
            }
            if (!printBlock) {
                graphicsDisplayImpl->xw->fillRectangle(j * xMultiplier + 60, i * yMultiplier + 350, xMultiplier - 1,
                                                       yMultiplier - 1, Xwindow::White);
            }

        }
    }

    graphicsDisplayImpl->xw->fillRectangle(225, 0, 275, 500, Xwindow::Black);

    // Prints the board
    Block b = Block(graphicsDisplayImpl->game->getCurrentBlock()->getCells());
    vector<vector<shared_ptr<Cell>>> *board = graphicsDisplayImpl->game->getBoard();

    for (int i = 0; i < graphicsDisplayImpl->game->getHeight(); i++) {
        for (int j = 0; j < graphicsDisplayImpl->game->getWidth(); j++) {
            bool printBlock = false;
            for (int k = 0; k < b.getCells().size(); k++) {
                if (b.getCells().at(k)->getX() == j && b.getCells().at(k)->getY() == i) {
                    b.getCells().at(k)->draw(graphicsDisplayImpl->xw, (j * xMultiplier) + 225, (i * yMultiplier) + 50,
                                             xMultiplier - 1, yMultiplier - 1);
                    printBlock = true;
                    break;
                }
            }
            if (!printBlock) {
                (*board).at(i).at(j)->draw(graphicsDisplayImpl->xw, (j * xMultiplier) + 225, (i * yMultiplier) + 50,
                                           xMultiplier - 1, yMultiplier - 1);
            }
        }
    }
}

GraphicsDisplay::~GraphicsDisplay() {}
