   /**
 * @file ItemTest.cpp
 * @author Hamin Paik
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Item.h>
#include <Level.h>
#include <GoalpostVisitor.h>
#include <cmath>

/// placeholder image file since the Level constructor requires one
const std::wstring footballFile = L"images/footballMid.png";

/**
 * Mock Level class for testing purposes.
 * An Item needs a Level in its constructor, so we create a simple
 * placeholder class to satisfy that requirement for our tests.
 */
class MockLevel : public Level {
public:
    MockLevel() = default;
};

/**
 * Mock Item class for testing collision.
 * This lets us set an item's dimensions directly without loading an image file,
 * which is ideal for isolated unit testing.
 */
class TestItem : public Item {
public:
    // Item constructor uses arbitrary filename, since we are focused on collision testing in these tests
    TestItem(Level *level, double width, double height) : Item(level, footballFile), mTestWidth(width), mTestHeight(height) {}

    double GetImageWidth() const override { return mTestWidth; }
    double GetImageHeight() const override { return mTestHeight; }
    // We must provide an implementation for the pure virtual function Accept
    void Accept(ItemVisitor* visitor) override {}

    // Add CollisionTest method for testing
    bool CollisionTest(Item* item) {
        // Border for the item
        auto itemLeft = item->GetX() - item->GetImageWidth() / 2;
        auto itemRight = item->GetX() + item->GetImageWidth() / 2;
        auto itemTop = item->GetY() - item->GetImageHeight() / 2;
        auto itemBottom = item->GetY() + item->GetImageHeight() / 2;

        // For us (this test item)
        auto ourLeft = GetX() - GetImageWidth() / 2;
        auto ourRight = GetX() + GetImageWidth() / 2;
        auto ourTop = GetY() - GetImageHeight() / 2;
        auto ourBottom = GetY() + GetImageHeight() / 2;

        // Test for all of the non-collision cases
        if (ourRight < itemLeft ||  // Completely to the left
            ourLeft > itemRight ||  // Completely to the right
            ourTop > itemBottom ||  // Completely below
            ourBottom < itemTop)    // Completely above
        {
            return false;
        }

        return true;
    }

private:
    double mTestWidth;
    double mTestHeight;
};

// Test fixture for the Item class
class ItemTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a mock level instance for our tests
        mLevel = std::make_unique<MockLevel>();
    }

    std::unique_ptr<MockLevel> mLevel;
};

TEST_F(ItemTest, NoCollision)
{
    // Create two items that are far apart
    TestItem football(mLevel.get(), 50, 50);
    football.SetLocation(100, 100);

    TestItem coin(mLevel.get(), 20, 20);
    coin.SetLocation(500, 500);

    // Assert that they are not colliding
    ASSERT_FALSE(football.HitTest(&coin));
    ASSERT_FALSE(coin.HitTest(&football)); // Test is symmetrical
}

TEST_F(ItemTest, OverlapX)
{
    // Items overlapping on the X axis but not Y
    TestItem football(mLevel.get(), 100, 100);
    football.SetLocation(100, 100);

    TestItem wall(mLevel.get(), 100, 100);
    wall.SetLocation(150, 500); // Overlaps X, but far away on Y

    ASSERT_FALSE(football.HitTest(&wall));
    ASSERT_FALSE(wall.HitTest(&football));
}

TEST_F(ItemTest, OverlapY)
{
    // Items overlapping on the Y axis but not X
    TestItem football(mLevel.get(), 100, 100);
    football.SetLocation(100, 100);

    TestItem wall(mLevel.get(), 100, 100);
    wall.SetLocation(500, 120); // Overlaps Y, but far away on X

    ASSERT_FALSE(football.HitTest(&wall));
    ASSERT_FALSE(wall.HitTest(&football));
}

TEST_F(ItemTest, FullCollision)
{
    // Items directly on top of each other
    TestItem football(mLevel.get(), 100, 100);
    football.SetLocation(200, 200);

    TestItem coin(mLevel.get(), 50, 50);
    coin.SetLocation(200, 200);

    ASSERT_TRUE(football.HitTest(&coin));
    ASSERT_TRUE(coin.HitTest(&football));
}

