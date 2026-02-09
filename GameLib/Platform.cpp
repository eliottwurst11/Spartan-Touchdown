/**
 * @file Platform.cpp
 * @author Matthew Lopez
 */

#include "pch.h"
#include "Platform.h"
#include "Level.h"
#include <wx/graphics.h>

using namespace std;

/**
 * Constructor
 * @param level the level this item belongs to
 * @param initX the initial x coordinate in pixels
 * @param initY the initial y coordinate in pixels
 * @param width the width of the entire platform in pixels
 * @param height the height of the entire platform in pixels
 * @param id the id of the declaration that this item will be made with
 */
Platform::Platform(Level* level, double initX, double initY, int width, int height, std::wstring id)
: Item(level, initX, initY, id), mWidth(width), mHeight(height)
{
    auto declaration = GetLevel()->GetDeclaration(id);
    auto pictureLeft = GetLevel()->GetPicture(declaration->GetImageLeft());
    mLeftImage = pictureLeft->GetImage();
    mLeftBitmap = pictureLeft->GetBitmap();

    auto pictureRight = GetLevel()->GetPicture(declaration->GetImageRight());
    mRightImage = pictureRight->GetImage();
    mRightBitmap = pictureRight->GetBitmap();
}

/**
 * Draw the platform. Each platform is made up of multiple segments
 * of amount width/segment width.
 * @param graphics the graphics context to draw on
 */
void Platform::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{

    // get the height and width of any tile as they are all the same
    double imageWidth = mRightBitmap->GetWidth();
    double imageHeight = mRightBitmap->GetHeight();

    double numTiles = mWidth / imageWidth;

    double leftEdge = GetX() - (numTiles * imageWidth) / 2;

    if (mWidth % int(imageWidth) != 0)
    {
        numTiles--;
    }
    double rightEdge = GetX() - imageWidth + (numTiles * imageWidth) / 2;

    graphics->DrawBitmap(*mLeftBitmap, leftEdge, GetY() - imageHeight / 2 , imageWidth, imageHeight);

    for (int i = 1; i < numTiles - 1; i++)
    {
            graphics->DrawBitmap(*GetBitmap(), leftEdge + i * imageWidth, GetY() - imageHeight / 2, imageWidth, imageHeight);
    }

    graphics->DrawBitmap(*mRightBitmap, rightEdge, GetY() - imageHeight / 2, imageWidth, imageHeight);

}

/**
 * Test to see if this item is colliding with another item.
 * This function uses Axis-Aligned Bounding Box (AABB) collision detection.
 *
 * @param item The other item to test for a collision with.
 * @return true if the items' bounding boxes are overlapping.
 */
bool Platform::CollisionTest(Item* item)
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