#include "board.h"

Board::Board(int size) {
    std::cout << "Welcome to TIC TAC TOE game!" << std::endl;
    initialize_board(size);
    print_board(size); 
}

void Board::initialize_board(int size) {
    board.resize(size, std::vector<char>(size, 0));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = '0' + i * size + (j + 1);
        }
    }
}

void Board::set_cell(int cell_num, char xo) {
    int x = (cell_num - 1) / board.size();
    int y = (cell_num - 1) % board.size();
    board[x][y] = xo;
}

char Board::get_cell(int cell_num) const {
    int x = (cell_num - 1) / board.size();
    int y = (cell_num - 1) % board.size();
    return board[x][y];
}

char Board::get_cell(int i, int j) const {
    return board[i][j];
}

bool Board::cell_is_not_empty(int cell) {
    int x = (cell - 1) / board.size();
    int y = (cell - 1) % board.size();
    if(get_cell(x, y) == 'X' || get_cell(x, y) == 'O') {
        return false;
    }
    return true;
}

void Board::print_board(int size) {
    std::cout << "  ------------------" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << " " << " | " ;
        for (int j = 0; j < size; j++) {
            std::cout << board[i][j] << "  |  ";     
        }
        std::cout << std::endl;
        std::cout << "  ------------------" << std::endl;
    }
}
    
std::string Board::get_board_as_string() {
    std::ostringstream output;
    output << "  ------------------" << std::endl;
    for (int i = 0; i < 3; i++) {
        output << " " << " | " ;
        for (int j = 0; j < 3; j++) {
            output << board[i][j] << "  |  ";
        }
        output << std::endl;
        output << "  ------------------" << std::endl;

    }

    // Get the result as a string
    std::string result = output.str();

    return result;
}

std::size_t Board::size() const {
    return board.size();
}
