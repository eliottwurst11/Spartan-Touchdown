/**
 * @file Item.cpp
 * @author Matthew Lopez
 */

#include "pch.h"
#include "Item.h"
#include "Level.h"
#include <wx/graphics.h>

using namespace std;

/**
 * Constructor
 * @param level the level this item exists in
 * @param initX the initial x coordinate in pixels
 * @param initY the initial y coordinate in pixels
 * @param id the id of the declaration this item will be made with
 */
Item::Item(Level* level, double initX, double initY, std::wstring id)
    : mLevel(level), mX(initX), mY(initY)
{
    auto declaration = mLevel->GetDeclaration(id);
    auto picture = mLevel->GetPicture(declaration->GetImageName());
    mItemImage = picture->GetImage();
    mItemBitmap = picture->GetBitmap();
}


/**
 * Football constructor
 *
 * The football loads its own images and is not made with a declaration.
 * It is made automatically by the level.
 *
 * @param level the level this item is contained in
 * @param filename the name of the file that has the image
 */
Item::Item(Level *level, const std::wstring &filename) : mLevel(level)
{
    mItemImage = make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY);
    mItemBitmap = make_unique<wxBitmap>(*mItemImage);
}

/**
 * Destructor
 */
Item::~Item()
{
}

/**
 * Draw the item
 * @param graphics the graphics context to draw on
 */
void Item::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (mItemBitmap)
    {
        double width = mItemBitmap->GetWidth();
        double height = mItemBitmap->GetHeight();
        graphics->DrawBitmap(*mItemBitmap,
                             (int)(GetX() - width / 2),
                             (int)(GetY() - height / 2),
                             width,
                             height);
    }
}

/**
 * Test to see if this item is colliding with another item.
 * This function uses Axis-Aligned Bounding Box (AABB) collision detection.
 *
 * @param other The other item to test for a collision with.
 * @return true if the items' bounding boxes are overlapping.
 */
bool Item::HitTest(Item *other)
{
    // The 'this' item's properties
    double ourX = GetX();
    double ourY = GetY();
    double ourWidth = GetImageWidth();
    double ourHeight = GetImageHeight();

    // The 'other' item's properties
    double otherX = other->GetX();
    double otherY = other->GetY();
    double otherWidth = other->GetImageWidth();
    double otherHeight = other->GetImageHeight();

    // A collision occurs if the distance between the centers of the two items
    // is less than half of their combined widths (on the X axis) AND
    // less than half of their combined heights (on the Y axis).

    bool collisionX = std::abs(ourX - otherX) * 2 < (ourWidth + otherWidth);
    bool collisionY = std::abs(ourY - otherY) * 2 < (ourHeight + otherHeight);

    // If there is an overlap on BOTH axes, we have a collision.
    return collisionX && collisionY;
}

/**
 * Set the Item's bitmap using an image filename, or reset the item to the image given by a level file if the
 * "reset" parameter is set to true. The "reset" parameter is set to false by default.
 * @param filename Name of file to use for the bitmap
 * @param reset Reset item image back to what the level file provided; false by default
 */
void Item::SetItemBitmap(const std::wstring& filename, bool reset)
{
    if (reset)
    {
        mItemBitmap = make_unique<wxBitmap>(*mItemImage);
    }
    else
    {
        auto itemImage = make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY);
        mItemBitmap = make_unique<wxBitmap>(*itemImage);
    }
}