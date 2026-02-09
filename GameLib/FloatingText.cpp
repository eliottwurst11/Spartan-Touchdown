/**
 * @file FloatingText.cpp
 * @author Hamin Paik
 */

#include "pch.h"
#include "FloatingText.h"

/**
 * Constructor
 * @param text The text to display (e.g., L"Double Jump!")
 * @param x The starting X location (world-space)
 * @param y The starting Y location (world-space)
 * @param growing optional param which indicates if the text should increase in size
 * @param yVelocity optional param which indicates a specific Y velocity
 * @param fontSize optional param which indicates a specific desired font size
 * @param darkGreen optional param which indicates if the text should be dark green
 * where the default is a lighter green
 */
FloatingText::FloatingText(std::wstring text, double x, double y,
    bool growing,
    double yVelocity,
    double fontSize,
    bool darkGreen
    )
    : mText(text), mX(x), mY(y), mGrowing(growing), mFontSize(fontSize),
        mYVelocity(yVelocity), mDarkGreen(darkGreen)
{
    // Set the timer to its full duration
    mTimer = mDuration;
}

/**
 * Update the text's position and lifetime
 * @param elapsed Time since last update
 */
void FloatingText::Update(double elapsed)
{
    if (mTimer > 0)
    {
        // Move the text
        mY += mYVelocity * elapsed;

        // Grow the text
        if (mGrowing)
        {
            mFontSize += mGrowFactor * elapsed;
        }

        // Count down the timer
        mTimer -= elapsed;
    }
}

/**
 * Draw the text to the screen
 * @param graphics The graphics context to draw on
 */
void FloatingText::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (IsFinished())
    {
        return; // Don't draw if finished
    }

    // Calculate opacity. Fades out in the last 0.5 seconds.
    double opacity = 1.0;
    if (mTimer < 0.5)
    {
        opacity = mTimer / 0.5; // Fades from 1.0 down to 0
    }

    // Set font and color
    wxFont font(wxSize(0, mFontSize), wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    // Green color with fading alpha
    if (mDarkGreen)
    {
        graphics->SetFont(font, wxColour(0, 100, 0, (int)(opacity * 255)));
    }
    else
    {
        graphics->SetFont(font, wxColour(60, 200, 60, (int)(opacity * 255)));
    }

    // Center the text over its X, Y coordinate
    double textWidth, textHeight;
    graphics->GetTextExtent(mText, &textWidth, &textHeight);
    graphics->DrawText(mText, mX - (textWidth / 2), mY - (textHeight / 2));
}