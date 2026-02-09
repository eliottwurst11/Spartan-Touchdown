/**
 * @file CollisionVisitor.cpp
 * @author Matthew Lopez
 */

#include "pch.h"
#include "CollisionVisitor.h"
#include "PlatformBreakable.h"
#include "Football.h"
#include "Platform.h"
#include "Wall.h"

/**
 * Constructor. Only one velocity component should be set at once. This only handles collisions in
 * each axis one at a time
 * @param football
 * @param x The X coordinate before collision
 * @param y The Y coordinate before collision
 * @param vX The velocity of the football in the x direction
 * @param vY The velocity of the football int he y direction
 */
CollisionVisitor::CollisionVisitor(Football* football, double x, double y, double vX, double vY)
    : mFootball(football), mOldX(x), mOldY(y), mVelocityX(vX), mVelocityY(vY)
{
}


/**
 * Visits each platform in the level and checks if we have collided with them.
 * Sets closest platform based on proximity and velocity/direction the ball is moving.
 *
 * @param platform The platform we are visiting
 */
void CollisionVisitor::VisitPlatform(Platform* platform)
{
    // Only enter if we have detected a collision
    if (platform->CollisionTest(mFootball))
    {
        // If we are testing for horizontal collision
        if (mVelocityX != 0)
        {

            // moving to the right therefore check the left edge for closest
            if (mVelocityX > 0)
            {
                auto leftEdge = platform->GetX() - platform->GetImageWidth() / 2;
                if (abs(leftEdge - mOldX) < mClosestDistance)
                {
                    mClosestDistance = abs(leftEdge - mOldX);
                    mClosestCollision = platform;
                }
            }
            else
            {
                //only here if velocityX is negative, therefore moving left and check for right edge
                auto rightEdge = platform->GetX() + platform->GetImageWidth() / 2;
                if (abs(rightEdge - mOldX) < mClosestDistance)
                {
                    mClosestDistance = abs(rightEdge - mOldX);
                    mClosestCollision = platform;
                }
            }
        }
        else if (mVelocityY != 0)
        {
            // only here if there is a vertical collision. same logic as horizontal collisions.
            if (mVelocityY > 0)
            {
                auto topEdge = platform->GetY() - platform->GetImageHeight() / 2;
                if (abs(topEdge - mOldY) < mClosestDistance)
                {
                    mClosestDistance = abs(topEdge - mOldY);
                    mClosestCollision = platform;
                }
            }
            else
            {
                auto bottomEdge = platform->GetY() + platform->GetImageHeight() / 2;
                if (abs(bottomEdge - mOldY) < mClosestDistance)
                {
                    mClosestDistance = abs(bottomEdge - mOldY);
                    mClosestCollision = platform;
                }
            }
        }
    }
}

/**
 * Visit each wall in the level and checks if the football has collided with it.
 * Sets closest wall collision based on proximity if a collision is found.
 *
 * @param wall The wall object we are visiting
 */
void CollisionVisitor::VisitWall(Wall* wall)
{
    // Only enter if we have detected a collision
    if (wall->CollisionTest(mFootball))
    {
        // If we are testing for horizontal collision
        if (mVelocityX != 0)
        {

            // moving to the right therefore check the left edge for closest
            if (mVelocityX > 0)
            {
                auto leftEdge = wall->GetX() - wall->GetImageWidth() / 2;
                if (abs(leftEdge - mOldX) < mClosestDistance)
                {
                    mClosestDistance = abs(leftEdge - mOldX);
                    mClosestCollision = wall;
                }
            }
            else
            {
                // only here if velocityX is negative, therefore moving left and check for right edge
                auto rightEdge = wall->GetX() + wall->GetImageWidth() / 2;
                if (abs(rightEdge - mOldX) < mClosestDistance)
                {
                    mClosestDistance = abs(rightEdge - mOldX);
                    mClosestCollision = wall;
                }
            }
        }
        else if (mVelocityY != 0)
        {
            if (mVelocityY > 0)
            {
                auto topEdge = wall->GetY() - wall->GetImageHeight() / 2;
                if (abs(topEdge - mOldY) < mClosestDistance)
                {
                    mClosestDistance = abs(topEdge - mOldY);
                    mClosestCollision = wall;
                }
            }
            else
            {
                auto bottomEdge = wall->GetY() + wall->GetImageHeight() / 2;
                if (abs(bottomEdge - mOldY) < mClosestDistance)
                {
                    mClosestDistance = abs(bottomEdge - mOldY);
                    mClosestCollision = wall;
                }
            }
        }
    }
}

/**
 * Visits each breakable platform in the level and checks for collisions.
 * (This logic is identical to VisitPlatform)
 *
 * @param platform The platform we are visiting
 */
void CollisionVisitor::VisitPlatformBreakable(PlatformBreakable* platform)
{
    // Only enter if we have detected a collision
    if (platform->CollisionTest(mFootball))
    {
        // If we are testing for horizontal collison
        if (mVelocityX != 0)
        {
            // moving to the right therefore check the left edge for closest
            if (mVelocityX > 0)
            {
                auto leftEdge = platform->GetX() - platform->GetImageWidth() / 2;
                if (abs(leftEdge - mOldX) < mClosestDistance)
                {
                    mClosestDistance = abs(leftEdge - mOldX);
                    mClosestCollision = platform;
                    mCollidedPlatformBreakable = platform;
                }
            }
            else
            {
                //only here if velocityX is negative, therefore moving left and check for right edge
                auto rightEdge = platform->GetX() + platform->GetImageWidth() / 2;
                if (abs(rightEdge - mOldX) < mClosestDistance)
                {
                    mClosestDistance = abs(rightEdge - mOldX);
                    mClosestCollision = platform;
                    mCollidedPlatformBreakable = platform;
                }
            }
        }
        else if (mVelocityY != 0)
        {
            if (mVelocityY > 0)
            {
                auto topEdge = platform->GetY() - platform->GetImageHeight() / 2;
                if (abs(topEdge - mOldY) < mClosestDistance)
                {
                    mClosestDistance = abs(topEdge - mOldY);
                    mClosestCollision = platform;
                    mCollidedPlatformBreakable = platform;
                }
            }
            else
            {
                auto bottomEdge = platform->GetY() + platform->GetImageHeight() / 2;
                if (abs(bottomEdge - mOldY) < mClosestDistance)
                {
                    mClosestDistance = abs(bottomEdge - mOldY);
                    mClosestCollision = platform;
                    mCollidedPlatformBreakable = platform;
                }
            }
        }
    }
}
