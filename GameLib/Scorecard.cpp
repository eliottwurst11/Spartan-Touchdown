/**
* @file Scorecard.cpp
 * @author Hamin Paik
 */

#include "pch.h"
#include "Scorecard.h"
#include <wx/graphics.h>

Scorecard::Scorecard()
{
}

/**
 * Update the scorecard's internal state.
 * @param elapsed Time since the last update in seconds.
 */
void Scorecard::Update(double elapsed)
{
    mTime += elapsed;
    mScoreUpdateTimer += elapsed;

    // Decrease the score by 1 for every second that has passed
    while (mScoreUpdateTimer >= 1.0)
    {
        if (mScore > 0)
        {
            mScore--;
        }
        mScoreUpdateTimer -= 1.0; // Subtract one second
    }

    // Count down the double jump timer
    if (mDoubleJumpTimer > 0)
    {
        mDoubleJumpTimer -= elapsed;
        if (mDoubleJumpTimer < 0)
        {
            mDoubleJumpTimer = 0;
        }
    }
}

/**
 * Draw the timer and score onto the screen.
 * @param graphics The graphics context to draw on.
 * @param width The virtual width of the window.
 * @param height The virtual height of the window.
 */
void Scorecard::Draw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height)
{
    wxFont font(wxSize(0, 60), wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    graphics->SetFont(font, wxColour(255, 0, 0));

    // --- Draw the Timer (left side) ---
    int totalSeconds = static_cast<int>(mTime);
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;
    wxString timeString = wxString::Format(L"%d:%02d", minutes, seconds);
    graphics->DrawText(timeString, 20, 10);

    // --- Draw the Score (right side) ---
    wxString scoreString = wxString::Format(L"%d", mScore);
    double textWidth, textHeight;
    graphics->GetTextExtent(scoreString, &textWidth, &textHeight);
    graphics->DrawText(scoreString, width - textWidth - 20, 10);

    // Draw the Double Jump Timer below the score if active
    if (mDoubleJumpTimer > 0)
    {
        // Use a slightly smaller font
        wxFont djFont(wxSize(0, 40), wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        graphics->SetFont(djFont, wxColour(60, 200, 60)); // Green color

        wxString djString = wxString::Format(L"Double Jump: %.1f", mDoubleJumpTimer);
        double djTextWidth, djTextHeight;
        graphics->GetTextExtent(djString, &djTextWidth, &djTextHeight);
        // Draw it below the score, aligned to the right
        graphics->DrawText(djString, width - djTextWidth - 20, 10 + textHeight + 5);
    }

    if (mLevelIsLost)
    {
        wxFont fontBig(wxSize(0, 150), wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        graphics->SetFont(fontBig, wxColour(80, 120, 220));

        // Draw the "You Lose!" message
        std::wstring lossMessage = L"You Lose!";
        wxString lossString = wxString::Format(L"%s", lossMessage);
        double lossTextWidth, lossTextHeight;
        graphics->GetTextExtent(lossString, &lossTextWidth, &lossTextHeight);
        graphics->DrawText(lossString, (width/2)-(lossTextWidth/2), (height/2)-(lossTextHeight/2));
    }

    if (mStartGrace)
    {
        wxFont levelMessage(wxSize(0,150), wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        graphics->SetFont(levelMessage, wxColour(80, 120, 220));

        std::wstring startMessage = L"Level " + std::to_wstring(mLevelNum) + L" Start!";
        wxString startString = wxString::Format(L"%s", startMessage);
        double startTextWidth, startTextHeight;
        graphics->GetTextExtent(startString, &startTextWidth, &startTextHeight);
        graphics->DrawText(startString, width/2 - startTextWidth / 2, (height/2)-(startTextHeight/2));
    }

    if (mLevelIsWon)
    {
        wxFont levelMessage(wxSize(0,150), wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        graphics->SetFont(levelMessage, wxColour(80, 120, 220));

        std::wstring startMessage = L"Level Complete!";
        wxString startString = wxString::Format(L"%s", startMessage);
        double startTextWidth, startTextHeight;
        graphics->GetTextExtent(startString, &startTextWidth, &startTextHeight);
        graphics->DrawText(startString, width/2 - startTextWidth / 2, (height/2)-(startTextHeight/2));
    }
}
