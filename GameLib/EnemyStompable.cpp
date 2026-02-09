/**
 * @file EnemyStompable.cpp
 * @author Beckham Lee
 */

#include "pch.h"
#include "EnemyStompable.h"
#include "Level.h"

#include <algorithm>

using namespace std;

const double HorizontalSpeed = 250;       ///< pixels per second
const double MaxHorizontalMovement = 350; ///< max X displacement
const double VerticalSpeed = 500;         ///< vertical speed in pixels per second
const double MaxVerticalMovement = 1500;  ///< maximum Y value position in pixels

/**
 * Constructor
 * @param level Level this enemy is a part of
 * @param initX Initial X position of the enemy in pixels
 * @param initY Initial Y position of the enemy in pixels
 * @param id ID for the enemy, used for level loading
 */
EnemyStompable::EnemyStompable(Level* level, double initX, double initY, std::wstring id)
    : Enemy(level, initX, initY, id)
{
    mInitX = initX;
}

/**
 * Update the state of the enemy
 * @param elapsed Time in seconds since last call to EnemyStompable::Update()
 */
void EnemyStompable::Update(double elapsed)
{
    double currentX = GetX();
    double newX = 0;

    // calculate the height if defeated
    if (mDefeated)
    {
        // move enough to no longer be visible
        double newYCandidate = this->GetY() + VerticalSpeed * elapsed;
        auto newY = std::min(MaxVerticalMovement, newYCandidate);
        this->SetLocation(currentX, newY);
        return;
    }


    if (!mMovingLeft && !mMovingRight)
    {
        mMovingRight = true;
    }
    if (mMovingRight)
    {
        newX = currentX + HorizontalSpeed * elapsed;
    }
    if (mMovingLeft)
    {
        newX = currentX - HorizontalSpeed * elapsed;
    }

    if (newX > mInitX + MaxHorizontalMovement)
    {
        newX = mInitX + MaxHorizontalMovement;
        mMovingRight = false;
        mMovingLeft = true;
    }
    else if (newX < mInitX)
    {
        newX = mInitX;
        mMovingRight = true;
        mMovingLeft = false;
    }

    SetLocation(newX, GetY());
}