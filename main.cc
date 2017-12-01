#include "Game.h"

// it called grid's constructor and then grid init


int main(int argc, char *argv[]) {
    unique_ptr<Game> game = make_unique<Game>();
    game->initInterpreter(argc, argv);
}
