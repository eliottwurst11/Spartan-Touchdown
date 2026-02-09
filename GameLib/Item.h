/**
 * @file Item.h
 * @author Matthew Lopez
 *
 * Base class for all of the game items
 */

#ifndef GAME_ITEM_H
#define GAME_ITEM_H

#include "ItemVisitor.h"
#include "Picture.h"
#include "Declaration.h"

class Level;

/**
 * Base class for all of the game items
 */
class Item {
private:
    /// The level this game is part of
    Level *mLevel;

    // Location in level
    double mX = 0; ///< X location of the center of the item
    double mY = 0; ///< Y location of center of the item

    /// The image of the item
    std::shared_ptr<wxImage> mItemImage;

    /// The bitmap of the item
    std::shared_ptr<wxBitmap> mItemBitmap;

protected:
    // The constructor for the football
    Item(Level *level, const std::wstring &filename);

    // The constructor for every other item in the game
    Item(Level *level, double initX, double initY, std::wstring id);

public:
    virtual ~Item();

    // getter

    /**
     * Get the X location of the item
     * @return X location of item in pixels
     */
    double GetX() const { return mX; }

    /**
     * Get the Y location of the item
     * @return Y location of item in pixels
     */
    double GetY() const { return mY; }

    /**
     * Get the current level this item is in
     * @return Pointer to the level this item is in
     */
    Level* GetLevel() const{ return mLevel; }

    /**
    * Get the Item's bitmap
    * @return Pointer to mItemBitmap
    */
    std::shared_ptr<wxBitmap> GetBitmap() { return mItemBitmap; }

    /**
    * Returns the height of the image
    * @return height of the image
    */
    virtual double GetImageHeight() const { return mItemImage->GetHeight(); }

    /**
    * Returns the width of the image.
    * @return width of the image
    */
    virtual double GetImageWidth() const { return mItemImage->GetWidth(); }

    // Setters

    /**
     * Set a specific location
     * @param x X location in pixels
     * @param y Y location in pixels
     */
    virtual void SetLocation(double x, double y) {mX = x; mY = y; }

    void SetItemBitmap(const std::wstring& filename, bool reset=false);


    // constructor disables

    /// disable the default constructor
    Item() = delete;

    /// disable the copy constructor
    Item(const Item &) = delete;

    /// disable assignment operator
    void operator=(const Item &) = delete;

    // drawing

    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    /**
     * Handles updates for animation
     * @param elapsed the time since the last update
     */
    virtual void Update(double elapsed) {}

    virtual bool HitTest(Item *other);

    /**
     * Check if the item is in a 'broken' state and should be removed.
     * Base implementation returns false.
     * @return true if the item is considered broken.
     */
    virtual bool IsBroken() const { return false; }

    /**
     * Pure virtual function to accept a visitor.
     * Makes this an abstract class, since the function is pure virtual
     * @param visitor ItemVisitor to accept
     */
     virtual void Accept(ItemVisitor* visitor) = 0;
};


#endif //GAME_ITEM_H