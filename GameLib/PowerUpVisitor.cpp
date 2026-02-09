/**
 * @file PowerUpVisitor.cpp
 * @author Nishit Nagpal
 */

#include "pch.h"
#include "PowerUpVisitor.h"
#include "PowerUp.h"
#include "Football.h"
#include "Item.h"

/**
 * Constructor
 * @param football The football to check for collisions
 */
PowerUpVisitor::PowerUpVisitor(Football* football) : mFootball(football)
{
}

/**
 * Visit a power-up
 * @param powerUp The power-up to visit
 */
void PowerUpVisitor::VisitPowerUp(PowerUp* powerUp)
{
    // Only check collision if we haven't found a power-up yet and this one isn't consumed
    if (mPowerUp == nullptr && !powerUp->IsConsumed()) {
        // Check if the football collides with this power-up using the base class HitTest method
        if (mFootball->Item::HitTest(powerUp)) {
            mPowerUp = powerUp;
        }
    }
}
