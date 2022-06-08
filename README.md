# Soduku Solver
Created a Sudoku game in C++ that first prompts the user for a board to use, then pulls up the board with an option menu that the user can pick from a list of those options on that menu. Some of those options include “?” – which shows the option menu again, “D” – which displays the board,“E” – prompts the user for a coordinate to edit and then, if it is allowed by the game logic, the value is inputted in the board, “S” – Asks the user what file they would like to save the board in, and saves the board, and “F” – Solves any Sudoku board, even to the most extreme difficulty. This game enforces the rules of Sudoku, which are every square must contain a single number, only the numbers from 1 through to 9 can be used, each 3×3 box can only contain each number from 1 to 9 once, and each vertical column can only contain each number from 1 to 9 once.

## Getting Started
---
Make sure you have C++ installed and are using a C++ compiler. Personally, I use
Xcode, but you can use Eclipse or use VSCode with a C++ compiler as well.

## Project Structure
---
The project files and folders are organized as follows:
```
sudokuSolver                  (project root folder)
+-- game                      (source code for game)
  +-- sudokuSolver.cpp        (soduku game and solver code)
+-- gameTextFiles             (text files to try out games)
  +-- hardestGamePossible.txt (hardest game known to man, used to check effiency of program)
  +-- normalGame.txt          (regular game)
+-- README.md                 (general info)
```

## Required Technologies
---
* C++
* C++ Compiler

## Author
---
*  Mason Schenk: sch19013@byui.edu
*  Chris Slack:  sla19004@byui.edu
*  Alec Day:     day19011@byui.edu
