/**
 * @file PlatformBreakable.cpp
 * @author Eliott Wurst
 * @author Hamin Paik
 */

#include "pch.h"
#include "PlatformBreakable.h"
#include "Level.h"
#include <wx/graphics.h>
#include "ItemVisitor.h"

using namespace std;

/// The image file for the breaking state
const std::wstring BreakingImageName = L"breakingPlatform.png";

/// Time in seconds before the platform changes its image
const double TimeToBreak = 1.0;

/// Time in seconds after changing image before it disappears
const double TimeToDisappear = 1.0;

/**
 * Constructor
 * @param level the level this item belongs to
 * @param initX the initial x coordinate in pixels
 * @param initY the initial y coordinate in pixels
 * @param width the width of the entire breakable platform in pixels
 * @param height the height of the entire breakable platform in pixels
 * @param id the id of the declaration this item will be made with
 */
PlatformBreakable::PlatformBreakable(Level* level, double initX, double initY, int width, int height, std::wstring id)
    : Item(level, initX, initY, id), mWidth(width), mHeight(height)
{
    auto declaration = GetLevel()->GetDeclaration(id);

    // Load the 'solid' image
    mSolidPicture = GetLevel()->GetPicture(declaration->GetSolidImageName());
    mSolidBitmap = mSolidPicture->GetBitmap();

    // Load the 'breaking' image
    mBreakingPicture = GetLevel()->GetPicture(declaration->GetBreakingImageName());
    mBreakingBitmap = mBreakingPicture->GetBitmap();
}



/**
 * Triggers the platform to start its breaking sequence.
 */
void PlatformBreakable::TriggerBreak()
{
    if (mState == State::Solid)
    {
        mState = State::Breaking;
        mTimer = 0.0;
    }
}

/**
 * Handles updates for animation
 */
void PlatformBreakable::Update(double elapsed)
{
    if (mState == State::Breaking)
    {
        mTimer += elapsed;
        if (mTimer > TimeToBreak + TimeToDisappear)
        {
            mState = State::Broken;
        }
    }
}

/**
 * Draw the platform
 * @param graphics the graphics context to draw on
 */
void PlatformBreakable::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (mState == State::Broken)
    {
        return; // Don't draw
    }

    wxBitmap* bitmapToDraw = mSolidBitmap.get();

    // If we are in the "breaking" state AND past the initial timer
    if (mState == State::Breaking && mTimer > TimeToBreak)
    {
        bitmapToDraw = mBreakingBitmap.get();
    }

    // Draw the correct bitmap, stretched to the platform's full size
    graphics->DrawBitmap(*bitmapToDraw,
                         int(GetX() - mWidth / 2),
                         int(GetY() - mHeight / 2),
                         mWidth,
                         mHeight);
}

/**
 * Accept an ItemVisitor
 * @param visitor ItemVisitor to accept
 */
void PlatformBreakable::Accept(ItemVisitor* visitor)
{
    visitor->VisitPlatformBreakable(this);
}

/**
 * Test for collision with another item
 * @param item The item to test collision with
 * @return true if the items are colliding
 */
bool PlatformBreakable::CollisionTest(Item* item)
{
    // Platform's boundaries
    double pLeft = GetX() - mWidth / 2;
    double pRight = GetX() + mWidth / 2;
    double pTop = GetY() - mHeight / 2;
    double pBottom = GetY() + mHeight / 2;

    // Item's boundaries
    double iLeft = item->GetX() - item->GetImageWidth() / 2;
    double iRight = item->GetX() + item->GetImageWidth() / 2;
    double iTop = item->GetY() - item->GetImageHeight() / 2;
    double iBottom = item->GetY() + item->GetImageHeight() / 2;

    // AABB collision check
    return pLeft < iRight && pRight > iLeft &&
           pTop < iBottom && pBottom > iTop;
}