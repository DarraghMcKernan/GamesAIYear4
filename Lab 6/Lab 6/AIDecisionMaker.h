#pragma once
#include "globals.h"

/**
* @class AIDescisionMaker
* @brief Used to make decisions and use them in the game
*/
class AIDescisionMaker
{
public:
	/**
	* @brief Initiates the AI
	*/
	void init();
	/**
	* @brief Updates the AI
	*/
	void update();
	/**
	* @brief Return the AIs chosen cell
	*/
	int pickCellToPlace();
	/**
	* @brief Return the AIs chosen piece
	*/
	int pickPieceToPlace();
	/**
	* @brief Return the AIs chosen rotation
	*/
	int pickRotation();
	/**
	* @brief Give the AI all of the cells so they can be used for checking if the positions are valid
	* @param t_gridOverview passes in the entire grid of cell values to see if they are used or not
	*/
	void giveGridOverview(std::vector<int> t_gridOverview);

	std::vector<int> checkThisCollisionAllowed(int t_pieceType);

	/**
	* @brief The best piece the ai has picked
	*/
	int bestPiece = 0;

private:
	/**
	* @brief The cell that the AI has picked
	*/
	int chosenCell = 49;
	/**
	* @brief used to keep track of what pieces have been used
	*/
	int AIPiecesUsed[11] = { 0,0,0,0 ,0,0,0,0, 0,0,0};
	/**
	* @brief the current piece we are checking
	*/
	int currentPiece = 10;
	/**
	* @brief this can be used to check if a move is valid or more valuable
	*/
	std::vector<int> gridCellTypes;
};