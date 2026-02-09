/**
 * @file Platform.h
 * @author Matthew Lopez
 *
 * Class that describes a platform
 */

#ifndef GAME_PLATFORM_H
#define GAME_PLATFORM_H

#include "Item.h"
#include "PlatformDeclaration.h"

/**
 * Class that describes a platform
 */
class Platform : public Item {
private:
    /// the image of the left end of the platform
    std::shared_ptr<wxImage> mLeftImage;

    /// the image of the right end of the platform
    std::shared_ptr<wxImage> mRightImage;

    /// bitmap of the left end of the platform
    std::shared_ptr<wxBitmap> mLeftBitmap;

    /// bitmap of the right end of the platform
    std::shared_ptr<wxBitmap> mRightBitmap;

    /// width of the platform in pixels
    int mWidth;

    /// height of the platform in pixels
    int mHeight;

public:

    Platform(Level *level, double initX, double initY, int width, int height, std::wstring id);

    /// disable the default constructor
    Platform() = delete;

    /// disable the copy constructor
    Platform(const Platform &) = delete;

    /// disable assignment operator
    void operator=(const Platform &) = delete;

    /**
     * Accept an ItemVisitor
     * @param visitor ItemVisitor to accept
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitPlatform(this); }

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Override GetImageWidth to return platform width
     * @return Platform width in pixels
     */
    double GetImageWidth() const override { return mWidth; }

    /**
     * Override GetImageHeight to return platform height  
     * @return Platform height in pixels
     */
    double GetImageHeight() const override { return mHeight; }

    bool CollisionTest(Item* item);

};


#endif //GAME_PLATFORM_H