#include "tttgame.h"
#include "tttgameai.h"

TicTacToeGame::TicTacToeGame()
{
	// initialize the board by setting all spaces to empty
	for (int i = 0; i < 3; i++) // to cover all row spaces
	{
		for (int j = 0; j < 3; j++)  // to cover all column spaces
		{
			currentState.mBoard[i][j] = GameState::SquareState::Empty; // set each space to Empty enum value
		}
	}
}


GameState TicTacToeGame::getBoard() const
{
	// return the current game state
	return currentState;	// output the appropriate member variable
}


bool TicTacToeGame::setSquareState(unsigned short row, unsigned short col, GameState::SquareState state)
{
	bool success = false; // retval set to false

	// given the column number and row number, check if spot is available
	if (currentState.mBoard[row][col] == GameState::SquareState::Empty)
	{
		currentState.mBoard[row][col] = state; // set the state if it is available
		success = true; // update the boolean value to represent sucesss!
	}
	// else the boolean value will remain false because the spot was not available

	return success;	// return the boolean indicating function outcome
}

bool TicTacToeGame::setSquareState(unsigned short square, GameState::SquareState state)
{
	bool success; // retval which will indicate outcome of this function

	// use a switch statement to set square value to appropriate row,col values for function call (to other setSquareState)
	switch (square)
	{
	case 1:  // [0][0]
		success = setSquareState(0, 0, state); 
		break;

	case 2:  // [0][1]
		success = setSquareState(0, 1, state);
		break;
	
	case 3:  // [0][2]
		success = setSquareState(0, 2, state);
		break;

	case 4:  // [1][0]
		success = setSquareState(1, 0, state);
		break;

	case 5:  // [1][1]
		success = setSquareState(1, 1, state);
		break;

	case 6:  // [1][2]
		success = setSquareState(1, 2, state);
		break;

	case 7:  // [2][0]
		success = setSquareState(2, 0, state);
		break;

	case 8:  // [2][1]
		success = setSquareState(2, 1, state);
		break;

	case 9:  // [2][2]
		success = setSquareState(2, 2, state);
		break;

	default:
		break;
	}

	return success;	// return the outcome
}

char TicTacToeGame::getWinner()
{
	char retVal; // the return value character
	
	// check for horizontal wins
	if (horizontalWin(GameState::SquareState::X))
	{
		retVal = 'X';
	}
	else if (horizontalWin(GameState::SquareState::O))
	{
		retVal = 'O';
	}
	// check for vertical wins, otherwise
	else if (verticalWin(GameState::SquareState::X))
	{
		retVal = 'X';
	}
	else if (verticalWin(GameState::SquareState::O))
	{
		retVal = 'O';
	}
	// check for diagonal wins, otherwise
	else if (diagonalWin(GameState::SquareState::X))
	{
		retVal = 'X';
	}
	else if (diagonalWin(GameState::SquareState::O))
	{
		retVal = 'O';
	}
	// check if board still has empty spots, otherwise
	else if (isEmpty())
	{
		retVal = ' '; // return a space since game isn't over
	}
	// if none apply, means all spots filled with no winner --> it is a TIE GAME 
	else if (!isEmpty())
	{
		retVal = 'N'; // tie game, nobody won
	}

	return retVal;	// return the outcome character
}

// ADDED THIS FUNCTION
bool TicTacToeGame::isEmpty()
{
	bool isEmpty = false; // retVal representing if empty spots remain, initialized to false

	// check each spot on a board to see if an empty spot remains
	for (int i = 0; i < 3; i++) // to cover all row spaces
	{
		for (int j = 0; j < 3; j++)  // to cover all column spaces
		{
			if (currentState.mBoard[i][j] == GameState::SquareState::Empty) 
			{
				isEmpty = true; // if even a single spot on board is currently empty, isEmpty is true
			}
		}
	}

	return isEmpty; // return the boolean outcome
}

// ADDED THIS FUNCTION
bool TicTacToeGame::horizontalWin(GameState::SquareState state)
{
	bool isWinner = false; // retVal representing if player (rep by state) has a horizontal win (initialized to false)

	// check for horizontal win
	if ( ((currentState.mBoard[0][0] == currentState.mBoard[0][1]) && (currentState.mBoard[0][1] == currentState.mBoard[0][2]) 
		&& (currentState.mBoard[0][0] == state))
		|| ((currentState.mBoard[1][0] == currentState.mBoard[1][1]) && (currentState.mBoard[1][1] == currentState.mBoard[1][2])
			&& (currentState.mBoard[1][0] == state))
		|| ((currentState.mBoard[2][0] == currentState.mBoard[2][1]) && (currentState.mBoard[2][1] == currentState.mBoard[2][2])
			&& (currentState.mBoard[2][0] == state)) )
	{
		isWinner = true; // has met conditions to have a horizontal win
	}

	return isWinner; // return the boolean outcome
}

// ADDED THIS FUNCTION
bool TicTacToeGame::verticalWin(GameState::SquareState state)
{
	bool isWinner = false; // retVal representing if player (rep by state) has a vertical win (initialized to false)

	// check for vertical win
	if (((currentState.mBoard[0][0] == currentState.mBoard[1][0]) && (currentState.mBoard[1][0] == currentState.mBoard[2][0])
		&& (currentState.mBoard[0][0] == state))
		|| ((currentState.mBoard[0][1] == currentState.mBoard[1][1]) && (currentState.mBoard[1][1] == currentState.mBoard[2][1])
			&& (currentState.mBoard[0][1] == state))
		|| ((currentState.mBoard[0][2] == currentState.mBoard[1][2]) && (currentState.mBoard[1][2] == currentState.mBoard[2][2])
			&& (currentState.mBoard[0][2] == state)))
	{
		isWinner = true; // has met conditions to have a vertical win
	}

	return isWinner; // return the boolean outcome
}

// ADDED THIS FUNCTION
bool TicTacToeGame::diagonalWin(GameState::SquareState state)
{
	bool isWinner = false; // retVal representing if player (rep by state) has a diagonal win (initialized to false)

	// check for diagonal win
	if ( ((currentState.mBoard[0][0] == currentState.mBoard[1][1]) && (currentState.mBoard[1][1] == currentState.mBoard[2][2])
		&& (currentState.mBoard[0][0] == state))
		|| ((currentState.mBoard[2][0] == currentState.mBoard[1][1]) && (currentState.mBoard[1][1] == currentState.mBoard[0][2])
			&& (currentState.mBoard[2][0] == state)) )
	{
		isWinner = true; // has met conditions to have a diagonal win
	}

	return isWinner; // return the boolean outcome
}
