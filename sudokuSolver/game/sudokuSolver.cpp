// libraries
#include <iostream>
#include <fstream>
using namespace std;

//calls
void userInput(int sudokuArray[9][9], int *possibleValue, char *letter,
               int *number);
void showValues(int sudokuArray[9][9], int *possibleValue, char *letter,
                int *number);
bool isSolved = false;
bool findLocation(int sudokuArray[][9], int &row, int &col);
bool safe(int sudokuArray[][9],int row, int col, int valOne);

/**********************************************************************
 * This function gets file location.
 ***********************************************************************/
void getFileLocation(char *boardName)
{
   cout << "Where is your board located? ";
   cin >> boardName;
}

/**********************************************************************
 * This function displays the options one has and how to preform them.
 ***********************************************************************/
void optionMenu(int sudokuArray[9][9])
{
   cout << "Options:"
        << endl;

   cout << "   ?  "
        << "Show these instructions"
        << endl;
   
   cout << "   D  "
        << "Display the board"
        << endl;
   
   cout << "   E  "
        << "Edit one square"
        << endl;

   cout << "   S  "
        << "Show the possible values for a square"
        << endl;
   
   cout << "   F  "
        << "FINISH HIM"
        << endl;

   cout << "   Q  "
        << "Save and Quit"
        << endl;

   cout << endl;
}


/**********************************************************************
 * This function prompts the user for the square they wish to see or edit.
 **********************************************************************/
void squareSelect(char *letter, int *number)
{
   cout << "What are the coordinates of the square: ";
   cin >> *letter
       >> *number;
   
   *letter = toupper(*letter);
}

/**********************************************************************
 * This function prompts the user for a grid location to edit. Then replaces
 * that spot in the array with the input.
 ***********************************************************************/
void editSquare(int sudokuArray[9][9], int *possibleValue, char *letter,
                int *number)
{
   int answer;
   int letterToInt;

   //This converts the letter column into a number for the array
   if (*letter == 'A')
      letterToInt = 0;
   if (*letter == 'B')
      letterToInt = 1;
   if (*letter == 'C')
      letterToInt = 2;
   if (*letter == 'D')
      letterToInt = 3;
   if (*letter == 'E')
      letterToInt = 4;
   if (*letter == 'F')
      letterToInt = 5;
   if (*letter == 'G')
      letterToInt = 6;
   if (*letter == 'H')
      letterToInt = 7;
   if (*letter == 'I')
      letterToInt = 8;
   
   if (*letter > 64 && *letter < 74 && *number > 0 && *number < 10)
   {
      if (sudokuArray[* number - 1][letterToInt] < 1)
      {
         cout << "What is the value at \'"
              << *letter
              << *number
              << "\': ";
         cin >> answer;
         
         int count = 0;
         showValues(sudokuArray, possibleValue, letter, number);
         for (int p = 0; p < 9; p++)
         {
            if (answer == possibleValue[p])
            {
               count++;
            }
         }

         if (count > 0)
         {
            sudokuArray[* number - 1][letterToInt] = answer;
         }
         else if (count == 0)
         {
            cout << "ERROR: Value \'"
                 << answer
                 << "\' in square \'"
                 << *letter
                 << *number
                 << "\' is invalid"
                 << endl;
         }
      }

      else
      {
         cout << "ERROR: Square \'"
              << *letter
              << *number
              << "\' is filled"
              << endl;
      }

      cout << endl;
   }

   else
   {
      cout << "ERROR: Square \'"
           << *letter
           << *number
           << "\' is invalid"
           << endl
           << endl;
   }

   userInput(sudokuArray, possibleValue, letter, number);
}

/**********************************************************************
 * This function checks rows, columns, and 3 by 3 squares for possible values
 * of a square.
 ***********************************************************************/
