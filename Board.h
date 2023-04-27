#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <random>
#include <iostream>

class Board
{
private:
    unsigned int scr_width;
    unsigned int scr_height;
    unsigned int cell_size;
    std::vector<std::vector<sf::RectangleShape> > grid;
    sf::Color color;

    unsigned int get_rows();
    unsigned int get_cols();
    void init_grid();
    unsigned int count_surrounding_cells(int x, int y);

public:
    Board(unsigned int scr_width, unsigned int scr_height, unsigned int cell_size, sf::Color color);
    virtual ~Board();
    
    // Gets the XY positions of the cell and is either created nor killed
    void make_cell(unsigned int x, unsigned int y);
    void kill_cell(unsigned int x, unsigned int y);

    // Draws the grid in the window
    void draw_board(sf::RenderWindow& window);

    // Clears the entire grid
    void clear_board();
    
    // Create many random cells at random places
    void randomize();

    // Getters
    unsigned int get_cellSize();

    // Setters
    void set_scale(unsigned int new_cellSize);
    void set_color(sf::Color color);

    // This is where the real magic takes place ****************
    void evolve();
};
