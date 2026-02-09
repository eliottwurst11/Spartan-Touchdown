/**
 * @file Football.cpp
 * @author Nishit Nagpal
 */

#include "pch.h"
#include "Football.h"
#include "Level.h"
#include "ItemVisitor.h"
#include <wx/event.h>
#include <wx/graphics.h>
#include <cmath>
#include "CollisionVisitor.h"
#include "PlatformBreakable.h"

using namespace std;

/// Constants from specs
const double Gravity = 1150.0;   ///< gravitational constant in pixels per second squared
const double HorizontalSpeed = 500.0;   ///< motion speed in X direction in pixels per second
const double BounceSpeed = -800.0;   ///< motion speed for football jump in pixels per second
const double DoubleJumpSpeed = -600.0;  ///< jump speed when a double jump is used, Less powerful than normal jump

/// Small value in pixels; prevents getting stuck in collision
const double Epsilon = 0.01;

/// Football image filenames
const wstring FootballMidImageName = L"images/footballMid.png";   ///< used when football X position is constant
const wstring FootballLeftImageName = L"images/footballLeft.png";   ///< used when football is moving left
const wstring FootballRightImageName = L"images/footballRight.png";   ///< used when football is moving right

/// Basketball image filenames
const wstring BasketballMidImageName = L"images/spartybasketball.png";  ///< used when basketball X position is constant
const wstring BasketballLeftImageName = L"images/spartybasketball.png";  ///< used when basketball is moving left
const wstring BasketballRightImageName = L"images/spartybasketball.png";  ///< used when basketball is moving right

/**
 * Constructor that loads display images
 * @param level the level this is part of
 */
Football::Football(Level *level) : Item(level, FootballMidImageName)
{
    // Load all football images
    wxImage midImage(FootballMidImageName, wxBITMAP_TYPE_ANY);
    wxImage leftImage(FootballLeftImageName, wxBITMAP_TYPE_ANY);
    wxImage rightImage(FootballRightImageName, wxBITMAP_TYPE_ANY);

    mFootballMid = make_unique<wxBitmap>(midImage);
    mFootballLeft = make_unique<wxBitmap>(leftImage);
    mFootballRight = make_unique<wxBitmap>(rightImage);

    // Load all basketball images
    wxImage basketballMidImage(BasketballMidImageName, wxBITMAP_TYPE_ANY);
    wxImage basketballLeftImage(BasketballLeftImageName, wxBITMAP_TYPE_ANY);
    wxImage basketballRightImage(BasketballRightImageName, wxBITMAP_TYPE_ANY);

    mBasketballMid = make_unique<wxBitmap>(basketballMidImage);
    mBasketballLeft = make_unique<wxBitmap>(basketballLeftImage);
    mBasketballRight = make_unique<wxBitmap>(basketballRightImage);
}

/**
 * Test to see if we hit this object with a mouse click
 * @param x X-coordinate to test
 * @param y Y-coordinate to test
 * @return true if we hit the object
 */
bool Football::HitTest(int x, int y)
{
    return false;
}



/**
 * Update the football's position based on velocity and elapsed time
 * @param elapsed Time since last update in seconds
 */
void Football::Update(double elapsed)
{
    // No basketball countdown; basketball state is controlled by the level logic

    // Get current position
    double currentX = GetX();
    double currentY = GetY();

    // Apply horizontal movement based on key states with precedence
    double horizontalVelocity = 0;
    
    // Use key precedence: most recently pressed key takes priority
    if (mLeftPressed && mRightPressed) {
        // Both keys pressed - use the most recently pressed one
        if (mLastDirection == LastDirection::LEFT) {
            horizontalVelocity = -HorizontalSpeed;
        } else if (mLastDirection == LastDirection::RIGHT) {
            horizontalVelocity = HorizontalSpeed;
        }
    } else if (mLeftPressed) {
        horizontalVelocity = -HorizontalSpeed;
    } else if (mRightPressed) {
        horizontalVelocity = HorizontalSpeed;
    }
    
    mVelocityX = horizontalVelocity;


    // Update stepping animation when moving horizontally on ground
    if ((mLeftPressed || mRightPressed) && mOnGround && horizontalVelocity != 0) {
        mStepTime += elapsed;
        if (mStepTime >= mStepDuration) {
            mStepTime = 0.0;
        }
        // Create vertical stepping motion using sine wave
        mStepOffset = sin((mStepTime / mStepDuration) * 2.0 * 3.14159) * mMaxStepOffset;
    } else {
        // Reset step animation when not moving or airborne
        mStepTime = 0.0;
        mStepOffset = 0.0;
    }


    // Apply gravity to vertical velocity
    mVelocityY = mVelocityY + Gravity * elapsed;

    // simulate a jump after stomping an enemy
    if (mStomping)
    {
        mVelocityY = BounceSpeed;
        mStomping = false;
    }

    // Handle space bar bounce (only when on ground or with double jump)
    if (mSpacePressed && (mOnGround || CanDoubleJump())) {
        if (!mOnGround && CanDoubleJump()) {
            mVelocityY = DoubleJumpSpeed;
            mDoubleJumpsUsed++;
        } else {
            mVelocityY = BounceSpeed;
        }
        
        mOnGround = false;
        mSpacePressed = false;
    }

    // Update position using: position += velocity * elapsed
    double newX = currentX + mVelocityX * elapsed;
    double newY = currentY + mVelocityY * elapsed;

    CollisionVisitor collisionVisitorY(this, currentX, currentY, 0, mVelocityY);

    SetLocation(currentX, newY);
    GetLevel()->Accept(&collisionVisitorY);
    auto collided = collisionVisitorY.GetCollision();

    if (collided != nullptr)
    {
        if (mVelocityY > 0)
        {
            newY = collided->GetY() - collided->GetImageHeight() / 2 - GetImageHeight() / 2 - Epsilon;
            mOnGround = true;
            mDoubleJumpsUsed = 0;

            // Check if we landed on a breakable platform
            if (collisionVisitorY.GetPlatformBreakable() != nullptr)
            {
                (collisionVisitorY.GetPlatformBreakable())->TriggerBreak();
            }
        }
        else
        {
            newY = collided->GetY() + collided->GetImageHeight() / 2 + GetImageHeight() / 2 + Epsilon;
        }
        mVelocityY = 0;

    }
    else
    {
        mOnGround = false;
    }


    CollisionVisitor collisionVisitorX(this, currentX, currentY, 0, mVelocityX);
    SetLocation(newX, newY);
    GetLevel()->Accept(&collisionVisitorX);
    collided = collisionVisitorX.GetCollision();
    if (collided != nullptr)
    {
        if (mVelocityX > 0)
        {
            newX = collided->GetX() - collided->GetImageWidth() / 2 - GetImageWidth() / 2 - Epsilon;
        }
        else
        {
            newX = collided->GetX() + collided->GetImageWidth() / 2 + GetImageWidth() / 2 + Epsilon;
        }
        mVelocityX = 0;
    }




    // Apply step offset to vertical position when stepping on ground
    if (mOnGround && horizontalVelocity != 0) {
        newY -= mStepOffset;
    }

    // Update the football's position
    SetLocation(newX, newY);
}

