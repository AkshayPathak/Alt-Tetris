# CS246 Quadris

By: Stanley Zhang, Brendan Power & Akshay Pathak

To build this game run the command `make`

Help text:

```
Usage: ./quadris [option]

Features << endl <<
Multiplier                         Use commands such as 10right to move 10 units to the right
Minimum Recognizable Commands      Use commands that are the minimum, e.g. 10ri moves 10 units to the right
Persistent High Score              Store the high score even when the game is quit completely. Use the quit command to save scores correctly
Keyboard Input                     To play the game with keyboard input, use the -keyboard flag as a command line argument. Make sure to have the terminal selected!
         
Command Line Arguments             
-text                              Only show the text, no grapical display
-seed          [int]               Seed for the random number generator
-scriptfile    [string]            The name of the file to read blocks from
-startlevel    [int]               The level to start at
-highscorefile [string]            Name of the file from which the highscore should be read from
-keyboard                          Enable keyboard input such as left-arrow, right-arrow, etc
-help                              Show usage text
         
In-Game Text [KEYBOARD] Commands  
         
left               [LEFT-ARROW]    Move the current block one unit left
right              [RIGHT-ARROW]   Move the current block one unit right
down               [DOWN-ARROW]    Move the current block one unit down
clockwise          [R]             Rotate the current block 90 degrees clockwise
counterclockwise   [E]             Rotate the current block 90 degrees counter-clockwise
drop               [SPACE]         Drop the current block and move on to the next one
levelup            [+]             Increase the current level by one
develdown          [-]             Decrease the current level by one
norandom           [M]             Switch to blocks from the given sequence file (not applicable for level 0)
random             [N]             Switch to generate blocks randomly (not applicable for level 0)
I                  [I]             Switch the current block to an I block
J                  [J]             Switch the current block to an J block
L                  [L]             Switch the current block to an L block
O                  [O]             Switch the current block to an O block
S                  [S]             Switch the current block to an S block
Z                  [Z]             Switch the current block to an Z block
T                  [T]             Switch the current block to an T block
restart            [P]             Restart the game
quit               [Q]             Quit the game (saves the highscore)
```
