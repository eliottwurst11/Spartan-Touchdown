/**
 * @file WallVisitor.cpp
 * @author Eliott Wurst
 */

#include "pch.h"
#include "WallVisitor.h"
#include "Wall.h"

/**
 * Visit a Wall object
 * @param wall Wall to visit
 */
void WallVisitor::VisitWall(Wall* wall)
{
    if (wall->HitTest(mItem))
    {
        mWall = wall;
    }
}

