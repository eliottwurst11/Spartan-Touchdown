/**
 * @file EnemyChaserVisitor.h
 * @author Eliott Wurst
 *
 * Definition for a visitor of EnemyChaser objects
 */

#ifndef GAME_ENEMYCHASERVISITOR_H
#define GAME_ENEMYCHASERVISITOR_H

#include "ItemVisitor.h"

/**
 * Visitor class for an EnemyChaser
 */
class EnemyChaserVisitor : public ItemVisitor {
private:

    /// the football we are matching the hit to the EnemyChaser with
    std::shared_ptr<Football> mFootball;

    /// pointer to the hit EnemyChaser
    EnemyChaser* mEnemyChaser = nullptr;

public:
    /**
     * Constructor
     * @param football The football passed to the visitor
     */
    EnemyChaserVisitor(std::shared_ptr<Football> football) : mFootball(std::move(football)) {}

    /**
     * Getter for the EnemyChaser
     * @return Pointer to an EnemyChaser
     */
    EnemyChaser* GetEnemyChaser() const { return mEnemyChaser; }

    /**
     * Setter for the EnemyChaser
     * @param enemyChaser EnemyChaser to set
     */
    void SetEnemyChaser(EnemyChaser* enemyChaser) { mEnemyChaser = enemyChaser; }

    void VisitEnemyChaser(EnemyChaser* enemyChaser) override;
};


#endif //GAME_ENEMYCHASERVISITOR_H