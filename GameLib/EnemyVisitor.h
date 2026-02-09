/**
 * @file EnemyVisitor.h
 * @author Eliott Wurst
 *
 * Defines a visitor for an enemy
 */

#ifndef GAME_ENEMYVISITOR_H
#define GAME_ENEMYVISITOR_H

#include "ItemVisitor.h"

/**
 * Visitor for an enemy
 */
class EnemyVisitor : public ItemVisitor {
private:

    /// the football we are matching the hit to the enemy with
    std::shared_ptr<Football> mFootball;

    /// pointer to the hit enemy
    Enemy* mEnemy = nullptr;

public:
    /**
     * Constructor
     * @param football The football passed to the visitor
     */
    EnemyVisitor(std::shared_ptr<Football> football) : mFootball(std::move(football)) {}

    /**
     * Getter for the Enemy
     * @return Pointer to an Enemy
     */
    Enemy* GetEnemy() const { return mEnemy; }

    /**
     * Setter for the Enemy
     * @param enemy Enemy to set
     */
    void SetEnemy(Enemy* enemy) { mEnemy = enemy; }

    void VisitEnemy(Enemy* enemy) override;
};


#endif //GAME_ENEMYVISITOR_H