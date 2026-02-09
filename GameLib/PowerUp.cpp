/**
 * @file PowerUp.cpp
 * @author Matthew Lopez
 */

#include "pch.h"
#include "PowerUp.h"
#include "Level.h"
#include "ItemVisitor.h"

using namespace std;

/// Greatest Y value the powerup can move to
const double MaxVerticalMovement = 1500;

/**
 * Constructor; makes an upcall to the Item constructor
 * @param level Level this powerup is a part of
 * @param initX Initial X position of the powerup in pixels
 * @param initY Initial Y position of the powerup in pixels
 * @param id ID for the powerup, used for level loading
 */
PowerUp::PowerUp(Level* level, double initX, double initY, std::wstring id)
    : Item(level, initX, initY, id)
{
}

/**
 * Updates the powerup's state. If mIsFalling is true, moves it downwards.
 * @param elapsed Time since the last update in seconds.
 */
void PowerUp::Update(double elapsed)
{
    // Call base class update if it does anything (currently empty)
    // Item::Update(elapsed);

    // If the powerup has been collected and is falling...
    if (mIsFalling)
    {
        // Move downwards
        double newYCandidate = GetY() + FallingSpeed * elapsed;
        double newY = std::min(MaxVerticalMovement, newYCandidate);
        SetLocation(GetX(), newY);
    }
}

/**
 * Accept an ItemVisitor. Default implementation calls VisitPowerUp.
 * @param visitor ItemVisitor to accept.
 */
void PowerUp::Accept(ItemVisitor* visitor)
{
    // Allow the visitor to interact with this PowerUp
    if (visitor) {
        visitor->VisitPowerUp(this);
    }
}

/**
 * Start the falling animation.
 */
void PowerUp::StartFalling()
{
    mIsFalling = true;
}