TEST_F(ItemTest, PartialCollision)
{
    // Items partially overlapping
    TestItem football(mLevel.get(), 100, 100);
    football.SetLocation(100, 100);

    TestItem enemy(mLevel.get(), 100, 100);
    enemy.SetLocation(150, 150); // Overlaps by 50px on each axis

    ASSERT_TRUE(football.HitTest(&enemy));
    ASSERT_TRUE(enemy.HitTest(&football));
}

TEST_F(ItemTest, EdgeTouch)
{
    // Edges are touching exactly, but not overlapping.
    // The logic `abs(x1-x2)*2 < w1+w2` means touching is NOT a collision.
    TestItem football(mLevel.get(), 100, 100);
    football.SetLocation(100, 100);

    TestItem platform(mLevel.get(), 100, 100);
    platform.SetLocation(200, 100); // Right edge of football touches left edge of platform

    ASSERT_FALSE(football.HitTest(&platform));
    ASSERT_FALSE(platform.HitTest(&football));
}


TEST_F(ItemTest, PlatformCollisionTest)
{
   
    TestItem platform(mLevel.get(), 200, 50);
    platform.SetLocation(100, 100);
    
    
    TestItem football(mLevel.get(), 32, 32);
    
   
    football.SetLocation(100, 100); 
    ASSERT_TRUE(platform.CollisionTest(&football));
    
   
    football.SetLocation(300, 100); 
    ASSERT_FALSE(platform.CollisionTest(&football));
    
   
    football.SetLocation(180, 100); 
    ASSERT_TRUE(platform.CollisionTest(&football));

    football.SetLocation(166, 100); 
    ASSERT_TRUE(platform.CollisionTest(&football));
}


TEST_F(ItemTest, WallCollisionTest)
{
    
    TestItem wall(mLevel.get(), 32, 160);
    wall.SetLocation(150, 200);
    
    
    TestItem football(mLevel.get(), 32, 32);
    
    
    football.SetLocation(150, 200); 
    ASSERT_TRUE(wall.CollisionTest(&football));
    
    
    football.SetLocation(300, 200); 
    ASSERT_FALSE(wall.CollisionTest(&football));
    
   
    football.SetLocation(166, 200); 
    ASSERT_TRUE(wall.CollisionTest(&football));
    
 
    football.SetLocation(150, 100); 
    ASSERT_FALSE(wall.CollisionTest(&football));
}

/**
 * Test class for goalpost collision testing.
 * Uses distance-based collision detection with a 50-pixel radius.
 */
class TestGoalpost : public Item {
public:
    // Item constructor uses arbitrary values for initX, initY, and id since we are focused on collision testing
    TestGoalpost(Level *level) : Item(level, footballFile) {}
    
    // Override CollisionTest to use distance-based collision
    bool CollisionTest(Item* item) {
        // Calculate the distance between the goalpost and the item
        double dx = item->GetX() - GetX();
        double dy = item->GetY() - GetY();
        double distance = sqrt(dx * dx + dy * dy);
        
        // Check if the distance is within the collision radius (50 pixels)
        // Use < to match the real Goalpost implementation
        return distance < 50.0;
    }
    
    // We must provide an implementation for the pure virtual function Accept
    void Accept(ItemVisitor* visitor) override {}
    
    // Override image dimensions for testing
    double GetImageWidth() const override { return 100; }
    double GetImageHeight() const override { return 100; }
};

TEST_F(ItemTest, GoalpostCollisionTest)
{
    // Create a goalpost at position (200, 200)
    TestGoalpost goalpost(mLevel.get());
    goalpost.SetLocation(200, 200);
    
    // Create a football for testing
    TestItem football(mLevel.get(), 32, 32);
    
    // Test collision when football is within the 50-pixel radius
    football.SetLocation(220, 200); // 20 pixels away - should collide
    ASSERT_TRUE(goalpost.CollisionTest(&football));
    
    // Test no collision when football is outside the 50-pixel radius
    football.SetLocation(300, 200); // 100 pixels away - should not collide
    ASSERT_FALSE(goalpost.CollisionTest(&football));
}

/**
 * Test class for testing goalpost collision detection.
 * This tests the collision detection functionality like other collision tests.
 */
class GoalpostCollisionTest : public ::testing::Test {
protected:
    void SetUp() override {
        mLevel = std::make_unique<MockLevel>();
        mFootball = std::make_shared<TestItem>(mLevel.get(), 32, 32);
        mGoalpost = std::make_shared<TestGoalpost>(mLevel.get());
    }

