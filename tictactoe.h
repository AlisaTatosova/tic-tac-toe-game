#ifndef TICTACTOE_H
#define TICTACTOE_H

#include "board.h"
#include "players.h"
#include "gameover.h"

#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <iostream>
#include <sstream>
#include <vector>
#include <functional>

class TicTacToe {
public:
    TicTacToe(int size);

    void sending(int client_socket, const std::string& message); // sending message by socket
    void start_game(int client_socketX, int client_socketO); // the main game logic
    void send_result(int client_socket, char flag, const std::string& final, char XO); // sending game result by socket
    void send_to_clients(int client_socket, const std::string& board); // sending message to both clients simultaneously
    void client_handler(int& client_socket, int& other_socket, char& XO, std::string& turn, std::string& not_turn, char& flag, char& invalid, char& is_occupied, std::string& final); // function for handling play with client

private:
    Board board;
    PlayerXO player;
    GameOver gameover;
};

#endif
