#include <sstream>
#include "Interpreter.h"

using namespace std;

void Interpreter::init(shared_ptr<Game> game, int argc, char *argv[]) {

    int level = 0;
    int seed = 123;
    bool graphicsEnabled = true;
    string scriptFileName = "sequence.txt";

    for (int i = 1; i < argc; i++) {
        istringstream iss{argv[i]};

        string commandName;
        iss >> commandName;

        if (commandName == "-text") {
            graphicsEnabled = false;
        } else if (commandName == "-seed") {
            istringstream seedIss{argv[i + 1]};
            iss >> seed;
            i++;
        } else if (commandName == "-scriptfile") {
            istringstream scriptFileIss{argv[i + 1]};
            iss >> scriptFileName;
            i++;
        } else if (commandName == "-startlevel") {
            istringstream startLevelIss{argv[i + 1]};
            iss >> level;
            i++;
        }
    }

//    vecto

    // Init the game given the command line args
//    game->initGame(level, seed, , graphicsEnabled);

    // Start the command interpreter
    string cmd;
    while(!cin.eof()) {
        cin >> cmd;

        if(cmd == "left") {
            game->left();
        } else if(cmd == "right") {
            game->right();
        } else if(cmd == "down") {
            game->down();
        } else if(cmd == "clockwise") {
            game->clockwise();
        } else if(cmd == "counterclockwise") {
            game->counterClockwise();
        } else if(cmd == "drop") {
            game->drop();
        } else if(cmd == "levelup") {
            game->levelUp();
        } else if(cmd == "leveldown") {
            game->levelDown();
        } else if(cmd == "norandom") {
            string inFile;
            cin >> inFile;
            game->noRandom(inFile);
        } else if(cmd == "random") {
            game->random();
        } else if(cmd == "sequence") {
            string inFile;
            cin >> inFile;
            game->sequence(inFile);
        } else if(cmd == "I") {
            game->I();
        } else if(cmd == "J") {
            game->J();
        } else if(cmd == "L") {
            game->L();
        } else if(cmd == "O") {
            game->O();
        } else if(cmd == "S") {
            game->S();
        } else if(cmd == "Z") {
            game->Z();
        } else if(cmd == "T") {
            game->T();
        } else if(cmd == "restart") {
            game->restart();
        } else if(cmd == "hint") {
            game->hint();
        }
    }
}