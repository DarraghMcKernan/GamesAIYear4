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
	/**
	 * @brief Will return a list of cells that the piece specified had no collisions on
	 * @param t_pieceType the type of piece that we want to check off of the grid
	 * @return A std::vector of type <int> that holds all the cells that were valid for placement
	 */
	std::vector<int> checkThisCollisionAllowed(int t_pieceType);
	/**
	 * @brief will go through possible
	 * @param t_newGrid is the most recent modified grid
	 * @param t_depth is how deep we have already searched
	 * @param t_maximizingPlayer the bool to show whos turn it is
	 * @param t_pieceType the piece type that we want to add onto the grid
	 * @return the value of the moves to get this far into the simulated game
	 */
	int minimax(std::vector<int> t_newGrid, int t_depth, bool t_maximizingPlayer,int t_piece);
	/**
	 * @brief Will work out if the given simulated moves are of high value so we know if its a good move
	 * @param t_newGrid is the current grid with all the simulated moves on it
	 * @return Return the value of this spevific set of moves
	 */
	int evaluateBoard(std::vector<int> t_newGrid);
	/**
	* @brief Will modify the given grid to add in the piece(t_pieceType) at the cell(t_cellToPlaceOn)
	* @param t_newGrid is the most recent modified grid
	* @param t_cellToPlaceOn is the specific cell we are placing the piece on
	* @param t_pieceType the piece type that we want to add onto the grid
	* @param t_player the bool to show whos turn it is and if the cells need to be type 2 or 3 when set
	* @return A std::vector of type <int> that holds all the cells that were valid for placement
	*/
	std::vector<int> returnUpdatedGrid(std::vector<int> t_newGrid, int t_cellToPlaceOn, int t_pieceType, bool t_player);

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
	* @brief Used to keep track of what pieces have been used
	*/
	int AIPiecesUsed[11] = { 0,0,0,0 ,0,0,0,0, 0,0,0};
	/**
	* @brief The current piece we are checking
	*/
	int currentPiece = 10;
	/**
	* @brief This can be used to check if a move is valid or more valuable
	*/
	std::vector<int> gridCellTypes;
	/**
	* @brief How many times was minimax called
	*/
	int movesTaken = 0;
	/**
	* @brief How deep will we search
	*/
	int maxDepth = 2;
};