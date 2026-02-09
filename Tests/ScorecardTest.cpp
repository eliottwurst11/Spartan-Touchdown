/**
 * @file ScorecardTest.cpp
 * @author Hamin Paik
 */

#include <pch.h>
#include <gtest/gtest.h>
#include <Scorecard.h>

TEST(ScorecardTest, ScoreDecrease) {
    Scorecard scorecard;

    // Add an initial score
    scorecard.AddScore(10);
    ASSERT_EQ(scorecard.GetScore(), 10);

    // Simulate time passing. For each full second, the score should decrease by 1.
    for (int i = 0; i < 10; ++i) {
        // Update by one full second
        scorecard.Update(1.0);
        ASSERT_EQ(scorecard.GetScore(), 9 - i);
    }

    // After 10 seconds, score should be 0
    ASSERT_EQ(scorecard.GetScore(), 0);

    // Simulate another second passing, score should remain 0
    scorecard.Update(1.0);
    ASSERT_EQ(scorecard.GetScore(), 0);

    // Simulate a large chunk of time, score should still be 0
    scorecard.Update(100.0);
    ASSERT_EQ(scorecard.GetScore(), 0);
}
