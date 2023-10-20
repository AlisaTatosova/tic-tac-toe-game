#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <mutex>

std::mutex m;

void sending(int clientSocket) {
      int cell_num;
        std::cin >> cell_num;

        char move[1] = { static_cast<char>(cell_num + '0')};
        send(clientSocket, move, 1, 0);
}


char rec(int clientSocket) {
	char buffer[1000];
	recv(clientSocket, buffer, sizeof(buffer), 0);	
	bool flag = false;
	if (buffer[153] != 'P' && buffer[153] != 'D' && buffer[153] != 'A' && buffer[153] != 'R' && buffer[153] != 'C') {
	//	std::cout << "flag";
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

//void sending(int clientSocket) {
//	int cell_num;
//        std::cin >> cell_num;

//        char move[1] = { static_cast<char>(cell_num + '0')};
//        send(clientSocket, move, 1, 0);

//}

int main() {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return -1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12362);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Failed to connect to the server" << std::endl;
        return -1;
    }

//    char buffer[174];

    while (true) {
        //recv(clientSocket, buffer, sizeof(buffer), 0);
        //std::cout << buffer;
	    //std::thread th1(rec, clientSocket);
            char res = rec(clientSocket);

	   // std::cout << res;  
	    if (res == ':') {
		sending(clientSocket);
	    }
	    else if (res == '*') {
			break;
	    }
    }

    close(clientSocket);

    return 0;
}
