cmake_minimum_required(VERSION 3.10)
project(Battleship)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(battleship
    main.cpp
    Board.cpp
    Player.cpp
    Game.cpp
    Ship.cpp
    Ship.h
    ShipFactory.h
)
