/**
 * @file Level.h
 * @author nishi
 *
 *
 * Manages all items and the scorecard for a level.
 */

#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include <map>
#include <vector>
#include <memory>
#include "Item.h"
#include "Scorecard.h"

#include <vector>
#include <memory>
#include <string>
#include "FloatingText.h"
#include "Background.h"
#include "Football.h"
#include "Item.h"

class Item;
class wxDC;
class wxXmlNode;
class Background;
class Declaration;
class LevelView;
class EnemyBoss;

/**
 * class for a single game level
 * It is responsible for loading all its contents from an XML file
 * and managing all the objects within it.
 */
class Level {
public:
    /// Default constructor
    Level();

    virtual ~Level();

    void Add(std::shared_ptr<Item> item);

    /// removes an item from the level given the pointer
    void Remove(Item* item);
    
    /// Reset football's double jump state
    void ResetFootballDoubleJump();
    
    /// Reset football's basketball transformation state
    void ResetFootballBasketball();

    std::shared_ptr<Football> Load(const std::wstring& filename, LevelView* levelView);

    void Update(double elapsed);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics);


    /**
     * Gets a reference to the level's scorecard.
     * @return A reference to the Scorecard object.
     */
    Scorecard& GetScorecard() { return mScorecard; }

    /**
     * Getter for the level view
     * @returns Pointer to the LevelView member
     */
    LevelView* GetLevelView() { return mLevelView; }

    /**
     * Getter for the football
     * @return Pointer to the level's football
     */
    std::shared_ptr<Football> GetFootball() { return mFootball; }

    void Accept(ItemVisitor* visitor);

    std::shared_ptr<Picture> GetPicture(std::wstring name);

    std::shared_ptr<Declaration> GetDeclaration(std::wstring id);

    /**
     * Get the freeze state of the game
     * @returns true if the level is currently frozen
     */
    bool GetFreeze() { return mFreeze; }

    /**
     * toggle the freeze state of the game
     */
    void ToggleFreeze() { mFreeze ? mFreeze = false : mFreeze = true; }

    /**
     * Reset the freeze timer
     */
    void ResetFreeze() { mFreezeTimer = 0; }

    /// start the lose level sequence
    void StartLoseLevel();

    /// end the lose level sequence
    void EndLoseLevel();

    /// reset the variable that indicate the grace period at start of levels
    void EndGracePeriod();

    /**
     * Get the grace period state of the game
     * @returns true if the game is currently in the grace period
     */
    bool GetGracePeriod() { return mStartGrace; }

    /// Spawns the goalpost on Level 4 after the boss is defeated.
    void SpawnBossGoalpost(double x, double y);

    /// Start the sequence to win the level
    void StartWinLevel();

    /// end the sequence after winning the level
    void EndWinLevel();

    /**
     * Gets the list of floating text objects (for testing).
     * @return A const reference to the vector of floating text.
     */
    const std::vector<std::shared_ptr<FloatingText>>& GetFloatingTexts() const { return mFloatingTexts; }

private:
    /// hold the football of the level
    std::shared_ptr<Football> mFootball;

    /// Pointer to the LevelView that holds this level
    LevelView* mLevelView;

    /// Hold the freeze state of the animation
    bool mFreeze = false;

    /// hold the grace period state of the level
    bool mStartGrace = true;

    /// hold the level won state of the level
    bool mLevelWon = false;

    /// Track time since the animation was frozen
    double mFreezeTimer = 0;

    /// A list of all items in the level.
    std::vector<std::shared_ptr<Item>> mItems;

    /// A list of animated text objects
    std::vector<std::shared_ptr<FloatingText>> mFloatingTexts;

    /// The scorecard for this level.
    Scorecard mScorecard;

    double mWidth = 0;   ///< The total width of the level in virtual pixels.
    double mHeight = 0;  ///< The total height of the level (renamed from mLength to match XML).
    double mStartX = 0;  ///< The initial X starting position for the football.
    double mStartY = 0;  ///< The initial Y starting position for the football.

    /// map that holds the pictures for the level
    std::map<std::wstring, std::shared_ptr<Picture>> mPictures;

    /// map that holds the declarations for the level
    std::map<std::wstring, std::shared_ptr<Declaration>> mDeclarations;

    /**
     * Check if the item is in a 'broken' state (relevant for breakable items).
     * Base implementation returns false.
     * @return true if the item is considered broken.
     */
    virtual bool IsBroken() const { return false; }

    // --- LINKS from your design diagram ---


    /// Link to Background: A list of all non-interactive background images.
    /// We keep these separate to ensure they are always drawn first (in the back).
    //std::vector<std::shared_ptr<Background>> mBackgrounds;
    //std::shared_ptr<Background> mBackground;

    /// Flag to track if we are currently on level 4
    bool mIsLevel4 = false;

    /// Flag to track if we have spawned the goalpost after the boss kill
    bool mBossGoalpostSpawned = false;

};

#endif //GAME_LEVEL_H

