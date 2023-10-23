#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "board.h"
#include "players.h"

class GameOver {
public:
    GameOver(Board& board);

    bool check_diagonal_win();
    bool check_anti_diagonal_win();
    bool check_row_win(int row);
    bool check_column_win(int col);
    std::pair<bool, std::string> game_over(char turn, int cell_num);
    std::pair<bool, std::string> game_over_none();

private:
    Board& board;
    PlayerXO player;
};

#endif
