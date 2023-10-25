#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "board.h"
#include "players.h"

class GameOver {
public:
    GameOver(Board& board);

    bool check_diagonal_win(); // checking diagonal win
    bool check_anti_diagonal_win(); // checking antidiagonal win
    bool check_row_win(int row); // checking row win
    bool check_column_win(int col); // checking column win
    std::pair<bool, std::string> game_over(char turn, int cell_num); // checking game is over
    std::pair<bool, std::string> game_over_none(); // checking for nobody wins ending

private:
    Board& board;
    PlayerXO player;
};

#endif
