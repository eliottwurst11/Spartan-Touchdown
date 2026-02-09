/**
 * @file EnemyStompableVisitor.h
 * @author Beckham Lee
 *
 * Holds the visitor class for the stompable enemy variant
 */

#ifndef GAME_ENEMYSTOMPABLEVISITOR_H
#define GAME_ENEMYSTOMPABLEVISITOR_H

#include "ItemVisitor.h"

/**
 * Class that holds the visitor for the stompable variant of enemy
 */
class EnemyStompableVisitor : public ItemVisitor
{
private:
    /// the football we are matching to hit with
    std::shared_ptr<Football> mFootball;

    /// the stompable enemy, if it was stomped
    EnemyStompable* mEnemyStomped = nullptr;

    /// bool to hold if the player should die
    bool mFootballDefeated = false;

public:
    /**
     * Constructor for this visitor
     * @param football The football passed to the visitor
     */
    EnemyStompableVisitor(std::shared_ptr<Football> football) : mFootball(std::move(football)) {}

    /**
     * Getter for the enemy if it was stomped by player
     * @returns true if the enemy was stomped
     */
    EnemyStompable* GetEnemyStomped() { return mEnemyStomped; }

    /**
     * Getter for the football defeated condition
     * @returns true if the football was stomped
     */
    bool GetFootballDefeated() { return mFootballDefeated; }

    void VisitEnemyStompable(EnemyStompable* enemyStompable) override;

};


#endif //GAME_ENEMYSTOMPABLEVISITOR_H