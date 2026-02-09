/**
 * @file PowerUpDoubleJump.h
 * @author Eliott Wurst
 *
 * Timed double jump powerup as a child of PowerUp
 */

#ifndef GAME_POWERUPDOUBLEJUMP_H
#define GAME_POWERUPDOUBLEJUMP_H

#include "PowerUp.h"

/**
 * Power up that allows the football to double jump for a limited period of time after consumption
 */
class PowerUpDoubleJump : public PowerUp
{
private:
    /// keeps track of time left for the powerup before it expires, in seconds, set to 15
    double mSecondsRemaining = 15;

public:

    PowerUpDoubleJump(Level *level, double initX, double initY, std::wstring id);

    /// disable the default constructor
    PowerUpDoubleJump() = delete;

    /// disable the copy constructor
    PowerUpDoubleJump(const PowerUpDoubleJump &) = delete;

    /// disable assignment operator
    void operator=(const PowerUpDoubleJump &) = delete;

    void Update(double elapsed) override;
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Accept an ItemVisitor
     * @param visitor item visitor to accept
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitPowerUpDoubleJump(this); }

};


#endif //GAME_POWERUPDOUBLEJUMP_H