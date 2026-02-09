  /**
 * @file EnemyChaser.cpp
 * @author Eliott Wurst
 */

#include "pch.h"
#include "WallVisitor.h"
#include "Wall.h"
#include "PlatformVisitor.h"
#include "Platform.h"
#include "EnemyChaser.h"
#include "Level.h"
#include "Football.h"

/// Motion speed constants
const double gravity = 1000.0;   ///< gravity for accelerating a falling chaser in pixels per second squared
const double chillSpeed = 50;   ///< movement speed when the player is not in the chaser's view in pixels per second
const double angrySpeed = 300;   ///< movement speed when the chaser is chasing the player in pixels per second

/// Motion distance constants in pixels
const double maxPatrolDistance = 400;   ///< maximum distance the chaser can move from its initial position when relaxed
const double verticalViewDistance = 500;   ///< maximum distance in Y direction that chaser can view the player
const double horizontalViewDistance = 500;   ///< maximum distance in X direction that chaser can view the player
const double horizontalTouchDistance = 5;   ///< chaser freezes when a football is this close to its center but too high

/// Stun period length in seconds
const double stunPeriod = 0.5;

/// Image for when the cactus is chasing the player
const std::wstring angryImage = L"images/angry_cactus.png";

/**
 * Constructor
 * @param level Level the EnemyChaser is part of
 * @param initX Initial X position for the EnemyChaser
 * @param initY Initial Y position for the EnemyChaser
 * @param id Id provided by an xml file
 */
EnemyChaser::EnemyChaser(Level* level, double initX, double initY, std::wstring id)
    : Enemy(level, initX, initY, id)
{
    // set initial x value, which needs to be remembered for movement behavior
    mInitX = initX;
    mMovingRight = true;
}

/**
 * Update the position and state of the EnemyChaser object.
 *
 * The new position of the chaser depends on whether it is chasing the football or not.
 * If the chaser has lost sight of the football, it returns to its patrol zone and its speed decreases.
 *
 * Check if the chaser has collided with a Wall or Platform. If it has collided with a Wall, stun it.
 * If it has collided with a Platform, land it on the Platform.
 *
 * This function has many similarities to the Enemy::Update() function for its patrol implementation.
 * @param elapsed Time elapsed since last update
 */
void EnemyChaser::Update(double elapsed)
{
    double currentX = GetX();
    double currentY = GetY();

    // Chaser does not get updated if it is frozen
    if (mIsFrozen)
    {
        return;
    }

    // Handle the stun timer. If a chaser is stunned, it does not chase the user.
    if (mIsStunned)
    {
        mStunTimer += elapsed;
        if (mStunTimer >= stunPeriod)
        {
            EndStun();
        }
    }

    // Check for a wall collision
    WallVisitor wallVisitor(this);
    GetLevel()->Accept(&wallVisitor);
    auto collidedWall = wallVisitor.GetWall();
    if (collidedWall != nullptr)
    {
        // The chaser is temporarily stunned when it hits a wall
        StartStun();
    }

    // Check for a platform collision beneath the chaser
    PlatformVisitor platformVisitor(this);
    GetLevel()->Accept(&platformVisitor);
    auto collidedPlatform = platformVisitor.GetPlatform();
    if (collidedPlatform != nullptr)
    {
        if (collidedPlatform->GetY() > GetY())
        {
            mVelocityY = 0;
        }
    }
    else
    {
        // No platform collision was detected, so the chaser is falling
        mVelocityY += gravity * elapsed;
    }

    // Check if the football is within the chaser's view; chase it if so
    if (mChaseFootballLeft && !mIsStunned)
    {
        mVelocityX = -angrySpeed;
        SetItemBitmap(angryImage);
        mMovingRight = false;
        mMovingLeft = true;
    }
    else if (mChaseFootballRight && !mIsStunned)
    {
        mVelocityX = angrySpeed;
        SetItemBitmap(angryImage);
        mMovingRight = true;
        mMovingLeft = false;
    }
    else
    {
        // Football is not in view or the chaser is stunned. Return to relaxed patrol state
        if (mMovingRight)
        {
            mVelocityX = chillSpeed;
        }
        else if (mMovingLeft)
        {
            mVelocityX = -chillSpeed;
        }
        SetItemBitmap(angryImage, true);
    }

    // Set the new position
    double newX = currentX + mVelocityX * elapsed;
    double newY = currentY + mVelocityY * elapsed;

    // Prevent movement out of bounds. If the EnemyChaser has left its zone without viewing a football,
    // it slowly returns to its patrol zone.
    if (!mChaseFootballLeft && !mChaseFootballRight)
    {
        if (newX < mInitX - maxPatrolDistance)
        {
            newX = currentX + chillSpeed * elapsed;
            mMovingLeft = false;
            mMovingRight = true;
        }
        else if (newX > mInitX)
        {
            newX = currentX - chillSpeed * elapsed;
            mMovingLeft = true;
            mMovingRight = false;
        }
    }

    // Update the new location of the chaser
    SetLocation(newX, newY);
}

/**
 * Check if the chaser can view the football.
 * This function has similarities to the Item::HitTest() function.
 * @param football The football the chaser is looking for
 * @return True if the football is in the range of the enemy, False otherwise
 */
bool EnemyChaser::FootballInVisionTest(Football* football)
{
    // The EnemyChaser object's position
    double chaserX = GetX();
    double chaserY = GetY();

    // The football object's position
    double footballX = football->GetX();
    double footballY = football->GetY();

    // The football is in view of the EnemyChaser if:
    // the horizontal distance between the centers of the two items is less than the horizontalViewDistance AND
    // the vertical distance between the centers of the two items is less than the verticalViewDistance.
    bool inViewX = std::abs(chaserX - footballX) < horizontalViewDistance;
    bool inViewY = std::abs(chaserY - footballY) < verticalViewDistance;

    // If the football is within the X and Y boundary of the EnemyChaser, return true.
    return inViewX && inViewY;
}

/**
 * Check if the football's X position is close enough for collision
 * @param football The football the chaser is looking for
 * @return True if the football's X position is close enough for collision, false otherwise;
 */
bool EnemyChaser::FootballUnreachableTest(Football* football)
{
    // The EnemyChaser object's position
    double chaserX = GetX();
    double chaserY = GetY();

    // The football object's position
    double footballX = football->GetX();
    double footballY = football->GetY();

    // The football is unreachable if:
    // the horizontal distance between the centers of the two items is less than the horizontalTouchDistance AND
    // the vertical distance between the centers of the two items is less than the verticalViewDistance.
    bool closeX = std::abs(chaserX - footballX) < horizontalTouchDistance;
    bool unreachableY = std::abs(chaserY - footballY) < verticalViewDistance;

    return closeX && unreachableY;
}

/**
 * Set the EnemyChaser to chase the football to the left
 */
void EnemyChaser::ChaseFootballLeft()
{
    mChaseFootballRight = false;
    mChaseFootballLeft = true;
}

/**
 * Set the EnemyChaser to chase the football to the right
 */
void EnemyChaser::ChaseFootballRight()
{
    mChaseFootballRight = true;
    mChaseFootballLeft = false;
}

/**
 * Stop the chaser from chasing the football
 */
void EnemyChaser::EndChase()
{
    mChaseFootballRight = false;
    mChaseFootballLeft = false;
}

/**
 * Stun the enemy
 */
void EnemyChaser::StartStun()
{
    mIsStunned = true;
    EndChase();
    mVelocityX = -mVelocityX;
}

/**
 * End the enemy's stun
 */
void EnemyChaser::EndStun()
{
    mIsStunned = false;
    mStunTimer = 0;
}
