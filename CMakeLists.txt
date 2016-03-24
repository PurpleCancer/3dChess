cmake_minimum_required(VERSION 3.4)
project(3dChess)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Game.cpp Game.h Player.cpp Player.h Piece.cpp Piece.h Board.cpp Board.h Delarations.h)
add_executable(3dChess ${SOURCE_FILES})