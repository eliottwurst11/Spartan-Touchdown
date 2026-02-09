/**
 * @file CollisionVisitor.h
 * @author Matthew Lopez
 *
 * Visitor Class for collisions with walls and platforms
 *
 * Checks in one direction at a time, ie only y-axis collisions
 * or only x-axis collisions
 */

#ifndef GAME_COLLISIONVISITOR_H
#define GAME_COLLISIONVISITOR_H

#include "Item.h"
#include "ItemVisitor.h"

class Football;
class Platform;
class Wall;
class PlatformBreakable;

/**
 * Visitor Class for collisions with walls and platforms
 */
class CollisionVisitor : public ItemVisitor {
private:

    /// The football we are checking collisons with
    Football* mFootball = nullptr;

    /// The item that we collided with and is the closest
    Item* mClosestCollision = nullptr;

    /// Pointer to a breakable platform that the football collided with, if it is the closest collision
    PlatformBreakable* mCollidedPlatformBreakable = nullptr;

    /// The distance from the last place before the collision the closest object that we have collided with
    double mClosestDistance = INFINITY;

    /// The last x coordinate the football was located before collision
    double mOldX = 0;

    /// The last y coordinate the football was located before collision
    double mOldY = 0;

    /// Velocity in the X direction
    double mVelocityX = 0;

    /// Velocity in the Y direction
    double mVelocityY = 0;

public:

    CollisionVisitor(Football* football, double x, double y, double vX, double vY);

    void VisitPlatform(Platform* platform) override;

    void VisitWall(Wall* wall) override;

    void VisitPlatformBreakable(PlatformBreakable* platform) override;

    /**
     * Get an Item that collided with the football
     * @return pointer to the closest item that the football collided with
     */
    Item* GetCollision() { return mClosestCollision; }

    /**
     * Get the breakable platform the football collided with
     * @return Pointer to the breakable platform the football collided with
     */
    PlatformBreakable* GetPlatformBreakable() const { return mCollidedPlatformBreakable; }

};


#endif //GAME_COLLISIONVISITOR_H