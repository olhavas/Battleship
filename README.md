# Battleship Game

A C++ implementation of the classic Battleship game, following SOLID principles and Object-Oriented Design patterns.

## Features

- Two-player gameplay
- Different ship types (Carrier, Battleship, Destroyer, Submarine)
- Interactive board display
- Input validation for moves and ship placement
- Ships cannot be placed adjacent to each other
- Clear game state tracking

## Ship Types

- Carrier (C): 5 cells
- Battleship (B): 4 cells
- Destroyer (D): 3 cells
- Submarine (S): 2 cells

## Game Rules

1. Each player places their ships on their board
2. Players take turns guessing coordinates to attack
3. Hits are marked with 'X', misses with 'O'
4. The game ends when all of one player's ships are sunk

## Building the Game

### Prerequisites

- CMake (version 3.10 or higher)
- C++ compiler with C++17 support

### Build Instructions

1. Create a build directory:
```bash
mkdir build
cd build
```

2. Generate build files:
```bash
cmake ..
```

3. Build the project:
```bash
cmake --build .
```

## Running the Game

After building, run the executable:
```bash
./Battleship
```

## Project Structure

- `main.cpp`: Entry point of the application
- `Game.h/cpp`: Main game logic and flow
- `Board.h/cpp`: Board management and ship placement
- `Player.h/cpp`: Player actions and state
- `Ship.h/cpp`: Base ship class
- `ShipType.h`: Ship type definitions
- `ShipFactory.h`: Factory for creating different ship types

## Design Principles

This project follows SOLID principles:
- Single Responsibility Principle
- Open/Closed Principle
- Liskov Substitution Principle
- Interface Segregation Principle
- Dependency Inversion Principle

## License

This project is open source and available under the MIT License. 