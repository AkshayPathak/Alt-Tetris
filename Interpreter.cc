#include "Interpreter.h"


using namespace std;

void Interpreter::init(unique_ptr<Game> theGame, int argc, char argv[]) {


    string cmd;
    while(!cin.eof()) {
        cin >> cmd;

        if(cmd == "left") {
            theGame->left();
        } else if(cmd == "right") {
            theGame->right();
        } else if(cmd == "down") {
            theGame->down();
        } else if(cmd == "clockwise") {
            theGame->clockwise();
        } else if(cmd == "counterclockwise") {
            theGame->counterClockwise();
        } else if(cmd == "drop") {
            theGame->drop();
        } else if(cmd == "levelup") {
            theGame->levelUp();
        } else if(cmd == "leveldown") {
            theGame->levelDown();
        } else if(cmd == "norandom") {
            string inFile;
            cin >> inFile;
            theGame->noRandom(inFile);
        } else if(cmd == "random") {
            theGame->random();
        } else if(cmd == "sequence") {
            string inFile;
            cin >> inFile;
            theGame->sequence(inFile);
        } else if(cmd == "I") {
            theGame->I();
        } else if(cmd == "J") {
            theGame->J();
        } else if(cmd == "L") {
            theGame->L();
        } else if(cmd == "O") {
            theGame->O();
        } else if(cmd == "S") {
            theGame->S();
        } else if(cmd == "Z") {
            theGame->Z();
        } else if(cmd == "T") {
            theGame->T();
        } else if(cmd == "restart") {
            theGame->restart();
        } else if(cmd == "hint") {
            theGame->hint();
        }
    }
}