cmake_minimum_required(VERSION 3.10)
project(Battleship VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define source and header files
set(SOURCES
    src/main.cpp
    src/Board.cpp
    src/Game.cpp
    src/Player.cpp
    src/Ship.cpp
)

set(HEADERS
    include/Board.h
    include/Game.h
    include/Player.h
    include/Ship.h
    include/ShipType.h
    include/ShipFactory.h
)

# Create executable
add_executable(Battleship ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(Battleship PRIVATE include)

# Set output directories
set_target_properties(Battleship PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
