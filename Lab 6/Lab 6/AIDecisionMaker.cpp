#include "AIDecisionMaker.h"

void AIDescisionMaker::init()
{

}

void AIDescisionMaker::update()
{

}

int AIDescisionMaker::pickCellToPlace()
{
	int pieceToCheck = pickPieceToPlace() + 1;
	std::vector<int> validMoves = checkThisCollisionAllowed(pieceToCheck);
	if (validMoves.empty())
	{
		return -1;
	}

	int bestMove = validMoves[0];
	int bestScore = -999999;

	for (int move : validMoves) 
	{
		std::vector<int> nextBoard = gridCellTypes;
		//nextBoard = returnUpdatedGrid(nextBoard,move,bestPiece+1);
		int score = minimax(nextBoard, 0, false,pieceToCheck);
		if (score > bestScore) 
		{
			bestScore = score;
			bestMove = move;
		}
	}
	std::cout << "Total minimax calls: " << movesTaken << "\n";
	return bestMove;
}

//the more shapes that make up the piece the higher its value
	//collision check just needs to compare the matrix of the shape to the board to find if there is a slot for that particular piece
	// 0,1,0      if the board has a series of cells that lines up with this we use that as one of its possible places
	// 1,1,1      this also avoids sfmls collision check which is probably more expensive
	// 0,1,0	  we will want to place the largest piece we can typically, if there is no space work down in size

	// also can check if a position is optimal as it will be near a friendly tile - type 1 is invalid(wall), 2 is player, 3 is AI

//a good move will let us place a high value piece and make the player place a low value piece

int AIDescisionMaker::pickPieceToPlace() 
{
	bestPiece = currentPiece;//get biggest piece for now
	AIPiecesUsed[currentPiece]++;
	if (currentPiece <= 3)
	{
		if (AIPiecesUsed[currentPiece] == 2)
		{
			currentPiece--;
		}
	}
	else if (AIPiecesUsed[currentPiece] == 1)
	{
		currentPiece--;
	}

	return bestPiece;
}

int AIDescisionMaker::pickRotation()
{
	return 0;
}

void AIDescisionMaker::giveGridOverview(std::vector<int> t_gridOverview)
{
	gridCellTypes = t_gridOverview;
}

int AIDescisionMaker::minimax(std::vector<int> board, int depth, bool maximizingPlayer, int piece) {
	if (depth == maxDepth)
	{
		//std::cout << "Max Reached\n";
		return evaluateBoard(board);//stop here and return amount of pieces placed in simulation
	}
	movesTaken++;
	if (maximizingPlayer) {
		int bestScore = -999999;
		for (int cellToCheck = 0; cellToCheck < board.size(); cellToCheck++)
		{
			if (board[cellToCheck] == 0)
			{
				std::vector<int> nextBoard = returnUpdatedGrid(board, cellToCheck, piece, true);
				bestScore = std::max(bestScore, minimax(nextBoard, depth + 1, false, piece));
			}
		}
		return bestScore;
	}
	else
	{
		int bestScore = 999999;
		for(int cellToCheck = 0;cellToCheck < board.size();cellToCheck++)
		{
			if (board[cellToCheck] == 0)
			{
				std::vector<int> nextBoard = returnUpdatedGrid(board, cellToCheck, piece, false);
				bestScore = std::min(bestScore, minimax(nextBoard, depth + 1, true, piece));
			}
			
		}
		return bestScore;
	}
}

int AIDescisionMaker::evaluateBoard(std::vector<int> board)
{	
	int aiPieceCount = 0;
	for (int index = 0;index < board.size();index++) 
	{
		if (board[index] == 3)
		{
			aiPieceCount++;
		}
	}
	return aiPieceCount;
}

