#include "server.h"

int main() {
    TicTacToe game(3);
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return -1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(11302);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Failed to bind socket" << std::endl;
        return -1;
    }

    listen(server_socket, 2);
    std::cout << "Waiting for players to connect..." << std::endl;

    int client_socketX = accept(server_socket, NULL, NULL);
    int client_socketO = accept(server_socket, NULL, NULL);




   
    game.start_game(client_socketX, client_socketO);




    close(server_socket);
}
