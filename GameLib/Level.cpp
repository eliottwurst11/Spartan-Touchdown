/**
 * @file Level.cpp
 * @author nishi
 */

#include "pch.h"
#include "Level.h"


#include <map>

// #include "Background"
#include <thread> //< Used for a timed screen freeze
#include <chrono>

#include "Platform.h"
#include "Coin.h"
#include "Wall.h"
#include "Enemy.h"
#include "Goalpost.h"
#include "PowerUp.h"
#include "Football.h"

#include "Declaration.h"
#include "CoinDeclaration.h"
#include "PlatformDeclaration.h"
#include "PlatformBreakable.h"
#include "PlatformBreakableDeclaration.h"
#include "Picture.h"

#include <wx/dcclient.h>
#include <wx/xml/xml.h>

#include "CoinIncrementVisitor.h"
#include "CoinVisitor.h"
#include "EnemyBoss.h"
#include "EnemyVisitor.h"
#include "GoalpostVisitor.h"
#include "PowerUpVisitor.h"
#include "PowerUpDoubleJump.h"
#include "PowerUpBasketball.h"
#include "PowerUpPoints.h"
#include "PowerUpPointsVisitor.h"
#include "EnemyChaser.h"
#include "EnemyChaserVisitor.h"
#include "EnemyStompable.h"
#include "EnemyStompableVisitor.h"
#include "LevelView.h"
#include "FloatingText.h"
#include "PowerUpBasketballVisitor.h"
#include "PowerUpDoubleJumpVisitor.h"

using namespace std;

/// time limit for the football's invulnerability state
const double invulnerableTimeLimit = 0.3;

Level::Level() {}

Level::~Level() {}

/**
 * Load all items in the level
 * @param filename The level file name to load
 * @param levelView The LevelView object that holds the level
 * @return a pointer to the level's football, or nullptr if there was an error
 */
