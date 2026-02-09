/**
 * @file DeclarationsTest.cpp
 * @author Matthew Lopez
 */


#include <pch.h>
#include <Declaration.h>
#include <PlatformBreakableDeclaration.h>
#include <PlatformDeclaration.h>
#include <CoinDeclaration.h>

#include "gtest/gtest.h"

using namespace std;

/**
 * Test if each declaration can be constructed without error
 */
TEST(DeclarationsTest, constructor)
{
    Declaration regular(L"i001", L"wall1.png");
    PlatformBreakableDeclaration breakable(L"i002", L"break", L"unbreaking");
    PlatformDeclaration platform(L"i003", L"left", L"mid", L"right");
    CoinDeclaration coin(L"i004", L"coin", 10);
}

/**
 * Test if each declaration correctly retrieves info
 * and overrides base functions when needed
 */
TEST(DeclarationsTest, getters)
{
    Declaration regular(L"i001", L"wall1.png");

    // check if ID correctly returns
    ASSERT_TRUE(regular.GetID() == L"i001");

    // regular declarations should not have these initialized
    ASSERT_TRUE(regular.GetImageLeft() == L"");
    ASSERT_TRUE(regular.GetImageRight() == L"");
    ASSERT_TRUE(regular.GetValue() == 0);
    ASSERT_TRUE(regular.GetBreakingImageName() == L"");
    ASSERT_TRUE(regular.GetSolidImageName() == L"");

    // check if the image name correctly returns
    ASSERT_TRUE(regular.GetImageName() == L"wall1.png");

    PlatformBreakableDeclaration breakable(L"i002", L"unbreaking", L"break");
    ASSERT_TRUE(breakable.GetID() == L"i002");

    // previous ID's should not be overwritten
    ASSERT_TRUE(regular.GetID() == L"i001");

    // breakable declaration should correctly override the base version
    ASSERT_TRUE(breakable.GetBreakingImageName() == L"break");
    ASSERT_TRUE(breakable.GetSolidImageName() == L"unbreaking");

    // breakable should only override paramaters that pertain to it, ie
    // should not override coin declaration values
    ASSERT_TRUE(breakable.GetValue() == 0);


    PlatformDeclaration platform(L"i003", L"left", L"mid", L"right");
    ASSERT_TRUE(platform.GetID() == L"i003");

    // correctly retrieves and overrides the base class
    ASSERT_TRUE(platform.GetImageLeft() == L"left");
    ASSERT_TRUE(platform.GetImageName() == L"mid");
    ASSERT_TRUE(platform.GetImageRight() == L"right");


    CoinDeclaration coin(L"i004", L"coin", 10);
    ASSERT_TRUE(coin.GetID() == L"i004");
    ASSERT_TRUE(coin.GetImageName() == L"coin");
    ASSERT_TRUE(coin.GetValue() == 10);
}

