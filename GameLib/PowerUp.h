/**
 * @file PowerUp.h
 * @author Matthew Lopez
 *
 * Class for a powerup
 */

#ifndef GAME_POWERUP_H
#define GAME_POWERUP_H

#include "Item.h"
#include "Declaration.h"
#include "ItemVisitor.h"

/**
 * Base class for a powerup
 */
class PowerUp : public Item {
private:
    /// boolean indicating if the powerup has been consumed yet
    /// set this to TRUE when the football collides with the object
    bool mIsConsumed = false;

    /// Is the powerup currently falling off the screen?
    bool mIsFalling = false;

    /// Vertical speed when falling (pixels per second)
    const double FallingSpeed = 1000.0;

public:

    PowerUp(Level *level, double initX, double initY, std::wstring id);

    /// disable the default constructor
    PowerUp() = delete;

    /// disable the copy constructor
    PowerUp(const PowerUp &) = delete;

    /// disable assignment operator
    void operator=(const PowerUp &) = delete;

    void Update(double elapsed) override;

    void Accept(ItemVisitor* visitor) override = 0;

    /**
     * Consume the item (use this instead of a setter)
     */
    void ConsumePowerUp() { mIsConsumed = true; }

    /**
     * Check if the powerup has been consumed
     * @return true if powerup has been consumed
     */
    bool IsConsumed() const { return mIsConsumed; }

    /**
     * Get the type of powerup
     * @return string identifying the powerup type
     */
    virtual std::string GetPowerUpType() const { return "PowerUp"; }

    /**
     * Check if the powerup is currently in its falling state.
     * @return true if falling.
     */
    bool IsFalling() const { return mIsFalling; }

    /**
     * Start the falling animation for this powerup.
     * Sets the internal state to begin moving downwards in the Update method.
     */
    void StartFalling();

};


#endif //GAME_POWERUP_H