/**
 * Draw the football with the appropriate image based on movement direction
 * @param graphics The device context to draw on
 */
void Football::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Select the appropriate bitmap based on movement direction with precedence
    wxBitmap* bitmapToDraw;
    
    // Choose between football and basketball images based on transformation state
    if (mIsBasketball)
    {
        bitmapToDraw = mBasketballMid.get();
        
        // Use directional images both on ground and in air when direction keys are pressed
        if (mLeftPressed && mRightPressed) {
            // Both keys pressed - use the most recently pressed one
            if (mLastDirection == LastDirection::LEFT) {
                bitmapToDraw = mBasketballLeft.get();
            } else if (mLastDirection == LastDirection::RIGHT) {
                bitmapToDraw = mBasketballRight.get();
            }
        } else if (mLeftPressed) {
            bitmapToDraw = mBasketballLeft.get();
        } else if (mRightPressed) {
            bitmapToDraw = mBasketballRight.get();
        }
    }
    else
    {
        bitmapToDraw = mFootballMid.get();
        
        // Use directional images both on ground and in air when direction keys are pressed
        if (mLeftPressed && mRightPressed) {
            // Both keys pressed - use the most recently pressed one
            if (mLastDirection == LastDirection::LEFT) {
                bitmapToDraw = mFootballLeft.get();
            } else if (mLastDirection == LastDirection::RIGHT) {
                bitmapToDraw = mFootballRight.get();
            }
        } else if (mLeftPressed) {
            bitmapToDraw = mFootballLeft.get();
        } else if (mRightPressed) {
            bitmapToDraw = mFootballRight.get();
        }
    }
    
    // Draw the bitmap at the football's position
    double width = bitmapToDraw->GetWidth();
    double height = bitmapToDraw->GetHeight();
    
    // Make basketball smaller than football
    if (mIsBasketball)
    {
        width *= 0.1;  // Make basketball 70% of original size
        height *= 0.1;
    }
    
    graphics->DrawBitmap(*bitmapToDraw, int(GetX() - width / 2), int(GetY() - height / 2), width, height);
}

/**
 * Accept a visitor for the visitor pattern
 * @param visitor ItemVisitor to accept
 */
void Football::Accept(ItemVisitor* visitor)
{
    visitor->VisitFootball(this);
}

/**
 * Handle key down events
 * @param event The key event
 */
void Football::OnKeyDown(wxKeyEvent& event)
{
    switch (event.GetKeyCode())
    {
    case WXK_LEFT:
        mLeftPressed = true;
        mLastDirection = LastDirection::LEFT;  // Track most recent direction key
        break;

    case WXK_RIGHT:
        mRightPressed = true;
        mLastDirection = LastDirection::RIGHT; // Track most recent direction key
        break;

    case WXK_SPACE:
        mSpacePressed = true;
        break;
    }
}

/**
 * Handle key up events
 * @param event The key event
 */
void Football::OnKeyUp(wxKeyEvent& event)
{
    switch (event.GetKeyCode())
    {
    case WXK_LEFT:
        mLeftPressed = false;
        // Reset last direction if this was the last pressed key
        if (mLastDirection == LastDirection::LEFT && !mRightPressed) {
            mLastDirection = LastDirection::NONE;
        }
        break;

    case WXK_RIGHT:
        mRightPressed = false;
        // Reset last direction if this was the last pressed key
        if (mLastDirection == LastDirection::RIGHT && !mLeftPressed) {
            mLastDirection = LastDirection::NONE;
        }
        break;

    case WXK_SPACE:
        mSpacePressed = false;
        break;
    }
}

/**
 * Set double jump state to true
 */
void Football::ActivateDoubleJump()
{
    mHasDoubleJump = true;
}

/**
 * Set basketball state to true and start its timer
 */
void Football::ActivateBasketball()
{
    mIsBasketball = true;
    mBasketballTimeRemaining = 0.0;
}

/**
 * Set the jump that happens after stomping an enemy
 */
void Football::ActivateStompJump()
{
    mStomping = true;
}