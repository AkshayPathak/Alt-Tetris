#ifndef TEST_TEXTDISPLAY_H
#define TEST_TEXTDISPLAY_H

#include "Observer.h"
#include <memory>

using namespace std;

class Game;

// attach to the board... i don't think it can attach itself...
class TextDisplay : public Observer {
    struct TextDisplayImpl;

    unique_ptr<TextDisplayImpl> textDisplayImpl;

public:
    TextDisplay(Game *game);

    virtual ~TextDisplay(); // virtual dtor

    virtual void notify() override;


};


#endif //TEST_TEXTDISPLAY_H
