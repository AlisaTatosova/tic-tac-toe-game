#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <sstream>

class Board {
public:
    Board(int size);

    void initialize_board(int size); // for initializing board
    void set_cell(int cell_num, char xo); // for setting given board cell X or O
    char get_cell(int cell_num) const; // for getting symbol inside cell
    char get_cell(int i, int j) const; //  for getting symbol inside cell
    bool cell_is_not_empty(int cell); // checking if cell is not empty
    void print_board(int size); // printing board
    std::size_t size() const; // getting size of board
    std::string get_board_as_string(); // getting board as string
    
private:
    std::vector<std::vector<char>> board;
};

#endif
