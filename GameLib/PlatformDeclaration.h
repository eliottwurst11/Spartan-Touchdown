/**
 * @file PlatformDeclaration.h
 * @author Matthew Lopez
 *
 * A declaration made for platform objects.
 * Holds 2 extra image slots for the left and right segments
 */

#ifndef GAME_PLATFORMDECLARATION_H
#define GAME_PLATFORMDECLARATION_H

#include "Declaration.h"

/**
 * A declaration made for platform objects
 */
class PlatformDeclaration : public Declaration {
private:

    /// holds the image name for the left platform
    std::wstring mImageLeft;

    /// holds the image name for the right platform
    std::wstring mImageRight;

public:

    PlatformDeclaration(std::wstring id, std::wstring pathLeft, std::wstring pathMid, std::wstring pathRight);

    /// disable the default constructor
    PlatformDeclaration() = delete;

    /// disable the copy constructor
    PlatformDeclaration(const PlatformDeclaration &) = delete;

    /// disable assignment operator
    void operator=(const PlatformDeclaration &) = delete;

    /**
     * Gets the name of the left end cap
     * @return the image name of the left end cap
     */
    std::wstring GetImageLeft() override { return mImageLeft; }

    /**
     * Gets the name of the right end cap
     * @return the image name of the right end cap
     */
    std::wstring GetImageRight() override { return mImageRight; }
};


#endif //GAME_PLATFORMDECLARATION_H