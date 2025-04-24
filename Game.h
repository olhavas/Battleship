#pragma once
#include "Player.h"
#include "ShipFactory.h"
#include <memory>

class Game {
private:
    std::unique_ptr<Player> player1;
    std::unique_ptr<Player> player2;
    bool isPlayer1Turn;
    std::unique_ptr<IShipFactory> shipFactory;

public:
    Game();
    void start();
    void playTurn();
    bool isGameOver() const;
    void displayWinner() const;
}; 