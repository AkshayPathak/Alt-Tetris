#include "Game.h"
#include <memory>

int main(int argc, char *argv[]) {
    unique_ptr<Game> game = make_unique<Game>();
    game->initInterpreter(argc, argv);
}
