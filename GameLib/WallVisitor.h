/**
 * @file WallVisitor.h
 * @author Eliott Wurst
 *
 * Definition for a visitor for a Wall object
 */

#ifndef GAME_WALLVISITOR_H
#define GAME_WALLVISITOR_H

#include "Item.h"
#include "ItemVisitor.h"

/**
 * Visitor for a Wall object used for collisions with items
 */
class WallVisitor : public ItemVisitor {
private:

    /// the item we are matching the hit to the Wall with
    Item* mItem;

    /// pointer to the hit Wall
    Wall* mWall = nullptr;

public:
    /**
     * construct this Wall visitor with the Item
     * @param item the item we are comparing this wall to
     */
    WallVisitor(Item* item) : mItem(item) {}

    /**
     * Getter for the Wall
     * @return Pointer to a Wall
     */
    Wall* GetWall() const { return mWall; }

    /**
     * Setter for the Wall
     * @param wall Wall to set
     */
    void SetWall(Wall* wall) { mWall = wall; }

    void VisitWall(Wall* wall) override;
};


#endif //GAME_WALLVISITOR_H