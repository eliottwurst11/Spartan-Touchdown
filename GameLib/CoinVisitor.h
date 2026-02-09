/**
 * @file CoinVisitor.h
 * @author Eliott Wurst
 *
 * Visitor for a Coin object
 */

#ifndef GAME_COINVISITOR_H
#define GAME_COINVISITOR_H

#include <utility>

#include "ItemVisitor.h"

/**
 * Definition for a visitor of a coin
 *
 * How to use: do item.Accept(&coinVisitor), where "item" is an Item object and
 * "coinVisitor" is a CoinVisitor object.
 */
class CoinVisitor : public ItemVisitor {
private:

    /// the football we are matching the hit to the coin with
    std::shared_ptr<Football> mFootball;

    /// pointer to the hit coin
    Coin* mCoin = nullptr;

public:
    /**
     * Constructor that saves a pointer to the football
     * @param football the football to check collisions for with the coins we are visiting
     */
    CoinVisitor(std::shared_ptr<Football> football) : mFootball(std::move(football)) {}

    /**
     * Getter for the Coin
     * @return Pointer to a Coin
     */
    Coin* GetCoin() const { return mCoin; }

    /**
     * Setter for the Coin
     * @param coin Coin to set
     */
    void SetCoin(Coin* coin) { mCoin = coin; }

    void VisitCoin(Coin* coin) override;
};


#endif //GAME_COINVISITOR_H