#pragma once
#include "Ship.h"
#include <memory>

class IShipFactory {
public:
    virtual ~IShipFactory() = default;
    virtual std::unique_ptr<Ship> createCarrier() = 0;
    virtual std::unique_ptr<Ship> createBattleship() = 0;
    virtual std::unique_ptr<Ship> createDestroyer() = 0;
    virtual std::unique_ptr<Ship> createSubmarine() = 0;
};

class ShipFactory : public IShipFactory {
public:
    std::unique_ptr<Ship> createCarrier() override {
        return std::make_unique<Carrier>();
    }

    std::unique_ptr<Ship> createBattleship() override {
        return std::make_unique<Battleship>();
    }

    std::unique_ptr<Ship> createDestroyer() override {
        return std::make_unique<Destroyer>();
    }

    std::unique_ptr<Ship> createSubmarine() override {
        return std::make_unique<Submarine>();
    }
}; 