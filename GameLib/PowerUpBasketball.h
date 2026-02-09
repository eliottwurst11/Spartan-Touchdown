/**
 * @file PowerUpBasketball.h
 * @author Nishit Nagpal
 *
 * Basketball transformation powerup as a child of PowerUp
 */

#ifndef GAME_POWERUPBASKETBALL_H
#define GAME_POWERUPBASKETBALL_H

#include "PowerUp.h"

/**
 * Power up that transforms the football into a basketball for a limited time
 */
class PowerUpBasketball : public PowerUp
{
private:
    /// keeps track of time left for the powerup before it expires, in seconds, set to 15
    double mSecondsRemaining = 15;

public:

    PowerUpBasketball(Level *level, double initX, double initY, std::wstring id);

    /// disable the default constructor
    PowerUpBasketball() = delete;

    /// disable the copy constructor
    PowerUpBasketball(const PowerUpBasketball &) = delete;

    /// disable assignment operator
    void operator=(const PowerUpBasketball &) = delete;

    void Update(double elapsed) override;
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Accept the ItemVisitor
     * @param visitor Visitor to accept
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitPowerUpBasketball(this); }
};

#endif //GAME_POWERUPBASKETBALL_H
