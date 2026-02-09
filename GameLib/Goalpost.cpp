/**
 * @file Goalpost.cpp
 * @author Matthew Lopez
 */

#include "pch.h"
#include "Goalpost.h"
#include "Level.h"

using namespace std;

/// Collision distance for the goalpost in pixels
const double CollisionDistance = 50;

/**
 * Constructor
 * @param level the level this goalpost belongs to
 * @param initX the initial x coordinate on the screen in pixels
 * @param initY the initial y coordinate on the screen in pixels
 * @param id the id of the declaration that will be used to make this item
 */
Goalpost::Goalpost(Level* level, double initX, double initY, std::wstring id)
    : Item(level, initX, initY, id)
{
}

/**
 * Test for collision with another item using distance-based collision detection
 * The goalpost collision is different from other items - it uses a circular
 * collision area rather than rectangular bounds
 * @param item The item to test collision with
 * @return true if the items are colliding
 */
bool Goalpost::CollisionTest(Item* item)
{
    // Calculate the distance between the goalpost and the item
    double dx = item->GetX() - GetX();
    double dy = item->GetY() - GetY();
    double distance = sqrt(dx * dx + dy * dy);
    
    // Check if the distance is within the collision radius
    if (distance < CollisionDistance)
    {
        return true;
    }

    return false;
}