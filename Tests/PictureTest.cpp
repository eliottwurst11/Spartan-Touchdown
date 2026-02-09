/**
 * @file PictureTest.cpp
 * @author Eliott Wurst
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Picture.h>

using namespace std;

/// image filenames
const wstring door = L"images/door.png";
const wstring wall1 = L"images/wall1.png";
const wstring wall2 = L"images/wall2.png";
const wstring coin10 = L"images/coin10.png";
const wstring background0 = L"images/background0.png";
const wstring gog = L"images/gog.png";

/**
 * Check if the image file loaded into the Picture object matches
 * the same image file manually loaded in the test for an image file
 * given in the project
 */
TEST(PictureTest, LoadCorrectGivenImage) {
    // Expected image and bitmap values
    auto imageExpected = make_shared<wxImage>(wall1);
    auto bitmapExpected = make_shared<wxBitmap>(*imageExpected);

    auto imageWidthExpected = bitmapExpected->GetWidth();
    auto imageHeightExpected = bitmapExpected->GetHeight();
    auto bitmapWidthExpected = bitmapExpected->GetWidth();
    auto bitmapHeightExpected = bitmapExpected->GetHeight();

    // Actual image and bitmap values
    Picture picture(wall1);
    auto imageActual = picture.GetImage();
    auto bitmapActual = picture.GetBitmap();

    auto imageWidthActual = bitmapActual->GetWidth();
    auto imageHeightActual = bitmapActual->GetHeight();
    auto bitmapWidthActual = bitmapActual->GetWidth();
    auto bitmapHeightActual = bitmapActual->GetHeight();

    ASSERT_EQ(imageWidthExpected, imageWidthActual);
    ASSERT_EQ(imageHeightExpected, imageHeightActual);
    ASSERT_EQ(bitmapWidthExpected, bitmapWidthActual);
    ASSERT_EQ(bitmapHeightExpected, bitmapHeightActual);
}

/**
 * Check if the image file loaded into the Picture object matches
 * the same image file manually loaded in the test for an image file
 * our team selected
 */
TEST(PictureTest, LoadCorrectCustomImage) {
    // Expected image and bitmap values
    auto imageExpected = make_shared<wxImage>(door);
    auto bitmapExpected = make_shared<wxBitmap>(*imageExpected);

    auto imageWidthExpected = bitmapExpected->GetWidth();
    auto imageHeightExpected = bitmapExpected->GetHeight();
    auto bitmapWidthExpected = bitmapExpected->GetWidth();
    auto bitmapHeightExpected = bitmapExpected->GetHeight();

    // Actual image and bitmap values
    Picture picture(door);
    auto imageActual = picture.GetImage();
    auto bitmapActual = picture.GetBitmap();

    auto imageWidthActual = bitmapActual->GetWidth();
    auto imageHeightActual = bitmapActual->GetHeight();
    auto bitmapWidthActual = bitmapActual->GetWidth();
    auto bitmapHeightActual = bitmapActual->GetHeight();

    ASSERT_EQ(imageWidthExpected, imageWidthActual);
    ASSERT_EQ(imageHeightExpected, imageHeightActual);
    ASSERT_EQ(bitmapWidthExpected, bitmapWidthActual);
    ASSERT_EQ(bitmapHeightExpected, bitmapHeightActual);
}

/**
 * Check if the image file loaded into the Picture object is different
 * from a different image file manually loaded in the test for two image
 * files given in the project
 */
TEST(PictureTest, LoadIncorrectGivenImage) {
    // Expected image and bitmap values
    auto imageExpected = make_shared<wxImage>(wall2);
    auto bitmapExpected = make_shared<wxBitmap>(*imageExpected);

    auto imageWidthExpected = bitmapExpected->GetWidth();
    auto imageHeightExpected = bitmapExpected->GetHeight();
    auto bitmapWidthExpected = bitmapExpected->GetWidth();
    auto bitmapHeightExpected = bitmapExpected->GetHeight();

    // Actual image and bitmap values
    Picture picture(background0);
    auto imageActual = picture.GetImage();
    auto bitmapActual = picture.GetBitmap();

    auto imageWidthActual = bitmapActual->GetWidth();
    auto imageHeightActual = bitmapActual->GetHeight();
    auto bitmapWidthActual = bitmapActual->GetWidth();
    auto bitmapHeightActual = bitmapActual->GetHeight();

    ASSERT_NE(imageWidthExpected, imageWidthActual);
    ASSERT_NE(imageHeightExpected, imageHeightActual);
    ASSERT_NE(bitmapWidthExpected, bitmapWidthActual);
    ASSERT_NE(bitmapHeightExpected, bitmapHeightActual);
}

/**
 * Check if the image file loaded into the Picture object is different
 * from a different image file manually loaded in the test for two image
 * files selected by our team
 */
TEST(PictureTest, LoadIncorrectCustomImage) {
    // Expected image and bitmap values
    auto imageExpected = make_shared<wxImage>(gog);
    auto bitmapExpected = make_shared<wxBitmap>(*imageExpected);

    auto imageWidthExpected = bitmapExpected->GetWidth();
    auto imageHeightExpected = bitmapExpected->GetHeight();
    auto bitmapWidthExpected = bitmapExpected->GetWidth();
    auto bitmapHeightExpected = bitmapExpected->GetHeight();

    // Actual image and bitmap values
    Picture picture(door);
    auto imageActual = picture.GetImage();
    auto bitmapActual = picture.GetBitmap();

    auto imageWidthActual = bitmapActual->GetWidth();
    auto imageHeightActual = bitmapActual->GetHeight();
    auto bitmapWidthActual = bitmapActual->GetWidth();
    auto bitmapHeightActual = bitmapActual->GetHeight();

    ASSERT_NE(imageWidthExpected, imageWidthActual);
    ASSERT_NE(imageHeightExpected, imageHeightActual);
    ASSERT_NE(bitmapWidthExpected, bitmapWidthActual);
    ASSERT_NE(bitmapHeightExpected, bitmapHeightActual);
}