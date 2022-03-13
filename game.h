#pragma once

// Prevents circular dependency
class Player;

// Possible states of the game
enum class GameState
{
	TurnP1,
	TurnP2,
	P1Won,
	P2Won,
	Draw,
};

// Possible board states
enum class BoardField
{
	Empty,
	Player1,
	Player2,
};

class Game
{
public:
	// Board dimensions
	static int const BoardWidth = 7;
	static int const BoardHeight = 6;

	// Constructor
	Game(Player &p1, Player &p2);

	// Current game state
	GameState getState() const;

	// If the game is still going
	bool isRunning() const;

	// Move mechanics
	void nextTurn();

	// Getting index of board
	BoardField operator() (int x, int y) const;

private:
	// Number of tokens required in a winning combo
	static int const winComboCondition = 4;

	// Player objs
	Player& pl1;
	Player& pl2;

	// Game state
	GameState state;

	// Board
	BoardField board[BoardHeight][BoardWidth];

	// Game running
	bool running;

	// End of game conditions
	bool CheckForDraw();
	bool CheckForWin(int x, int y, BoardField pl);
	bool DiagonalLeftRight(int x, int y, BoardField pl);
	bool DiagonalRightLeft(int x, int y, BoardField pl);
	bool Vertical(int x, int y, BoardField pl);
	bool Horizontal(int x, int y, BoardField pl);
};

