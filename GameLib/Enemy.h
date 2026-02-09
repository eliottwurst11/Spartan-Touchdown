/**
 * @file Enemy.h
 * @author Beckham Lee
 *
 * Class for the enemy. If the football collides with an enemy, then the
 * player loses. Classes derived from this inherit this basic functionality.
 */

#ifndef GAME_ENEMY_H
#define GAME_ENEMY_H

#include "Item.h"
#include "Declaration.h"

/**
 * Class for the enemy
 */
class Enemy : public Item {
private:

    /// Movement states
    bool mMovingUp = false;   ///< true if the enemy is moving up
    bool mMovingDown = false;   ///< true if the enemy is moving down

    /// Store the initial Y so we know when to reverse direction
    double mInitY;

public:

    Enemy(Level *level, double initX, double initY, std::wstring id);

    /// disable the default constructor
    Enemy() = delete;

    /// disable the copy constructor
    Enemy(const Enemy &) = delete;

    /// disable assignment operator
    void operator=(const Enemy &) = delete;

    /**
     * Accept an ItemVisitor
     * @param visitor ItemVisitor to accept
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitEnemy(this); }

    /// update the position of the enemy
    void Update(double elapsed) override;
};


#endif //GAME_ENEMY_H