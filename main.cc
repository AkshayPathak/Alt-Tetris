#include "Game.h"
#include <memory>

int main(int argc, char *argv[]) {
    shared_ptr<Game> game = make_shared<Game>(new Game);
    game->initInterpreter(argc, argv);
}
