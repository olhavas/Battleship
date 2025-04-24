#pragma once
#include <string>

class Ship {
protected:
    std::string name;
    int length;
    int hits;
    int startX;
    int startY;
    bool isHorizontal;

public:
    Ship(const std::string& name, int length);
    virtual ~Ship() = default;

    // Getters
    const std::string& getName() const { return name; }
    int getLength() const { return length; }
    int getHits() const { return hits; }
    bool isSunk() const { return hits >= length; }
    bool getIsHorizontal() const { return isHorizontal; }
    int getStartX() const { return startX; }
    int getStartY() const { return startY; }

    // Setters
    void setPosition(int x, int y, bool horizontal);
    void hit() { hits++; }

    // Virtual methods
    virtual char getSymbol() const = 0;
    virtual std::string getDescription() const = 0;
};

class Carrier : public Ship {
public:
    Carrier();
    char getSymbol() const override { return 'C'; }
    std::string getDescription() const override { return "Aircraft Carrier"; }
};

class Battleship : public Ship {
public:
    Battleship();
    char getSymbol() const override { return 'B'; }
    std::string getDescription() const override { return "Battleship"; }
};

class Destroyer : public Ship {
public:
    Destroyer();
    char getSymbol() const override { return 'D'; }
    std::string getDescription() const override { return "Destroyer"; }
};

class Submarine : public Ship {
public:
    Submarine();
    char getSymbol() const override { return 'S'; }
    std::string getDescription() const override { return "Submarine"; }
}; 