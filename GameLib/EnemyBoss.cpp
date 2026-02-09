/**
 * @file EnemyBoss.cpp
 * @author Beckham Lee
 * @author Eliott Wurst
 */

#include "pch.h"
#include "EnemyBoss.h"
#include "Level.h"

using namespace std;

/// boss image paths
const wstring rightImage = L"images/cat_right.png";  ///< default boss image for rightward motion
const wstring leftImage = L"images/cat_left.png";    ///< default boss image for leftward motion
const wstring rightProtectedImage = L"images/cat_protected_right.png"; ///< rightward motion image for protected states
const wstring leftProtectedImage = L"images/cat_protected_left.png";   ///< leftward motion image for protected states
const wstring defeatedImage = L"images/cat_sad.png"; ///< boss image in the DEFEATED state

const double stateChangeTimeIncrement = 4; ///< time in seconds spent roaming between jumps and dashes

const double stompedStateTimeLength = 8;  ///< time length in seconds for the enemy to speed up after being stomped
const double thinkingStateTimeLength = 1.5; ///< time length in seconds for the enemy to freeze before jumping or dashing

/// gravitational constant in pixels per second squared
const double gravity = 1000.0;

/// boss speeds in pixels per second
const double roamSpeedX = 200;    ///< horizontal speed while the boss is in the default roaming state
const double jumpSpeedX = 300;    ///< horizontal speed while the boss is in the air after a jump
const double jumpSpeedY = -1200;  ///< vertical jump speed; decreasing this value increases jump height
const double dashSpeedX = 800;    ///< horizontal speed while the boss is dashing at the player
const double stompedSpeedX = 750; ///< horizontal speed after the boss has been stomped

/// movement distance limits for the boss in pixels
const double rightBoundX = 750;           ///< farthest right the enemy can travel
const double leftBoundX = -750;           ///< farthest left the enemy can travel
const double lowerBoundY = 900;           ///< lowest Y value the boss can reach
const double protectedImageLowerBoundY = lowerBoundY + 10; ///< lowest Y value the boss can reach while protecting self
const double sinkAfterDefeatY = 1024;     ///< Y value the boss sinks to after being defeated

/**
 * Constructor
 * @param level Level this boss is a part of
 * @param initX Initial X position of the boss in pixels
 * @param initY Initial Y position of the boss in pixels
 * @param id ID for the boss, used for level loading
 */
EnemyBoss::EnemyBoss(Level* level, double initX, double initY, std::wstring id)
    : EnemyStompable(level, initX, initY, id)
{
    // set initial state to the default ROAMING state
    mSpeedX = roamSpeedX;
    SetMovingRight();
    SetMovementState(BossState::ROAMING);

    // set the first automatically triggered special state to be the JUMPING state
    mNextSpecialState = BossState::JUMPING;
}

/**
 * Manage enemy boss movement states. Similar to the EnemyStompable::Update() function
 * @param elapsed
 */
void EnemyBoss::Update(double elapsed)
{
    // current position of the boss
    double currentX = GetX();
    double currentY = GetY();
    double newX = currentX;
    double newY = currentY;

    // mMovementState = BossState::DEFEATED;

    // Check if the boss has been stomped. GetDefeatedState() evaluates to true after a stomp.
    if (GetDefeatedState() && GetStompable()) //&&  mMovementState != BossState::STOMPED)
    {
        StompBoss();
    }

    // Handle the current movement state
    if (mMovementState == BossState::DEFEATED)
    {
        // move down and stop harming the player
        double newYCandidate = this->GetY() + roamSpeedX * elapsed;
        if (newYCandidate < sinkAfterDefeatY)
            this->SetLocation(currentX, newYCandidate);
        return;
    }
    else if (mMovementState == BossState::STOMPED)
    {
        mStompedTimer += elapsed;
        if (mStompedTimer > stompedStateTimeLength)
        {
            // return boss to the default ROAMING state
            mStompedTimer = 0;
            Roam();

            // this call allows the boss to be stomped again, now that it has returned to the ROAMING state
            SetStomped(false, true);
        }
    }
    else
    {
        // the boss is in one of the auto-cycled states; JUMPING, DASHING, or ROAMING

        // if the motion timer has passed a time increment, prepare to cycle the auto-state change
        if (IncrementIsPassed())
        {
            Think();
        }
        // Handle X velocity according to the current movement state
        if (mMovementState == BossState::ROAMING)
        {
            // keep track of time using the motion timer
            mMotionTimer += elapsed;
        }
        else if (mMovementState == BossState::THINKING)
        {
            mThinkingTimer += elapsed;
            if (mThinkingTimer > thinkingStateTimeLength)
            {
                // cycle the auto-state change
                SetStomped(false, true);
                StartNextSpecialState();
                mThinkingTimer = 0;
            }
        }
        else if (mMovementState == BossState::JUMPING)
        {
            // // make the boss chase the football while the boss is in the air
            // ChaseFootballX(jumpSpeedX);
        }
        else if (mMovementState == BossState::DASHING)
        {
        }
        else
        {
            // BREAK; something has gone wrong and the movement state is invalid.
            return;
        }
    }


    // Calculate the X and Y velocities for the movement state of the boss so that we can update its location.
    // Handle Y velocity
    if (GetY() < lowerBoundY)
    {
        mSpeedY += gravity * elapsed;
    }

    // Second, now that X and Y velocities have been determined by
    // the movement state, apply them to the boss's current position.
    // Handle Y movement
    newY = currentY + mSpeedY * elapsed;

    // Handle X movement
    if (GetMovingRight())
    {
        newX = currentX + mSpeedX * elapsed;
        SetImageRight();
    }
    if (GetMovingLeft())
    {
        newX = currentX - mSpeedX * elapsed;
        SetImageLeft();
        // SetItemBitmap(leftRoamImage);
    }

    // Third, check if the newly calculated position violates constraints.
    // Handle new Y location
    if (newY > lowerBoundY && !ProtectedState(mMovementState))
    {
        newY = lowerBoundY;
        // Handle ground collision at the end of a jump
        if (mMovementState == BossState::JUMPING)
        {
            Roam();
        }
    }
    else if (newY > protectedImageLowerBoundY && ProtectedState(mMovementState))
    {
        newY = protectedImageLowerBoundY;
    }

    // Handle new X location
    if ( (newX > rightBoundX) || (newX < leftBoundX) )
    {
        if (newX > rightBoundX)
        {
            newX = rightBoundX;
            SetMovingLeft();
        }
        else if (newX < leftBoundX)
        {
            newX = leftBoundX;
            SetMovingRight();
        }

        // Handle boundary collision during dash state; end the dash
        if (mMovementState == BossState::DASHING)
        {
            Roam();
            SetStomped(false, true);
        }
    }

    // save the new location
    SetLocation(newX, newY);
}

