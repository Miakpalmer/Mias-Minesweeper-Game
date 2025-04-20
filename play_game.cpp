// Mia Palmer
// This class is used to get what level the user wants to play, makes the board and sees if the user won or lost.
// It uses abstract data types, pointers, constructors, destructors, and exception handling

#include <iostream>
#include <vector>
#include <ctime>
#include <stdexcept>
#include <sstream>
#include <iomanip>

using namespace std;

class playGame
{
private:
	int boardSize;
	int numMines;
	bool gameEnded;
	vector < vector<int>> *board;
	vector < vector<bool>> *revealed;
	vector < vector<bool>> *flagged;

public:

	// Constructor using dynamic memory allocation with pointers
	playGame(int size, int mines) : boardSize(size), numMines(mines)
	{
		board = new vector<vector<int>>(boardSize, vector<int>(boardSize, 0));
		revealed = new vector<vector<bool>>(boardSize, vector<bool>(boardSize, false));
		flagged = new vector<vector<bool>>(boardSize, vector<bool>(boardSize, false));
	}

	// Destructor to clean up dynamically allocated memory
	~playGame()
	{
		delete board;
		delete revealed;
		delete flagged;
	}

	// Places mines randomly on the board
	void initializeBoard()
	{
		int placedMines = 0;
		while (placedMines < numMines)
		{
			int x = rand() % boardSize;
			int y = rand() % boardSize;
			if ((*board)[x][y] != -1)
			{
				(*board)[x][y] = -1;
				placedMines++;
			}
		}

		// Loop to count neighboring mines for each cell
		for (int i = 0; i < boardSize; i++)
		{
			for (int j = 0; j < boardSize; j++)
			{
				if ((*board)[i][j] != -1)
				{
					int count = 0;
					for (int dx = -1; dx <= 1; dx++)
					{
						for (int dy = -1; dy <= 1; dy++)
						{
							if (dx == 0 && dy == 0) continue;
							int nx = i + dx;
							int ny = j + dy;
							if (nx >= 0 && nx < boardSize && ny >= 0 && ny < boardSize && (*board)[nx][ny] == -1)
							{
								count++;
							}
						}
					}
					(*board)[i][j] = count;
				}
			}
		}
	}

	// Prints the game board
	void printBoard(bool revealALL = false)
	{
		cout << "  ";
		for (int col = 0; col < boardSize; col++)
		{
			cout << setw(3) << col + 1;
		}
		cout << endl;

		for (int i = 0; i < boardSize; i++)
		{
			cout << setw(3) << i + 1;

			for (int j = 0; j < boardSize; j++)
			{
				if ((*revealed)[i][j] || revealALL)
				{
					if ((*board)[i][j] == -1)
					{
						cout << " * ";
					}
					else
					{
						cout << ":D ";
					}
				}
				else if ((*flagged)[i][j])
				{
					cout << "flagged ";
				}
				else
				{
					cout << "[] ";
				}
			}
			cout << endl;
		}
	}

	// Checks if the game is won
	bool isGameWon()
	{
		for (int i = 0; i < boardSize; i++)
		{
			for (int j = 0; j < boardSize; j++)
			{
				if (!(*revealed)[i][j] && (*board)[i][j] != -1)
				{
					return false;
				}
			}
		}
		return true;
	}

	// Reveals the chosen cell and handles game over or win condition
	void revealCell(const int row, int column)
	{
		// Exception handling for invalid row or column input
		if (row < 0 || row >= boardSize || column < 0 || column >= boardSize)
		{
			throw out_of_range("One or both of the numbers you have entered is not a valid entry. Please try again: ");
		}
			
		// Exception handling for revealing an already revealed cell
		if ((*revealed)[row][column])
		{
			throw runtime_error("Cell already revealed. Please try again: ");
		}

		// Reveal the selected cell
		(*revealed)[row][column] = true;

		// If the user hits a mine
		if ((*board)[row][column] == -1)
		{
			printBoard(true);
			cout << "Uh oh! Game over!" << endl;
			cout << "You hit the mine at " << row + 1 << ", " << column + 1 << endl;
			gameEnded = true;
		}

		// If the user wins
		if (isGameWon())
		{
			printBoard(true);
			cout << "Congratulations! You won!" << endl;
			gameEnded = true;
		}
	}

	// Checks if the game has ended
	bool hasGameEnded() const
	{
		return gameEnded;
	}
};
