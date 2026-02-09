/**
 * @file EnemyChaser.h
 * @author Eliott Wurst
 *
 * Definition for the enemy that chases the player.
 *
 * The enemy has a limited range of view in the X and Y directions. When a player
 * enters its view, it moves in the direction of the player and speeds up.
 *
 * Possible collisions include Platform floor collisions and Wall collisions. An EnemyChaser
 * will fall until it lands on a platform. If the EnemyChaser touches a wall, it will
 * enter a stun state in which it moves in one direction and cannot chase the player.
 */

#ifndef GAME_ENEMYCHASER_H
#define GAME_ENEMYCHASER_H

#include "Enemy.h"

/**
 * Enemy that chases the player
 */
class EnemyChaser : public Enemy {
private:

    /// Movement states
    bool mMovingLeft = false;   ///< true if the chaser is moving left
    bool mMovingRight = false;   ///< true if the chaser is moving right
    bool mChaseFootballLeft = false;   ///< true if the chaser is chasing the football to the left
    bool mChaseFootballRight = false;   ///< true if the chaser is chasing the football to the right
    bool mIsFrozen = false;   ///< true if the chaser is unable to move
    bool mIsStunned = false;   ///< true if the chaser has recently collided with a Wall

    /// Velocity in the Y direction
    double mVelocityY = 0;

    /// Velocity in the X direction
    double mVelocityX = 0;

    /// Track time after the chaser becomes stunned
    double mStunTimer = 0;;

    /// Store the initial X so we know when to reverse direction in the chill state
    double mInitX;

    /// Default sprite image filename
    std::wstring mImageFilename;

public:

    EnemyChaser(Level *level, double initX, double initY, std::wstring id);

    /// disable the default constructor
    EnemyChaser() = delete;

    /// disable the copy constructor
    EnemyChaser(const EnemyChaser &) = delete;

    /// disable assignment operator
    void operator=(const EnemyChaser &) = delete;

    /**
     * Accept an ItemVisitor
     * @param visitor ItemVisitor to accept
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitEnemyChaser(this); }

    void Update(double elapsed) override;

    bool FootballInVisionTest(Football* football);
    bool FootballUnreachableTest(Football* football);

    void ChaseFootballLeft();
    void ChaseFootballRight();
    void EndChase();

    void StartStun();
    void EndStun();

    /**
     * Set the freeze state of the EnemyChaser.
     * Set to true to freeze the EnemyChaser. Set false to allow it to move.
     * @param boolean True to allow EnemyChaser to move, False otherwise
     */
    void SetFrozen(bool boolean) { mIsFrozen = boolean; }

};


#endif //GAME_ENEMYCHASER_H