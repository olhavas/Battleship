#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Ship.h"

enum class CellState {
    EMPTY,
    SHIP,
    HIT,
    MISS
};

class Board {
private:
    static const int SIZE = 10;
    std::vector<std::vector<CellState>> grid;
    std::vector<std::unique_ptr<Ship>> ships;
    bool isPlayerBoard;

public:
    Board(bool isPlayerBoard);
    Board(const Board& other);
    Board& operator=(const Board& other);
    void initialize();
    bool placeShip(std::unique_ptr<Ship> ship, int startX, int startY, bool isHorizontal);
    bool isValidPlacement(int startX, int startY, int length, bool isHorizontal) const;
    CellState getCellState(int x, int y) const;
    bool makeMove(int x, int y);
    void display() const;
    bool isGameOver() const;
    std::string getCoordinateString(int x, int y) const;
    const std::vector<std::unique_ptr<Ship>>& getShips() const;
    bool isMoveValid(int x, int y) const;
    bool applyMove(int x, int y);
}; 