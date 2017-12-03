#include "GraphicsDisplay.h"
#include "Game.h"
#include "window.h"
#include "Cell.h"

using namespace std;

struct GraphicsDisplay::GraphicsDisplayImpl {
    Game *game;
    shared_ptr<Xwindow> xw;

    // ctor
    GraphicsDisplayImpl(Game * game) : game{game}, xw{make_shared<Xwindow>()} {}
};

GraphicsDisplay::GraphicsDisplay(Game *game)
        : graphicsDisplayImpl{make_unique<GraphicsDisplayImpl>(game)} {}

GraphicsDisplay::~GraphicsDisplay() {}


// the print function
void GraphicsDisplay::notify() {
    // TODO : title here AND how big each cell is on the board... that math logic

    // MATH LOGIC:
    int multiplier = 25;


    // prints the level... score and hi score here to the left
    // prints next block

    // prints the board
    Block b = Block(graphicsDisplayImpl->game->getCurrentBlock()->getCells());
    vector<vector<shared_ptr<Cell>>> *board = graphicsDisplayImpl->game->getBoard();

    for (int i = 0; i < graphicsDisplayImpl->game->getHeight(); i++) {
        for (int j = 0; j < graphicsDisplayImpl->game->getWidth(); j++) {
            bool printBlock = false;
            for (int k = 0; k < b.getCells().size(); k++) {
                if (b.getCells().at(k)->getX() == j && b.getCells().at(k)->getY() == i) {
                    b.getCells().at(k)->draw(graphicsDisplayImpl->xw, j*multiplier, i*multiplier, multiplier, multiplier);
                    printBlock = true;
                    break;
                }
            }
            if (!printBlock) {
                (*board).at(i).at(j)->draw(graphicsDisplayImpl->xw, j*multiplier, i*multiplier, multiplier, multiplier);
            }
        }
    }



}





