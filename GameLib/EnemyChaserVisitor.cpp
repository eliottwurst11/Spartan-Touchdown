/**
 * @file EnemyChaserVisitor.cpp
 * @author Eliott Wurst
 */

#include "pch.h"
#include "EnemyChaserVisitor.h"
#include "EnemyChaser.h"
#include "Football.h"

/**
 * Visit an EnemyChaser object and check if it has collided with the football
 * or if the football is within its view range. Freeze the EnemyChaser if the football
 * is viewable, too far in the Y direction for collision, and close enough in the X
 * direction for collision.
 * @param enemyChaser EnemyChaser to visit
 */
void EnemyChaserVisitor::VisitEnemyChaser(EnemyChaser* enemyChaser)
{
    if (enemyChaser->HitTest(mFootball.get()))
    {
        mEnemyChaser = enemyChaser;
    }
    else
    {
        // Check if the chaser is in line with the football, but above it
        if (enemyChaser->FootballUnreachableTest(mFootball.get()))
        {
            enemyChaser->SetFrozen(true);
        }
        // enemyChaser is not in line with the football
        else
        {
            enemyChaser->SetFrozen(false);

            // Check if the football is in view of the chaser
            if (enemyChaser->FootballInVisionTest(mFootball.get()))
            {
                enemyChaser->EndChase();
                if (mFootball->GetX() < enemyChaser->GetX())
                {
                    enemyChaser->ChaseFootballLeft();
                }
                else
                {
                    enemyChaser->ChaseFootballRight();
                }
            }
            else
            {
                enemyChaser->EndChase();
            }
        }
    }
}