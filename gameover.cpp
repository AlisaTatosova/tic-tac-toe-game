#include "gameover.h"

GameOver::GameOver(Board& board) : board{board} {}

// checking for diagonal win
bool GameOver::check_diagonal_win() {
    int size = 0;
    for (int i = 0; i < board.size() - 1; ++i) {
        if (board.get_cell(i, i) == board.get_cell(i + 1, i + 1)) {
            ++size;
        } 
    }

    if (size == board.size() - 1) {
        return true;
    }
    return false;
}

// checking for antidiagonal win
bool GameOver::check_anti_diagonal_win() {
    int size = 0;
    for (int i = 0; i < board.size(); ++i) {
        int j = board.size() - i - 1;
        if (board.get_cell(j, i) == board.get_cell(board.size() - 1, 0)) {
            ++size;
        } 
    }

    if (size == board.size()) {
        return true;
    }
    return false;
}

// checking for row win
bool GameOver::check_row_win(int row) {
    int size = 0;
    for (int i = 0; i < board.size() - 1; ++i) {
        if (board.get_cell(row, i) == board.get_cell(row, i + 1)) {
            ++size;
        }
    }

    if (size == board.size() - 1) {
        return true;
    }
    return false;
}

// checking for column win
bool GameOver::check_column_win(int col) {
    int size = 0;
    for (int i = 0; i < board.size() - 1; ++i) {
        if (board.get_cell(i, col) == board.get_cell(i + 1, col)) {
            ++size;
        }
    }

    if (size == board.size() - 1) {
        return true;
    }
    return false;
}

// checking for if game is over
std::pair<bool, std::string> GameOver::game_over(char turn, int cell_num) {
    bool win = false;
    std::string res = "";
    if (check_diagonal_win()) {
        if (turn == 'X') {
            res = "Diagonal win of X";
            win = true;
        } else {
            res = "Diagonal win of O";
            win = true;
        }
    }

    if (check_anti_diagonal_win()) {
        if (turn = 'X') {
            res = "Antidiagonal win of X";
            win = true;
        } else {
            res = "Antidiagonal win of O";
            win = true;
       }
    }

    if (check_row_win((cell_num - 1) / board.size())) {
        if (turn == 'X') {
            res = "Row win of X";
            win = true;
        } else {
            res = "Row win of O";
            win = true;
        }
    }

    if (check_column_win((cell_num - 1) % board.size())) {
        if (turn == 'X') {
            res = "Column win of X";
            win = true;
        } else {
            res = "Column win of O";
            win = true;
        }
    }     
    return {win, res};
}

std::pair<bool, std::string> GameOver::game_over_none() {
    for (int i = 1; i <= board.size() * board.size(); ++i) {
        if (board.cell_is_not_empty(i)) {
            return {false, ""};
        }
    }
    std::string res = "";
    res = "End: None has won!";
    return {true, res};
}
