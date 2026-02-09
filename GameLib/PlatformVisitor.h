/**
 * @file PlatformVisitor.h
 * @author Eliott Wurst
 *
 * Definition for a visitor that visits a Platform
 */

#ifndef GAME_PLATFORMVISITOR_H
#define GAME_PLATFORMVISITOR_H

#include "Item.h"
#include "ItemVisitor.h"

/**
 * Visitor for a Platform object
 */
class PlatformVisitor : public ItemVisitor {
private:

    /// the item we are matching the hit to the Platform with
    Item* mItem;

    /// pointer to a hit platform
    Platform* mPlatform = nullptr;

public:
    /**
     * construct this PlatformVisitor with the Item
     * @param item the item we are comparing this platform to
     */
    PlatformVisitor(Item* item) : mItem(item) {}

    /**
     * Getter for a collided Platform
     * @return Pointer to a Platform
     */
    Platform* GetPlatform() const { return mPlatform; }

    void VisitPlatform(Platform* platform) override;
};


#endif //GAME_PLATFORMVISITOR_H