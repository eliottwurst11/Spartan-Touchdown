/**
 * @file PlatformDeclaration.cpp
 * @author Matthew Lopez
 */

#include "pch.h"
#include "PlatformDeclaration.h"

/**
 * Constructor
 * @param id the id that this declaration belongs to
 * @param pathLeft the image name of the left cap of the platform
 * @param pathMid the image name of the middle tiles of the platform
 * @param pathRight the image name of the right cap of the platform
 */
PlatformDeclaration::PlatformDeclaration(std::wstring id, std::wstring pathLeft, std::wstring pathMid, std::wstring pathRight)
        : Declaration(id, pathMid), mImageLeft(pathLeft), mImageRight(pathRight)
{
}
