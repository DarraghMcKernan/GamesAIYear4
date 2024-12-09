#pragma once
#include "globals.h"
#include "Cell.h"

/**
 * @class GameShapes
 * @brief The class that handles and creates the shapes for the game pieces
 */
class GameShapes
{
public:
	/**
	* @brief Default constructor for the game shapes
	* @param t_shapeType The type of piece this will be
	* @param t_team The team this piece will be on
	* @param t_originPos The position this piece will be generated on
	* @param t_rotation The rotation this piece will be set at
	*/
	GameShapes(int t_shapeType,int t_team, sf::Vector2f t_originPos,int t_rotation);
	/**
	* @brief Update the game once every frame
	*/
	void update();
	/**
	* @brief Renders the game shapes on the given render window
	* @param t_window Reference to the SFML render window
	*/
	void render(sf::RenderWindow& t_window);
	/**
	* @brief change to the piece of t_shapeType
	* @param t_shapeType the type of piece the shape will be
	*/
	void generatePiece(int t_shapeType);
	/**
	* @brief Reposition all the squares of the piece
	*/
	void redoShapes();
	/**
	* @brief Rotate the piece according to the specified rotations
	* @param t_rotation Specifies how many times we should rotate
	*/
	void rotatePieceRight(int t_rotation);
	/**
	* @brief Change the current position to the new position
	* @param t_newPos The new position to move the piece to
	*/
	void updateOriginPos(sf::Vector2f t_newPos);
	/**
	* @brief Get the current position of the piece
	* @return the position of the piece
	*/
	sf::Vector2f returnOriginPos();
	/**
	* @brief Update the team of this piece
	* @param t_num The new team we are assigning this piece to
	*/
	void updateTeamNum(int t_num);
	/**
	* @brief Check collisions off of the nearby cells
	* @param t_nearbyCells A list of the 9 nearest cells to the piece
	* @return True if there are no collisions and false if there is
	*/
	bool checkCollisions(std::vector<Cell> t_nearbyCells);
	/**
	* @brief Used to check if all of the cells are colliding or not
	*/
	std::vector<bool> cellChecked;
	/**
	* @brief is this piece a type cathedral
	* @return True it is a cathedral False is not
	*/
	bool isCathedral();
	/**
	* @brief Get the current rotation of this piece
	* @return int Return the current rotation of this piece
	*/
	int getRotation();
	/**
	* @brief Get the cell type that the mouse is currently over
	* @param t_mousePos The position of the mouse
	* @return The number of the cell we are hovering over
	*/
	int getHoveredType(sf::Vector2f t_mousePos);
	/**
	* @brief use up one of the pieces of type that is specified
	* @param t_type The cell type that we want to use one of
	*/
	void useType(int t_type);
	/**
		* @brief Are there any of this type of cell let
		* @param t_type The cell type that we want to check
		* @return True if we can use it False if we cant
		*/
	bool pieceAllowed(int t_type);
	/**
	* @brief Grey out the player piece buttons as they get used up
	*/
	void deactivateButton();
	/**
	* @brief get the 9 shaped that make up a piece
	* @return std::vector<int> returns the 9 shapes that make up this game piece
	*/
	std::vector<int> getMatrixOfCells();

	/**
	* @brief used to check if this is a cathedral piece
	*/
	bool cathedralEdgeCase = false;
	/**
	* @brief used to set tiles as used
	*/
	sf::Vector2f positionToSetUsed;

private:
	/**
	* @brief type of piece this shape is
	*/
	int type;
	/**
	* @brief team this piece is on
	*/
	int team;
	/**
	* @brief current rotation of this piece
	*/
	int rotation = 0;
	/**
	* @brief how many of the 9 shapes are used for this piece
	*/
	int shapesActive = 0;
	/**
	* @brief the max amount of pieces in a shape
	*/
	int piecesNeeded = 9;
	/**
	* @brief used to store what pieces the player has used
	*/
	int playerPiecesUsed[11] = {0,0,0,0 ,0,0,0,0, 0,0,0};
	/**
	* @brief used to store what pieces the ai has used
	*/
	int AIPiecesUsed[11] = {0,0,0,0 ,0,0,0,0, 0,0,0};

	/**
	* @brief The shapes that make up this piece
	*/
	std::vector<sf::RectangleShape> pieceShapes;
	/**
	* @brief The position of the center of this tile
	*/
	sf::Vector2f originPos;
	/**
	* @brief The colour this team uses	
	*/
	sf::Color teamColour;

	/**
	* @brief The positions of the piece stored as a matrix
	*/
	std::vector<int>pieceShapesPositions;
};