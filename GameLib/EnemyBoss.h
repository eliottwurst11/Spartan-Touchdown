/**
 * @file EnemyBoss.h
 * @author Beckham Lee
 * @author Eliott Wurst
 *
 * Holds the boss class
 */

#ifndef GAME_ENEMYBOSS_H
#define GAME_ENEMYBOSS_H

#include "EnemyStompable.h"

/**
 * Class that holds the boss enemy, more complex movement and health
 */
class EnemyBoss : public EnemyStompable
{
private:

    /// hold the health of the boss
    int mHealth = 3;

    /**
     * The boss has six states, divided into a few categories.
     *
     * "Default" state
     * ROAMING: boss traverses across its bounded zone until a state change is caused.
     *
     * "Special" states are automatically cycled on a timer increment.
     * DASHING: boss dashes in the direction of the player, and only stops when it hits a boundary.
     * JUMPING: boss jumps in the direction of the player.
     *
     * "Protected" states; states in which the boss cannot be stomped on.
     * THINKING: boss freezes for a set period of time. Player is defeated if they attempt to stomp the boss.
     * STOMPED: boss rushes across its bounded zone for a set period of time. Player is defeated on a stomp attempt.
     * DEFEATED: boss sinks to a minimum level and can no longer interact with the player.
     * DASHING: boss cannot be stomped while dashing.
     *
     * "Unprotected" states include ROAMING, DASHING, and JUMPING.
     * In these states, the boss can be stomped on to take one of its lives.
     */
    enum class BossState { ROAMING, THINKING, JUMPING, DASHING, STOMPED, DEFEATED };

    /// hold the movement state of the boss
    BossState mMovementState;

    /// track the time for the STOMPED state
    double mStompedTimer = 0.0;

    /// track the time for a THINKING state
    double mThinkingTimer = 0.0;

    double mMotionTimer = 0.0;   ///< track time for timer-activated movement state changes on increments
    bool mStateChangeDue;   ///< track whether an enemy action is due after an increment
    double mNextIncrement;    ///< track the next time increment value. Check this
    BossState mNextSpecialState;   ///< track the next special state to switch to on the timer increment.
    ///< special states include JUMPING and DASHING

    /// current movement speed of the boss in pixels per second
    double mSpeedX = 0;   ///< horizontal speed
    double mSpeedY = 0;   ///< vertical speed


    void Update(double elapsed) override;

    void StartNextSpecialState();
    void Jump();
    void Dash();
    void Roam();
    void Think();

    bool IncrementIsPassed();

    void ChaseFootballX(const double &speed);

    void SetImageRight();
    void SetImageLeft();

    bool ProtectedState(BossState state);

public:
    /// valid constructor
    EnemyBoss(Level* level, double initX, double initY, std::wstring id);

    /// deleted constructors
    EnemyBoss() = delete;
    EnemyBoss(const EnemyBoss&) = delete;
    void operator=(const EnemyBoss&) = delete;

    /**
     * Set the movement state of the boss
     * @param state BossState enum that indicates the boss's current state
     */
    void SetMovementState(BossState state) { mMovementState = state; }

    /// Deal damage to the boss
    void StompBoss();

    /**
     * Check if the boss is in the DEFEATED state
     * @return true if the boss's health is 0 or less and is defeated
     */
    bool IsDefeated() const { return mMovementState == BossState::DEFEATED; }
};


#endif //GAME_ENEMYBOSS_H