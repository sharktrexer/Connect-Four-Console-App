#include <iostream>

#include "game.h"
#include "players.h"

using namespace std;

static int playerNumber = 1;

Player* getPlayer()
{
    int input;

    cout << "Select Player " << playerNumber << " (human: 1, ai: 2): ";
    cin >> input;

    // Checks for invalid input
    while (std::cin.fail() || input < 1 || input > 2)
    {
        std::cin.clear();
        std::cin.ignore(256, '\n');
        cout << "Select Player " << playerNumber << " (human: 1, ai: 2): ";
        std::cin >> input;
    }

    playerNumber++;

    // Return player type
    if (input == 1)
    {
        return new HumanPlayer;
    }
    else 
    {
        return new AiPlayer;
    }

}

// Prints board in terminal
void PrintBoard(const Game & game)
{
    cout << "\n";

    for (int y = 0; y < game.BoardHeight; y++)
    {
        cout << "  | ";
        for (int x = 0; x < game.BoardWidth; x++)
        {
            char boardChar = '?';
            switch (game(x, y))
            {
                case BoardField::Empty:
                    boardChar = ' ';
                    break;

                case BoardField::Player1:
                    boardChar = 'O';
                    break;

                case BoardField::Player2:
                    boardChar = 'X';
                    break;
            }
            cout << boardChar << ' ';
        }
        cout << "|\n";
    }

    cout << "  ---";
    for (int x = 0; x < game.BoardWidth; x++)
    {
        cout << "--";
    }
    cout << "\n";

    cout << "   ";
    for (int x = 0; x < game.BoardWidth; x++)
    {
        cout << " " << x + 1;
    }
    cout << "\n\n" << flush;

}

int main()
{
    // Game Loop
    while (true)
    {
        cout << "* * * * * * * * * * * * *\n";
        cout << "  Welcome to Connect 4!\n\n";

        Player* player1 = getPlayer();
        Player* player2 = getPlayer();

        Game game(*player1, *player2);

        while (game.isRunning())
        {
            PrintBoard(game);

            int curPlayer;

            switch (game.getState())
            {
            case GameState::TurnP1:
                curPlayer = 1;
                break;

            case GameState::TurnP2:
                curPlayer = 2;
                break;
            }

            cout << "Turn for Player " << curPlayer << ": ";

            game.nextTurn();
        }

        PrintBoard(game);

        switch (game.getState())
        {
        case GameState::P1Won:
            cout << "Player 1 won the game!";
            break;

        case GameState::P2Won:
            cout << "Player 2 won the game!";
            break;

        case GameState::Draw:
            cout << "Draw, no winner.";
            break;
        }

        cout << endl;

        delete player1;
        delete player2;

        // Determines if game loop is continued
        char input;
        cout << "\nWant to play again? (restart: y, exit: any other input)\n";
        cin >> input;
        if (input == 'y')
        {
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
            playerNumber = 1;
        }
        else
        {
            break;
        }
    }

    // End application
    return 0;
}
