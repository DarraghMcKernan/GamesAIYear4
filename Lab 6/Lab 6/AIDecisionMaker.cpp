#include "AIDecisionMaker.h"

void AIDescisionMaker::init()
{

}

void AIDescisionMaker::update()
{

}

int AIDescisionMaker::pickCellToPlace()
{
	chosenCell = rand() % MAX_CELLS;
	
	return chosenCell;
}

//the more shapes that make up the piece the higher its value
	//collision check just needs to compare the matrix of the shape to the board to find if there is a slot for that particular piece
	// 0,1,0      if the board has a series of cells that lines up with this we use that as one of its possible places
	// 1,1,1      this also avoids sfmls collision check which is probably more expensive
	// 0,1,0	  we will want to place the largest piece we can typically, if there is no space work down in size

	// also can check if a position is optimal as it will be near a friendly tile - type 1 is invalid(wall), 2 is player, 3 is AI

int AIDescisionMaker::pickPieceToPlace() 
{
	int bestPiece = currentPiece;
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
	return 1;
}

void AIDescisionMaker::giveGridOverview(std::vector<int> t_gridOverview)
{
	gridCellTypes = t_gridOverview;
}