std::shared_ptr<Football> Level::Load(const std::wstring& filename, LevelView* levelView) {
    mItems.clear();
    mFloatingTexts.clear();
    //mScorecard.SetStartGrace(true);
    mIsLevel4 = false;
    mBossGoalpostSpawned = false;
    try {
        wxXmlDocument doc;
        if (!doc.Load(filename)) {
            // File doesn't exist or can't be loaded - fail silently
            return nullptr;
        }

        auto root = doc.GetRoot();
        if (!root) {
            return nullptr;
        }

        root->GetAttribute(L"width", L"0").ToDouble(&mWidth);
        root->GetAttribute(L"height", L"0").ToDouble(&mHeight);
        root->GetAttribute(L"start-x", L"0").ToDouble(&mStartX);
        root->GetAttribute(L"start-y", L"0").ToDouble(&mStartY);

        auto declarationsNode = root->GetChildren();
        if (!declarationsNode) {
            return nullptr;
        }

        auto declNode = declarationsNode->GetChildren();
        while (declNode) {
            wxString id = declNode->GetAttribute(L"id");
            wxString name = declNode->GetName();

            if (name == L"platform")
            {
                wxString leftImage = declNode->GetAttribute(L"left-image");
                wxString midImage = declNode->GetAttribute(L"mid-image");
                wxString rightImage = declNode->GetAttribute(L"right-image");
                auto decl = make_shared<PlatformDeclaration>(std::wstring(id.c_str()), std::wstring(leftImage.c_str()), std::wstring(midImage.c_str()), std::wstring(rightImage.c_str()));
                mDeclarations[std::wstring(id.c_str())] = decl; // <-- FIX 1
            }
            else if (name == L"platform-breakable")
            {
                wxString image = declNode->GetAttribute(L"image");
                wxString breakingImage = declNode->GetAttribute(L"breaking-image");
                auto decl = make_shared<PlatformBreakableDeclaration>(std::wstring(id.c_str()), std::wstring(image.c_str()), std::wstring(breakingImage.c_str()));
                mDeclarations[std::wstring(id.c_str())] = decl; // <-- FIX 2
            }
            else if (name == L"coin")
            {
                wxString image = declNode->GetAttribute(L"image");
                wxString value = declNode->GetAttribute(L"value");
                int coinValue;
                value.ToInt(&coinValue);
                auto decl = make_shared<CoinDeclaration>(std::wstring(id.c_str()), std::wstring(image.c_str()), coinValue);
                mDeclarations[std::wstring(id.c_str())] = decl; // <-- FIX 3
            }
            else // For all simple declarations (background, wall, enemy, etc.)
            {
                wxString image = declNode->GetAttribute(L"image");
                auto decl = make_shared<Declaration>(std::wstring(id.c_str()), std::wstring(image.c_str()));
                mDeclarations[std::wstring(id.c_str())] = decl; // <-- FIX 4
            }

            declNode = declNode->GetNext();
        }


        auto itemsNode = declarationsNode->GetNext();
        if (!itemsNode) {
            return nullptr;
        }


        auto itemNode = itemsNode->GetChildren();
        while (itemNode) {
            wxString id = itemNode->GetAttribute(L"id");
            wxString name = itemNode->GetName();

            auto declShared = GetDeclaration(std::wstring(id.c_str()));

            if (!declShared) {
                // This ID has no declaration, skip it
                itemNode = itemNode->GetNext();
                continue;
            }

            std::shared_ptr<Item> newItem;

            if (name == L"background") {
                double x, y;
                itemNode->GetAttribute(L"x", L"0").ToDouble(&x);
                itemNode->GetAttribute(L"y", L"0").ToDouble(&y);
                newItem = make_shared<Background>(this, x, y, wstring(id.c_str()));
            }
            else if (name == L"platform") {
                double x, y, width, height;
                itemNode->GetAttribute(L"x", L"0").ToDouble(&x);
                itemNode->GetAttribute(L"y", L"0").ToDouble(&y);
                itemNode->GetAttribute(L"width", L"0").ToDouble(&width);
                itemNode->GetAttribute(L"height", L"0").ToDouble(&height);
                newItem = make_shared<Platform>(this, x, y, width, height, wstring(id.c_str()));
            }
            else if (name == L"platform-breakable") {
                double x, y, width, height;
                itemNode->GetAttribute(L"x", L"0").ToDouble(&x);
                itemNode->GetAttribute(L"y", L"0").ToDouble(&y);
                itemNode->GetAttribute(L"width", L"0").ToDouble(&width);
                itemNode->GetAttribute(L"height", L"0").ToDouble(&height);
                newItem = make_shared<PlatformBreakable>(this, x, y, width, height, wstring(id.c_str()));

            }
            else if (name == L"coin") {
                double x, y;
                itemNode->GetAttribute(L"x", L"0").ToDouble(&x);
                itemNode->GetAttribute(L"y", L"0").ToDouble(&y);
                newItem = make_shared<Coin>(this, x, y, wstring(id.c_str()));
            }
            else if (name == L"wall") {
                double x, y, width, height;
                itemNode->GetAttribute(L"x", L"0").ToDouble(&x);
                itemNode->GetAttribute(L"y", L"0").ToDouble(&y);
                itemNode->GetAttribute(L"width", L"0").ToDouble(&width);
                itemNode->GetAttribute(L"height", L"0").ToDouble(&height);
                newItem = make_shared<Wall>(this, x, y, width, height, wstring(id.c_str()));
            }
            else if (name == L"enemy") {
                double x, y;
                itemNode->GetAttribute(L"x", L"0").ToDouble(&x);
                itemNode->GetAttribute(L"y", L"0").ToDouble(&y);
                newItem = make_shared<Enemy>(this, x, y, wstring(id.c_str()));
            }
            else if (name == L"goalpost") {
                double x, y;
                itemNode->GetAttribute(L"x", L"0").ToDouble(&x);
                itemNode->GetAttribute(L"y", L"0").ToDouble(&y);
                newItem = make_shared<Goalpost>(this, x, y, wstring(id.c_str()));
            }
            else if (name == L"power-up") {
                double x, y;
                itemNode->GetAttribute(L"x", L"0").ToDouble(&x);
                itemNode->GetAttribute(L"y", L"0").ToDouble(&y);
                newItem = make_shared<PowerUpPoints>(this, x, y, wstring(id.c_str()));
            }
            else if (name == L"power-up-double-jump") {
                if (filename.find(L"level3.xml") != std::wstring::npos) {
                    double x, y;
                    itemNode->GetAttribute(L"x", L"0").ToDouble(&x);
                    itemNode->GetAttribute(L"y", L"0").ToDouble(&y);
                    newItem = make_shared<PowerUpDoubleJump>(this, x, y, wstring(id.c_str()));
                }
            }
            else if (name == L"power-up-basketball") {
                if (filename.find(L"level3.xml") != std::wstring::npos) {
                    double x, y;
                    itemNode->GetAttribute(L"x", L"0").ToDouble(&x);
                    itemNode->GetAttribute(L"y", L"0").ToDouble(&y);
                    newItem = make_shared<PowerUpBasketball>(this, x, y, wstring(id.c_str()));
                }
            }
            else if (name == L"enemy-chaser")
            {
                double x, y;
                itemNode->GetAttribute(L"x", L"0").ToDouble(&x);
                itemNode->GetAttribute(L"y", L"0").ToDouble(&y);
                newItem = make_shared<EnemyChaser>(this, x, y, wstring(id.c_str()));
            }
            else if (name == L"enemy-stompable")
            {
                double x, y;
                itemNode->GetAttribute(L"x", L"0").ToDouble(&x);
                itemNode->GetAttribute(L"y", L"0").ToDouble(&y);
                newItem = make_shared<EnemyStompable>(this, x, y, wstring(id.c_str()));
            }
            else if (name == L"enemy-boss")
            {
                double x, y;
                itemNode->GetAttribute(L"x", L"0").ToDouble(&x);
                itemNode->GetAttribute(L"y", L"0").ToDouble(&y);
                newItem = make_shared<EnemyBoss>(this, x, y, wstring(id.c_str()));
            }

            if (newItem != nullptr)
            {
                mItems.push_back(newItem);
            }

            itemNode = itemNode->GetNext();
        }


        // Create football, set its location, and return it to be added to the level
        std::shared_ptr<Football> football = std::make_shared<Football>(this);
        football->SetLocation(mStartX, mStartY);
        Add(football);
        mFootball = football;

        // If loading level 4, automatically activate basketball
        if (filename.find(L"level4.xml") != std::wstring::npos)
        {
            mFootball->ActivateBasketball();
            mIsLevel4 = true;
        }

        mLevelView = levelView;

        mStartGrace = true;

        mScorecard.StartDoubleJumpTimer(0);

        return football;
    }
    catch (...) {
        // Catch any exceptions and fail silently
        return nullptr;
    }
}


