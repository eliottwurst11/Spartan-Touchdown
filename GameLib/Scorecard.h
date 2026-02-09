  /**
* @file Scorecard.h
 * @author Hamin Paik
 *
 * Manages the display of the game's timer.
 */

#ifndef GAME_SCORECARD_H
#define GAME_SCORECARD_H

#include <wx/string.h>

class wxDC;

/**
 * Manages and draws the game's heads-up display elements, like the timer.
 */
class Scorecard {
public:
    Scorecard();

    void Update(double elapsed);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);

    /**
     * Get the current score.
     * @return The score as an integer.
     */
    int GetScore() const { return mScore; }

    /**
     * Add to the current score.
     * @param score The amount to add to the score.
     */
    void AddScore(int score) { mScore += score; }

    /**
     * Reset the time for the level back to 0
     */
    void ResetTime() { mTime = 0; }

    /**
     * Reset the score for the level back to 0
     */
    void ResetScore() {mScore = 0; }

    /**
     * Set the mLevelIsLost member
     * @param boolean True if the level should be set to lost, False otherwise
     */
    void SetLevelIsLost(bool boolean) { mLevelIsLost = boolean;}

    /**
     * Check if the level is lost
     * @return True if lost, false otherwise
     */
    bool GetLevelIsLost() const { return mLevelIsLost; }

    /**
     * set the grace period indicator
     * @param grace perdio state as bool
     */
    void SetStartGrace(bool grace) { mStartGrace = grace;}

    /**
     * get the grace period indicator
     * @return the grace period state as bool
     */
    bool GetStartGrace() const { return mStartGrace; }

    /**
     * Starts the 15-second double jump countdown.
     * @param duration Time in seconds.
     */
    void StartDoubleJumpTimer(double duration) { mDoubleJumpTimer = duration; }

    /**
     * Gets the remaining time on the double jump powerup.
     * @return Time in seconds, or 0 if inactive.
     */
    double GetDoubleJumpTimer() const { return mDoubleJumpTimer; }

    /**
     * set the current level number for the scorecard
     * @param levelNum the number of the level to set
     */
    void SetLevelNum(int levelNum) { mLevelNum = levelNum; }

    /**
     * set the level won display member
     * @param win the win state of the game to set
     */
    void SetLevelIsWon(bool win) { mLevelIsWon = win; }

private:
    /// The total elapsed time for the level in seconds
    double mTime = 0;

    /// The current score for the level
    int mScore = 0;

    /// Timer to track when to decrease the score (once per second)
    double mScoreUpdateTimer = 0;

    /// Bool to track when to display the "You Lose!" message
    bool mLevelIsLost;

    /// bool to track when to display level complete message
    bool mLevelIsWon;

    /// bool to track when to display level start message
    bool mStartGrace;

    /// Timer for the double jump powerup
    double mDoubleJumpTimer = 0;

    /// the level number as an integer
    int mLevelNum = 0;

};

#endif //GAME_SCORECARD_H
