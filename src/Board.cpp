#include "../include/Board.h"
#include <iostream>

Board::Board(bool isPlayerBoard) : isPlayerBoard(isPlayerBoard) {
    initialize();
}

Board::Board(const Board& other) : isPlayerBoard(other.isPlayerBoard) {
    // Kopiujemy siatkę
    grid = other.grid;
    
    // Tworzymy nowe statki na podstawie starych
    for (const auto& ship : other.ships) {
        std::unique_ptr<Ship> newShip;
        switch (ship->getSymbol()) {
            case 'C':
                newShip = std::make_unique<Carrier>();
                break;
            case 'B':
                newShip = std::make_unique<Battleship>();
                break;
            case 'D':
                newShip = std::make_unique<Destroyer>();
                break;
            case 'S':
                newShip = std::make_unique<Submarine>();
                break;
        }
        newShip->setPosition(ship->getStartX(), ship->getStartY(), ship->getIsHorizontal());
        ships.push_back(std::move(newShip));
    }
}

Board& Board::operator=(const Board& other) {
    if (this != &other) {
        isPlayerBoard = other.isPlayerBoard;
        grid = other.grid;
        ships.clear();
        
        // Tworzymy nowe statki na podstawie starych
        for (const auto& ship : other.ships) {
            std::unique_ptr<Ship> newShip;
            switch (ship->getSymbol()) {
                case 'C':
                    newShip = std::make_unique<Carrier>();
                    break;
                case 'B':
                    newShip = std::make_unique<Battleship>();
                    break;
                case 'D':
                    newShip = std::make_unique<Destroyer>();
                    break;
                case 'S':
                    newShip = std::make_unique<Submarine>();
                    break;
            }
            newShip->setPosition(ship->getStartX(), ship->getStartY(), ship->getIsHorizontal());
            ships.push_back(std::move(newShip));
        }
    }
    return *this;
}

void Board::initialize() {
    grid.resize(SIZE, std::vector<CellState>(SIZE, CellState::EMPTY));
    ships.clear();
}

bool Board::isValidPlacement(int startX, int startY, int length, bool isHorizontal) const {
    if (startX < 0 || startY < 0 || startX >= SIZE || startY >= SIZE) {
        return false;
    }

    if (isHorizontal) {
        if (startX + length > SIZE) return false;
        // Sprawdzamy czy miejsce jest puste i czy nie ma statków w sąsiedztwie
        for (int i = 0; i < length; ++i) {
            if (grid[startY][startX + i] != CellState::EMPTY) return false;
            // Sprawdzamy sąsiednie pola (góra, dół, lewo, prawo)
            if (startY > 0 && grid[startY - 1][startX + i] != CellState::EMPTY) return false;
            if (startY < SIZE - 1 && grid[startY + 1][startX + i] != CellState::EMPTY) return false;
        }
        // Sprawdzamy rogi
        if (startX > 0) {
            if (grid[startY][startX - 1] != CellState::EMPTY) return false;
            if (startY > 0 && grid[startY - 1][startX - 1] != CellState::EMPTY) return false;
            if (startY < SIZE - 1 && grid[startY + 1][startX - 1] != CellState::EMPTY) return false;
        }
        if (startX + length < SIZE) {
            if (grid[startY][startX + length] != CellState::EMPTY) return false;
            if (startY > 0 && grid[startY - 1][startX + length] != CellState::EMPTY) return false;
            if (startY < SIZE - 1 && grid[startY + 1][startX + length] != CellState::EMPTY) return false;
        }
    } else {
        if (startY + length > SIZE) return false;
        // Sprawdzamy czy miejsce jest puste i czy nie ma statków w sąsiedztwie
        for (int i = 0; i < length; ++i) {
            if (grid[startY + i][startX] != CellState::EMPTY) return false;
            // Sprawdzamy sąsiednie pola (góra, dół, lewo, prawo)
            if (startX > 0 && grid[startY + i][startX - 1] != CellState::EMPTY) return false;
            if (startX < SIZE - 1 && grid[startY + i][startX + 1] != CellState::EMPTY) return false;
        }
        // Sprawdzamy rogi
        if (startY > 0) {
            if (grid[startY - 1][startX] != CellState::EMPTY) return false;
            if (startX > 0 && grid[startY - 1][startX - 1] != CellState::EMPTY) return false;
            if (startX < SIZE - 1 && grid[startY - 1][startX + 1] != CellState::EMPTY) return false;
        }
        if (startY + length < SIZE) {
            if (grid[startY + length][startX] != CellState::EMPTY) return false;
            if (startX > 0 && grid[startY + length][startX - 1] != CellState::EMPTY) return false;
            if (startX < SIZE - 1 && grid[startY + length][startX + 1] != CellState::EMPTY) return false;
        }
    }
    return true;
}

