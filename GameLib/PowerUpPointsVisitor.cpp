/**
 * @file PowerUpPointsVisitor.cpp
 * @author Beckham Lee
 */

#include "pch.h"
#include "PowerUpPointsVisitor.h"
#include "Football.h"

/**
 * visit the point powerup object and check for the football collision
 * @param powerUpPoints the powerup object to visit
 */
void PowerUpPointsVisitor::VisitPowerUpPoints(PowerUpPoints* powerUpPoints)
{
    if (powerUpPoints->HitTest(mFootball.get()))
    {
        mPowerUpPoints = powerUpPoints;
    }
}
