#include "TextDisplay.h"
#include "Game.h"
#include <iomanip>
#include <iostream>

using namespace std;

struct TextDisplay::TextDisplayImpl{
    Game *game;

    //ctor
    TextDisplayImpl(Game *game) : game{game} {};
};

TextDisplay::TextDisplay(Game *game) :
        textDisplayImpl{make_unique<TextDisplayImpl>(game)} {}

// basically acts as the print function.. cause it is observing the Grid
void TextDisplay::notify() {
    cout << "Level:" << std::right << std::setw(7) << textDisplayImpl->game->getLevel() << endl;     // TODO: HOW DO I GET ACCESS OF LEVEL OR ANY OTHER FIELD, CAUSE GAMEIMPL IS PRIVATE: SOLVED, just use a getter for the level pointer
    cout << "Score:" << std::right << std::setw(7) << "40" << endl;
    cout << "Hi Score:" << std::right << std::setw(4) << "40" << endl;
}

// if i ever wanted to change where it goes, i could make it a field and make a setter, then output it like that