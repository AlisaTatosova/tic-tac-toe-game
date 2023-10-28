cmake_minimum_required(VERSION 3.10)
project(tictac)

set(CMAKE_CXX_STANDARD 17)

add_executable(server server.cpp board.cpp gameover.cpp players.cpp main.cpp)
add_executable(client client.cpp)

target_compile_options(server PRIVATE -O2 -march=native)

target_link_libraries(server PRIVATE pthread)
