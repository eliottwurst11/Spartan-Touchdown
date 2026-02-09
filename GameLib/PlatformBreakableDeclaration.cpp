/**
 * @file PlatformBreakableDeclaration.cpp
 * @author Hamin Paik
 */

#include "pch.h"
#include "PlatformBreakableDeclaration.h"

/**
 * Constructor
 * @param id The ID for this declaration
 * @param solidImage Filename for the solid image
 * @param breakingImage Filename for the breaking image
 */
PlatformBreakableDeclaration::PlatformBreakableDeclaration(const std::wstring& id,
                                                         const std::wstring& solidImage,
                                                         const std::wstring& breakingImage)
    : Declaration(id, solidImage), mSolidImageName(solidImage), mBreakingImageName(breakingImage)
{
}