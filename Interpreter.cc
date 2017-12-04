#include <sstream>
#include <fstream>
#include "Interpreter.h"

using namespace std;

struct Interpreter::InterpreterImpl {
    int level = 0;
    int seed = 123;
    int highscore = 0;
    bool graphicsEnabled = true;
    string scriptFileName = "sequence.txt";
    string highScoreFileName = "hiscore.txt";
    vector<char> blockSequence;
};

Interpreter::Interpreter() : interpreterImpl{make_unique<InterpreterImpl>()} {}

void Interpreter::init(Game *game, int argc, char *argv[]) {

    interpretCommandLineArgs(argc, argv);

    parseSequenceFile();

    parseHighScoreFile();

    // Init the game given the command line args
    game->initGame(interpreterImpl->level, interpreterImpl->seed,
                   interpreterImpl->blockSequence, interpreterImpl->graphicsEnabled,
                   interpreterImpl->highscore);

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
            game->random(true);
        } else if (cmd == "random") {
            game->random(false);
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
        } else if (cmd == "quit") {
            break;
        } else {
            cout << "Invalid command" << endl;
        }
    }

    // Save high score file
    saveHighScoreFile(game->getHiScore());
}

void Interpreter::interpretCommandLineArgs(int argc, char *const argv[]) {
    for (int i = 1; i < argc; i++) {
        istringstream iss{argv[i]};

        string commandName;
        iss >> commandName;

        if (commandName == "-text") {
            interpreterImpl->graphicsEnabled = false;
        } else if (commandName == "-seed") {
            try {
                istringstream seedIss{argv[i + 1]};
                if (seedIss >> interpreterImpl->seed) {
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
                if (scriptFileIss >> interpreterImpl->scriptFileName) {
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
                if (startLevelIss >> interpreterImpl->level) {
                    i++;
                } else {
                    cerr << "Usage for the command line option is: -startlevel [int]. Skipping." << endl;
                }
            } catch (const logic_error &e) {
                cerr << "Usage for the command line option is: -startlevel [int]. Skipping." << endl;
            }
        } else if (commandName == "-highscorefile") {
            try {
                istringstream startLevelIss{argv[i + 1]};
                if (startLevelIss >> interpreterImpl->highScoreFileName) {
                    i++;
                } else {
                    cerr << "Usage for the command line option is: -highscorefile [string]. Skipping." << endl;
                }
            } catch (const logic_error &e) {
                cerr << "Usage for the command line option is: -highscorefile [string]. Skipping." << endl;
            }
        } else {
            cerr << "Invalid command line option " << commandName << endl;
        }
    }
}

void Interpreter::parseSequenceFile() {
    ifstream inFile{interpreterImpl->scriptFileName};

    // If the file is readable, read from it
    if (inFile.good()) {
        char blockName;
        while (inFile >> blockName) {
            interpreterImpl->blockSequence.emplace_back(blockName);
        }
    } else {
        cout << "Error reading from sequence file. Using default list." << endl;

        // Otherwise default to the following list
        interpreterImpl->blockSequence.emplace_back('I');
        interpreterImpl->blockSequence.emplace_back('J');
        interpreterImpl->blockSequence.emplace_back('S');
        interpreterImpl->blockSequence.emplace_back('Z');
        interpreterImpl->blockSequence.emplace_back('T');
        interpreterImpl->blockSequence.emplace_back('O');
    }
}

void Interpreter::parseHighScoreFile() {
    ifstream inFile{interpreterImpl->highScoreFileName};

    if (inFile.good()) {
        int highscore;
        if (inFile >> highscore) {
            interpreterImpl->highscore = highscore;
        } else {
            cout << "Could not read highscore file, skipping." << endl;
        }
    } else {
        cout << "Could not read highscore file, skipping." << endl;
    }
}

void Interpreter::saveHighScoreFile(int score) {
    ofstream outfile{interpreterImpl->highScoreFileName};

    if (outfile.good()) {
        outfile << score << endl;
        outfile.close();
    } else {
        cout << "Could not save highscore. Skipping." << endl;
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

Interpreter::~Interpreter() {}


