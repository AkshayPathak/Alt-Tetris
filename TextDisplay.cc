#include "TextDisplay.h"
#include "Game.h"
#include "Grid.h"
#include "Block.h"
#include <iomanip>
#include <iostream>

using namespace std;

struct TextDisplay::TextDisplayImpl{
    Game *game;

    explicit TextDisplayImpl(Game *game) : game{game} {};
};

TextDisplay::TextDisplay(Game *game) :
        textDisplayImpl{make_unique<TextDisplayImpl>(game)} {}

void TextDisplay::notify() {
    printTitle();

    // Print the top 3 rows
    cout << "Level:" << std::right << std::setw(7) << textDisplayImpl->game->getLevel() << endl;
    cout << "Score:" << std::right << std::setw(7) << textDisplayImpl->game->getScore() << endl;
    cout << "Hi Score:" << std::right << std::setw(4) << textDisplayImpl->game->getHiScore() << endl;
    cout << "-------------" << endl;

    Block b = Block(textDisplayImpl->game->getCurrentBlock()->getCells());
    vector<vector<shared_ptr<Cell>>> *board = textDisplayImpl->game->getBoard();

    // Prints the board
    for (int i = 0; i < textDisplayImpl->game->getHeight(); i++) {
        cout << "|";
        for (int j = 0; j < textDisplayImpl->game->getWidth(); j++) {
            bool printBlock = false;
            for (int k = 0; k < b.getCells().size(); k++) {
                if ((b.getCells().at(k)->getX() == j) && b.getCells().at(k)->getY() == i) {
                    cout << b.getCells().at(k)->getC();
                    printBlock = true;
                    break;
                }
            }
            if (!printBlock) {
                if ((*board).at(i).at(j)->getC() == ' ') {
                    cout << '.';
                } else {
                    cout << (*board).at(i).at(j)->getC();
                }
            }
        }
        cout << "|" << endl;
    }

    // Prints the next block section
    cout << "-------------" << endl;
    cout << "Next:" << endl;
    Block next = Block(textDisplayImpl->game->getNextBlock()->getCells());
    for (int i = 0; i < 2; i++) {
        for(int j = 0; j < 4; j++) {
            bool printBlock = false;
            for (int k = 0; k < next.getCells().size(); k++) {
                if (next.getCells().at(k)->getX() == j && next.getCells().at(k)->getY() == i) {
                    cout << next.getCells().at(k)->getC();
                    printBlock = true;
                    break;
                }
            }
            if (!printBlock) cout << ' ';
        }
        cout << endl;
    }
}

void TextDisplay::printTitle() {
    cout << " _______           _______  ______   _______ _________ _______ \n"
            "(  ___  )|\\     /|(  ___  )(  __  \\ (  ____ )\\__   __/(  ____ \\\n"
            "| (   ) || )   ( || (   ) || (  \\  )| (    )|   ) (   | (    \\/\n"
            "| |   | || |   | || (___) || |   ) || (____)|   | |   | (_____ \n"
            "| |   | || |   | ||  ___  || |   | ||     __)   | |   (_____  )\n"
            "| | /\\| || |   | || (   ) || |   ) || (\\ (      | |         ) |\n"
            "| (_\\ \\ || (___) || )   ( || (__/  )| ) \\ \\_____) (___/\\____) |\n"
            "(____\\/_)(_______)|/     \\|(______/ |/   \\__/\\_______/\\_______)\n"
         << endl;
}

TextDisplay::~TextDisplay() {

}
