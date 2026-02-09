/**
 * @file PlatformBreakableDeclaration.h
 * @author Hamin Paik
 *
 * Declaration for a breakable platform, holding its solid and breaking images.
 */

#ifndef GAME_PLATFORMBREAKABLEDECLARATION_H
#define GAME_PLATFORMBREAKABLEDECLARATION_H

#include "Declaration.h"

/**
 * Declaration for a PlatformBreakable object
 */
class PlatformBreakableDeclaration : public Declaration {
private:
    /// The image filename for the "solid" state
    std::wstring mSolidImageName;

    /// The image filename for the "breaking" state
    std::wstring mBreakingImageName;

public:
    PlatformBreakableDeclaration(const std::wstring& id, const std::wstring& solidImage, const std::wstring& breakingImage);

    /// Get the solid image filename
    /// @return Solid image filename
    std::wstring GetSolidImageName() override { return mSolidImageName; }

    /// Get the breaking image filename
    /// @return Breaking image filename
    std::wstring GetBreakingImageName() override { return mBreakingImageName; }


};

#endif //GAME_PLATFORMBREAKABLEDECLARATION_H