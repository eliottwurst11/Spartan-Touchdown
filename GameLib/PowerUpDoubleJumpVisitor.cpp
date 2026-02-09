/**
 * @file PowerUpDoubleJumpVisitor.cpp
 * @author Beckham Lee
 */

#include "pch.h"
#include "PowerUpDoubleJumpVisitor.h"
#include "Football.h"

/**
 * Visit the double jump powerup and check if it has collided with the player
 * @param powerUpDoubleJump powerup to visit
 */
void PowerUpDoubleJumpVisitor::VisitPowerUpDoubleJump(PowerUpDoubleJump* powerUpDoubleJump)
{
    // don't visit if we already have a powerup, prioritizing first found by visitor
    // or if detected powerup is consumed, avoids collecting powerup every frame of contact
    if (mPowerUpDoubleJump != nullptr || powerUpDoubleJump->IsConsumed())
    {
        return;
    }

    if (powerUpDoubleJump->HitTest(mFootball.get()))
    {
        mPowerUpDoubleJump = powerUpDoubleJump;
    }
}