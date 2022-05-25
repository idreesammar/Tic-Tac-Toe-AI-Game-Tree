#pragma once
#include "tttgamedata.h"

// Represents the current TicTacToe Game
class TicTacToeGame
{
public:

	// Function: Constructor
	// Purpose: Creates a GameState with empty spots
	// Input: None
	// Returns: None
	TicTacToeGame();

	// Function: getBoard
	// Purpose: Return the current GameState
	// Input: None
	// Returns: The current game state
	GameState getBoard() const;

	// Function: setSquareState
	// Purpose: Claims the entered state for the inputted player
	// Input:	1. Unsigned short for row
	//			2. Unsigned short for column
	//			3. The player's symbol (X or O)
	// Returns: boolean -- true if the spot was set successfully
	// Note: Uses the row/column to identify a board position
	bool setSquareState(unsigned short row, unsigned short col, GameState::SquareState state);

	// Function: setSquareState
	// Purpose: Claims the entered state for the inputted player
	// Input:	1. Unsigned short spot number
	//			2. The player's symbol (X or O)
	// Returns: boolean -- true if the spot was set successfully
	// Note: Uses the number ordering to indicate a spot
	//		1 is upper left corner, 9 is lower, right corner
	bool setSquareState(unsigned short square, GameState::SquareState state);

	// Function: getWinner
	// Purpose: Determines if there's a game winner
	// Input: None
	// Returns: Character to determine winner
	//			'X' to indicate X player wins
	//			'O' to indicate O player wins
	//			'N' to indicate tie game
	//			' ' to indicate no winner yet
	char getWinner();

	// Function: isEmpty
	// Purpose: Checks if empty spots remain on board (indicating game is still going or not)
	// Input:	none
	// Returns: boolean -- true if no more remaining spots, false otherwise
	// Note: I ADDED THIS FUNCTION!!!!
	bool isEmpty();

	// Function: horizontalWin, verticalWin, diagonalWin (win checking functions)
	// Purpose: Checks if player won in one of 3 ways (has 3 consecutive pieces in one of three ways)
	// Input:	3. The player's symbol (X or O)
	// Returns: boolean -- true if player has matching pieces arrangment, false otherwise
	// Note: I ADDED THESE FUNCTIONS!!!!
	bool horizontalWin(GameState::SquareState state);
	bool verticalWin(GameState::SquareState state);
	bool diagonalWin(GameState::SquareState state);

private:
	// Represents the current game state
	// Update this variable as the game progresses
	GameState currentState;
};

