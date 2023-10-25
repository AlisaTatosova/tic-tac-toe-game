#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>


void sending(int client_socket) {
    int cell_num;
    std::cin >> cell_num;
    std::cout << std::endl;
    char move[1] = { static_cast<char>(cell_num + '0')};
    send(client_socket, move, 1, 0);
}


char recieving(int client_socket) {
    char buffer[300];
    recv(client_socket, buffer, sizeof(buffer), 0);  
    system("clear");
    bool flag = false;
    std::cout << buffer;
    if (buffer[197] == ':') {
         sending(client_socket);
         return ' ';
    } else if (buffer[153] == 'I') {
	 sending(client_socket);
         return ' ';
    } else {
	std::cout << std::endl;
    }
    
    if (strncmp(buffer + 153, "Diagonal win of X", 17) == 0) {
  	return '*';
    } else if (strncmp(buffer + 153, "Diagonal win of O", 17) == 0) {
	return '*';
    } else if (strncmp(buffer + 153, "Antidiagonal win of X", 21) == 0) {
    	return '*';
    } else if (strncmp(buffer + 153, "Antidiagonal win of O", 21) == 0) {
        return '*';
    } else if (strncmp(buffer + 153, "Row win of X", 12) == 0) {
        return '*';
    } else if (strncmp(buffer + 153, "Row win of O", 12) == 0) {
        return '*';
    } else if (strncmp(buffer + 153, "Column win of X", 15) == 0) {
        return '*';
    } else if (strncmp(buffer + 153, "Column win of O", 15) == 0) {
        return '*';
    } else if (strncmp(buffer + 153, "End: None has won!", 18) == 0) {
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

    sockaddr_in server_address;;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(11302);
    server_address.sin_addr.s_addr = inet_addr("10.0.2.15");

    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        std::cerr << "Failed to connect to the server" << std::endl;
        return -1;
    }


    while (true) {
      char res = recieving(client_socket);

      if (res == ':') {
          sending(client_socket);
	  system("clear");
      } else if (res == '*') {
          break;
      } 

    }

    close(client_socket);

    return 0;
}
