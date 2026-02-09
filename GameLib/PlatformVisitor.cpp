/**
 * @file PlatformVisitor.cpp
 * @author Eliott Wurst
 */

#include "pch.h"
#include "PlatformVisitor.h"
#include "Platform.h"
#include "PlatformBreakable.h"

/**
 * Visit a Platform object and check if an item collided with it
 * @param platform Platform to visit
 */
void PlatformVisitor::VisitPlatform(Platform* platform)
{
    if (platform->HitTest(mItem))
    {
        mPlatform = platform;
    }
}