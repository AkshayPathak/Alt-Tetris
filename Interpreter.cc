#include <sstream>
#include <fstream>
#include "Interpreter.h"

using namespace std;


void Interpreter::init(Game *game, int argc, char *argv[]) {

    interpretCommandLineArgs(argc, argv);

    if (level == 0) {
//        parseSequenceFile();
        blockSequence.emplace_back('I');
        blockSequence.emplace_back('J');
        blockSequence.emplace_back('S');
        blockSequence.emplace_back('Z');
        blockSequence.emplace_back('T');
        blockSequence.emplace_back('O');
    }
    // Init the game given the command line args
    game->initGame(level, seed, blockSequence, graphicsEnabled);

    // Start the command interpreter
    string cmd;
    while (cout << "Enter a command: " && cin >> cmd) {

        int multiplier = getMultiplier(cmd);

        // Check multiplier is >= 0
        if (multiplier < 0) {
            cerr << "Invalid multiplier, must be >= 0";
        }

        // If multiplier is 0, do nothing
        if (multiplier == 0) {
            continue;
        }

        cmd = matchCommand(cmd);

        // Check that the command was not ambiguous
        if (cmd == "ambiguous") {
            continue;
        }

        if (cmd == "left") {
            multiplierFunction(game, multiplier, &Game::left);
        } else if (cmd == "right") {
            multiplierFunction(game, multiplier, &Game::right);
        } else if (cmd == "down") {
            multiplierFunction(game, multiplier, &Game::down);
        } else if (cmd == "clockwise") {
            multiplierFunction(game, multiplier, &Game::clockwise);
        } else if (cmd == "counterclockwise") {
            multiplierFunction(game, multiplier, &Game::counterClockwise);
        } else if (cmd == "drop") {
            multiplierFunction(game, multiplier, &Game::drop);
        } else if (cmd == "levelup") {
            multiplierFunction(game, multiplier, &Game::levelUp);
        } else if (cmd == "leveldown") {
            multiplierFunction(game, multiplier, &Game::levelDown);
        } else if (cmd == "norandom") {
            string inFile;
            cin >> inFile;
            //game->noRandom(inFile);    TODO: ...
        } else if (cmd == "random") {
            //game->random();              TODO: ...
        } else if (cmd == "sequence") {
            string inFile;
            cin >> inFile;
            //game->sequence(inFile);      TODO: ...
        } else if (cmd == "I") {
            game->I();
        } else if (cmd == "J") {
            game->J();
        } else if (cmd == "L") {
            game->L();
        } else if (cmd == "O") {
            game->O();
        } else if (cmd == "S") {
            game->S();
        } else if (cmd == "Z") {
            game->Z();
        } else if (cmd == "T") {
            game->T();
        } else if (cmd == "restart") {
            game->restart();
        } else if (cmd == "hint") {
            game->hint();
        } else if (cmd == "quit") {
            break;
        } else {
            cout << "Invalid command" << endl;
        }
    }
}

void Interpreter::interpretCommandLineArgs(int argc, char *const argv[]) {
    for (int i = 1; i < argc; i++) {
        istringstream iss{argv[i]};

        string commandName;
        iss >> commandName;

        if (commandName == "-text") {
            graphicsEnabled = false;
        } else if (commandName == "-seed") {
            try {
                istringstream seedIss{argv[i + 1]};
                if (seedIss >> seed) {
                    i++;
                } else {
                    cerr << "Usage for the command line option is: -seed [int]. Skipping." << endl;
                }
            } catch (const logic_error &e) {
                cerr << "Usage for the command line option is: -seed [int]. Skipping." << endl;
            }
        } else if (commandName == "-scriptfile") {
            try {
                istringstream scriptFileIss{argv[i + 1]};
                if (scriptFileIss >> scriptFileName) {
                    i++;
                } else {
                    cerr << "Usage for the command line option is: -scriptfile [filename]. Skipping." << endl;
                }
            } catch (const logic_error &e) {
                cerr << "Usage for the command line option is: -scriptfile [filename]. Skipping." << endl;
            }
        } else if (commandName == "-startlevel") {
            try {
                istringstream startLevelIss{argv[i + 1]};
                if (startLevelIss >> level) {
                    i++;
                } else {
                    cerr << "Usage for the command line option is: -startlevel [int]. Skipping." << endl;
                }
            } catch (const logic_error &e) {
                cerr << "Usage for the command line option is: -startlevel [int]. Skipping." << endl;
            }
        } else {
            cerr << "Invalid command line option " << commandName << endl;
        }
    }
}

void Interpreter::parseSequenceFile() {
    ifstream inFile{scriptFileName};

    char blockName;
    while (inFile >> blockName) {
        blockSequence.emplace_back(blockName);
    }
}

int Interpreter::getMultiplier(string &cmd) {
    // Get the number of numbers at the beginning of the command
    int numberOfInts = 0;
    while (true) {
        if (cmd.at(numberOfInts) < '0' || cmd.at(numberOfInts) > '9') {
            break;
        } else {
            numberOfInts++;
        }
    }

    // Check if there was no multiplier
    if (numberOfInts == 0) {
        return 1;
    }

    // Extract the number at the beginning and remove it from the actual command
    string multiplierString = cmd.substr(0, numberOfInts);
    cmd = cmd.substr(numberOfInts);

    // Convert the string of integer into an actual integer
    istringstream iss{multiplierString};
    int multiplier;
    iss >> multiplier;

    return multiplier;
}

void Interpreter::multiplierFunction(Game *game, int multiplier, GameFunction function) {
    for (int i = 0; i < multiplier; i++) {
        (game->*function)();
    }
}

string Interpreter::matchCommand(const string &cmd) {
    vector<string> allCommands{"left", "right", "down", "clockwise", "counterclockwise", "drop",
                               "levelup", "leveldown", "norandom", "random", "sequence", "I", "J", "L", "O", "S",
                               "Z", "T", "restart", "hint", "quit"};

    // Filter every item that does not start with the given command
    // Don't increment manually since when removing, we don't want to skip element
    for (auto it = allCommands.begin(); it != allCommands.end();) {
        if (it->compare(0, cmd.length(), cmd)) {
            it = allCommands.erase(it);
        } else {
            it++;
        }
    }


    // If there is only one item, return that
    if (allCommands.size() == 1) {
        return allCommands.at(0);
    }

    // If there are no items, command is invalid, return the given command
    if (allCommands.empty()) {
        return cmd;
    }

    // Otherwise print error message
    cout << "Ambiguous command. Did you mean any of the following: " << endl;
    for (const auto &str : allCommands) {
        cout << str << endl;
    }

    return "ambiguous";
}

