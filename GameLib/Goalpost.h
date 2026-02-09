/**
 * @file Goalpost.h
 * @author Matthew Lopez
 *
 * Class for the Goalpost
 */

#ifndef GAME_GOALPOST_H
#define GAME_GOALPOST_H

#include "Item.h"

/**
 * Class for the Goalpost
 */
class Goalpost : public Item {
private:

public:

    Goalpost(Level *level, double initX, double initY, std::wstring id);

    /// disable the default constructor
    Goalpost() = delete;

    /// disable the copy constructor
    Goalpost(const Goalpost &) = delete;

    /// disable assignment operator
    void operator=(const Goalpost &) = delete;

    /**
     * Accept an ItemVisitor
     * @param visitor ItemVisitor to accept
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitGoalpost(this); }

    bool CollisionTest(Item* item);
};


#endif //GAME_GOALPOST_H