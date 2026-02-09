/**
 * @file Football.h
 * @author Nishit Nagpal
 *
 * Definition for the football, which the player moves through each level
 * by using the football's scrolling functionality.
 */

#ifndef GAME_FOOTBALL_H
#define GAME_FOOTBALL_H
#include "Item.h"

/**
 * Football that the player moves through the levels
 */
class Football : public Item {
private:
    /// Velocity components
    double mVelocityX = 0.0;   ///< Velocity in X direction
    double mVelocityY = 0.0;   ///< Velocity in Y direction

    /// Key states for movement
    bool mLeftPressed = false;   ///< true if left arrow key was pressed
    bool mRightPressed = false;   ///< true if right arrow key was pressed
    bool mSpacePressed = false;   ///< true if space bar was pressed
    
    /// Track the most recently pressed direction key for precedence
    enum class LastDirection { NONE, LEFT, RIGHT };   ///< enumerate for motion direction
    LastDirection mLastDirection = LastDirection::NONE;   ///< most recently selected direction

    /// Ground state
    bool mOnGround = false;

    /// Indicates an enemy stomp to initiate a jump
    bool mStomping = false;

    /// Double jump state
    bool mHasDoubleJump = false;   ///< true if the football collided with a PowerUpDoubleJump
    int mDoubleJumpsUsed = 0;   ///< track the number of extra jumps the football has used

    /// Basketball transformation state
    bool mIsBasketball = false;   /// true if the football image was changed to a basketball
    double mBasketballTimeRemaining = 0.0;   /// timer for the PowerUpBasketball image change effect

    /// Animation state
    double mStepTime = 0.0;   ///< step time
    const double mStepDuration = 0.3;   ///< step duration
    double mStepOffset = 0.0;   ///< step offset
    const double mMaxStepOffset = 5.0;   ///< maximum offset

    /// Basketball permanence (for level 4)
    bool mBasketballPermanent = false;   ///< if true, basketball state never times out

    /// Track whether the football can currently be hit by enemies
    bool mVulnerable = true;          ///< true if football can collide with enemies
    double mInvulnerableTimer = 0.0;  ///< timer for the limited invulnerability state

    /// Football images for different states
    std::unique_ptr<wxBitmap> mFootballMid;   ///< image when the football is not moving left or right
    std::unique_ptr<wxBitmap> mFootballLeft;   ///< image when the football is moving left
    std::unique_ptr<wxBitmap> mFootballRight;   ///< image when the football is moving right
    
    /// Basketball images for different states
    std::unique_ptr<wxBitmap> mBasketballMid;   ///< image when the basketball is not moving left or right
    std::unique_ptr<wxBitmap> mBasketballLeft;   ///< image when the basketball is moving left
    std::unique_ptr<wxBitmap> mBasketballRight;   ///< image when the basketball is moving right



public:
    Football(Level *level);

    /// disable the default constructor
    Football() = delete;

    /// disable the copy constructor
    Football(const Football &) = delete;

    /// disable assignment operator
    void operator=(const Football &) = delete;

    bool HitTest(int x, int y);

    /// New methods for movement
    void Update(double elapsed) override;
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void Accept(ItemVisitor* visitor) override;
    void OnKeyDown(wxKeyEvent& event);
    void OnKeyUp(wxKeyEvent& event);
    
    /// Double jump methods
    void ActivateDoubleJump();

    /**
     * Check if the football can double jump
     * @return true if it has consumed a PowerUpDoubleJump object and it has not used a double jump
     */
    bool CanDoubleJump() const { return mHasDoubleJump && mDoubleJumpsUsed < 1; }

    /**
     * End the double jump state
     */
    void ResetDoubleJump() { mHasDoubleJump = false; mDoubleJumpsUsed = 0; }
    
    /// Basketball transformation methods
    void ActivateBasketball();

    /// Activate the jump after stomping an enemy
    void ActivateStompJump();

    /**
     * Permanently keep the basketball form (no timer countdown)
     * @param permanent true to make basketball permanent
     */
    void SetBasketballPermanent(bool permanent) { mBasketballPermanent = permanent; if (permanent) { mIsBasketball = true; } }

    /**
     * End the basketball image display state
     */
    void ResetBasketball() { mIsBasketball = false; mBasketballTimeRemaining = 0.0; }

    /**
     * Get the value of the vulnerable state
     * @returns value of the vulnerable state
     */
    bool GetVulnerable() const { return mVulnerable; }

    /**
     * Set the invulnerability state
     * @param boolean True if the football is currently vulnerable
     */
    void SetVulnerable(bool boolean=true) { mVulnerable = boolean; }

    /**
     * Get access to the invulnerability timer
     * @return pointer to the invulnerability timer
     */
    double* GetInvulnerableTime() { return &mInvulnerableTimer; }
};

#endif //GAME_FOOTBALL_H