/**
 * Update the state of the level, including the scorecard.
 * @param elapsed Time since the last update in seconds.
 */
void Level::Update(double elapsed)
{
    // short circuit the update if the level is in the freeze state
    if (mFreeze)
    {
        mFreezeTimer += elapsed;
        if (mFreezeTimer > 2)
        {
            EndLoseLevel();
        }
        else
        {
            return;
        }
    }

    if (mLevelWon)
    {
        mFreezeTimer += elapsed;
        if (mFreezeTimer > 2)
        {
            EndWinLevel();
        }
        else
        {
            return;
        }
    }

    if (mStartGrace)
    {
        mFreezeTimer += elapsed;
        if (mFreezeTimer > 2)
        {
            EndGracePeriod();
        }
        else
        {
            return;
        }
    }
    else
    {
        mScorecard.SetStartGrace(false);
    }

    if (mFootball->GetY() > 1024)
    {
        StartLoseLevel();
    }

    for (auto& item : mItems) {
        item->Update(elapsed);
    }

    auto textIt = mFloatingTexts.begin();
    while (textIt != mFloatingTexts.end())
    {
        (*textIt)->Update(elapsed);
        if ((*textIt)->IsFinished())
        {
            textIt = mFloatingTexts.erase(textIt);
        }
        else
        {
            ++textIt;
        }
    }

    // Remove items that are "broken" (like finished breakable platforms)
    auto it = std::remove_if(mItems.begin(), mItems.end(),
        [](const std::shared_ptr<Item>& item) {
            return item->IsBroken();
        });
    mItems.erase(it, mItems.end());

    // Update the scorecard to advance its timer
    mScorecard.Update(elapsed);

    if (mScorecard.GetDoubleJumpTimer() <= 0)
    {
        mFootball->ResetDoubleJump();
    }

    // check for enemy collision
    EnemyVisitor enemyVisitor(mFootball);
    Accept(&enemyVisitor);
    if (enemyVisitor.GetEnemy())
    {
        StartLoseLevel();
    }

    // check for goalpost collision
    GoalpostVisitor goalpostVisitor(mFootball);
    Accept(&goalpostVisitor);
    if (goalpostVisitor.GetGoalpost())
    {
        StartWinLevel();

    }

    while (true)
    {
        CoinVisitor visitor(mFootball);
        Accept(&visitor);

        // Get the coin that was hit
        Coin* collectedCoin = visitor.GetCoin();

        // If a coin was hit...
        if (collectedCoin != nullptr && !collectedCoin->IsFlying())
        {
            // Add its value to the score
            mScorecard.AddScore(collectedCoin->GetValue());

            // Set the coin to start its flying animation
            collectedCoin->SetFlying();

            //create the coin text based on value and position and add it to the floating texts
            auto coinText = std::make_shared<FloatingText>(std::to_wstring(collectedCoin->GetValue()),
                collectedCoin->GetX() + 15,
                collectedCoin->GetY() + 15,
                false,
                -800,
                30,
                true
                );
            mFloatingTexts.push_back(coinText);
        }
        else
        {
            // If no uncollected coin was hit, we are done.
            break;
        }
    }

    // Check for the double jump power up collision
    PowerUpDoubleJumpVisitor powerUpDoubleJumpVisitor(mFootball);
    Accept(&powerUpDoubleJumpVisitor);
    PowerUpDoubleJump* collectedDoubleJump = powerUpDoubleJumpVisitor.GetPowerUpDoubleJump();
    if (collectedDoubleJump != nullptr)
    {
        mFootball->ActivateDoubleJump();
        collectedDoubleJump->ConsumePowerUp();
        collectedDoubleJump->StartFalling();
        auto newText = std::make_shared<FloatingText>(L"Double Jump!",
                                                      collectedDoubleJump->GetX(),
                                                      collectedDoubleJump->GetY());
        mFloatingTexts.push_back(newText);
        mScorecard.StartDoubleJumpTimer(15.0);
    }

    // Check for the basketball power up collision
    PowerUpBasketballVisitor powerUpBasketballVisitor(mFootball);
    Accept(&powerUpBasketballVisitor);
    PowerUpBasketball* collectedBasketball = powerUpBasketballVisitor.GetPowerUpBasketball();
    if (collectedBasketball != nullptr)
    {
        mFootball->ActivateBasketball();
        collectedBasketball->ConsumePowerUp();
        collectedBasketball->StartFalling();

        auto newText = std::make_shared<FloatingText>(L"Basketball!",
                                                          collectedBasketball->GetX(),
                                                          collectedBasketball->GetY());
        mFloatingTexts.push_back(newText);

        // Check if this is the door in level 3 - transition to level 4
        if (mLevelView->GetCurrentLevel().find(L"level3.xml") != std::wstring::npos)
        {
            // Transition to level 4
            mLevelView->LoadNextLevel();
        }
    }


    // Check for points power up collision
    PowerUpPointsVisitor powerUpPointsVisitor(mFootball);
    Accept(&powerUpPointsVisitor);
    PowerUpPoints* collectedPointsPower = powerUpPointsVisitor.GetPowerUpPoints();
    if (collectedPointsPower != nullptr && !collectedPointsPower->IsConsumed())
    {
        // create the text and add it to the level texts
        auto powerupText = std::make_shared<FloatingText>(L"Power Up!",
            collectedPointsPower->GetX(),
            collectedPointsPower->GetY(),
            true,
            -700
             );
        mFloatingTexts.push_back(powerupText);

        // increment the points here, then consume
        CoinIncrementVisitor incrementer = CoinIncrementVisitor();
        Accept(&incrementer);
        collectedPointsPower->ConsumePowerUp();
        collectedPointsPower->StartFalling();
    }

    // Check for EnemyChaser collision
    EnemyChaserVisitor enemyChaserVisitor(mFootball);
    Accept(&enemyChaserVisitor);
    EnemyChaser* enemyChaser = enemyChaserVisitor.GetEnemyChaser();
    if (enemyChaser != nullptr)
    {
        StartLoseLevel();
    }

    // Only handle football collision with stompable enemy when the football is not invulnerable
    if (mFootball->GetVulnerable())
    {
        EnemyStompableVisitor enemyStompableVisitor(mFootball);
        Accept(&enemyStompableVisitor);
        auto stomped = enemyStompableVisitor.GetEnemyStomped();
        if (enemyStompableVisitor.GetFootballDefeated())
        {
            StartLoseLevel();
        }
        else if (stomped != nullptr)
        {
            // create the text and add it to the level texts
            auto powerupText = std::make_shared<FloatingText>(L"Stomp!",
                stomped->GetX(),
                stomped->GetY(),
                true,
                -700
                 );
            auto gogText = std::make_shared<FloatingText>(L"OUCH!",
                stomped->GetX() + 35,
                stomped->GetY() - 65,
                false,
                500,
                35,
                true
                );
            mFloatingTexts.push_back(powerupText);
            mFloatingTexts.push_back(gogText);
            stomped->SetStomped();
            mFootball->ActivateStompJump();
        }
    }
    else
    {
        // count down the invulnerability timer
        *(mFootball->GetInvulnerableTime()) += elapsed;
        if ( *(mFootball->GetInvulnerableTime()) > invulnerableTimeLimit)
        {
            mFootball->SetVulnerable(true);
        }
    }
}