/**
 * Handle situation when a time increment is passed. This will be used
 * to trigger a movement state change.
 *
 * @return true if the motion timer passed the time increment
 */
bool EnemyBoss::IncrementIsPassed()
{
    if (mMotionTimer > mNextIncrement)
    {
        mNextIncrement = mMotionTimer + stateChangeTimeIncrement;
        return true;
    }
    return false;
}

/**
 * Make the boss jump
 */
void EnemyBoss::Jump()
{
    mSpeedY = jumpSpeedY;
    ChaseFootballX(jumpSpeedX);
    mMovementState = BossState::JUMPING;
}

/**
 * Make the boss dash at the player
 */
void EnemyBoss::Dash()
{
    ChaseFootballX(dashSpeedX);
    mMovementState = BossState::DASHING;
    SetStomped(false, false);
}

/**
 * Make boss move slowly in its boundary
 */
void EnemyBoss::Roam()
{
    mSpeedX = roamSpeedX;
    mMovementState = BossState::ROAMING;
}

/**
 * Make the boss stop and think
 */
void EnemyBoss::Think()
{
    mSpeedX = 0;
    mMovementState = BossState::THINKING;
    SetStomped(false, false);
}

/**
 * Make the boss move in the horizontal direction of the football using a specific speed.
 *
 * This function does NOT cause the boss to constantly chase the football. It simply changes the boss's direction to
 * match the location of the football in the instant the function is called.
 *
 * @param speed Speed to move in the football's direction with
 */
void EnemyBoss::ChaseFootballX(const double &speed)
{
    // get the football for the boss to chase
    auto football = GetLevel()->GetFootball();
    if (football->GetX() > GetX())
    {
        SetMovingRight();
        mSpeedX = speed;
    }
    else if (football->GetX() < GetX())
    {
        SetMovingLeft();
        mSpeedX = speed;
    }
}

/**
 * Deal damage to the boss and send it into the stomped state
 */
void EnemyBoss::StompBoss()
{
    mHealth -= 1;
    if (mHealth < 1)
    {
        mMovementState = BossState::DEFEATED;
        SetItemBitmap(defeatedImage);

        GetLevel()->SpawnBossGoalpost(GetX(), GetY());
    }
    else
    {
        mMovementState = BossState::STOMPED;
        mSpeedX = stompedSpeedX;
        if (mSpeedY < 0)
            mSpeedY = -mSpeedY;

        // this call prevents the boss from being stomped while it is in the STOMPED state
        SetStomped(false, false);
    }
}

/**
 * Switch to the next special state
 */
void EnemyBoss::StartNextSpecialState()
{
    if (mNextSpecialState == BossState::JUMPING)
    {
        Jump();
        mNextSpecialState = BossState::DASHING;
    }
    else if (mNextSpecialState == BossState::DASHING)
    {
        Dash();
        mNextSpecialState = BossState::JUMPING;
    }
}

/**
 * Set the correct image for a right-moving boss
 */
void EnemyBoss::SetImageRight()
{
    if (!ProtectedState(mMovementState))
    {
        SetItemBitmap(rightImage);
    }
    else
    {
        SetItemBitmap(rightProtectedImage);
        SetLocation(GetX(), protectedImageLowerBoundY);
    }
}

/**
 * Set the correct image for a left-moving boss
 */
void EnemyBoss::SetImageLeft()
{
    if (!ProtectedState(mMovementState))
    {
        SetItemBitmap(leftImage);
    }
    else
    {
        SetItemBitmap(leftProtectedImage);
        SetLocation(GetX(), protectedImageLowerBoundY);
    }
}

/**
 * Check if a state is a protected state
 * @param state State to check if the user cannot hit the boss when it is in that state
 * @returns true if the player cannot hit the boss in the given state
 */
bool EnemyBoss::ProtectedState(BossState state)
{
    return (state == BossState::THINKING ||
            state == BossState::DEFEATED ||
            state == BossState::STOMPED ||
            state == BossState::DASHING);
}
