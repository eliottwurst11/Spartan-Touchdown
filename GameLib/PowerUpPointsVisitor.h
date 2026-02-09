/**
 * @file PowerUpPointsVisitor.h
 * @author Beckham Lee
 *
 * Holds the class that visits the points powerup
 */

#ifndef GAME_POWERUPPOINTSVISITOR_H
#define GAME_POWERUPPOINTSVISITOR_H

#include "Item.h"
#include "ItemVisitor.h"
#include "PowerUpPoints.h"

/**
 * Visitor for a PowerUpPoints object
 */
class PowerUpPointsVisitor : public ItemVisitor {
private:
    /// the football we are matching the hit to the coin with
    std::shared_ptr<Football> mFootball;

    /// the points powerup collected
    PowerUpPoints* mPowerUpPoints = nullptr;

public:
    /**
     * Constructor
     * @param football The football to pass to the visitor
     */
    PowerUpPointsVisitor(std::shared_ptr<Football> football) : mFootball(std::move(football)) {}

    /**
     * Getter for the points powerup
     * @return pointer to the points power up
     */
    PowerUpPoints* GetPowerUpPoints() const { return mPowerUpPoints; }

    void VisitPowerUpPoints(PowerUpPoints* powerUpPoints) override;

};


#endif //GAME_POWERUPPOINTSVISITOR_H