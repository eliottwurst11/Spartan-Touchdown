   /**
 * @file PowerUpDoubleJump.cpp
 * @author Eliott Wurst
 */

#include "pch.h"
#include "PowerUpDoubleJump.h"
#include "ItemVisitor.h"
#include "Level.h"

using namespace std;

/**
 * Constructor
 * @param level Level this powerup is part of
 * @param initX X position of the powerup
 * @param initY Y position of the powerup
 * @param id the id that corresponds to the declaration
 */
PowerUpDoubleJump::PowerUpDoubleJump(Level* level, double initX, double initY, std::wstring id)
    : PowerUp(level, initX, initY, id)
{
}

/**
* Update the state of the double jump powerup
* @param elapsed Time in seconds since the last call to PowerUpDoubleJump::Update()
*/
void PowerUpDoubleJump::Update(double elapsed)
{
    if (IsConsumed())
    {
        Item::Update(elapsed);
        mSecondsRemaining -= elapsed;
        if (mSecondsRemaining <= 0)
        {
            GetLevel()->ResetFootballDoubleJump();
        }
    }
}

/**
 * Draw the powerup
 * @param graphics Graphics context to draw on
 */
void PowerUpDoubleJump::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (!IsConsumed()) {
        Item::Draw(graphics);
    }
}