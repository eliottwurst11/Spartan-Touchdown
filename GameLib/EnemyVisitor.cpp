/**
 * @file EnemyVisitor.cpp
 * @author Eliott Wurst
 */

#include "pch.h"
#include "EnemyVisitor.h"
#include "Enemy.h"
#include "Football.h"

/**
 * Visit an Enemy object and check if collided with the football
 * @param enemy Enemy to visit
 */
void EnemyVisitor::VisitEnemy(Enemy* enemy)
{
    if (enemy->HitTest(mFootball.get()))
    {
        mEnemy = enemy;
    }
}
