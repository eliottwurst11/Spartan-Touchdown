/**
 * @file GoalpostVisitor.cpp
 * @author Nishit Nagpal
 */

#include "pch.h"
#include "GoalpostVisitor.h"
#include "Goalpost.h"
#include "Football.h"

void GoalpostVisitor::VisitGoalpost(Goalpost* goalpost)
{
    if (goalpost->CollisionTest(mFootball.get()))
    {
        mGoalpost = goalpost;
    }
}