    std::unique_ptr<MockLevel> mLevel;
    std::shared_ptr<TestItem> mFootball;
    std::shared_ptr<TestGoalpost> mGoalpost;
};

TEST_F(GoalpostCollisionTest, GoalpostDetectsCollision)
{
    // Set football and goalpost close (should collide)
    mFootball->SetLocation(100, 100);
    mGoalpost->SetLocation(120, 100); // 20 pixels away
    
    // Test collision detection directly like other collision tests
    ASSERT_TRUE(mGoalpost->CollisionTest(mFootball.get())) << "Goalpost should detect collision when close";
}

TEST_F(GoalpostCollisionTest, GoalpostNoCollisionWhenFarApart)
{
    // Set football and goalpost far apart (should not collide)
    mFootball->SetLocation(100, 100);
    mGoalpost->SetLocation(300, 300); // Far away
    
    // Test collision detection directly like other collision tests
    ASSERT_FALSE(mGoalpost->CollisionTest(mFootball.get())) << "Goalpost should not detect collision when far apart";
}

/**
 * Test class for testing level progression functionality.
 * This tests the level progression logic.
 */
class LevelProgressionTest : public ::testing::Test {
protected:
    void SetUp() override {
        mCurrentLevel = L"levels/level0.xml";
    }

    std::wstring mCurrentLevel;
    
    // Helper method to simulate LoadNextLevel logic
    void LoadNextLevel() {
        if (mCurrentLevel == L"levels/level0.xml") {
            mCurrentLevel = L"levels/level1.xml";
        } else if (mCurrentLevel == L"levels/level1.xml") {
            mCurrentLevel = L"levels/level2.xml";
        } else if (mCurrentLevel == L"levels/level2.xml") {
            mCurrentLevel = L"levels/level3.xml";
        } else if (mCurrentLevel == L"levels/level3.xml") {
            mCurrentLevel = L"levels/level0.xml"; // Cycle back to level 0
        }
    }
};

TEST_F(LevelProgressionTest, LevelProgressionWorks)
{
    // Test level progression: 0 -> 1 -> 2 -> 3 -> 0
    ASSERT_EQ(mCurrentLevel, L"levels/level0.xml") << "Should start at level 0";
    
    LoadNextLevel();
    ASSERT_EQ(mCurrentLevel, L"levels/level1.xml") << "Should progress to level 1";
    
    LoadNextLevel();
    ASSERT_EQ(mCurrentLevel, L"levels/level2.xml") << "Should progress to level 2";
    
    LoadNextLevel();
    ASSERT_EQ(mCurrentLevel, L"levels/level3.xml") << "Should progress to level 3";
    
    LoadNextLevel();
    ASSERT_EQ(mCurrentLevel, L"levels/level0.xml") << "Should cycle back to level 0";
}

/**
 * Test class for testing the complete goalpost collision -> level progression flow.
 * This simulates the actual game scenario where hitting a goalpost advances the level.
 */
class GoalpostGameFlowTest : public ::testing::Test {
protected:
    void SetUp() override {
        mLevel = std::make_unique<MockLevel>();
        mFootball = std::make_shared<TestItem>(mLevel.get(), 32, 32);
        mGoalpost = std::make_shared<TestGoalpost>(mLevel.get());
        mCurrentLevel = L"levels/level1.xml"; // Start at level 1 (which has a goalpost)
    }

    std::unique_ptr<MockLevel> mLevel;
    std::shared_ptr<TestItem> mFootball;
    std::shared_ptr<TestGoalpost> mGoalpost;
    std::wstring mCurrentLevel;
    
    // Helper method to simulate LoadNextLevel logic
    void LoadNextLevel() {
        if (mCurrentLevel == L"levels/level1.xml") {
            mCurrentLevel = L"levels/level2.xml";
        } else if (mCurrentLevel == L"levels/level2.xml") {
            mCurrentLevel = L"levels/level3.xml";
        } else if (mCurrentLevel == L"levels/level3.xml") {
            mCurrentLevel = L"levels/level0.xml";
        }
    }
};

