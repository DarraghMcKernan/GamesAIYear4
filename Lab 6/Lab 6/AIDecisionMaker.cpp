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

int AIDescisionMaker::pickPieceToPlace() 
{
	return 4;
}

int AIDescisionMaker::pickRotation()
{
	return 1;
}