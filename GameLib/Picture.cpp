/**
 * @file Picture.cpp
 * @author Matthew Lopez
 */
#include "pch.h"
#include "Picture.h"

using namespace std;

/**
 * Constructor
 * @param path the path to the image
 */
Picture::Picture(std::wstring path)
{
    mImage = make_shared<wxImage>(path);
    mBitmap = make_shared<wxBitmap>(*mImage);
}