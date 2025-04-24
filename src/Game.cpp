#include "../include/Game.h"
#include <iostream>

Game::Game() : isPlayer1Turn(true) {
    shipFactory = std::make_unique<ShipFactory>();
    player1 = std::make_unique<Player>("Player 1", std::make_unique<ShipFactory>());
    player2 = std::make_unique<Player>("Player 2", std::make_unique<ShipFactory>());
}

void Game::start() {
    std::cout << "Welcome to Battleship!\n";
    
    // Setup phase
    player1->setupBoard();
    player2->setupBoard();
    
    // Game loop
    while (!isGameOver()) {
        playTurn();
        isPlayer1Turn = !isPlayer1Turn;
    }
    
    displayWinner();
}

void Game::playTurn() {
    const Player& currentPlayer = isPlayer1Turn ? *player1 : *player2;
    const Player& opponent = isPlayer1Turn ? *player2 : *player1;
    
    currentPlayer.displayBoards();
    
    std::cout << currentPlayer.getName() << "'s turn.\n";
    std::cout << "Enter target coordinates (e.g., A1): ";
    
    std::string pos;
    std::cin >> pos;
    
    int x = toupper(pos[0]) - 'A';
    int y = std::stoi(pos.substr(1)) - 1;
    
    bool hit = currentPlayer.makeMove(x, y, opponent);
    
    if (hit) {
        std::cout << "Hit!\n";
    } else {
        std::cout << "Miss!\n";
    }
}

bool Game::isGameOver() const {
    return player1->hasWon() || player2->hasWon();
}

void Game::displayWinner() const {
    if (player1->hasWon()) {
        std::cout << "Player 1 wins!\n";
    } else {
        std::cout << "Player 2 wins!\n";
    }
} 