void showValues(int sudokuArray[9][9], int *possibleValue, char *letter, 
                int *number)
{
   int rowPosVal[9] = {0};
   int colPosVal[9] = {0};
   int squarePosVal[9] = {0};
   int possibleNotValue[9] = {0};
   int possibleCrossOff[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
   int i = 0;
   int letterToInt;
   int a = 0;
   int count = 0;

   for (int p = 0; p < 9; p++)
   {
      if (possibleValue[p] != 0)
      {
         possibleValue[count] = 0;
         count++;
      }
      count++;
   }

   if (*letter == 'A')
      letterToInt = 0;
   if (*letter == 'B')
      letterToInt = 1;
   if (*letter == 'C')
      letterToInt = 2;
   if (*letter == 'D')
      letterToInt = 3;
   if (*letter == 'E')
      letterToInt = 4;
   if (*letter == 'F')
      letterToInt = 5;
   if (*letter == 'G')
      letterToInt = 6;
   if (*letter == 'H')
      letterToInt = 7;
   if (*letter == 'I')
      letterToInt = 8;

   //Rows
   for (int c = 0; c < 9; c++)
   {
      if (sudokuArray[* number - 1][c] > 0)
      {
         rowPosVal[a] = sudokuArray[* number - 1][c];
         a++;
      }
   }
   
   //Columns
   a = 0;
   for (int r = 0; r < 9; r++)
   {
      if (sudokuArray[r][letterToInt] > 0)
      {
         colPosVal[a] = sudokuArray[r][letterToInt];
         a++;
      }
   }

   //3 by 3 Square
   a = 0;
   if (*number < 3 && letterToInt < 3) //1
   {
      for (int r = 0; r < 3; r++)
      {
         for (int c = 0; c < 3; c++)
         {
            if (sudokuArray[r][c] > 0)
            {
               squarePosVal[a] = sudokuArray[r][c];
               a++;
            }
         }
      }
   }
   else if (*number < 3 && letterToInt > 2 && letterToInt < 6) //2
   {
      for (int r = 0; r < 3; r++)
      {
         for (int c = 3; c < 6; c++)
         {
            if (sudokuArray[r][c] > 0)
            {
               squarePosVal[a] = sudokuArray[r][c];
               a++;
            }
         }
      }
   }
   else if (*number < 3 && letterToInt > 5 && letterToInt < 9)  //3
   {
      for (int r = 0; r < 3; r++)
      {
         for (int c = 6; c < 9; c++)
         {
            if (sudokuArray[r][c] > 0)
            {
               squarePosVal[a] = sudokuArray[r][c];
               a++;
            }
         }
      }
   }
   else if (*number > 2 && *number < 6 && letterToInt < 3) //4
   {
      for (int r = 3; r < 6; r++)
      {
         for (int c = 0; c < 3; c++)
         {
            if (sudokuArray[r][c] > 0)
            {
               squarePosVal[a] = sudokuArray[r][c];
               a++;
            }
         }
      }
   }
   else if (*number > 2 && *number < 6 && letterToInt > 2 && letterToInt < 6)
   {
      for (int r = 3; r < 6; r++)
      {
         for (int c = 3; c < 6; c++)
         {
            if (sudokuArray[r][c] > 0)
            {
               squarePosVal[a] = sudokuArray[r][c];
               a++;
            }
         }
      }
   }
   else if (*number > 2 && *number < 6 && letterToInt > 5 && letterToInt < 9)
   {
      for (int r = 3; r < 6; r++)
      {
         for (int c = 6; c < 9; c++)
         {
            if (sudokuArray[r][c] > 0)
            {
               squarePosVal[a] = sudokuArray[r][c];
               a++;
            }
         }
      }
   }
   else if (*number > 5 && *number < 9 && letterToInt < 3) //7
   {
      for (int r = 6; r < 9; r++)
      {
         for (int c = 0; c < 3; c++)
         {
            if (sudokuArray[r][c] > 0)
            {
               squarePosVal[a] = sudokuArray[r][c];
               a++;
            }
         }
      }
   }
   else if (*number > 5 && *number < 9 && letterToInt > 2 && letterToInt < 6)
   {
      for (int r = 6; r < 9; r++)
      {
         for (int c = 3; c < 6; c++)
         {
            if (sudokuArray[r][c] > 0)
            {
               squarePosVal[a] = sudokuArray[r][c];
               a++;
            }
         }
      }
   }
   else if (*number > 5 && *number < 9 && letterToInt > 5 && letterToInt < 9)
   {
      for (int r = 6; r < 9; r++)
      {
         for (int c = 6; c < 9; c++)
         {
            if (sudokuArray[r][c] > 0)
            {
               squarePosVal[a] = sudokuArray[r][c];
               a++;
            }
         }
      }
   }

   //order the possible values
   int temp;
   for (i = 0; i < 9; i++) //Rows
   {
      for (int j = i + 1; j < 9; j++)
      {
         if (rowPosVal[i] > rowPosVal[j])
         {
            temp = rowPosVal[i];
            rowPosVal[i] = rowPosVal[j];
            rowPosVal[j] = temp;
         }
      }
   }
   for (i = 0; i < 9; i++) //Columns
   {
      for (int j = i + 1; j < 9; j++)
      {
         if (colPosVal[i] > colPosVal[j])
         {
            temp = colPosVal[i];
            colPosVal[i] = colPosVal[j];
            colPosVal[j] = temp;
         }
      }
   }
   for (i = 0; i < 9; i++) //Square
   {
      for (int j = i + 1; j < 9; j++)
      {
         if (squarePosVal[i] > squarePosVal[j])
         {
            temp = squarePosVal[i];
            squarePosVal[i] = squarePosVal[j];
            squarePosVal[j] = temp;
         }
      }
   }
 
   //condenses and reduce to possible values
   count = 0;
   for (int value = 1; value < 10; value++)
   {
      for (int r = 0; r < 9; r++)
      {
         if (rowPosVal[r] == value)
         {
            possibleNotValue[count] = value;
         }
      }
      for (int c = 0; c < 9; c++)
      {
         if (colPosVal[c] == value)
         {
            possibleNotValue[count] = value;
         }
      }
      for (int s = 0; s < 9; s++)
      {
         if (squarePosVal[s] == value)
         {
            possibleNotValue[count] = value;
         }
      }
      count++;
   }

   count = 0;
   for (int p = 0; p < 9; p++)
   {
      if (possibleCrossOff[p] != possibleNotValue[p])
      {
         possibleValue[count] = possibleCrossOff[p];
         count++;
      }
   }
}

/***********************************************************************
 * This function displays the possible values for a square
 ***********************************************************************/
void displayPosValue(int sudokuArray[9][9], int *possibleValue, char *letter, 
                     int *number)
{
   int letterToInt;
   if (*letter == 'A')
      letterToInt = 0;
   if (*letter == 'B')
      letterToInt = 1;
   if (*letter == 'C')
      letterToInt = 2;
   if (*letter == 'D')
      letterToInt = 3;
   if (*letter == 'E')
      letterToInt = 4;
   if (*letter == 'F')
      letterToInt = 5;
   if (*letter == 'G')
      letterToInt = 6;
   if (*letter == 'H')
      letterToInt = 7;
   if (*letter == 'I')
      letterToInt = 8;

   if (sudokuArray[* number - 1][letterToInt] > 0)
   {
      cout << "ERROR: Square \'"
           << *letter
           << *number
           << "\' is filled";
   }

   else
   {
      cout << "The possible values for \'"
           << *letter
           << *number
           << "\' are: "
           << possibleValue[0];

      for (int i = 1; i < 10; i++)
      {
         if (possibleValue[i] != 0)
         {
            cout << ", "
                 << possibleValue[i];
         }
      }
   }

   cout << endl
        << endl;

   userInput(sudokuArray, possibleValue, letter, number);
}

/**********************************************************************
 * This function asks the user for a name for a file to save the game to.
 * Then writes the sudoku array to the file and closes.
 ***********************************************************************/
void quit(int sudokuArray[9][9])
{
   char saveGame[256];

   cout << "What file would you like to write your board to: ";
   cin >> saveGame;

   ofstream fout;

   fout.open(saveGame);
   for (int r = 0; r < 9; r++)
   {
      for (int c = 0; c < 9; c++)
      {
         fout << sudokuArray[r][c];
         fout << " ";

         if (c == 8)
         {
            fout << endl;
         }
      }
   }
   
   fout.close();
   
   cout << "Board written successfully"
        << endl;
}

/**********************************************************************
 * This file uses the file name, then reads the file and writes its content
 * to the sudoku array.
 ***********************************************************************/
void readFile(char boardName[], int sudokuArray[9][9])
{
   ifstream fin(boardName);

   while (!fin.eof())
   {
      for (int r = 0; r < 9; r++)
      {
         for (int c = 0; c < 9; c++)
         {
            fin >> sudokuArray[r][c];
         }
      }
   }

   fin.close();
}

/**********************************************************************
 * This function generates the basic board setup, and inserts the sudoku
 * array into the board setup and displays it for the user.
 ***********************************************************************/
void displayBoard(int sudokuArray[9][9], int *possibleValue, char *letter,
                  int *number)
{
   cout << "   A B C D E F G H I"
        << endl;

   int gridlabel = 1;
   for (int r = 0; r < 9; r++)
   {
     
      cout << gridlabel << " ";
      for (int c = 0; c < 3; c++)
      {
         cout << " ";
         if (sudokuArray[r][c] == 0)
         {
            cout << " ";
         }
         else
         {
            cout << sudokuArray[r][c];
         }
      }
      cout << "|";

      for (int c = 3; c < 6; c++)
      {
         if (sudokuArray[r][c] == 0)
         {
            cout << " ";
         }
         else
         {
            cout << sudokuArray[r][c];
         }

         if ( c < 5)
         {
            cout << " ";
         }
      }
      cout << "|";

      for (int c = 6; c < 9; c++)
      {
         if (sudokuArray[r][c] == 0)
         {
            cout << " ";
         }
         else
         {
            cout << sudokuArray[r][c];
         }

         if (c < 8)
         {
            cout << " ";
         }
      }

      if (r == 2)
      {
         cout << endl;
         cout << "   -----+-----+-----";
      }

      if (r == 5)
      {
         cout << endl;
         cout << "   -----+-----+-----";
      }

      gridlabel++;

      cout << endl;
   }

   cout << endl;

   userInput(sudokuArray, possibleValue, letter, number);
}

/**********************************************************************
 * This function solves any sudoku using the other solve functions.
 ***********************************************************************/
bool solve(int sudokuArray[][9])
{
   int row; 
   int col;
   int valOne;

   if (!findLocation(sudokuArray, row, col))
      return true;
   for (int valOne = 1; valOne <= 9; valOne++)
   {
      if (safe(sudokuArray, row, col, valOne))
      {
         sudokuArray[row][col] = valOne;
         if (solve(sudokuArray))
            return true;
         sudokuArray[row][col] = 0;
      }
   }
   return false;
}

/**********************************************************************
 * This function finds an empty spot.
 ***********************************************************************/
bool findLocation(int sudokuArray[][9], int &row, int &col)
{
   for (row = 0; row < 9; row++)
      for (col = 0; col < 9; col++)
         if (sudokuArray[row][col] == 0)
            return true;
   return false;
}

/**********************************************************************
 * This function checks if the number is being used in the row.
 ***********************************************************************/
bool usedInRow(int sudokuArray[][9],int row, int valOne)
{
   for (int col = 0; col < 9; col++)
      if (sudokuArray[row][col] == valOne)
         return true;
   return false;
}

/**********************************************************************
 * This function checks if the number is used in the column.
 ***********************************************************************/
bool usedInCol(int sudokuArray[][9], int col, int valOne)
{
   for (int row = 0; row < 9; row++)
      if (sudokuArray[row][col] == valOne)
         return true;
   return false;
}

/**********************************************************************
 * This function checks if the number is used in the box.
 ***********************************************************************/
bool usedInBox(int sudokuArray[][9], int boxStartR, int boxStartC, int valOne)
{
   for (int row = 0; row < 3; row++)
      for (int col = 0; col < 3; col++ )
         if (sudokuArray[row + boxStartR] [col + boxStartC] == valOne)
            return true;
   return false;
}

/**********************************************************************
 * This function checks to make sure the value inputted is valid.
 ***********************************************************************/
bool safe(int sudokuArray[][9],int row, int col, int valOne)
{
   return !usedInRow (sudokuArray, row, valOne) &&
      !usedInCol (sudokuArray, col, valOne) &&
      !usedInBox (sudokuArray, row - row % 3, col - col % 3, valOne);
}

/**********************************************************************
 * This function prompts for user input and then runs the various function
 * that is related to that input.
 ***********************************************************************/
void userInput(int sudokuArray[9][9], int *possibleValue, char *letter, 
               int *number)
{
   char optioncommand;

   cout << "> ";
   cin >> optioncommand;

   optioncommand = toupper(optioncommand);

   if (optioncommand == '?')       //Option Menu
   {
      optionMenu(sudokuArray);
      cout << endl;
      userInput(sudokuArray, possibleValue, letter, number);
   }

   if (optioncommand == 'D')       //Display Board
   {
      displayBoard(sudokuArray, possibleValue, letter, number);
   }

   if (optioncommand == 'E')       //Edit Square
   {
      squareSelect(letter, number);
      editSquare(sudokuArray, possibleValue, letter, number);
   }

   if (optioncommand == 'S')       //Show Values
   {
      squareSelect(letter, number);
      showValues(sudokuArray, possibleValue, letter, number);
      displayPosValue(sudokuArray, possibleValue, letter, number);
   }
   
   if (optioncommand == 'F')    // FINISHES THE SUDOKU
   {
      while (true)
      {
         isSolved = solve(sudokuArray);
         if (isSolved == true)
         {
            cout << endl;
            break;
         }
      }
      displayBoard(sudokuArray, possibleValue, letter, number);
      userInput(sudokuArray, possibleValue, letter, number);
   }

   if (optioncommand == 'Q')       //Save and Quit
   {
      quit(sudokuArray);
   }
}

/**********************************************************************
 * The Main function runs each of the other functions in the program.
 ***********************************************************************/
int main()
{
   char boardName[256];
   int sudokuArray[9][9] = {0};
   int possibleValue[9] = {0};
   char letter[2] = {0};
   int number[1] = {0};
   bool isSolved = false;
   int valOne;

   getFileLocation(boardName);
   readFile(boardName, sudokuArray);
   optionMenu(sudokuArray);
   displayBoard(sudokuArray, possibleValue, letter, number);
   return 0;
}