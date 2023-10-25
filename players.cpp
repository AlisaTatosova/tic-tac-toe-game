#include "players.h"

PlayerXO::PlayerXO(char turn) : turn(turn) {}
PlayerXO::PlayerXO() : turn('X') {}
  

std::pair<std::string, bool> PlayerXO::make_move(int cell_num, char XO, Board& board) { // making move
    bool cell_is_not_busy = true; 

    if (cell_num < 1 || cell_num > 9) { // if give cell is invalid cell number
        cell_is_not_busy = false;
	return {"invalid", cell_is_not_busy};

    }

    if (board.cell_is_not_empty(cell_num)) {
        board.set_cell(cell_num, XO); // if chosen cell is not occupied setting corresponding player move
    }  else { // if the cell is already occupied
        cell_is_not_busy = false;
	return {"occupied", cell_is_not_busy};

    }

    return {"", cell_is_not_busy};
}

