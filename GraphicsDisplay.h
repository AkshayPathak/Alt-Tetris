#ifndef TEST_GRAPHICSDISPLAY_H
#define TEST_GRAPHICSDISPLAY_H

#include "Observer.h"
#include <iostream>
#include <memory>

using namespace std;


class Game;

class GraphicsDisplay : public Observer {
    struct GraphicsDisplayImpl;
    unique_ptr<GraphicsDisplayImpl> graphicsDisplayImpl;

public:
    GraphicsDisplay(Game *game);
    virtual ~GraphicsDisplay();
    void notify() override;
};


#endif //TEST_GRAPHICSDISPLAY_H
