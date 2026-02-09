/**
 * @file Picture.h
 * @author Matthew Lopez
 *
 * A simple picture class. Holds a shared pointer to the image and
 * bitmap that is used multiple times to prevent loading the image
 * multiple times.
 */

#ifndef GAME_PICTURE_H
#define GAME_PICTURE_H


/**
* Simple picture class
*/
class Picture {
private:
    /// wxImage of the picture
    std::shared_ptr<wxImage> mImage;

    /// wxBitmap of the picture
    std::shared_ptr<wxBitmap> mBitmap;

public:
    Picture(std::wstring path);

    /// disable the default constructor
    Picture() = delete;

    /// disable the copy constructor
    Picture(const Picture &) = delete;

    /// disable assignment operator
    void operator=(const Picture &) = delete;

    /**
     * Gets the image pointer
     * @return a pointer to the image
     */
    std::shared_ptr<wxImage> GetImage() { return mImage; }

    /**
     * Gets the image bitmap
     * @return a pointer to the image bitmap
     */
    std::shared_ptr<wxBitmap> GetBitmap() { return mBitmap; }

};


#endif //GAME_PICTURE_H