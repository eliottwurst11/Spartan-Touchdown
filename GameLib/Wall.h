/**
 * @file Wall.h
 * @author Matthew Lopez
 *
 * Class for a wall
 */

#ifndef GAME_WALL_H
#define GAME_WALL_H

#include "Item.h"
#include "Declaration.h"

/**
 * Class for a wall
 */
class Wall : public Item {
private:
    /// the height of the wall in pixels
    int mHeight;

    /// the width of the wall in pixels
    int mWidth;

public:

    Wall(Level *level, double initX, double initY, int width, int height, std::wstring id);

    /// disable the default constructor
    Wall() = delete;

    /// disable the copy constructor
    Wall(const Wall &) = delete;

    /// disable assignment operator
    void operator=(const Wall &) = delete;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Accept an ItemVisitor
     * @param visitor ItemVisitor to accept
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitWall(this); }

    /**
     * Override GetImageWidth to return wall width
     * @return Wall width in pixels
     */
    double GetImageWidth() const override { return mWidth; }

    /**
     * Override GetImageHeight to return wall height  
     * @return Wall height in pixels
     */
    double GetImageHeight() const override { return mHeight; }

    bool CollisionTest(Item* item);

};


#endif //GAME_WALL_H