std::vector<int> AIDescisionMaker::returnUpdatedGrid(std::vector<int> board, int cellToPlaceOn, int t_pieceType,bool t_player)
{
	std::vector<int> pieceShapesPositions;

	int playerCell = 2;
	if (t_player == false)
	{
		playerCell = 3;
	}

	if (t_pieceType == 0)
	{
		pieceShapesPositions =
		{ 0,1,0
		 ,1,1,1
		 ,0,1,0 };
	}
	else if (t_pieceType == 1)
	{
		pieceShapesPositions =
		{ 0,0,0
		,0,1,0
		,0,0,0 };
	}
	else if (t_pieceType == 2)
	{
		pieceShapesPositions =
		{ 0,1,0
		,0,1,0
		,0,0,0 };
	}
	else if (t_pieceType == 3)
	{
		pieceShapesPositions =
		{ 0,1,0
		,1,1,0
		,0,0,0 };
	}
	else if (t_pieceType == 4)
	{
		pieceShapesPositions =
		{ 0,1,0
		,0,1,0
		,0,1,0 };
	}
	else if (t_pieceType == 5)
	{
		pieceShapesPositions =
		{ 1,1,0
		,1,1,0
		,0,0,0 };
	}
	else if (t_pieceType == 6)
	{
		pieceShapesPositions =
		{ 0,1,0
		,1,1,0
		,0,1,0 };
	}
	else if (t_pieceType == 7)
	{
		pieceShapesPositions =
		{ 0,1,1
		,1,1,0
		,0,0,0 };
	}
	else if (t_pieceType == 8)
	{
		pieceShapesPositions =
		{ 1,1,0
		,0,1,1
		,0,1,0 };
	}
	else if (t_pieceType == 9)
	{
		pieceShapesPositions =
		{ 0,1,0
		,1,1,1
		,0,1,0 };
	}
	else if (t_pieceType == 10)
	{
		pieceShapesPositions =
		{ 0,0,0
		,1,1,1
		,1,0,1 };
	}
	else if (t_pieceType == 11)
	{
		pieceShapesPositions =
		{ 0,1,1
		,1,1,0
		,1,0,0 };
	}

	//this is yet again an awful way to do this :D
	if (board[cellToPlaceOn - GRID_SIZE - 1] == 0)
	{
		board[cellToPlaceOn - GRID_SIZE - 1] = pieceShapesPositions[0] * 3;
	}
	if (board[cellToPlaceOn - GRID_SIZE] == 0)
	{
		board[cellToPlaceOn - GRID_SIZE] = pieceShapesPositions[1] * playerCell;
	}
	if (board[cellToPlaceOn - GRID_SIZE + 1] == 0)
	{
		board[cellToPlaceOn - GRID_SIZE + 1] = pieceShapesPositions[2] * playerCell;
	}

	if (board[cellToPlaceOn - 1] == 0)
	{
		board[cellToPlaceOn - 1] = pieceShapesPositions[3] * playerCell;
	}
	if (board[cellToPlaceOn] == 0)
	{
		board[cellToPlaceOn] = pieceShapesPositions[4] * playerCell;
	}
	if (board[cellToPlaceOn + 1] == 0)
	{
		board[cellToPlaceOn + 1] = pieceShapesPositions[5] * playerCell;
	}

	if (board[cellToPlaceOn + GRID_SIZE - 1] == 0)
	{
		board[cellToPlaceOn + GRID_SIZE - 1] = pieceShapesPositions[6] * playerCell;
	}
	if (board[cellToPlaceOn + GRID_SIZE] == 0)
	{
		board[cellToPlaceOn + GRID_SIZE] = pieceShapesPositions[7] * playerCell;
	}
	if (board[cellToPlaceOn + GRID_SIZE + 1] == 0)
	{
		board[cellToPlaceOn + GRID_SIZE + 1] = pieceShapesPositions[8] * playerCell;
	}

	return board;
}

