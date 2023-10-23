#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <sstream>

class Board {
public:
    Board(int size);

    void initialize_board(int size);
    void set_cell(int cell_num, char xo);
    char get_cell(int cell_num) const;
    char get_cell(int i, int j) const;
    bool cell_is_not_empty(int cell);
    void print_board(int size);
    std::size_t size() const;
    std::string get_board_as_string();
    
private:
    std::vector<std::vector<char>> board;
};

#endif