/**
 * Draw all items in the level.
 * @param graphics The graphics context to draw on.
 */
void Level::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Draw all the game items
    for (auto& item : mItems)
    {
        item->Draw(graphics);
    }

    for (auto& text : mFloatingTexts)
    {
        text->Draw(graphics);
    }

}

/**
 * Accept an ItemVisitor for the entire collection of items
 * @param visitor ItemVisitor for a collection
 */
void Level::Accept(ItemVisitor* visitor)
{
    for (auto& item : mItems)
    {
        item->Accept(visitor);
    }
}

/**
 * Search for a picture in the list of pictures using its wstring path
 * @param name The path to the image name
 * @return pointer to the picture
 */
std::shared_ptr<Picture> Level::GetPicture(const wstring name)
{
    auto i = mPictures.find(name);
    if (i != mPictures.end())
    {
        return i->second;
    }

    try {
        std::wstring path = L"images/" + name;
        auto new_picture = std::make_shared<Picture>(path);
        mPictures[name] = new_picture;
        return new_picture;
    }
    catch (...) {
        // If image loading fails, return a nullptr or create a default picture
        return nullptr;
    }

}

/**
 * Looks for the declaration made with the specific id.
 * If none are present then a nullptr is returned signifying an
 * item was trying to be made with a non-existent declaration
 *
 * @param id The id of the declaration
 * @return The declaration made with that specific id
 */