std::vector<int> AIDescisionMaker::checkThisCollisionAllowed(int t_pieceType)
{
	std::vector<int>pieceShapesPositions;
	std::vector<int>validCellPositions;
	int counter = 0;

	//this is awful but its too late for me to care :)
	if (t_pieceType == 0)
	{
		pieceShapesPositions =
		{ 0,1,0
		 ,1,1,1
		 ,0,1,0 };
	}
	else if (t_pieceType == 1)
	{
		pieceShapesPositions =
		{ 0,0,0
		,0,1,0
		,0,0,0 };
	}
	else if (t_pieceType == 2)
	{
		pieceShapesPositions =
		{ 0,1,0
		,0,1,0
		,0,0,0 };
	}
	else if (t_pieceType == 3)
	{
		pieceShapesPositions =
		{ 0,1,0
		,1,1,0
		,0,0,0 };
	}
	else if (t_pieceType == 4)
	{
		pieceShapesPositions =
		{ 0,1,0
		,0,1,0
		,0,1,0 };
	}
	else if (t_pieceType == 5)
	{
		pieceShapesPositions =
		{ 1,1,0
		,1,1,0
		,0,0,0 };
	}
	else if (t_pieceType == 6)
	{
		pieceShapesPositions =
		{ 0,1,0
		,1,1,0
		,0,1,0 };
	}
	else if (t_pieceType == 7)
	{
		pieceShapesPositions =
		{ 0,1,1
		,1,1,0
		,0,0,0 };
	}
	else if (t_pieceType == 8)
	{
		pieceShapesPositions =
		{ 1,1,0
		,0,1,1
		,0,1,0 };
	}
	else if (t_pieceType == 9)
	{
		pieceShapesPositions =
		{ 0,1,0
		,1,1,1
		,0,1,0 };
	}
	else if (t_pieceType == 10)
	{
		pieceShapesPositions =
		{ 0,0,0
		,1,1,1
		,1,0,1 };
	}
	else if (t_pieceType == 11)
	{
		pieceShapesPositions =
		{ 0,1,1
		,1,1,0
		,1,0,0 };
	}

	//the cell is the center and move that along to check the whole grid
	//grid is 12*12 outer layer is walls so skip cells 0 - 11
	/*for (int index = 0; index < gridCellTypes.size(); index++)
	{
		if (gridCellTypes[index] / 12 != 0 && gridCellTypes[index] / 12 != 11 && gridCellTypes[index] % 12 != 0 && gridCellTypes[index] % 12 != 11)
		{

		}
	}*/

	//for (int cells = 0; cells < t_nearbyCells.size(); cells++)
	//{
	//	for (int index = 0; index < piecesNeeded; index++)
	//	{
	//		if (pieceShapes[index].getGlobalBounds().intersects(t_nearbyCells[cells].getCellShape().getGlobalBounds()) && (t_nearbyCells[index].getCellType() == 0) && cellChecked[index] == false)
	//		{
	//			cellChecked[index] = true;
	//			continue;//found a cell for the piece - look for more
	//		}
	//	}
	//}

	for (int row = 1; row <= 10; ++row)//doesnt seem to update cell list every time
	{
		for (int col = 1; col <= 10; ++col)
		{
			bool isValid = true;//look for any overlapping celles
			int cellWeCurrentlyChecking = col * 12 + row;
			//std::cout << "\n" + cellWeCurrentlyChecking;
			//why doesnt this work :(
			//im far too tired for this shit
			//this is actual nonsense tf am i typing
			//after sleeping i realised i had row and col the wrong way around lm
			if (pieceShapesPositions[0] != 0 && gridCellTypes[cellWeCurrentlyChecking - 1 - 12] !=0)
			{
				isValid = false;
			}
			if (pieceShapesPositions[1] != 0 && gridCellTypes[cellWeCurrentlyChecking - 12] != 0)
			{
				isValid = false;
			}
			if (pieceShapesPositions[2] != 0 && gridCellTypes[cellWeCurrentlyChecking + 1 - 12] != 0)
			{
				isValid = false;
			}
			if (pieceShapesPositions[3] != 0 && gridCellTypes[cellWeCurrentlyChecking - 1] != 0)
			{
				isValid = false;
			}
			if (pieceShapesPositions[4] != 0 && gridCellTypes[cellWeCurrentlyChecking] != 0)
			{
				isValid = false;
			}
			if (pieceShapesPositions[5] != 0 && gridCellTypes[cellWeCurrentlyChecking + 1] != 0)
			{
				isValid = false;
			}
			if (pieceShapesPositions[6] != 0 && gridCellTypes[cellWeCurrentlyChecking - 1 + 12] != 0)
			{
				isValid = false;
			}
			if (pieceShapesPositions[7] != 0 && gridCellTypes[cellWeCurrentlyChecking + 12] != 0)
			{
				isValid = false;
			}
			if (pieceShapesPositions[8] != 0 && gridCellTypes[cellWeCurrentlyChecking + 1 + 12] != 0)
			{
				isValid = false;
			}

			if (isValid==true)
			{
				//counter++;
				//std::cout << "\n" << counter << "cell current " << cellWeCurrentlyChecking << "\n";
				validCellPositions.push_back(cellWeCurrentlyChecking);//put the middle cell back in
			}
		}
	}
	//weirdly seems to allow cells through sometimes, might be an issue with type
	return validCellPositions;//list of all good positions for the cells
}