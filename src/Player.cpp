#include "../include/Player.h"
#include <iostream>
#include "Ship.h"

Player::Player(const std::string& playerName, std::unique_ptr<IShipFactory> factory)
    : name(playerName), playerBoard(true), opponentBoard(false), 
      shipFactory(std::move(factory)) {}

void Player::setupBoard() {
    std::cout << name << ", please set up your ships.\n";
    
    // Create ships using factory
    std::vector<std::unique_ptr<Ship>> ships;
    ships.push_back(shipFactory->createCarrier());
    ships.push_back(shipFactory->createBattleship());
    ships.push_back(shipFactory->createDestroyer());
    ships.push_back(shipFactory->createSubmarine());
    
    for (auto& ship : ships) {
        bool placed = false;
        while (!placed) {
            playerBoard.display();
            std::cout << "Place " << ship->getDescription() << " (length: " << ship->getLength() << ")\n";
            
            int x, y;
            char direction;
            std::cout << "Enter starting position (e.g., A1): ";
            std::string pos;
            std::cin >> pos;
            
            x = toupper(pos[0]) - 'A';
            y = std::stoi(pos.substr(1)) - 1;
            
            std::cout << "Enter direction (H for horizontal, V for vertical): ";
            std::cin >> direction;
            
            placed = playerBoard.placeShip(std::move(ship), x, y, 
                                         toupper(direction) == 'H');
            
            if (!placed) {
                std::cout << "Invalid placement. Try again.\n";
            }
        }
    }
}

bool Player::makeMove(int x, int y, const Player& opponent) const {
    // Since we can't modify the opponent's board directly (it's const),
    // we need to create a non-const copy of the board to make the move
    Board tempBoard = opponent.getPlayerBoard();
    return tempBoard.makeMove(x, y);
}

void Player::displayBoards() const {
    std::cout << "\n" << name << "'s boards:\n";
    std::cout << "Your board:\n";
    playerBoard.display();
    std::cout << "\nOpponent's board:\n";
    opponentBoard.display();
}

bool Player::hasWon() const {
    return opponentBoard.isGameOver();
}

const Board& Player::getPlayerBoard() const {
    return playerBoard;
}

const Board& Player::getOpponentBoard() const {
    return opponentBoard;
} 