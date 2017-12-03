#ifndef TEST_INTERPRETER_H
#define TEST_INTERPRETER_H

#include <iostream>
#include <vector>
#include <memory>
#include "Game.h"

using namespace std;

class Game;

class Interpreter {

    struct InterpreterImpl;
    unique_ptr<InterpreterImpl> interpreterImpl;

    typedef void (Game::*GameFunction)();

    /**
     * Interprets each of the command line args and sets the appropriate variables in interpreterImpl
     * @param argc Size of commands
     * @param argv Array of commands
     */
    void interpretCommandLineArgs(int argc, char *const *argv);

    /**
     * Reads in the sequence of blocks from a sequence file. If the file does not exist, defaults to a
     * a standard sequence which contains all the blocks
     */
    void parseSequenceFile();

    /**
     * Parses a command to find the multiplier given (eg if command is 10right, the multiplier is 10)
     * @param cmd The command to parse
     * @return Returns the multiplier. Also removes the multiplier from the original command.
     */
    int getMultiplier(string &cmd);

    /**
     * Performs the given function n times where n is the multiplier
     * @param game The game pointer
     * @param multiplier The number of times to run the function
     * @param function The function to execute. Has to be a member function of Game
     */
    void multiplierFunction(Game *game, int multiplier, GameFunction function);

    /**
     * Given a partial command, matches it to a command that the program can read
     * @param cmd The command to match
     * @return The command that is matched to. If command is ambiguous, it will print the possible commands and
     * return "ambiguous"
     */
    string matchCommand(const string &cmd);

public:

    Interpreter();

    /**
     * Initialize the interpreter to parse the command line args and listen to user commands
     * @param game The Game pointer
     * @param argc The number of command line args
     * @param argv The array of command line args
     */
    void init(Game *game, int argc, char *argv[]);

    virtual ~Interpreter();
};

#endif //TEST_INTERPRETER_H
