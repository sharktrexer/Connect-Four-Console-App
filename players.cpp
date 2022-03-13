#include "players.h"
#include "game.h"
#include <stdlib.h>
#include <iostream>

// Return random number between 1 and BoardWidth
int Player::getNextTurn(const Game& game)
{
	return rand() % game.BoardWidth + 1;
}

// Randomly choose a valid column to play their turn
int AiPlayer::getNextTurn(const Game& game)
{
	// Array and int to keep track of valid column choices
	int choices = 0;
	bool moveChoices[game.BoardWidth];
	std::fill_n(moveChoices, game.BoardWidth, false);

	// Loop through each column of first row, set index of valid columns that have empty spaces = true
	for (int i = 0; i < game.BoardWidth; i++)
	{
		if (game(i, 0) == BoardField::Empty)
		{
			moveChoices[i] = true;
			choices++;
		}
	}

	// Scope of possible col choices
	// EX: If move = 2 then iterate to 2nd valid move choice in bool array for move variance
	int move = rand() % choices + 1;
	int moveInc = -1;
	// Loop through choices array and count up valid choices till the move index chosen by rand
	for (int i = 0; i < game.BoardWidth; i++)
	{
		if (moveChoices[i])
		{
			moveInc++;
			if (moveInc == move)
			{
				// Set move to col index
				move = i;
				break;
			}
		}
	}

	// Print and return move
	std::cout << move << "\n";
	return move;
}

// Gets playuer input from terminal and returns input (unless input is not an integer)
int HumanPlayer::getNextTurn(const Game& game)
{
	int move;
	std::cin >> move;

	// Prevents input other than integers for an error-less game
	// Still excepts invalid integer inputs for the game class to handle
	while (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> move;
	}
	return move;
}
