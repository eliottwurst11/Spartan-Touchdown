/**
 * @file Wall.cpp
 * @author Matthew Lopez
 */

#include "pch.h"
#include "Wall.h"
#include "Level.h"
#include <wx/graphics.h>

using namespace std;

/**
 * Constructor
 * @param level the level this item belongs to
 * @param initX the initial x coordinate in pixels
 * @param initY the initial y coordinate in pixels
 * @param width the width of the entire wall object in pixels
 * @param height the height of the entire wall object in pixels
 * @param id the id of the declaration this item will be made with
 */
Wall::Wall(Level* level, double initX, double initY, int width, int height, std::wstring id)
    : Item(level, initX, initY, id), mHeight(height), mWidth(width)
{
}

/**
 * Draw this object. Walls are made up of multiple segments
 * of amount height/image height.
 * @param graphics the graphics context to draw on
 */
void Wall::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Get the width and height of the wall segment bitmap
    double wid = GetBitmap()->GetWidth();
    double hit = GetBitmap()->GetHeight();

    int numTiles = mHeight / hit;
    double topEdge = GetY() - (numTiles * hit) / 2;
    double bottomEdge = GetY() - hit + (numTiles * hit) / 2;

    graphics->DrawBitmap(*GetBitmap(), GetX() - hit / 2, topEdge, hit, wid);

    for (int i = 1; i < numTiles - 1; i++)
    {
        graphics->DrawBitmap(*GetBitmap(), GetX() - wid / 2, topEdge + i * hit, wid, hit);
    }

    graphics->DrawBitmap(*GetBitmap(), GetX() - hit / 2, bottomEdge, hit, wid);
}

/**
 * Test to see if this item is colliding with another item.
 * This function uses Axis-Aligned Bounding Box (AABB) collision detection.
 *
 * @param item The other item to test for a collision with.
 * @return true if the items' bounding boxes are overlapping.
 */
bool Wall::CollisionTest(Item* item)
{
    auto itemLeft = item->GetX() - item->GetImageWidth() / 2;
    auto itemRight = item->GetX() + item->GetImageWidth() / 2;
    auto itemTop = item->GetY() - item->GetImageHeight() / 2;
    auto itemBottom = item->GetY() + item->GetImageHeight() / 2;

    auto ourLeft = GetX() - mWidth / 2;
    auto ourRight = GetX() + mWidth / 2;
    auto ourTop = GetY() - mHeight / 2;
    auto ourBottom = GetY() + mHeight / 2;

    if (ourRight < itemLeft ||  
        ourLeft > itemRight ||  
        ourTop > itemBottom ||  
        ourBottom < itemTop)    
    {
        return false;
    }

    return true;
}