/**
 * @file CoinIncrementVisitor.h
 * @author Beckham Lee
 *
 * Visitor for increasing the value of every coin in the level.
 *
 * This is used when a PowerUpPoints object is collided with by
 * the player, doubling the value in points of every coin in a level.
 */

#ifndef GAME_COININCREMENTVISITOR_H
#define GAME_COININCREMENTVISITOR_H

#include "ItemVisitor.h"
#include "Coin.h"

/**
 * Visitor that visits every coin and increases its value
 */
class CoinIncrementVisitor : public ItemVisitor {
private:

public:
    /// default constructor
    CoinIncrementVisitor() {}

    void VisitCoin(Coin* coin) override;
};


#endif //GAME_COININCREMENTVISITOR_H