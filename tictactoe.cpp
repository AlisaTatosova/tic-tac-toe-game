#include "tictactoe.h"

TicTacToe::TicTacToe(int size) : board{size}, gameover{board} {}

// sending meessage through socket
void TicTacToe::sending(int client_socket, const std::string& message) {
    send(client_socket, message.c_str(), 300, 0);
}

// sending board to clients simultonously
void TicTacToe::send_to_clients(int client_socket, const std::string& board) {
    sending(client_socket, board); //each thread will send board to his client
}

// sending result of game to clients
void TicTacToe::send_result(int client_socket, char flag, const std::string& final, char XO) {
    if (flag) {
	std::string lose = final + ": You lose!"; // losing client message
	std::string win = final + ": You win!"; // wining client message
	if (XO == 'X' && final[final.size() - 1] == 'X') {
            sending(client_socket, win); 
	} else if (XO == 'O' && final[final.size() - 1] == 'O') {
            sending(client_socket, win);
        } else { 
            sending(client_socket, lose); 
	}
    }
}

// function to handle the connection with client
void TicTacToe::client_handler(int& client_socket, int& other_socket, char& XO, std::string& turn, std::string& not_turn, char& flag, char& invalid, char& is_occupied, std::string& final) {
    std::string game_board = board.get_board_as_string(); // getting board as string
    std::string invalid_input = "Invalid input: please enter your move again : ";
    std::string occupied = "Invalid input, given cell is already busy : choose another one :";
	
    std::string board_turn;
    std::string board_not_turn;
    if (invalid == 1) { // handling invalid input case
        board_turn = game_board + invalid_input;
        board_not_turn = game_board + not_turn;
	invalid = 0;
    } else if (is_occupied == 1) { // handling busy cell case
	board_turn = game_board + occupied;
        board_not_turn = game_board + not_turn;
	is_occupied  = 0;
    } else { 
        board_turn = game_board + turn; // also adding to board message the message who's turn it is now
        board_not_turn = game_board + not_turn;
    }

    // using threads to transfer board to both clients simultonusly
    std::thread th1(std::bind(&TicTacToe::send_to_clients, this, other_socket, std::ref(board_turn)));
    std::thread th2(std::bind(&TicTacToe::send_to_clients, this, client_socket, std::ref(board_not_turn)));
    th1.join();
    th2.join();


    int cell_num; // the cell num that client will enter in his turn
    char buffer[1]; // keeps the cell num that client enter

    // recieving message only from socket who's turn it has been
    if (turn == "Please enter your move: " && XO == 'X') {
        recv(other_socket, buffer, 1, 0); 
    } else if (turn == "Please enter your move: " && XO == 'O') { // if it is O turn, recieve info from client O
        recv(other_socket, buffer, 1, 0);
    }

    cell_num = buffer[0] - '0'; // making cell_num string 


    if (player.make_move(cell_num, XO, board).second) { // making move => updating board, make_move function returns true if the move is accessable
        if (gameover.game_over(XO, cell_num).first) { // checking for win
            final = board.get_board_as_string() + gameover.game_over(XO, cell_num).second; // saving the result of game in string final
	    flag = 1;
        }

        if (gameover.game_over_none().first) { // cheking for nobody win
            final = board.get_board_as_string() + gameover.game_over_none().second;
            flag = 1;	    
	}
    } else { // if move is not accesable
        int tmp = client_socket;
        client_socket = other_socket;
        other_socket = tmp;
	if (player.make_move(cell_num, XO, board).first == "invalid") {
            invalid = 1;
	} else {
	    is_occupied = 1;
	}
    }
 
    std::thread th3(std::bind(&TicTacToe::send_result, this, other_socket, flag,  final, XO)); // // if someone win thread will send the result to his clients
    std::thread th4(std::bind(&TicTacToe::send_result, this, client_socket, flag,  final, XO == 'X' ? 'O' : 'X')); // if someone win thread will send the result to his clients

    th3.join();
    th4.join();
}

// starting the game
void TicTacToe::start_game(int client_socketX, int client_socketO) {
    std::string turn = "Please enter your move: ";

    int socket = client_socketX;
    int other_socket = client_socketO;
    char symbol = 'X';
    char flag = 0;
    char invalid = 0;
    std::string not_turn = "The opponents turn, please wait for your turn";
    char is_occupied = 0;

    std::string final = "";
    while (true) {
        client_handler(socket, other_socket, symbol, turn, not_turn, flag, invalid, is_occupied,  final);

	// changing sockets after one move
        if (socket == client_socketX) {
                socket = client_socketO;
                other_socket = client_socketX;
        } else {
                socket = client_socketX;
                other_socket = client_socketO;
        }

	// checking for invalid moves
        if (!invalid && !is_occupied) {
	    if (symbol == 'X') {
                symbol = 'O';
            } else {
                symbol = 'X';
            }
        }
	
	// checking for game end
        if (flag) {
                flag = 0;
                break;
        }

    }

}
