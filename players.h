#ifndef PLAYERS_H
#define PLAYERS_H
#include "board.h"

class PlayerXO {
public:
    char turn; // turn
    PlayerXO(char turn);
    PlayerXO();
    std::pair<std::string, bool> make_move(int cell_num, char XO, Board& board); // making move in board
};



#endif
