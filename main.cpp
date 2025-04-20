// Mia Palmer's CSC1061 Capstone Project
// This is a Minesweeper game that gives the user three levels of difficulty to choose from.
// It uses classes to keep certain functions in a certain class
// This class is the main class
// It uses constructors, destructors and exception handling

#include <iostream>
#include <vector>
#include <ctime>
#include <stdexcept>
#include <string>
#include "play_game.cpp"

using namespace std;

int main()
{
	// For randomly placing the mines
	srand(time(0));

	// Declarations
	int level;
	int boardSize, numMines;
	bool badEntry = true;

	// Introduction
	cout << "Hi! This is Mia's Minesweeper Game!" << endl;
	cout << "Try to stay away from the mines and instead find these cute ladybug friends: :D" << endl << endl;

	// Exception handling while loop that makes sure that the user chooses an available level 
	while (badEntry)
	{
		// Asking for users input of level they choose
		cout << "Level 1: 9 * 9 with 10 mines. Level 2: 16 * 16 with 40 mines. Level 3: 24 * 24 with 90 mines." << endl;
		cout << "Please enter 1 for level 1, 2 for level 2 or 3 for level 3." << endl;
		cout << "Please enter level of difficulty that you would like to play: ";

		// Exception handling that checks the users input to make sure they did not enter a letter or word
		if (!(cin >> level))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl << "That is not valid input. Please enter a number. " << endl << endl;
			continue;
		}

		// Checking to see which level the user chose and deciding how many mines and cells there will be
		if (level == 1)
		{
			boardSize = 9;
			numMines = 10;
			badEntry = false;
		}
		else if (level == 2)
		{
			boardSize = 16;
			numMines = 40;
			badEntry = false;
		}
		else if (level == 3)
		{
			boardSize = 24;
			numMines = 90;
			badEntry = false;
		}
		else if (badEntry)
		{
			// Asks the user to try again if the user did not pick any of the levels that are given
			cout << endl << "That level is invalid. Please choose from the three levels provided: " << endl << endl;
		}
	}

	// Brings playGame class over to get the board and see if the user wins or loses
	playGame* game = new playGame(boardSize, numMines);
	game->initializeBoard();

	// while loop the continues until the game has ended
	while (!game->hasGameEnded()) {

		try {

			// Prints board according to users level choice
			game->printBoard();

			// Declaring the variables for the users row and column
			int row = 0;
			int column = 0;

			// Gets the user input of what cell they want to try
			cout << "Please enter the row you would like to try." << endl;

			// Making sure the user does not enter a letter or word
			if (!(cin >> row))
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << endl << "That is not valid input. Please enter a number: " << endl << endl;
				continue;
			}

			cout << "Please enter the column you would like to try." << endl;

			// Making sure the user does not enter a letter or word
			if (!(cin >> column))
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << endl << "That is not valid input. Please enter a number: " << endl << endl;
				continue;
			}

			// Reveals the users chosen cell
			game->revealCell(row - 1, column - 1);

		// Exception handling for invalid input
		}
		catch (const out_of_range& e)
		{
			cerr << endl << e.what() << endl << endl;
		}
		catch (const runtime_error& e)
		{
			cerr << endl << e.what() << endl << endl;
		}
	}

	// Ending the game after the user has looked at the board when they win or lose
	cout << "Please press enter to leave the game.";
	cin.ignore();
	cin.get();

	// Clearing the dynamically allocated memory
	delete game;
}
