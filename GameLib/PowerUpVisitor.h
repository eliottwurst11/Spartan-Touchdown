/**
 * @file PowerUpVisitor.h
 * @author Nishit Nagpal
 *
 * Visitor to find power-ups that collide with the football
 */

#ifndef GAME_POWERUPVISITOR_H
#define GAME_POWERUPVISITOR_H

#include "ItemVisitor.h"

class PowerUp;
class Football;

/**
 * Visitor to find power-ups that collide with the football
 */
class PowerUpVisitor : public ItemVisitor {
private:
    /// The football we are checking for collisions
    class Football* mFootball;
    
    /// The power-up that was hit (nullptr if none)
    PowerUp* mPowerUp = nullptr;

public:
    /**
     * Constructor
     * @param football The football to check for collisions
     */
    PowerUpVisitor(Football* football);

    /**
     * Visit a power-up
     * @param powerUp The power-up to visit
     */
    void VisitPowerUp(PowerUp* powerUp) override;

    /**
     * Get the power-up that was hit
     * @return Pointer to the power-up that was hit, or nullptr if none
     */
    PowerUp* GetPowerUp() const { return mPowerUp; }
};

#endif //GAME_POWERUPVISITOR_H
