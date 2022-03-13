#pragma once

// Prevents circular dependency
class Game;

// Abstract class
class Player
{
public:

	virtual int getNextTurn(const Game&);
};

// Sub-Classes
class HumanPlayer : public Player
{
public:

	int getNextTurn(const Game&);
};

class AiPlayer : public Player
{
public:

	int getNextTurn(const Game&);
};