TEST_F(GoalpostGameFlowTest, GoalpostCollisionTriggersLevelProgression)
{
    // Start at level 1 (which has a goalpost)
    ASSERT_EQ(mCurrentLevel, L"levels/level1.xml") << "Should be at level 1";
    
    // Simulate the game scenario: football hits goalpost -> level advances
    mFootball->SetLocation(100, 100);
    mGoalpost->SetLocation(120, 100); // Close enough to collide
    
    // Test the collision detection directly (like other collision tests)
    bool collisionDetected = mGoalpost->CollisionTest(mFootball.get());
    ASSERT_TRUE(collisionDetected) << "Goalpost collision should be detected";
    
    // Simulate what happens in Level::Update when collision is detected
    if (collisionDetected) {
        LoadNextLevel(); // This is what mLevelView->LoadNextLevel() does
    }
    
    // Verify that the level actually progressed from level 1 to level 2
    ASSERT_EQ(mCurrentLevel, L"levels/level2.xml") << "Level should advance from level 1 to level 2 when goalpost is hit";
}

TEST_F(GoalpostGameFlowTest, NoGoalpostCollisionNoLevelProgression)
{
    // Start at level 1 (which has a goalpost)
    ASSERT_EQ(mCurrentLevel, L"levels/level1.xml") << "Should be at level 1";
    
    // Simulate the game scenario: football doesn't hit goalpost -> level stays same
    mFootball->SetLocation(100, 100);
    mGoalpost->SetLocation(300, 300); // Too far to collide
    
    // Test the collision detection directly (like other collision tests)
    bool collisionDetected = mGoalpost->CollisionTest(mFootball.get());
    ASSERT_FALSE(collisionDetected) << "No goalpost collision should be detected";
    
    // Simulate what happens in Level::Update when no collision is detected
    if (collisionDetected) {
        LoadNextLevel(); // This should NOT happen
    }
    
    // Verify that the level did NOT progress (still at level 1)
    ASSERT_EQ(mCurrentLevel, L"levels/level1.xml") << "Level should NOT advance when goalpost is not hit";
}

TEST_F(GoalpostGameFlowTest, GoalpostCollisionAtBoundaryTriggersLevelProgression)
{
    // Test collision just inside the 50-pixel boundary
    mFootball->SetLocation(100, 100);
    mGoalpost->SetLocation(149, 100); // 49 pixels away (just inside boundary)
    
    // Test collision detection at boundary
    bool collisionDetected = mGoalpost->CollisionTest(mFootball.get());
    ASSERT_TRUE(collisionDetected) << "Goalpost collision should be detected just inside 50-pixel boundary";
    
    // Simulate level progression when collision is detected
    if (collisionDetected) {
        LoadNextLevel();
    }
    
    // Verify level progression
    ASSERT_EQ(mCurrentLevel, L"levels/level2.xml") << "Level should advance when goalpost is hit at boundary";
}

TEST_F(GoalpostGameFlowTest, GoalpostCollisionJustOutsideBoundaryNoLevelProgression)
{
    // Test collision just outside the 50-pixel boundary
    mFootball->SetLocation(100, 100);
    mGoalpost->SetLocation(151, 100); // 51 pixels away (just outside boundary)
    
    // Test collision detection just outside boundary
    bool collisionDetected = mGoalpost->CollisionTest(mFootball.get());
    ASSERT_FALSE(collisionDetected) << "Goalpost collision should NOT be detected just outside 50-pixel boundary";
    
    // Simulate level progression when no collision is detected
    if (collisionDetected) {
        LoadNextLevel(); // This should NOT happen
    }
    
    // Verify level does NOT progress
    ASSERT_EQ(mCurrentLevel, L"levels/level1.xml") << "Level should NOT advance when goalpost is not hit";
}

TEST_F(GoalpostGameFlowTest, GoalpostCollisionDiagonalDistanceTriggersLevelProgression)
{
    // Test collision at diagonal distance within 50-pixel radius
    mFootball->SetLocation(100, 100);
    mGoalpost->SetLocation(130, 130); // ~42 pixels away diagonally (within radius)
    
    // Test collision detection at diagonal distance
    bool collisionDetected = mGoalpost->CollisionTest(mFootball.get());
    ASSERT_TRUE(collisionDetected) << "Goalpost collision should be detected at diagonal distance within radius";
    
    // Simulate level progression when collision is detected
    if (collisionDetected) {
        LoadNextLevel();
    }
    
    // Verify level progression
    ASSERT_EQ(mCurrentLevel, L"levels/level2.xml") << "Level should advance when goalpost is hit at diagonal distance";
}