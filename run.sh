#!/bin/bash
#Run this in terminal
#+ Command to compile c++ program. here i used common one
g++ -std=c++11 main.cpp Board.cpp -o prog -lsfml-graphics -lsfml-window -lsfml-system
./prog
exit 0