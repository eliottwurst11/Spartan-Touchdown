/**
 * @file EnemyStompable.h
 * @author Beckham Lee
 *
 * Class that holds the stompable enemy, a varaint of enemy which
 * moves side to side and can be defeated by the player
 */

#ifndef GAME_ENEMYSTOMPABLE_H
#define GAME_ENEMYSTOMPABLE_H

#include "Enemy.h"

/**
 * The class that holds the stompable enemy, which is defeated by landing on its head
 */
class EnemyStompable : public Enemy
{
private:
    /// bools that hold the movement direction
    bool mMovingLeft = false;    ///< true when the boss is moving left
    bool mMovingRight = false;   ///< true when the boss is moving right

    /// initial x position to remember when to change movement direction
    double mInitX;

    /// bool that holds the defeated state of the enemy, true if the player landed on top
    bool mDefeated = false;

    /// true if the enemy is not currently stompable
    bool mStompable = true;

public:
    EnemyStompable(Level* level, double initX, double initY, std::wstring id);

    EnemyStompable() = delete;
    EnemyStompable(const EnemyStompable&) = delete;
    void operator=(const EnemyStompable&) = delete;

    /// Override Update for horizontal movement
    void Update(double elapsed) override;

    /**
     * Accept an ItemVisitor
     * @param visitor ItemVisitor to accept
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitEnemyStompable(this); }

    // Getters
    /**
     * Check if the enemy has been stomped on
     * @return true if the enemy was stomped on
     */
    bool GetDefeatedState() const { return mDefeated; }

    /**
     * Check if the stompable enemy is moving left
     * @return true if enemy is moving left
     */
    bool GetMovingLeft() const { return mMovingLeft; }

    /**
     * Check if the stompable enemy is moving right
     * @return true if enemy is moving right
     */
    bool GetMovingRight() const { return mMovingRight; }

    /**
     * Get the initial X position for the enemy
     * @return initial X value in pixels
     */
    double GetInitX() const { return mInitX; }

    /**
     * Get stompable status
     * @return true if the enemy is currently stompable
     */
    bool GetStompable() const { return mStompable; }

    // Setters
    /**
     * set the enemy to defeated state after being stomped by player
     * @param defeated State to set mDefeated. True by default
     * @param stompable State to set mStompable. True by default
     */
    void SetStomped(bool defeated=true, bool stompable=true) { mDefeated = defeated; mStompable = stompable; }

    /**
     * Set the enemy to move left
     */
    void SetMovingLeft() { mMovingLeft = true; mMovingRight = false; }

    /**
     * Set the enemy to move right
     */
    void SetMovingRight() { mMovingLeft = false; mMovingRight = true; }

};


#endif //GAME_ENEMYSTOMPABLE_H