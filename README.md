# Conway's Game of Life with C++ SFML

As a hobbyist project, this is a simple implementation of Conway's Game of Life using SFML, a cross-platform multimedia library. The Game of Life is a cellular automaton that was devised by the British mathematician John Horton Conway in 1970. The rules of the game are simple:
* Any live cell with two or three live neighbors survives.
* Any dead cell with three live neighbors becomes a live cell.
* All other live cells die in the next generation. Similarly, all other dead cells stay dead.

https://user-images.githubusercontent.com/68392000/234765720-ecac1e94-8d40-4cf9-b0a6-c907f79303ea.mov

The game is played on a two-dimensional grid of cells, where each cell is either alive or dead. In this implementation, you can interact with the grid by clicking on the cells to toggle their state between alive and dead.

## Requirements
To run this program, you will need:

- C++ compiler that supports C++11 or higher
- SFML library (version 2.5.1 or higher)

## Building and running the program
To run the program, run the following command:
```bash
#!/bin/bash
#Run this in terminal
#+ Command to compile c++ program. here i used common one
g++ -std=c++11 main.cpp Board.cpp -o prog -lsfml-graphics -lsfml-window -lsfml-system
./prog
exit 0
```

Or just simply run `run.sh` in the Terminal.

## Controls
* Left-click on a cell to set state to alive.
* Right-click on a living cell to kill them.
* Press the `space` key to start or stop the simulation.
* Press the `Bksp` key to clear the grid.
* Press the `Tab` key to randomize the grid.
* Numbers `0-9` changes colours of the cells.
* `Up/Down` arrow zooms in and out.
* `Left/Right` arrow changes sppeed.

## Acknowledgments
* [SFML](https://www.sfml-dev.org/index.php), the cross-platform multimedia library used in this project.
* [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life), the cellular automaton devised by John Horton Conway.
