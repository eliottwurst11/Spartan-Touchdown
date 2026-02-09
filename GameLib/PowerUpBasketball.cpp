/**
 * @file PowerUpBasketball.cpp
 * @author Nishit Nagpal
 */

#include "pch.h"
#include "PowerUpBasketball.h"
#include "ItemVisitor.h"
#include "Level.h"

using namespace std;

/**
 * Constructor; makes an upcall to the PowerUp constructor
 * @param level Level this powerup is a part of
 * @param initX Initial X position of the powerup in pixels
 * @param initY Initial Y position of the powerup in pixels
 * @param id ID for the powerup, used for level loading
 */
PowerUpBasketball::PowerUpBasketball(Level* level, double initX, double initY, std::wstring id)
    : PowerUp(level, initX, initY, id)
{
}

/**
 * Update the state of the powerup
 * @param elapsed Time in seconds since last PowerUpBasketball::Update() call
 */
void PowerUpBasketball::Update(double elapsed)
{
    if (IsConsumed())
    {
        Item::Update(elapsed);
        mSecondsRemaining -= elapsed;
        if (mSecondsRemaining <= 0)
        {
            GetLevel()->ResetFootballBasketball();
        }
    }
}

/**
 * Draw the powerup
 * @param graphics graphics context to draw on
 */
void PowerUpBasketball::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (!IsConsumed()) {
        Item::Draw(graphics);
    }
}
