#include <sstream>
#include <fstream>
#include <unistd.h>
#include <termios.h>
#include "Interpreter.h"

using namespace std;

struct Interpreter::InterpreterImpl {
    int level = 0;
    int seed = 123;
    int highscore = 0;
    bool graphicsEnabled = true;
    bool keyboard = false;
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
    if (interpreterImpl->keyboard) {
        /*
         * We did not write this code and take no credit for it. This code converts the command line
         * into real-time so that all inputs are immediately processed (ie enter does not have to be pressed every
         * time). This is to receive keyboard input in real time and process the graphical display
         *
         * Credits to Jörg Beyer at https://stackoverflow.com/a/9547954/3281971
         */
        struct termios old_tio, neww_tio;

        /* get the terminal settings for stdin */
        tcgetattr(STDIN_FILENO, &old_tio);

        /* we want to keep the old setting to restore them a the end */
        neww_tio = old_tio;

        /* disable canonical mode (buffered i/o) and local echo */
        neww_tio.c_lflag &= (~ICANON & ~ECHO);

        /* set the neww settings immediately */
        tcsetattr(STDIN_FILENO, TCSANOW, &neww_tio);
        // End of copied code (disabling is below the while loop)

        while (true) {
            string cmd;

            char inputChar;
            inputChar = getchar();

            if (inputChar == 27) {
                /*
                 * For up, down, right and left buttons, three characters are inputted: 27, 91, and then
                 * 65, 66, 67, 68 for up, down, right, left, respectively. So we get char the first time to get
                 * 27, then again to get 91 and then check against the 65, 66, 67, 68 to get the correct button
                 */

                inputChar = getchar();  // 2nd time

                if (inputChar != 91) {
                    cout << "Invalid command" << endl;
                    continue;
                }

                inputChar = getchar();

                if (inputChar == 66) {
                    cmd = "down";
                } else if (inputChar == 67) {
                    cmd = "right";
                } else if (inputChar == 68) {
                    cmd = "left";
                } else if (inputChar == 65) {
                    cout << "Invalid command" << endl;
                    continue;
                }
            } else  if (inputChar == ' ') {
                cmd = "drop";
            } else if (inputChar == 'e') {
                cmd = "counterclockwise";
            } else if (inputChar == 'r') {
                cmd = "clockwise";
            } else if (inputChar == 'i') {
                cmd = "I";
            } else if (inputChar == 'j') {
                cmd = "J";
            } else if (inputChar == 'l') {
                cmd = "L";
            } else if (inputChar == 'o') {
                cmd = "O";
            } else if (inputChar == 's') {
                cmd = "S";
            } else if (inputChar == 'z') {
                cmd = "Z";
            } else if (inputChar == 't') {
                cmd = "T";
            } else if (inputChar == '-') {
                cmd = "leveldown";
            } else if (inputChar == '+') {
                cmd = "levelup";
            } else if (inputChar == 'm') {
                cmd = "random";
            } else if (inputChar == 'n') {
                cmd = "norandom";
            } else if (inputChar == 'q') {
                break;
            } else if (inputChar == 'p') {
                cmd = "restart";
            } else if (inputChar == 'h') {
                cmd = "help";
            } else {
                cout << "Invalid command" << endl;
                continue;
            }
            interpretCommands(cmd, game);
        }

        // Start of copied code to disable the real time command prompt
        tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
        // End of copied code

    } else {
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

            if (cmd == "quit") {
                break;
            }

            interpretCommands(cmd, game, multiplier);
        }
    }

    // Save high score file
    saveHighScoreFile(game->getHiScore());
}

void Interpreter::interpretCommands(string cmd, Game *game, int multiplier) {
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
    } else if ("help") {
        showUsage();
    } else {
        cout << "Invalid command" << endl;
    }
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
        } else if (commandName == "-help") {
            showUsage();
            exit(0);
        } else if (commandName == "-keyboard") {
            interpreterImpl->keyboard = true;
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
                               "Z", "T", "restart", "help", "quit"};

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

void Interpreter::showUsage() {
    cout << "Quadris: Created by Stanley Zhang, Brendan Power & Akshay Pathak" << endl <<
         "Usage: ./quadris [option]" << endl
         << endl <<
         "Features" << endl <<
         "Multiplier                         Use commands such as 10right to move 10 units to the right." << endl <<
         "Minimum Recognizable Commands      Use commands that are the minimum, e.g. 10ri moves 10 units to the right." << endl <<
         "Persistent High Score              Store the high score even when the game is quit completely. Use the quit command to save scores correctly." << endl <<
         "Keyboard Input                     To play the game with keyboard input, use the -keyboard flag as a command line argument. Make sure to have the terminal selected!" << endl
         << endl <<
         "Command Line Arguments             " << endl <<
         "-text                              Only show the text, no grapical display" << endl <<
         "-seed          [int]               Seed for the random number generator" << endl <<
         "-scriptfile    [string]            The name of the file to read blocks from" << endl <<
         "-startlevel    [int]               The level to start at" << endl <<
         "-highscorefile [string]            Name of the file from which the highscore should be read from" << endl <<
         "-keyboard                          Enable keyboard input such as left-arrow, right-arrow, etc" << endl <<
         "-help                              Show usage text" << endl
         << endl <<
         "In-Game Text [KEYBOARD] Commands   " << endl <<
         "left               [LEFT-ARROW]    Move the current block one unit left" << endl <<
         "right              [RIGHT-ARROW]   Move the current block one unit right" << endl <<
         "down               [DOWN-ARROW]    Move the current block one unit down" << endl <<
         "clockwise          [R]             Rotate the current block 90 degrees clockwise" << endl <<
         "counterclockwise   [E]             Rotate the current block 90 degrees counter-clockwise" << endl <<
         "drop               [SPACE]         Drop the current block and move on to the next one" << endl <<
         "levelup            [+]             Increase the current level by one" << endl <<
         "develdown          [-]             Decrease the current level by one" << endl <<
         "norandom           [M]             Switch to blocks from the given sequence file (not applicable for level 0)" << endl <<
         "random             [N]             Switch to generate blocks randomly (not applicable for level 0)" << endl <<
         "I                  [I]             Switch the current block to an I block" << endl <<
         "J                  [J]             Switch the current block to an J block" << endl <<
         "L                  [L]             Switch the current block to an L block" << endl <<
         "O                  [O]             Switch the current block to an O block" << endl <<
         "S                  [S]             Switch the current block to an S block" << endl <<
         "Z                  [Z]             Switch the current block to an Z block" << endl <<
         "T                  [T]             Switch the current block to an T block" << endl <<
         "restart            [P]             Restart the game" << endl <<
         "quit               [Q]             Quit the game (saves the highscore)" << endl
         << endl;
}

Interpreter::~Interpreter() {}

