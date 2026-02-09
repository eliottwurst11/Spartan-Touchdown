/**
 * @file Coin.h
 * @author Matthew Lopez
 *
 * Class for coin item
 */

#ifndef GAME_COIN_H
#define GAME_COIN_H

#include "Item.h"
#include "CoinDeclaration.h"

/**
 * Class for coin item
 */
class Coin : public Item {
private:
    /// value of the coin
    int mValue = 0;

    /// bool set to true if this coin is currently flying
    bool mFlying = false;

    /// bool set to true if this coin is in level 2
    bool mIsLevel2 = false;

public:

    Coin(Level *level, double initX, double initY, std::wstring id);

    /// disable the default constructor
    Coin() = delete;

    /// disable the copy constructor
    Coin(const Coin &) = delete;

    /// disable assignment operator
    void operator=(const Coin &) = delete;

    /**
     * Accept an ItemVisitor
     * @param visitor ItemVisitor to accept
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitCoin(this); }

    /// set the flying to true so the coin can fly away after collection
    void SetFlying() { mFlying = true; }

    /// update the coin for its collection animation
    void Update(double elapsed) override;

    /**
     * Get the point value of the coin.
     * @return The integer value of the coin.
     */
    int GetValue() const { return mValue; }

    /**
     * Check if the coin is currently in its "flying away" state.
     * @return true if the coin is flying.
     */
    bool IsFlying() const { return mFlying; }

    /**
     * Set the point value of the coin
     * @param value integer value of the coin
     */
    void SetValue(int value) { mValue = value; }

};


#endif //GAME_COIN_H