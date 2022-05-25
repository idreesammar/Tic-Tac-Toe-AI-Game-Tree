// You can use this for the std::min / std::max functions
#include <algorithm>
#include "tttgameai.h"

bool IsGameOver(const GameState& state)
{
	// given the current state, check if somebody won or any empty spaces remain (if yes, game is NOT over)
	bool isDone = true; // retVal representing if game is done, intialized to true (for case where board filled but no winner)

	// first check for any winners on current board, starting with horizontal wins
	if (horizontalWin(state, GameState::SquareState::X))
	{
		isDone = true;
	}
	else if (horizontalWin(state, GameState::SquareState::O))
	{
		isDone = true;
	}
	// check for vertical wins, otherwise
	else if (verticalWin(state, GameState::SquareState::X))
	{
		isDone = true;
	}
	else if (verticalWin(state, GameState::SquareState::O))
	{
		isDone = true;
	}
	// check for diagonal wins, otherwise
	else if (diagonalWin(state, GameState::SquareState::X))
	{
		isDone = true;
	}
	else if (diagonalWin(state, GameState::SquareState::O))
	{
		isDone = true;
	}
	else  // check if empty spot remains
	{
		// check each spot on a board to see if an empty spot remains
		for (int i = 0; i < 3; i++) // to cover all row spaces
		{
			for (int j = 0; j < 3; j++)  // to cover all column spaces
			{
				if (state.mBoard[i][j] == GameState::SquareState::Empty)
				{
					isDone = false; // if even a single spot on board is currently empty, game is NOT over (so isDone is false)
				}
			}
		}
	}

	return isDone; // return the boolean outcome
}

void GenStates(GTNode* root, bool xPlayer)
{
	// base case (for winning, leaf nodes)
	if (IsGameOver(root->mState))
	{
		return;
	}
	
	// first iterate through all positions on board
	for (int i = 0; i < 3; i++) // to cover all row spaces
	{
		for (int j = 0; j < 3; j++)  // to cover all column spaces
		{
			// for the positions that are empty....
			if (root->mState.mBoard[i][j] == GameState::SquareState::Empty) 
			{
				// 1. Generate a new child node
				GTNode* child = new GTNode;
				
				// 2. Set child’s board to the root’s board
				for (int m = 0; m < 3; m++)  // for the rows
				{
					for (int n = 0; n < 3; n++) // for the columns
					{
						child->mState.mBoard[m][n] = root->mState.mBoard[m][n]; // set each board position
					}
				}
				
				// 3. Set the empty position to the X (or the player’s symbol)
				if (xPlayer) // currently X's turn
				{
					child->mState.mBoard[i][j] = GameState::X;
				}
				else // currently O's turn
				{
					child->mState.mBoard[i][j] = GameState::O;
				}

				// 4. Add the node as a child to root
				root->mChildren.push_back(child);

				// 5. Generate the child nodes for this child (or call the function recursively)
				GenStates(child, !xPlayer); // NOTE: flip the xPlayer bool value to indicate next player's turn in the recursive call
			}
		}
	}
}

float GetScore(const GameState& state)
{
	float retVal; // holds the outcome score

	// check for horizontal wins
	if (horizontalWin(state, GameState::SquareState::X))
	{
		retVal = -1.0;
	}
	else if (horizontalWin(state, GameState::SquareState::O))
	{
		retVal = 1.0;
	}
	// check for vertical wins, otherwise
	else if (verticalWin(state, GameState::SquareState::X))
	{
		retVal = -1.0;
	}
	else if (verticalWin(state, GameState::SquareState::O))
	{
		retVal = 1.0;
	}
	// check for diagonal wins, otherwise
	else if (diagonalWin(state, GameState::SquareState::X))
	{
		retVal = -1.0;
	}
	else if (diagonalWin(state, GameState::SquareState::O))
	{
		retVal = 1.0;
	}

	// if none apply, means it is a TIE GAME
	else
	{
		retVal = 0.0; // tie game, nobody won
	}

	return retVal;	// return the outcome
}

// ADDED THIS FUNCTION
bool horizontalWin(const GameState& currentState, GameState::SquareState state)
{
	bool isWinner = false; // retVal representing if player (rep by state) has a horizontal win (initialized to false)

	// check for horizontal win
	if (((currentState.mBoard[0][0] == currentState.mBoard[0][1]) && (currentState.mBoard[0][1] == currentState.mBoard[0][2])
		&& (currentState.mBoard[0][0] == state))
		|| ((currentState.mBoard[1][0] == currentState.mBoard[1][1]) && (currentState.mBoard[1][1] == currentState.mBoard[1][2])
			&& (currentState.mBoard[1][0] == state))
		|| ((currentState.mBoard[2][0] == currentState.mBoard[2][1]) && (currentState.mBoard[2][1] == currentState.mBoard[2][2])
			&& (currentState.mBoard[2][0] == state)))
	{
		isWinner = true; // has met conditions to have a horizontal win
	}

	return isWinner; // return the boolean outcome
}

