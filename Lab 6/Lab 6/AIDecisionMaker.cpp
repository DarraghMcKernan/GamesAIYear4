#include "AIDecisionMaker.h"

void AIDescisionMaker::init()
{

}

void AIDescisionMaker::update()
{

}

int AIDescisionMaker::pickCellToPlace()
{

	chosenCell -= 11;
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