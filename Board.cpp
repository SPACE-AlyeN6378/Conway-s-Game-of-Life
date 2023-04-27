#include "Board.h"

unsigned int Board::get_rows()
{
    return scr_width / cell_size;
}

unsigned int Board::get_cols()
{
    return scr_height / cell_size;
}

unsigned int Board::count_surrounding_cells(int x, int y)
{
    unsigned int count = 0;
    int rows = grid.at(0).size();
    int cols = grid.size();

    for (int j = y-1; j <= y+1; j++) {
        for (int i = x-1; i <= x+1; i++) {
            if (i != x || j != y) {
                // t_x and x_y are the the toroidal X and Y coordinates respectively
                int t_x = ((i % rows) + rows) % rows;
                int t_y = ((j % cols) + cols) % cols;
                
                if (this->grid.at(t_y).at(t_x).getFillColor() == this->color) {
                    count++;
                }
                
            }
        }
    }
    return count;
}

void Board::init_grid()
{
    for (unsigned int y=0; y<get_cols(); y++) {
        std::vector<sf::RectangleShape> row;
        for (unsigned int x=0; x<get_rows(); x++) {
            sf::RectangleShape cell(sf::Vector2f(cell_size, cell_size));
            cell.setFillColor(sf::Color::Black);
            cell.setOutlineColor(sf::Color(40, 40, 40));
            cell.setOutlineThickness(2.0f);
            cell.setPosition(sf::Vector2f(x * cell_size, y * cell_size));
            row.push_back(cell);
        }
        this->grid.push_back(row);
    }
}

Board::Board(unsigned int scr_width, unsigned int scr_height, unsigned int cell_size, sf::Color color)
{
    this->scr_width = scr_width;
    this->scr_height = scr_height;
    this->cell_size = cell_size;
    this->init_grid();
    this->color = color;
}

Board::~Board()
{
}

void Board::make_cell(unsigned int x, unsigned int y)
{
    this->grid.at(y).at(x).setFillColor(this->color);
}

void Board::kill_cell(unsigned int x, unsigned int y)
{
    this->grid.at(y).at(x).setFillColor(sf::Color::Black);
}

void Board::draw_board(sf::RenderWindow& window)
{
    for (const std::vector<sf::RectangleShape>& row: this->grid) {
        for (const sf::RectangleShape& cell: row) {
            window.draw(cell);
        }
    }
}

void Board::clear_board()
{
    for (std::vector<sf::RectangleShape>& row: this->grid) {
        for (sf::RectangleShape& cell: row) {
            cell.setFillColor(sf::Color::Black);
        }
    }
}

void Board::randomize()
{
    clear_board();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::bernoulli_distribution dis(0.3);

    for (unsigned int y=0; y<grid.size(); y++) {
        for (unsigned int x=0; x<grid.at(0).size(); x++) {

            bool allow_birth = dis(gen);
            if (allow_birth) {
                make_cell(x, y);
            }
        }
    }
}

unsigned int Board::get_cellSize()
{
    return cell_size;
}

void Board::set_scale(unsigned int new_cellSize)
{
    unsigned int current_rows = grid.at(0).size();
    unsigned int current_cols = grid.size();
    unsigned int new_rows = scr_width/new_cellSize;
    unsigned int new_cols = scr_height/new_cellSize;
    this->cell_size = new_cellSize;

    sf::RectangleShape new_cell = grid.at(0).at(0);
    new_cell.setFillColor(sf::Color::Black);

    if (new_rows != current_rows || new_cols != current_cols) {
        if (new_rows > current_rows && new_cols > current_cols) {

            for (std::vector<sf::RectangleShape>& row: grid) {
                for (int i=0; i<(new_rows - current_rows); i++) {
                    row.push_back(new_cell);
                }
            }

            std::vector<sf::RectangleShape> new_row(new_rows, new_cell);

            for (int i=0; i<(new_cols - current_cols); i++) {
                grid.push_back(new_row);
            }
        }
        else {

            for (std::vector<sf::RectangleShape>& row: grid) {
                for (int i=0; i<(current_rows - new_rows); i++) {
                    row.pop_back();
                }
            }

            for (int i=0; i<(current_cols - new_cols); i++) {
                grid.pop_back();
            }
        }

        // Change the size of the cells
        for (unsigned int y=0; y<new_cols; y++) {
            for (unsigned int x=0; x<new_rows; x++) {
                grid.at(y).at(x).setSize(sf::Vector2f(new_cellSize, new_cellSize));
                grid.at(y).at(x).setPosition(sf::Vector2f(x * new_cellSize, y * new_cellSize));
            }
        }
    }
}

void Board::set_color(sf::Color new_color)
{
    this->color = new_color;
    for (std::vector<sf::RectangleShape>& row: this->grid) {
        for (sf::RectangleShape& cell: row) {
            
            if (cell.getFillColor() != sf::Color::Black) {
                cell.setFillColor(this->color);
            }
        }
    }
}

void Board::evolve()
{
    std::vector<std::pair<unsigned int, unsigned int> > cells_to_be_born; 
    std::vector<std::pair<unsigned int, unsigned int> > cells_to_be_killed; 

    for (unsigned int y=0; y<grid.size(); y++) {
        for (unsigned int x=0; x<grid.at(0).size(); x++) {
            
            unsigned int living_cells_qty = this->count_surrounding_cells(x, y);
            if (this->grid.at(y).at(x).getFillColor() == this->color) {

                if (living_cells_qty < 2 || living_cells_qty > 3) {
                    cells_to_be_killed.push_back(std::make_pair(x, y));
                }
            }
            else {
                if (living_cells_qty == 3) {
                    cells_to_be_born.push_back(std::make_pair(x, y));
                }
            }
        }
    }

    for (const std::pair<unsigned int, unsigned int>& point: cells_to_be_born) {
        this->make_cell(point.first, point.second);
    } 

    for (const std::pair<unsigned int, unsigned int>& point: cells_to_be_killed) {
        this->kill_cell(point.first, point.second);
    }
}