std::shared_ptr<Declaration> Level::GetDeclaration(const wstring id)
{
    auto i = mDeclarations.find(id);
    if (i != mDeclarations.end())
    {
        return i->second;
    }
    return nullptr;
}

/**
 * Add an item to the level.
 * @param item The item to add.
 */
void Level::Add(std::shared_ptr<Item> item)
{
    mItems.push_back(item);
}

/**
 * Remove an item from the level
 * @param item The item to remove
 */
void Level::Remove(Item* item)
{
    auto it = std::remove_if(mItems.begin(), mItems.end(),
        [item](const std::shared_ptr<Item>& i) {
            return i.get() == item;
        });

    mItems.erase(it, mItems.end());
}

/**
 * Reset the football's double jump capability
 */
void Level::ResetFootballDoubleJump()
{
    if (mFootball != nullptr) {
        mFootball->ResetDoubleJump();
    }
}

/**
 * Reset the basketball back to a football
 */
void Level::ResetFootballBasketball()
{
    if (mFootball != nullptr) {
        mFootball->ResetBasketball();
    }
}

/**
 * Function called when a loss state should begin in the level. Freezes the window and displays a message
 */
void Level::StartLoseLevel()
{
    mScorecard.SetLevelIsLost(true);
    mFreeze = true;
}

