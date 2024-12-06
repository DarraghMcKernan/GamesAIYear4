#pragma once

class AIDescisionMaker
{
public:
	void init();
	void update();
	int pickCellToPlace();
	int pickPieceToPlace();
	int pickRotation();

private:
	int chosenCell = 49;
};