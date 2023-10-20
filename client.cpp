#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <mutex>

std::mutex m;

void sending(int client_socket) {
      int cell_num;
      std::cin >> cell_num;

      char move[1] = { static_cast<char>(cell_num + '0')};
      send(client_socket, move, 1, 0);
}


char rec(int client_socket) {
	char buffer[1000];
	recv(client_socket, buffer, sizeof(buffer), 0);	
	bool flag = false;
	if (buffer[153] != 'P' && buffer[153] != 'D' && buffer[153] != 'A' && buffer[153] != 'R' && buffer[153] != 'C') {
		flag = true;
	}
	if (flag) {
		flag = false;
		std::cout << "The opponents turn, please wait for your turn\n";
	} 

	std::cout << buffer;

	if (strncmp(buffer + 153, "Diagonal win of X: Congrats!", 29) == 0) {
                return '*';

	} else if (strncmp(buffer + 153, "Diagonal win of O: Congrats!", 29) == 0) {

                return '*';

	} else if (strncmp(buffer + 153, "Antidiagonal win of X: Congrats!", 33) == 0) {
		return '*';

        } else if (strncmp(buffer + 153, "Antidiagonal win of O: Congrats!", 33) == 0) {
                return '*';

        } else if (strncmp(buffer + 153, "Row win of X: Congrats!", 23) == 0) {
                return '*';

        } else if (strncmp(buffer + 153, "Row win of O: Congrats!", 23) == 0) {
                return '*';

        } else if (strncmp(buffer + 153, "Column win of X: Congrats!", 26) == 0) {
        	return '*';

	} else if (strncmp(buffer + 153, "Column win of O: Congrats!", 26) == 0) {
		return '*';
        }

	return buffer[175];
}


int main() {
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return -1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12362);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(client_socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Failed to connect to the server" << std::endl;
        return -1;
    }


    while (true) {
            char res = rec(client_socket);

	    if (res == ':') {
		sending(client_socket);
	    }
	    else if (res == '*') {
			break;
	    }
    }

    close(client_socket);

    return 0;
}
