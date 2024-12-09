#pragma once
#include "globals.h"
#include "Grid.h"
#include "GameShapes.h"
#include "AIDecisionMaker.h"

/**
 * @class Game
 * @brief Used to handle all functions of gameplay
 */
class Game
{
public:
	/**
	* @brief Setup the game
	*/
	void init();
	/**
	* @brief Update the game once every frame
	*/
	void update();
	/**
	* @brief Renders the games classes on the given render window
	* @param t_window Reference to the SFML render window
	*/
	void render(sf::RenderWindow& t_window);
	/**
	* @brief Finds the center of the cell nearest the mouse
	* @return sf::Vector2f return the center position of the found cell
	*/
	sf::Vector2f lockNearestCell();
	/**
	* @brief Finds the center of the cell requested
	* @param t_cellNum pass in the cell we want to snap to
	* @return sf::Vector2f return the center position of the found cell
	*/
	sf::Vector2f lockToKnownCell(int t_cellNum);

private:
	/**
	* @brief Instance of the grid class
	*/
	Grid myGrid;
	/**
	* @brief Position of the mouse stored as 2 floats rather than integers
	*/
	sf::Vector2f mousePos;
	/**
	* @brief instance of myAI
	*/
	AIDescisionMaker myAI;

	/**
	* @brief The type of piece the player wants to place
	*/
	int type = 0;
	/**
	* @brief A cooldown added between button presses and mouse clicks to prevent too many inputs at once
	*/
	int clickCooldown=0;
	/**
	* @brief The current team that gets to play
	*/
	int teamNum = 0;
	/**
	* @brief The rotation of the pieces
	*/
	int rotation = 0;
	/**
	* @brief The piece the ai has picked to place
	*/
	int aiPiece = 0;
	/**
	* @brief The rotation the ai has picked
	*/
	int aiRotation = 0;
	/**
	* @brief The cell the ai has picked
	*/
	int aiCell = 0;

	/**
	* @brief Is it valid to put a game piece here
	*/
	bool placementValid = true;
	/**
	* @brief Has a piece been picked already
	*/
	bool pieceSelected = false;
	/**
	* @brief Check to see if its the players or ai's turn
	*/
	bool playersTurn = true;
	/**
	* @brief Check to see if we are waiting for the ai to finished searching
	*/
	bool aiBeganSearch = false;
	/**
	* @brief Check to see if the game has ended
	*/
	bool gameOver = false;

	/**
	* @brief List of all of the pieces in the game
	*/
	std::vector<GameShapes> gamePieces;
	/**
	* @brief The shape that acts as a visually highlighter to show where the piece is being placed
	*/
	std::vector<GameShapes> highlighter;
	/**
	* @brief List of pieces to act as buttons for the playewr to select a new shape
	*/
	std::vector<GameShapes> pieceButtons;
	/**
	* @brief List of ints to show what cells have been set or not
	*/
	std::vector<int> gridCellTypes;
};