/**
 * Function called when the loss state should be ended. Unfreezes the window and resets the level.
 */
void Level::EndLoseLevel()
{
    mScorecard.SetLevelIsLost(false);

    if (mLevelView->GetCurrentLevel().find(L"level4.xml") != std::wstring::npos)
    {
        mLevelView->LoadLevelN(L"levels/level3.xml");
        mLevelView->SetLevelNum(3);
        mScorecard.SetLevelNum(3);
    }
    else
    {
        // This is the original behavior for all other levels
        mLevelView->ResetLevel();
    }
    mFreeze = false;
    mFreezeTimer = 0;
    mStartGrace = true;
}

/**
 * End the grace period at the beginning of the level
 */
void Level::EndGracePeriod()
{
    mStartGrace = false;
    mFreezeTimer = 0;
}

/**
 * start the win level sequence and set the scorecard to reflect the state
 */
void Level::StartWinLevel()
{
    mLevelWon = true;
    mScorecard.SetLevelIsWon(true);
}

/**
 * end the win level sequence and set the scorecard to reflect the state
 */
void Level::EndWinLevel()
{
    mLevelWon = false;
    mScorecard.SetLevelIsWon(false);
    mFreezeTimer = 0;

    // Check if we're completing level 4 - return to level 3 beginning
    if (mLevelView->GetCurrentLevel().find(L"level4.xml") != std::wstring::npos
        || mLevelView->GetCurrentLevel().find(L"level3.xml") != std::wstring::npos)
    {
        // Load level 3 from the beginning
        mLevelView->LoadLevelN(L"levels/level3.xml");
        // Set the correct level number for level 3
        mLevelView->SetLevelNum(3);
        mScorecard.SetLevelNum(3);
        // Note: Basketball state will be reset automatically when level 3 loads
        // since level 3 doesn't have automatic basketball activation
    }
    else
    {
        // Normal level progression for other levels
        mLevelView->LoadNextLevel();
    }
}

/**
 * Spawns the goalpost on Level 4 after the boss is defeated.
 * This is called by EnemyBoss when its health reaches zero.
 * @param x X-coordinate where the boss died
 * @param y Y-coordinate where the boss died
 */
void Level::SpawnBossGoalpost(double x, double y)
{
    if (mIsLevel4 && !mBossGoalpostSpawned)
    {
        auto decl = GetDeclaration(L"i011");
        if (decl != nullptr)
        {
            auto goalpost = make_shared<Goalpost>(this, 0, 892, L"i011");
            Add(goalpost);
            mBossGoalpostSpawned = true;
        }
    }
}