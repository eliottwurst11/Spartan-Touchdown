/**
 * @file Background.h
 * @author Beckham Lee
 *
 * Class containing information for the level background
 */

#ifndef GAME_BACKGROUND_H
#define GAME_BACKGROUND_H

#include <string>
#include "Item.h"

/**
 * Class that holds information for the background
 */
class Background : public Item {
private:

public:
    /// disabled default constructor
    Background() = delete;

    /// disabled copy constructor
    Background(const Background &) = delete;

    /// disabled assignment operator
    void operator=(const Background &) = delete;

    /// valid constructors for this background
    Background(Level* level, double initX, double initY, std::wstring id);

    /**
     * Accept an ItemVisitor object to visit this coin
     * @param visitor Visitor visiting this coin
     */
    void Accept(ItemVisitor* visitor) override {}

};


#endif //GAME_BACKGROUND_H