#pragma once
#include "globals.h"

class AIDescisionMaker
{
public:
	void init();
	void update();
	int pickCellToPlace();
	int pickPieceToPlace();
	int pickRotation();
	void giveGridOverview(std::vector<int> t_gridOverview);

private:
	int chosenCell = 49;

	int AIPiecesUsed[11] = { 0,0,0,0 ,0,0,0,0, 0,0,0};
	int currentPiece = 10;

	/// <summary>
	/// A list of the entire grid and the type of cells in order
	/// this can be used to check if a move is valid or more valuable
	/// </summary>
	std::vector<int> gridCellTypes;
};