/**
 * @file PowerUpBasketballVisitor.cpp
 * @author Beckham Lee
 */

#include "pch.h"
#include "PowerUpBasketballVisitor.h"
#include "Football.h"

/**
 * Visit a PowerUpBasketball object and check if it has collided with the football
 * @param powerUpBasketball powerup to visit
 */
void PowerUpBasketballVisitor::VisitPowerUpBasketball(PowerUpBasketball* powerUpBasketball)
{
    // don't visit if we already have a powerup, prioritizing first found by visitor
    // or if detected powerup is consumed, avoids collecting powerup every frame of contact
    if (mPowerUpBasketball != nullptr || powerUpBasketball->IsConsumed())
    {
        return;
    }

    if (powerUpBasketball->HitTest(mFootball.get()))
    {
        mPowerUpBasketball = powerUpBasketball;
    }
}