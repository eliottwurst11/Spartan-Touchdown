/**
 * @file EnemyStompableVisitor.cpp
 * @author Beckham lee
 */

#include "pch.h"
#include "EnemyStompableVisitor.h"
#include "EnemyStompable.h"
#include "Football.h"

/**
 * Visit the stompable enemy, and detect if the enemy, football, or neither were defeated
 * @param enemyStompable The EnemyStompable object to visit
 */
void EnemyStompableVisitor::VisitEnemyStompable(EnemyStompable* enemyStompable)
{
    // no change if no collision
    if (!enemyStompable->HitTest(mFootball.get()) || enemyStompable->GetDefeatedState())
    {
        return;
    }

    // get positions and measurements
    double enemyX = enemyStompable->GetX();
    double enemyY = enemyStompable->GetY();
    double enemyWidth = enemyStompable->GetImageWidth();
    double enemyHeight = enemyStompable->GetImageHeight();
    double footballX = mFootball->GetX();
    double footballY = mFootball->GetY();
    double footballWidth = mFootball->GetImageWidth();
    double footballHeight = mFootball->GetImageHeight();

    // find center points
    double enemyCenterX = enemyX + enemyWidth / 2.0;
    double enemyCenterY = enemyY + enemyHeight / 2.0;
    double footballCenterX = footballX + footballWidth / 2.0;
    double footballCenterY = footballY + footballHeight / 2.0;

    // find distance between centers
    double distanceX = footballCenterX - enemyCenterX;
    double distanceY = footballCenterY - enemyCenterY;

    // find overlap distances
    double overlapX = (enemyWidth / 2.0 + footballWidth / 2.0) - std::abs(distanceX);
    double overlapY = (enemyHeight / 2.0 + footballHeight / 2.0) - std::abs(distanceY);

    // if overlap in Y is smaller and football is above
    if ( (overlapY < overlapX && distanceY < 0) && enemyStompable->GetStompable())
    {
        mEnemyStomped = enemyStompable;
        mFootball->SetVulnerable(false);
    }
    else
    {
        mFootballDefeated = true;
    }
}


