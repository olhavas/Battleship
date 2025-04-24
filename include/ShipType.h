#pragma once
#include <string>

enum class ShipType {
    CARRIER,
    BATTLESHIP,
    DESTROYER,
    SUBMARINE
};

struct ShipInfo {
    ShipType type;
    std::string name;
    int length;
    int count;
};

const ShipInfo SHIP_TYPES[] = {
    {ShipType::CARRIER, "Carrier", 5, 1},
    {ShipType::BATTLESHIP, "Battleship", 4, 1},
    {ShipType::DESTROYER, "Destroyer", 2, 1},
    {ShipType::SUBMARINE, "Submarine", 3, 1}
}; 