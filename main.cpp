#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Board.h"

const int SCREEN_WIDTH = 1800;
const int SCREEN_HEIGHT = 1200;


int main() {

    // Scale factors, according to the cell sizes
    std::vector<unsigned int> cell_sizes = {15, 20, 25, 30, 40, 50, 60, 90, 100};
    unsigned int current_size_index = 3;

    // Core attributes
    sf::Event event;
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Conway's Game of Life");
    Board board(SCREEN_WIDTH, SCREEN_HEIGHT, cell_sizes[current_size_index], sf::Color::White);

    bool paused = true;
    bool isMousePressed = false;
    sf::Clock clock;


    float time_interval = 100.0f;

    while (window.isOpen()) {

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }

                if (event.key.code == sf::Keyboard::Space) {
                    paused = !paused;
                }

                if (event.key.code == sf::Keyboard::BackSpace) {
                    if (paused) {
                        board.clear_board();
                    }
                }

                if (event.key.code == sf::Keyboard::Tab) {
                    paused = true;
                    board.randomize();
                }

                // SCALE -------------------------------------------------------
                if (event.key.code == sf::Keyboard::Down) {

                    if (current_size_index < cell_sizes.size() - 1) {
                        current_size_index++;
                        board.set_scale(cell_sizes.at(current_size_index));
                    }

                }
                if (event.key.code == sf::Keyboard::Up) {

                    if (current_size_index > 0) {
                        current_size_index--;
                        board.set_scale(cell_sizes.at(current_size_index));
                    }
                }

                // SPEED -------------------------------------------------------
                if (event.key.code == sf::Keyboard::Left && time_interval < 1000) {
                    time_interval += 50;
                }

                if (event.key.code == sf::Keyboard::Right && time_interval > 50) {
                    time_interval -= 50;
                }

                // COLOR -------------------------------------------------------
                if (event.key.code == sf::Keyboard::Num1) {
                    board.set_color(sf::Color::Red);
                }

                if (event.key.code == sf::Keyboard::Num2) {
                    board.set_color(sf::Color(255, 165, 0)); // Orange
                }

                if (event.key.code == sf::Keyboard::Num3) {
                    board.set_color(sf::Color::Yellow);
                }

                if (event.key.code == sf::Keyboard::Num4) {
                    board.set_color(sf::Color::Green);
                }

                if (event.key.code == sf::Keyboard::Num5) {
                    board.set_color(sf::Color::Cyan);
                }

                if (event.key.code == sf::Keyboard::Num6) {
                    board.set_color(sf::Color::Blue);
                }

                if (event.key.code == sf::Keyboard::Num7) {
                    board.set_color(sf::Color(166, 0, 255)); // Purple
                }

                if (event.key.code == sf::Keyboard::Num8) {
                    board.set_color(sf::Color::Magenta);
                }

                if (event.key.code == sf::Keyboard::Num9) {
                    board.set_color(sf::Color(192, 192, 192)); // Silver
                }

                if (event.key.code == sf::Keyboard::Num0) {
                    board.set_color(sf::Color::White);
                }
            }

            // else if (event.type == sf::Event::MouseButtonPressed) {
            //     if (event.mouseButton.button == sf::Mouse::Left) {
            //         sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            //         board.make_cell(mousePos.x / board.get_cellSize(), mousePos.y / board.get_cellSize());
            //     }
            //     else if (event.mouseButton.button == sf::Mouse::Right) {
            //         sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            //         board.kill_cell(mousePos.x / board.get_cellSize(), mousePos.y / board.get_cellSize());
            //     }
            // }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            isMousePressed = true;
        }
        else {
            isMousePressed = false;
        }

        // Paint cells if left mouse button is being held down
        if (isMousePressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            if (mousePos.x >= 0 && mousePos.x < SCREEN_WIDTH && mousePos.y >= 0 && mousePos.y < SCREEN_HEIGHT) {
                board.make_cell(mousePos.x / board.get_cellSize(), mousePos.y / board.get_cellSize());
            }
            
        }

        if (!paused) {
            if (clock.getElapsedTime().asMilliseconds() >= time_interval) {
                board.evolve();
                clock.restart();
            }
        }
        

        window.clear();
        board.draw_board(window);
        window.display();
    
    }

    return 0;
}