bool Board::placeShip(std::unique_ptr<Ship> ship, int startX, int startY, bool isHorizontal) {
    if (!isValidPlacement(startX, startY, ship->getLength(), isHorizontal)) {
        return false;
    }

    ship->setPosition(startX, startY, isHorizontal);
    ships.push_back(std::move(ship));

    if (isHorizontal) {
        for (int i = 0; i < ships.back()->getLength(); ++i) {
            grid[startY][startX + i] = CellState::SHIP;
        }
    } else {
        for (int i = 0; i < ships.back()->getLength(); ++i) {
            grid[startY + i][startX] = CellState::SHIP;
        }
    }
    return true;
}

CellState Board::getCellState(int x, int y) const {
    return grid[y][x];
}

bool Board::isMoveValid(int x, int y) const {
    if (x < 0 || y < 0 || x >= SIZE || y >= SIZE) {
        return false;
    }
    return grid[y][x] == CellState::EMPTY || grid[y][x] == CellState::SHIP;
}

bool Board::applyMove(int x, int y) {
    if (!isMoveValid(x, y)) {
        return false;
    }

    if (grid[y][x] == CellState::SHIP) {
        grid[y][x] = CellState::HIT;
        // Update ship hits
        for (const auto& ship : ships) {
            if (ship->getIsHorizontal()) {
                if (y == ship->getStartY() && x >= ship->getStartX() && 
                    x < ship->getStartX() + ship->getLength()) {
                    ship->hit();
                }
            } else {
                if (x == ship->getStartX() && y >= ship->getStartY() && 
                    y < ship->getStartY() + ship->getLength()) {
                    ship->hit();
                }
            }
        }
        return true;
    } else if (grid[y][x] == CellState::EMPTY) {
        grid[y][x] = CellState::MISS;
        return true;
    }
    return false;
}

bool Board::makeMove(int x, int y) {
    return applyMove(x, y);
}

void Board::display() const {
    std::cout << "  ";
    for (int i = 0; i < SIZE; ++i) {
        if (isPlayerBoard) {
            std::cout << static_cast<char>('A' + i) << " ";
        } else {
            std::cout << (i + 1) << " ";
        }
    }
    std::cout << "\n";

    for (int y = 0; y < SIZE; ++y) {
        if (isPlayerBoard) {
            std::cout << (y + 1) << " ";
        } else {
            std::cout << static_cast<char>('A' + y) << " ";
        }
        for (int x = 0; x < SIZE; ++x) {
            switch (grid[y][x]) {
                case CellState::EMPTY:
                    std::cout << ". ";
                    break;
                case CellState::SHIP:
                    if (isPlayerBoard) {
                        for (const auto& ship : ships) {
                            if (ship->getIsHorizontal()) {
                                if (y == ship->getStartY() && x >= ship->getStartX() && 
                                    x < ship->getStartX() + ship->getLength()) {
                                    std::cout << ship->getSymbol() << " ";
                                    break;
                                }
                            } else {
                                if (x == ship->getStartX() && y >= ship->getStartY() && 
                                    y < ship->getStartY() + ship->getLength()) {
                                    std::cout << ship->getSymbol() << " ";
                                    break;
                                }
                            }
                        }
                    } else {
                        std::cout << ". ";
                    }
                    break;
                case CellState::HIT:
                    std::cout << "X ";
                    break;
                case CellState::MISS:
                    std::cout << "O ";
                    break;
            }
        }
        std::cout << "\n";
    }
}

bool Board::isGameOver() const {
    for (const auto& ship : ships) {
        if (!ship->isSunk()) {
            return false;
        }
    }
    return true;
}

std::string Board::getCoordinateString(int x, int y) const {
    if (isPlayerBoard) {
        return std::string(1, static_cast<char>('A' + x)) + std::to_string(y + 1);
    } else {
        return std::to_string(x + 1) + std::string(1, static_cast<char>('A' + y));
    }
}

const std::vector<std::unique_ptr<Ship>>& Board::getShips() const {
    return ships;
} 