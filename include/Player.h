#pragma once
#include "Board.h"
#include "ShipFactory.h"
#include <string>
#include <memory>

class Player {
private:
    std::string name;
    Board playerBoard;
    Board opponentBoard;
    std::unique_ptr<IShipFactory> shipFactory;

public:
    Player(const std::string& playerName, std::unique_ptr<IShipFactory> factory);
    void setupBoard();
    bool makeMove(int x, int y, const Player& opponent) const;
    void displayBoards() const;
    bool hasWon() const;
    const Board& getPlayerBoard() const;
    const Board& getOpponentBoard() const;
    const std::string& getName() const { return name; }
}; 