/**
 * @file FloatingTextTests.cpp
 * @author Hamin Paik
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <FloatingText.h>
#include <string>

/**
 * Test suite for the FloatingText class, testing it in isolation.
 */
namespace FloatingTextObjectTesting
{
    /**
     * Test Method: Checks that a new FloatingText object
     * has the correct initial Y-position and Y-velocity from its constructor.
     */
    TEST(FloatingTextObjectTests, TestInitialState)
    {
        double initialY = 150.0;
        FloatingText text(L"Test", 100.0, initialY);


        EXPECT_NEAR(initialY, text.GetY(), 0.001)
            << "Text did not spawn at the correct initial Y position.";

        EXPECT_NEAR(-100.0, text.GetYVelocity(), 0.001)
            << "Text does not have the correct initial Y velocity.";
    }

    /**
     * Test Method: Checks if the Y position updates correctly
     * after a small time step.
     */
    TEST(FloatingTextObjectTests, TestAnimationUpdate)
    {

        double initialY = 100.0;
        double initialVelocity = -100.0;
        FloatingText text(L"Test", 100.0, initialY);

        double elapsed = 0.1;
        text.Update(elapsed);

        double expectedNewY = initialY + (initialVelocity * elapsed);
        double actualNewY = text.GetY();

        EXPECT_NEAR(expectedNewY, actualNewY, 0.001)
            << "Text did not move correctly after 0.1s.";

        EXPECT_NEAR(initialVelocity, text.GetYVelocity(), 0.001)
            << "Text velocity changed unexpectedly.";
    }

    /**
     * Test Method: Checks if the IsFinished() method works correctly
     * after the text's duration has passed.
     */
    TEST(FloatingTextObjectTests, TestIsFinishedTimer)
    {
        FloatingText text(L"Test", 100.0, 100.0);

        text.Update(1.0);

        EXPECT_FALSE(text.IsFinished())
            << "Text finished too early (after 1.0s).";

        text.Update(0.6);

        EXPECT_TRUE(text.IsFinished())
            << "Text did not finish after 1.6s (duration 1.5s).";
    }
}
