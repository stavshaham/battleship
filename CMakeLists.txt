cmake_minimum_required(VERSION 4.3)
project(battleship)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(battleship
        main.cpp
        Board.cpp
        Board.h
        CellType.h
        Orientation.h
)
