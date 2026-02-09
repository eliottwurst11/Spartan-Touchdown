/**
 * @file PowerUpDoubleJumpVisitor.h
 * @author Beckham Lee
 *
 * Definition for a visitor of PowerUpDoubleJump objects
 */

#ifndef GAME_POWERUPDOUBLEJUMPVISITOR_H
#define GAME_POWERUPDOUBLEJUMPVISITOR_H

#include "Item.h"
#include "ItemVisitor.h"
#include "PowerUpDoubleJump.h"

/**
 * Visitor for a PowerUpDoubleJump object
 */
class PowerUpDoubleJumpVisitor : public ItemVisitor {
private:
    /// the football we are matching the hit to the coin with
    std::shared_ptr<Football> mFootball;

    /// the points powerup collected
    PowerUpDoubleJump* mPowerUpDoubleJump = nullptr;

public:
    /**
     * Constructor
     * @param football The football to pass to the visitor
     */
    PowerUpDoubleJumpVisitor(std::shared_ptr<Football> football) : mFootball(std::move(football)) {}

    /**
     * Getter for the double jump powerup
     * @return pointer to the points power up
     */
    PowerUpDoubleJump* GetPowerUpDoubleJump() const { return mPowerUpDoubleJump; }

    void VisitPowerUpDoubleJump(PowerUpDoubleJump* powerUpDoubleJump) override;

};


#endif //GAME_POWERUPDOUBLEJUMPVISITOR_H