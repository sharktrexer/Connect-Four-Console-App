#include "game.h"
#include "players.h"
#include <iostream>

// Stores player and intializes board and vars
Game::Game(Player &p1, Player &p2) : pl1(p1), pl2(p2)
{
	for (int h = 0; h < BoardHeight; h++)
	{
		for (int w = 0; w < BoardWidth; w++)
		{
			board[h][w] = BoardField::Empty;
		}
	}

	running = true;

	state = GameState::TurnP1;
}

// Returns current state of game
GameState Game::getState() const
{
	return state;
}

// If the game is running
bool Game::isRunning() const
{
	return running;
}

// Accordingly gets the move of each player and changes states
void Game::nextTurn()
{
	// Gets player move index and enum val
	int move = -1; // Set to -1 for 0-index conversion
	BoardField plToken; // Store token according to player turn
	switch (state)
	{
		case GameState::TurnP1:
			move += pl1.getNextTurn(*this);
			plToken = BoardField::Player1;
			break;

		case GameState::TurnP2:
			move += pl2.getNextTurn(*this);
			plToken = BoardField::Player2;
			break;
	}

	// If move is not valid, do nothing (only applies to player move)
	// This forces main.cpp to re-prompt player input
	if (move >= BoardWidth || move < 0 || board[0][move] != BoardField::Empty)
	{
		std::cout << "\nInvalid Move\n";
		return;
	}

	// Add move to board
	int y;
	for (int i = BoardHeight - 1; i >= 0; i--)
	{
		// Set board piece to player token once an empty space in col is found
		if (board[i][move] == BoardField::Empty) 
		{
			// Store move index for win condition checking
			y = i;
			board[i][move] = plToken;
			break;
		}
	}

	// Check win conditions using move coordinates
	if (CheckForWin(move, y, plToken))
	{
		running = false;
		state = state == GameState::TurnP1 ? GameState::P1Won : GameState::P2Won;
		return;
	}
	// Check draw condition
	if (CheckForDraw())
	{
		running = false;
		state = GameState::Draw;
		return;
	}

	// Change player turn (if game hasn't completed)
	state = state == GameState::TurnP1 ? GameState::TurnP2 : GameState::TurnP1;
}

// Returns if any of the win combos are true
bool Game::CheckForWin(int x, int y, BoardField pl)
{
	return DiagonalLeftRight(x, y, pl) || DiagonalRightLeft(x, y, pl)
		|| Vertical(x, y, pl) || Horizontal(x, y, pl);
}

// Checks combos diagonally from bottom left to top right in both directions
bool Game::DiagonalLeftRight(int x, int y, BoardField pl)
{
	int score = 1;
	int count = 1;

	while ((y - count >= 0) && (x + count < BoardWidth))
	{
		if (board[y - count][x + count] == pl)  // Check bottom left to top right
		{
			score++;
			count++;
		}
		else break;  // no combo is detected
	}

	count = 1;
	while ((y + count < BoardHeight) && (x - count >= 0))
	{
		if (board[y + count][x - count] == pl)  // Check top right to bottom left
		{
			score++;
			count++;
		}
		else break;  // no combo is detected
	}

	return score >= winComboCondition;
}

// Checks combos diagonally from bottom right to top left both ways
bool Game::DiagonalRightLeft(int x, int y, BoardField pl)
{
	int score = 1;
	int count = 1;

	while ((y + count >= 0) && (x + count < BoardWidth))
	{
		if (board[y + count][x + count] == pl)  // Check top left to bottom right
		{
			score++;
			count++;
		}
		else break;  // no combo is detected
	}

	count = 1;
	while ((y - count < BoardHeight) && (x - count >= 0))
	{
		if (board[y - count][x - count] == pl)  // Check bottom right to top left
		{
			score++;
			count++;
		}
		else break;  // no combo is detected
	}

	return score >= winComboCondition;
}

// Checks from top down the vertical combo
bool Game::Vertical(int x, int y, BoardField pl)
{
	int score = 1;
	int count = 1;

	while (y + count >= 0 && y + count < BoardHeight)
	{
		if (board[y + count][x] == pl)  // Check Down
		{
			score++;
			count++;
		}
		else break;  //no combo is detected
	}

	return score >= winComboCondition;
}

// Checks right and left horizontal combos
bool Game::Horizontal(int x, int y, BoardField pl)
{
	int score = 1;
	int count = 1;

	while ((x + count >= 0) && (x + count < BoardWidth))
	{
		if (board[y][x + count] == pl)  // Check Left
		{
			score++;
			count++;
		}
		else break;  // no combo is detected
	}

	count = 1;
	while ((x - count < BoardWidth) && (x - count >= 0))
	{
		if (board[y][x - count] == pl)  // Check Right
		{
			score++;
			count++;
		}
		else break;  //no combo is detected
	}

	return score >= winComboCondition;
}

// Checks if each col is filled
bool Game::CheckForDraw()
{
	int count = 1;
	// Only need to check top of column since that would mean it is filled up
	for (int i = 0; i < BoardWidth; i++)
	{
		if (board[0][i] != BoardField::Empty)
		{
			count++;
		}
	}
	return count == BoardWidth;
}

// Return state of the board from inputted coordinate
BoardField Game::operator()(int x, int y) const
{
	return board[y][x];
}


