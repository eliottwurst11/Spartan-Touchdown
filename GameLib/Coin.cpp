/**
 * @file Coin.cpp
 * @author Matthew Lopez
 */

#include "pch.h"
#include "Coin.h"
#include "Level.h"
#include "LevelView.h"

using namespace std;

/// vertical speed constant for coin motion animation
const double VerticalSpeed = 800;
/// horizontal speed constant for coin motion in level 2
const double HorizontalSpeed = 25;

/// level 2 xml file used to implement sliding coins in level 2
const std::wstring level2 = L"levels/level2.xml";

/**
 * Overloaded constructor
 * @param level Level this coin is a part of
 * @param initX Initial X position of the coin in pixels
 * @param initY Initial Y position of the coin in pixels
 * @param id ID for the coin, used for level loading
 */
Coin::Coin(Level* level, double initX, double initY, std::wstring id)
    :Item(level, initX, initY, id)
{
    auto declaration = GetLevel()->GetDeclaration(id);
    mValue = declaration->GetValue();
}

/**
 * Update the state of the coin.
 *
 * Check if the coin is flying, and animate it until it is off the screen if it is.
 * If the coin is not flying, slide the coin to the left if the current level is level 2.
 *
 * @param elapsed Time passed since last call to Coin::Update() in seconds
 */
void Coin::Update(double elapsed)
{
    // calculate the height if collected
    if (mFlying)
    {
        // move enough to no longer be visible
        auto newYCandidate = this->GetY() - VerticalSpeed * elapsed;
        auto newY = std::max(newYCandidate, 0 - (this->GetImageHeight()/2));
        SetLocation(GetX(), newY);
    }

    else
    {
        // check if the current level is level2, and slide the coin
        // slowly to the left if it is
        auto currentLevel = GetLevel();
        auto currentLevelView = currentLevel->GetLevelView();
        if (currentLevelView->GetCurrentLevel() == level2)
        {
            double currentX = GetX();
            double newX = currentX - HorizontalSpeed * elapsed;
            SetLocation(newX, GetY());
        }
    }
}

