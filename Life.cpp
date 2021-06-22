// Richard Herget, Brianna Cappo, Patrick Downing, Alexander Southerland, Evin Fisher, Cris Zbavitel
// Life simulation

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include <string>
using namespace std;

const int MAXWORLDROWS = 25;
const int MAXWORLDCOLS = 80;
const int MAXROWS = MAXWORLDROWS + 2;
const int MAXCOLS = MAXWORLDCOLS + 2;
const int FILENAMESIZE = 255;

// ASCII characters to use for display
// https://theasciicode.com.ar/extended-ascii-code/block-graphic-character-ascii-code-219.html
// for interesting effect use code 219 and 176 instead of the asterisk and space
const unsigned char CELL = '*';  // 219;
const unsigned char EMPTY = ' '; // 176;

enum class State { dead = 0, alive = 1 };

/*
* initWorld is used to initialize all positions in the world
* array to the 'dead' state
*/
void initWorld(State world[][MAXCOLS]);

/*
* display is used to draw the 'world' onto the screen
* for each 'alive' cell, the value CELL is displayed
* for each 'dead' cell, the value EMPTY is displayed
* does NOT display any items in:
*   row 0, row MAXROWS-1, column 0, or column MAXCOLS-1
* since these rows and columns are used as a "border"
* around the world grid
*/
void display(State world[][MAXCOLS]);

/*
* getFile will get a filename from the user. It then attmpts
* to open the file, read its contents, and update the world
* based on the contents of the file. The file should contain
* only spaces and asterisks. A space represents a 'dead' cell
* and an asterisk represents an 'alive' cell.
* The function stops reading and exits the program if > MAXWORLDCOLS
* characters are found on one row, or if > MAXWORLDROWS rows are
* found in the file.
*/
void getFile(State world[][MAXCOLS]);

/*
* calcNewWorld is used to calculate the new state of the world
* (i.e. a new generation) based upon analyzing the current world state
*/
void calcNewWorld(State world[][MAXCOLS]);

/*
* neighborCount is used to count the number of 'alive' cells in
* the 8 neighboring positions which are surrounding position
* [row][col] in world
*/
int neighborCount(State world[][MAXCOLS], int row, int col);

int main()
{
	State world[MAXROWS][MAXCOLS];
	int generation = 0;
	bool stop = false;

	initWorld(world);
	getFile(world);
	cin.ignore();

	do
	{
		// system("cls") clears the screen; only works on Windows machines
		// You will probably need to comment this out if working on
		// a non-Windows machine
		system("cls");

		display(world);
		generation++;
		cout << "Generation: " << generation << "\t";
		cout << "<ENTER> to continue / <Q + ENTER> to quit: ";

		char input[FILENAMESIZE];
		cin.getline (input, FILENAMESIZE);
		

		if (input[0] == 'Q' || input[0] == 'q')
		{
			stop = true;
		}
		calcNewWorld(world);
	} while (!stop);
	return 0;
}


int neighborCount(State world[][MAXCOLS], int row, int col)
{
	// This code checks to make sure you aren't trying to count neighbors for any
	// position on row #0, or on row #MAXWORLDROWS+1,
	// or in column 0, or in columnn MAXWORLDCOLUMNS+1
	// because if you are, you are going to run into array out-of-bounds problems
	if (row < 1 || row > MAXWORLDROWS)
	{
		cerr << "ERROR: invalid row parameter " << row << " in neighborCount\n";
		exit(1);
	}
	else if (col < 1 || col > MAXWORLDCOLS)
	{
		cerr << "ERROR: invalid col parameter " << col << " in neighborCount\n";
		exit(1);
	}

	int i = 0;

	//loops through each neighbor
	for (int index = 0; index < 8; index++)
	{
		int x, y = 0;

		//switches the neighbor it looks for depending on the index of the for loop
		switch (index)
		{
		case 0:
			x = -1;
			y = -1;
			break;
		case 1:
			x = -1;
			y = 0;
			break;
		case 2:
			x = -1;
			y = 1;
			break;
		case 3:
			x = 0;
			y = 1;
			break;
		case 4:
			x = 1;
			y = 1;
			break;
		case 5:
			x = 1;
			y = 0;
			break;
		case 6:
			x = 1;
			y = -1;
			break;
		case 7:
			x = 0;
			y = -1;
			break;
		}

		//looks and sees if the neighbor is alive and if it is, then increments i
		if (world[row + x][col + y] == State::alive)
		{
			i++;
		}
	}
	return i;
}

void calcNewWorld(State world[][MAXCOLS])
{
	int neighbor[MAXROWS][MAXCOLS];

	//this function calculates amount of neighboring points in the txt file
	for (int i = 1; i < MAXROWS - 1; i++)
	{
		for (int j = 1; j < MAXCOLS - 1; j++)
		{
			neighbor[i][j] = neighborCount(world, i, j);				
		}
	}

	//This function takes the information from neighbor and sets the states of each cell
	//in world
	for (int i = 1; i < MAXROWS - 1; i++)
	{
		for (int j = 1; j < MAXCOLS - 1; j++)
		{
			if (neighbor[i][j] == 0 || neighbor[i][j] == 1)
			{
				world[i][j] = State::dead;
			}
			else if (neighbor[i][j] == 2)
			{
				world[i][j] = world[i][j];
			}
			else if (neighbor[i][j] == 3)
			{
				world[i][j] = State::alive;
			}
			else if (neighbor[i][j] >= 4)
			{
				world[i][j] = State::dead;
			}
		}
	}
}

void getFile(State world[][MAXCOLS])
{
	// Reads file
	ifstream inFile;
	int row = 1;
	char fileName[FILENAMESIZE];
	char line[MAXWORLDCOLS + 1];

	cout << "What file name would you like to generate?\n";
	cin >> fileName;
	
	inFile.open(fileName);

	if(!inFile)
	{
		cerr << "\nERROR: Input file cannot be opened. \n";
		inFile.close();
		
		exit(1);
	}

	//Reads each line of file and checks position and quantity alive 
	for (row = 1; row <= MAXWORLDROWS && inFile.getline(line, MAXWORLDCOLS + 1); row++)
	{
		int length = (int)strlen(line);

		for (int i = 0; i < length; i++)
		{
			if (line[i] == '*')
			{
				world[row][i + 1] = State::alive;
			}
		}
	}

	// After file reading is finished, this code checks to see if the reading stopped
	// because of too many characters on a line in the file, or too many rows in the file
	// It is possible that you might have to change the conditions here depending on
	// exactly how you choose to read the file
	if (!inFile.eof())
	{
		if (row <= MAXWORLDROWS)
		{
			cerr << "\nERROR: Line " << row << " in input file contains more than " << MAXWORLDCOLS << " chars\n";
		}
		else
		{
			cerr << "\nERROR: There are more than " << MAXWORLDROWS << " lines in the file\n";
		}
		inFile.close();
		exit(1);
	}
	inFile.close();
}

void display(State world[][MAXCOLS])
{
	//displays each state in world to console as EMPTY or CELL
	for (int i = 1; i < MAXROWS; i++)
	{
		for (int j = 1; j < MAXCOLS; j++)
		{
			if (world[i][j] == State::dead)
			{
				cout << EMPTY;
			}
			else
			{
				cout << CELL;
			}
		}
		cout << endl;
	}
	cout << endl;
}

void initWorld(State world[][MAXCOLS])
{
	//initializes all cells in world array to dead
	for (int i = 0; i < MAXROWS; i++)
	{
		for (int j = 0; j < MAXCOLS; j++)
		{
			world[i][j] = State::dead;
		}
	}
}