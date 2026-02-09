/**
 * @file PowerUpPoints.cpp
 * @author Eliott Wurst
 */

#include "pch.h"
#include "PowerUpPoints.h"


/**
 * Constructor
 * @param level Level this powerup is part of
 * @param initX X position of the powerup
 * @param initY Y position of the powerup
 * @param id the id corresponding to the declaration of the item
 */
PowerUpPoints::PowerUpPoints(Level* level, double initX, double initY, std::wstring id)
    : PowerUp(level, initX, initY, id)
{
}
