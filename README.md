# tic-tac-toe-game
This is a implementation of the classic game of Tic-Tac-Toe in C++. The game consists of a server and two client components, allowing two players to play Tic-Tac-Toe over a network connection through server.

# Files
* server.cpp: This file contains the code for the server side of the game. The server manages the game state, waits for two client connections, and facilitates the gameplay.
* client.cpp: This file contains the code for the client side of the game. The client connects to the server and interacts with the game by sending and receiving game moves. Two clients are used to represent the two players.
* board.cpp: This file defines the Board class, which represents the game board. It includes methods to display the current board state.
* players.cpp: This file defines the Player class, which represents the players of the game. It includes methods to handle player moves and determine the winner.
* gameover.cpp: This file contains code related to the end of the game. It checks if there is a winner, a draw, or if the game is still ongoing.
* tictactoe.cpp: This is the main file that contains the entry point of the game. It sets up the server and two clients, handles player turns, and controls the flow of the game.

# How to Play

*Compile the server and client files using your C++ compiler. For example:

```cpp
g++ server.cpp -o server
g++ client.cpp -o client

* Start the server by running server on one machine. The server will listen for two incoming client connections.
* Start two clients on separate machines by running client.
* Players take turns to make their moves.
* The game continues until one of the players wins or the game ends in a draw.

# Rules
* The game is played on a 3x3 grid.
* Players take turns to place their symbol (X or O) on the grid.
* If the grid is filled, and no player has won, the game ends in a draw.

# Example Usage
* Start the server on one machine: ./server
* Start two clients on separate machines: ./client
* Follow the prompts to make your moves.
