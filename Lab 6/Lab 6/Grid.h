#pragma once
#include "globals.h"
#include "Cell.h"

/**
 * @class Grid
 * @brief The class that handles everything for the grid
 */
class Grid
{
public:
	/**
	* @brief Set up the grid
	*/
	void init();
	/**
	* @brief Update the grid once every 60 frames
	*/
	void update();
	/**
	* @brief Renders the grid
	* @param t_window Reference to the SFML render window
	*/
	void render(sf::RenderWindow& t_window);
	/**
	* @brief Renders the grid
	* @param t_mousePos is the position of the mouse
	* @return Returns the position of the cell the mouse is over
	*/
	sf::Vector2f returnHoveredCellPos(sf::Vector2f t_mousePos);
	/**
	* @brief return the 9 cells surrounding the mouse
	* @return std::vector<Cell> passes back the cells as a list
	*/
	std::vector<Cell> returnNearbyCellPos();
	/**
	* @brief Will set the cells the piece overlaps with to the number of the current team
	* @param t_cellsUsed is a list of cells that makes up a shape that we can check collisions off of
	* @param t_cathedral check if the piece a cathedral piece so we can do edge case checks on it
	* @param t_rotation the rotation of the piece we are applying to the board
	* @param t_teamNum the team the piece belongs to for setting to the board
	*/
	void setCellsTo(std::vector<bool> t_cellsUsed,bool t_cathedral,int t_rotation,int t_teamNum);
	/**
	* @brief return all of the cells in the grid
	* @return std::vector<Cell> passes back all of the cells on the grid
	*/
	std::vector<int> getAllGridCells();
	/**
	* @brief Will take in a cell and set it as used
	* @param t_cellPosition Set this specific cell as used
	*/
	void setCellAsUsed(sf::Vector2f t_cellPosition);
private:
	/**
	* @brief The list of the games cells that make up the grid
	*/
	std::vector<Cell> cells;
	/**
	* @brief The list of the cells by the type of cell that they are
	*/
	std::vector<int> cellsByType;
	/**
	* @brief Unique shape that makes up the border
	*/
	sf::RectangleShape boardWall;
	/**
	* @brief The current cell the mouse is hovering over
	*/
	sf::RectangleShape celllHoveredOver;
	/**
	* @brief The cell number of the cell we are hovering over
	*/
	int cellHoveredNumber;
	/**
	* @brief The position of the mouse
	*/
	sf::Vector2f mousePos;
};