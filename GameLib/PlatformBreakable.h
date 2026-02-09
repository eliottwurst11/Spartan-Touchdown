/**
 * @file PlatformBreakable.h
 * @author Eliott Wurst
 * @author Hamin Paik
 *
 * Definition for the PlatformBreakable class.
 *
 * If the player stands on the PlatformBreakable object, the object begins to break, and after a set period of time,
 * it is removed from the level.
 */

#ifndef GAME_PLATFORMBREAKABLE_H
#define GAME_PLATFORMBREAKABLE_H

#include "Item.h"
#include "Picture.h"
#include "PlatformBreakableDeclaration.h"

/**
 * Class for a platform that starts to break after the player has stood on it
 */
class PlatformBreakable : public Item {
private:
    /// The list of states of the breakable platform
    enum class State { Solid, Breaking, Broken };

    /// The state of the platform
    State mState = State::Solid;

    /// A timer to track breaking time
    double mTimer = 0.0;

    /// The picture object for the 'solid' state
    std::shared_ptr<Picture> mSolidPicture;

    /// The bitmap for the 'solid' state
    std::shared_ptr<wxBitmap> mSolidBitmap;

    /// The picture object for the 'breaking' state
    std::shared_ptr<Picture> mBreakingPicture;

    /// The bitmap for the 'breaking' state
    std::shared_ptr<wxBitmap> mBreakingBitmap;

    /// Width of the platform
    int mWidth;

    /// Height of the platform
    int mHeight;
public:

    PlatformBreakable(Level* level, double initX, double initY, int width, int height, std::wstring id);

    /// disable the default constructor
    PlatformBreakable() = delete;

    /// disable the copy constructor
    PlatformBreakable(const PlatformBreakable&) = delete;

    /// disable assignment operator
    void operator=(const PlatformBreakable&) = delete;

    /**
     * Triggers the platform to start its breaking sequence.
     * Called by the Football when it lands on it.
     */
    void TriggerBreak();

    /**
     * Handles updates for animation
     * @param elapsed the time since the last update
     */
    void Update(double elapsed) override;


    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Check if the platform is in a 'broken' state and should be removed.
     * @return true if the platform is broken.
     */
    bool IsBroken() const override { return mState == State::Broken; }

    void Accept(ItemVisitor* visitor) override;

    /**
     * Returns the width of the entire platform. Overrides
     * ImageWidth as we are only interested in the platform
     * as a whole and not the segments
     * @return the width of the platform in pixels
     */
    double GetImageWidth() const override { return mWidth; }

    /**
     * Returns the height of the entire platform. Overrides
     * ImageHeight as we are only interested in the platform
     * as a whole and not the segments
     * @return the height of the platform in pixels
     */
    double GetImageHeight() const override { return mHeight; }

    bool CollisionTest(Item* item);

};


#endif //GAME_PLATFORMBREAKABLE_H