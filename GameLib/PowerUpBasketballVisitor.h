/**
 * @file PowerUpBasketballVisitor.h
 * @author Beckham Lee
 *
 * Definition for a visitor of PowerUpBasketball objects
 */

#ifndef GAME_POWERUPBASKETBALLVISITOR_H
#define GAME_POWERUPBASKETBALLVISITOR_H


#include "Item.h"
#include "ItemVisitor.h"
#include "PowerUpBasketball.h"

/**
 * Visitor for a PowerUpBasketball object
 */
class PowerUpBasketballVisitor : public ItemVisitor {
private:
    /// the football we are matching the hit to the coin with
    std::shared_ptr<Football> mFootball;

    /// the points powerup collected
    PowerUpBasketball* mPowerUpBasketball = nullptr;

public:
    /**
     * Constructor
     * @param football The football to pass to the visitor
     */
    PowerUpBasketballVisitor(std::shared_ptr<Football> football) : mFootball(std::move(football)) {}

    /**
     * Getter for the basketball powerup
     * @return pointer to the points power up
     */
    PowerUpBasketball* GetPowerUpBasketball() const { return mPowerUpBasketball; }

    void VisitPowerUpBasketball(PowerUpBasketball* powerUpBasketball) override;

};


#endif //GAME_POWERUPBASKETBALLVISITOR_H