#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <sstream>
#include <mutex>
#include <vector>

std::mutex myMutex;
std::vector<std::vector<char>> board;

void initialize_board() {
    int size = 3;
    board.resize(size, std::vector<char>(size, 0));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = '0' + i * size + (j + 1);
        }
    }
}

void print_board() {
     std::cout << "  ------------------" << std::endl;
     for (int i = 0; i < 3; i++) {
	std::cout << " " << " | " ;
        for (int j = 0; j < 3; j++) {
		std::cout << board[i][j] << "  |  ";
        }
	std::cout << std::endl;
	std::cout << "  ------------------" << std::endl;
    }
}

void board_init() {
    std::cout << "Welcome to TIC TAC TOE game!" << std::endl;
    initialize_board();
    print_board();
}

std::string get_board_as_string() {
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

char get_cell(int cell_num) {
    int x = (cell_num - 1) / 3;
    int y = (cell_num - 1) % 3;
    return board[x][y];
}

char get_cell(int i, int j) {
    return board[i][j];
}


bool cell_is_not_empty(int cell) {
    int x = (cell - 1) / 3;
    int y = (cell - 1) % 3;
    if(get_cell(x, y) == 'X' || get_cell(x, y) == 'O') {
        return false;
    }
    return true;
}


bool make_move(int cell_num, char marker) {
    int x = (cell_num - 1) / 3;
    int y = (cell_num - 1) % 3;
    if (x < 0 ||  x > 2 || y < 0 ||  y > 2 || !cell_is_not_empty(cell_num)) {
        return false;
    }

    board[x][y] = marker;
    return true;
}


bool check_diagonal_win() {
    int size = 0;
    for (int i = 0; i < 2; ++i) {
        if (get_cell(i, i) == get_cell(i + 1, i + 1)) {
            ++size;
        }
    }

    if (size == 2) {
        return true;
    }
    return false;
}

bool check_anti_diagonal_win() {
    int size = 0;
    for (int i = 0; i < 3; ++i) {
        int j = 3 - i - 1;
        if (get_cell(j, i) == get_cell(2, 0)) {
            ++size;
        }
    }

    if (size == 3) {
        return true;
    }
    return false;
}

bool check_row_win(int row) {
    int size = 0;
    for (int i = 0; i < 2; ++i) {
        if (get_cell(row, i) == get_cell(row, i + 1)) {
            ++size;
        }
    }

    if (size == 2) {
        return true;
    }
    return false;
}

bool check_column_win(int col) {
    int size = 0;
    for (int i = 0; i < 2; ++i) {
        if (get_cell(i, col) == get_cell(i + 1, col)) {
            ++size;
        }
    }

    if (size == 2) {
        return true;
    }
    return false;
}



std::pair<bool, std::string> game_over(char turn, int cell_num) {
    bool win = false;
    std::string res = "";
    if (check_diagonal_win()) {
        if (turn == 'X') {
           // print_board();
            res = "Diagonal win of X: Congrats!";
            win = true;
        } else {
           // print_board();
            res = "Diagonal win of O: Congrats!";
            win = true;
        }
    }

    if (check_anti_diagonal_win()) {
        if (turn = 'X') {
           // print_board();
            res = "Antidiagonal win of X: Congrats!";
            win = true;
        } else {
           // print_board();
            res = "Antidiagonal win of O: Congrats!";
            win = true;
       }
    }

    if (check_row_win((cell_num - 1) / 3)) {
        if (turn == 'X') {
            //print_board();
            res = "Row win of X: Congrats!";
            win = true;
        } else {
            //print_board();
            res = "Row win of O: Congrats!";
            win = true;
        }
    }

    if (check_column_win((cell_num - 1) % 3)) {
        if (turn == 'X') {
            //print_board();
            res = "Column win of X: Congrats!";
            win = true;
        } else {
            //print_board();
            res = "Column win of O: Congrats!";
            win = true;
        }
    }

    return {win, res};
}

std::pair<bool, std::string> game_over_none() {
    for (int i = 1; i <= 9; ++i) {
        if (cell_is_not_empty(i)) {
            return {false, ""};
        }
    }
    std::string res = "End: None has won!";

    //print_board();
    //std::cout << "End: None has won!" << std::endl;
    return {true, res};
}



void sending(int client_socket, const std::string& message) {
	send(client_socket, message.c_str(), 200, 0);
}

void send_result(int client_socket, char flag,  const std::string final) {
	if (flag) {
                sending(client_socket, final);
		std::cout << "true";
  //              return true;
        }
//	std::cout << "fal";
//	return false;
}

bool fl = false;
std::string final;

void client_handler(int client_socket, char XO, const std::string& turn, char& flag) {
	send_result(client_socket, flag,  final); // if someone win each thread will send the result to both clients

	int recav_call = 0; 
	std::string board = get_board_as_string(); // getting board as string
	board += turn; // also adding to board message the message who's turn it is now

	sending(client_socket, board); //each thread will send board to his client

	int cell_num; // the cell num that client will enter in his turn
        char buffer[1]; // keeps the cell num that client enter

	std::unique_lock<std::mutex> lock(myMutex); // locking enter of the one thread untill unlocking 
	
	if (recav_call == 0) {	
		recav_call++; // incrementing variable recieve_call such that if one thread already enter this if condition, the other thread do not enter, beacause server must receve message only from player who's turn it is now
		if (turn == "Your move cell num : " && XO == 'X') { // if it is X turn, recieve info from client X
                	recv(client_socket, buffer, 1, 0);
        	}

		if (turn == "Your move cell num : " && XO == 'O') { // if it is O turn, recieve info from client O
                        recv(client_socket, buffer, 1, 0);
                }

	

		cell_num = buffer[0] - '0'; // making cell_num string 
        	if (make_move(cell_num, XO)) { // making move => updating board, make_move function returns true if the move is accessable
            		if (game_over(XO, cell_num).first) { // checking for win
	         		final = get_board_as_string() + game_over(XO, cell_num).second; // saving the result of game in string final
	       			flag = 1; 

	      			 fl = true; // as only one thread executes this part, we indicate some flag: fl as true, so that then other thread using the being true of this flag fl make the flag for his thread also true, so flag: fl for other thread also be true, so that other thread also know that the game is over 
            		}

           		 if (game_over_none().first) { // cheking for nobody win
				flag = 1;

				fl = true;
				final = get_board_as_string() + game_over_none().second;
            	         }
   		}

	}
	

	if (fl) {
		std::cout << XO;
		flag = 1;
	}

	lock.unlock();

}

int main() {
    board_init();
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return -1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12364);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Failed to bind socket" << std::endl;
        return -1;
    }

    listen(server_socket, 2);
    std::cout << "Waiting for players to connect..." << std::endl;

    int client_socketX = accept(server_socket, NULL, NULL);
    int client_socketO = accept(server_socket, NULL, NULL);

    std::string turn = "Your move cell num : ";
    std::string empty = "";

    char flag = 0;
    int i = 0;
    while (true) {

    	std::cout << get_board_as_string();	
	std::thread th1(client_handler, client_socketX, 'X', turn, std::ref(flag));
	std::thread th2(client_handler, client_socketO, 'O', empty, std::ref(flag));

	th1.join();
	th2.join();


	if (flag && i == 1) {
		//std::cout << "meeeeeeeeeeee";
		flag = 0;
		break;
	}

	if (flag && i == 0) {
                ++i;
        }


	if (turn == "Your move cell num : ") {
                turn = "";
                empty = "Your move cell num : ";
        } else {
                turn = "Your move cell num : " ;
                empty = "";
        }


    }

    close(server_socket);

    return 0;
}
