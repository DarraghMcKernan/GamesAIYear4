#pragma once
#include "globals.h"

/**
 * @class Cell
 * @brief Represents a single cell in the grid and holds its position, type and shape
 */
class Cell
{
public:
    /**
     * @brief Constructs a cell using its number on the grid and sets its position
     * @param t_cellNum The cell's number in the grid
     */
    Cell(int t_cellNum);
    /**
     * @brief Updates the state of the cell
     */
    void update();
    /**
     * @brief Renders the cell on the given render window
     * @param t_window Reference to the SFML render window
     */
    void render(sf::RenderWindow& t_window);
    /**
     * @brief Returns the sf::RectangleShape representing the cell
     * @return The sf::RectangleShape object used for this cell
     */
    sf::RectangleShape getCellShape();
    /**
     * @brief Returns the type of the cell
     * @return An integer representing the cell type:
     *         - 0: Empty cell
     *         - 1: Board border wall
     */
    int getCellType();
    /**
     * @brief Sets the type of the cell
     * @param t_type An integer representing the cell type - 0 means it is unused
     */
    void setCellType(int t_type);

private:
    /**
     * @brief The cells number in the grid
     */
    int cellNum = 0;
    /**
     * @brief The type of the cell
     */
    int type = 0;
    /**
     * @brief The shape representing this specific cell
     */
    sf::RectangleShape cellShape;
};