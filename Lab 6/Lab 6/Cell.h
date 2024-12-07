#pragma once
#include "globals.h"

class Cell
{
public:
	/// <summary>
	/// Default constructor of a cell that will take in its number
	/// on the grid and will set its position according to this
	/// </summary>
	/// <param name="t_cellNum"></param>
	Cell(int t_cellNum);
	/// <summary>
	/// Used to update the cells
	/// </summary>
	void update();
	/// <summary>
	/// Used to render the cells
	/// </summary>
	/// <param name="t_window"></param>
	void render(sf::RenderWindow& t_window);
	/// <summary>
	/// Returns the sf::RectangleShape that is used to represent this specific cell
	/// Can be used to check collisions or get positions
	/// </summary>
	/// <returns></returns>
	sf::RectangleShape getCellShape();
	/// <summary>
	/// Returns an int that represents what type of cell this is
	/// 0 - empty cell
	/// 1 - board border wall
	/// </summary>
	/// <returns></returns>
	int getCellType();
	/// <summary>
	/// Used to set the cell type
	/// 1 is used to signify it has been used
	/// </summary>
	/// <param name="t_type"></param>
	void setCellType(int t_type);

private:
	/// <summary>
	/// Variable to hold this cells number in the grid
	/// </summary>
	int cellNum = 0;
	/// <summary>
	/// Variable used to identify what type of cell this is
	/// </summary>
	int type = 0;

	/// <summary>
	/// The shape used to represnt this specific cell
	/// </summary>
	sf::RectangleShape cellShape;
};