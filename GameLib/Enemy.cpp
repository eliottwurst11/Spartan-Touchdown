/**
 * @file Enemy.cpp
 * @author Beckham Lee
 */

#include "pch.h"
#include "Enemy.h"
#include "Level.h"

using namespace std;

/// Motion constants
const double VerticalSpeed = 250; ///< Movement speed for the enemy in the Y direction in pixels per second
const double MaxHeightMovement = 350; ///< Maximum Y displacement from the enemy can move from its start in pixels

/**
 * Constructor
 * @param level Level this enemy is a part of
 * @param initX Initial X position of the enemy in pixels
 * @param initY Initial Y position of the enemy in pixels
 * @param id ID for the enemy, used for level loading
 */
Enemy::Enemy(Level* level, double initX, double initY, std::wstring id)
    : Item(level, initX, initY, id)
{
    mInitY = initY;
}

/**
 * Update the enemy's position based on the velocity, elapsed time,
 * current movement state, and relation to arbitrary movement boundary
 * @param elapsed Time elapsed since last update in seconds
 */
void Enemy::Update(double elapsed)
{
    double currentY = GetY();
    double newY = 0;

    // start condition is not moving, so set moving up
    if (!mMovingDown && !mMovingUp)
    {
        mMovingUp = true;
    }
    if (mMovingUp)
    {
        newY = currentY - VerticalSpeed * elapsed;
    }
    if (mMovingDown)
    {
        newY = currentY + VerticalSpeed * elapsed;
    }

    // disallow movement out of 'bounds'
    // and set the movement to the other direction
    if (newY < mInitY - MaxHeightMovement)
    {
        newY = mInitY - MaxHeightMovement;
        mMovingUp = false;
        mMovingDown = true;
    }
    else if (newY > mInitY)
    {
        newY = mInitY;
        mMovingUp = true;
        mMovingDown = false;
    }

    SetLocation(GetX(), newY);
}
