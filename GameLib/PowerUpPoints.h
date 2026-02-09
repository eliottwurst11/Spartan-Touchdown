/**
 * @file PowerUpPoints.h
 * @author Eliott Wurst
 *
 * Points powerup class definition as a child of PowerUp
 */

#ifndef GAME_POWERUPPOINTS_H
#define GAME_POWERUPPOINTS_H

#include "PowerUp.h"

/**
 * Points power up that doubles point values when consumed
 */
class PowerUpPoints : public PowerUp {
private:
public:

    PowerUpPoints(Level *level, double initX, double initY, std::wstring id);

    /// disable the default constructor
    PowerUpPoints() = delete;

    /**
     * Disable copy constructor
     * @param other power up
     */
    PowerUpPoints(const PowerUp& other) = delete;

    /**
     * Disable assignment operator
     * @param other
     */
    void operator=(const PowerUp& other) = delete;

    /**
     * accept an item visitor to visit this powerup
     * @param visitor  item visitor to accept
     */
    void Accept(ItemVisitor *visitor) override { visitor->VisitPowerUpPoints(this); }
};


#endif //GAME_POWERUPPOINTS_H