// ADDED THIS FUNCTION
bool verticalWin(const GameState& currentState, GameState::SquareState state)
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
bool diagonalWin(const GameState& currentState, GameState::SquareState state)
{
	bool isWinner = false; // retVal representing if player (rep by state) has a diagonal win (initialized to false)

	// check for diagonal win
	if (((currentState.mBoard[0][0] == currentState.mBoard[1][1]) && (currentState.mBoard[1][1] == currentState.mBoard[2][2])
		&& (currentState.mBoard[0][0] == state))
		|| ((currentState.mBoard[2][0] == currentState.mBoard[1][1]) && (currentState.mBoard[1][1] == currentState.mBoard[0][2])
			&& (currentState.mBoard[2][0] == state)))
	{
		isWinner = true; // has met conditions to have a diagonal win
	}

	return isWinner; // return the boolean outcome
}


float MinPlayer(const GTNode* node)
{
	// 1. If the node is a leaf node, return its score 
	if (node->mChildren.size() == 0)  // no children means leaf node
	{
		return GetScore(node->mState); // get the score of the current board
	}

	// 2. Otherwise return the smallest maximum score of all the child nodes (that means calling the MaxPlayer function on all the children)
	float smallestMax = 2.0; // initialized value
	for (GTNode* child : node->mChildren)
	{
		smallestMax = std::min(smallestMax, MaxPlayer(child));
	}
	return smallestMax;	// return the smallest max score of child nodes
}

float MaxPlayer(const GTNode* node)
{
	// 1. If the node is a leaf node, return its score 
	if (node->mChildren.size() == 0)  // no children means leaf node
	{
		return GetScore(node->mState); // get the score of the current board
	}

	// 2. Otherwise return the largest minimum score of all the child nodes(that means calling the MinPlayer function on all the children)
	float largestMin = -2.0; // default value
	for (GTNode* child : node->mChildren)
	{
		largestMin = std::max(largestMin, MinPlayer(child));
	}

	return largestMin;	// return the largest min score of child nodes
}

const GTNode* MinimaxDecide(const GTNode* root)
{
	GTNode* retVal = new GTNode; // this will be the node to return (has the LARGEST MinPlayer score)

	// Start with a given (or “root”) node – this will be the “current state” of the game
	float largestMin = -2.0; // default value

	// Go through each child node of the root
	for (GTNode* child : root->mChildren)
	{
		// Find the node with the largest MinPlayer score
		if (MinPlayer(child) > largestMin)
		{
			retVal = child;
			largestMin = MinPlayer(child); // update the largestMin value
		}
	}

	return retVal;	// Make the move to yield the state found above (return the node with largest MinPlayer score)
}


unsigned pickMove(const GameState& board)
{
	// first create a new GT node 
	GTNode* root = new GTNode;

	// set its member varible to the paramter
	root->mState = board;

	// determine who's turn it is based on given board (check to see if there are more X's or not)
	int xCounter = 0; // number of X's on current board
	int oCounter = 0; // number of O's on current board
	bool xPlayer; // tells if it is X's turn
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board.mBoard[i][j] == GameState::X)
			{
				xCounter++; // increment # of X
			}
			if (board.mBoard[i][j] == GameState::O)
			{
				oCounter++; // increment # of O
			}
		}
	}

	if (xCounter > oCounter)  // since X starts, if there are more X's, it is now O's turn
	{
		xPlayer = false;
	}
	else  // xCounter == oCounter, it is X's turn
	{
		xPlayer = true;
	}

	// generate the states/subtrees for the node
	GenStates(root,xPlayer);

	// call mimimax to get ideal move for the AI;
	int xPos; // holds the row position of the ideal move
	int yPos; // holds the column position of the ideal move
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			// find the spot where the new squarestate (either X or O) is added
			if (root->mState.mBoard[i][j] != MinimaxDecide(root)->mState.mBoard[i][j]) 
			{
				// get new position's coordinates
				xPos = i;
				yPos = j;
			}
		}
	}
	
	// upon getting the ideal position, convert to find position square 
	int posSquare;
	if (xPos == 0 && yPos == 0)  // [0][0]
	{
		posSquare = 1;
	}
	else if (xPos == 0 && yPos == 1) // [0][1]
	{
		posSquare = 2;
	}
	else if (xPos == 0 && yPos == 2) // [0][2]
	{
		posSquare = 3;
	}
	else if (xPos == 1 && yPos == 0) // [1][0]
	{
		posSquare = 4;
	}
	else if (xPos == 1 && yPos == 1) // [1][1]
	{
		posSquare = 5;
	}
	else if (xPos == 1 && yPos == 2) // [1][2]
	{
		posSquare = 6;
	}
	else if (xPos == 2 && yPos == 0) // [2][0]
	{
		posSquare = 7;
	}
	else if (xPos == 2 && yPos == 1) // [2][1]
	{
		posSquare = 8;
	}
	else if (xPos == 2 && yPos == 2) // [2][2]
	{
		posSquare = 9;
	}

	return posSquare;	// return the position square
}


