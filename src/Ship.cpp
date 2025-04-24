#include "../include/Ship.h"

Ship::Ship(const std::string& name, int length)
    : name(name), length(length), hits(0), startX(0), startY(0), isHorizontal(true) {}

void Ship::setPosition(int x, int y, bool horizontal) {
    startX = x;
    startY = y;
    isHorizontal = horizontal;
}

Carrier::Carrier() : Ship("Carrier", 5) {}

Battleship::Battleship() : Ship("Battleship", 4) {}

Destroyer::Destroyer() : Ship("Destroyer", 2) {}

Submarine::Submarine() : Ship("Submarine", 3) {} 