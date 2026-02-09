/**
 * @file Background.cpp
 * @author Beckham Lee
 */

#include "pch.h"
#include "Background.h"


/**
 * Overloaded constructor
 * @param level Level the background is a part of
 * @param initX X position of the background in pixels
 * @param initY Y position of the background in pixels
 * @param id ID for the background, used for level loading
 */
Background::Background(Level* level, double initX, double initY, std::wstring id)
    : Item(level, initX, initY, id)
{
}
