/**
 * @file LevelTest.cpp
 * @author nishi
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Level.h>
#include <wx/xml/xml.h>
#include <ItemVisitor.h>

using namespace std;


/**
 * Test fixture for the Level class
 * Done according to the TA, adding the load function to the dummy class and then
 * asserting that number of types is okay for 3 levels.
 */
class LevelTest : public ::testing::Test {
protected:
    void SetUp() override {
        mLevel = std::make_unique<Level>();
        // Reset counters
        backgroundCount = 0;
        platformCount = 0;
        coinCount = 0;
        wallCount = 0;
        enemyCount = 0;
        goalpostCount = 0;
        powerUpCount = 0;
    }


    void Load(const std::wstring& filename) {
        // Reset counters
        backgroundCount = 0;
        platformCount = 0;
        coinCount = 0;
        wallCount = 0;
        enemyCount = 0;
        goalpostCount = 0;
        powerUpCount = 0;

        try {
            wxXmlDocument doc;
            if (!doc.Load(filename)) {
                // File doesn't exist or can't be loaded - fail silently
                return;
            }

            auto root = doc.GetRoot();
            if (!root) {
                // Invalid XML structure - fail silently
                return;
            }

            // Skip reading attributes since we're just counting tags

            auto declarationsNode = root->GetChildren();
            if (!declarationsNode) {
                // No declarations section - fail silently
                return;
            }

            auto itemsNode = declarationsNode->GetNext();
            if (!itemsNode) {
                // No items section - fail silently
                return;
            }

            auto itemNode = itemsNode->GetChildren();
            while (itemNode) {
                wxString name = itemNode->GetName();

                if (name == L"background") {
                    backgroundCount++;
                } else if (name == L"platform") {
                    platformCount++;
                } else if (name == L"coin") {
                    coinCount++;
                } else if (name == L"wall") {
                    wallCount++;
                } else if (name == L"enemy") {
                    enemyCount++;
                } else if (name == L"goalpost") {
                    goalpostCount++;
                } else if (name == L"power-up") {
                    powerUpCount++;
                }

                itemNode = itemNode->GetNext();
            }
        }
        catch (...) {
            // Catch any exceptions and fail silently
            return;
        }
    }

    std::unique_ptr<Level> mLevel;
    
    // Counter variables
    int backgroundCount = 0;
    int platformCount = 0;
    int coinCount = 0;
    int wallCount = 0;
    int enemyCount = 0;
    int goalpostCount = 0;
    int powerUpCount = 0;
};
 

 
 TEST_F(LevelTest, Construct) {
     Level level;
 }
 
/**
 * Simple counting visitor that tallies items by type using the visitor pattern.
 * Backgrounds are intentionally not counted (no VisitBackground in ItemVisitor).
 */
class CountingVisitor : public ItemVisitor
{
public:
    int platforms = 0;
    int platformBreakables = 0;
    int coins = 0;
    int enemies = 0;
    int enemyChasers = 0;
    int enemyStompables = 0;
    int walls = 0;
    int goalposts = 0;
    int powerUps = 0; // generic power-up points
    int powerUpsDoubleJump = 0;
    int powerUpsBasketball = 0;

    void VisitPlatform(Platform*) override { platforms++; }
    void VisitPlatformBreakable(PlatformBreakable*) override { platformBreakables++; }
    void VisitCoin(Coin*) override { coins++; }
    void VisitEnemy(Enemy*) override { enemies++; }
    void VisitEnemyChaser(EnemyChaser*) override { enemyChasers++; }
    void VisitEnemyStompable(EnemyStompable*) override { enemyStompables++; }
    void VisitWall(Wall*) override { walls++; }
    void VisitGoalpost(Goalpost*) override { goalposts++; }
    void VisitPowerUpPoints(PowerUpPoints*) override { powerUps++; }
    void VisitPowerUpDoubleJump(PowerUpDoubleJump*) override { powerUpsDoubleJump++; }
    void VisitPowerUpBasketball(PowerUpBasketball*) override { powerUpsBasketball++; }
};

/**
 * Count tags directly from an XML level file for cross-check assertions.
 */
struct XmlCounts {
    int backgrounds = 0;
    int platforms = 0;
    int platformBreakables = 0;
    int coins = 0;
    int enemies = 0;
    int enemyChasers = 0;
    int enemyStompables = 0;
    int walls = 0;
    int goalposts = 0;
    int powerUps = 0; // generic power-up
    int powerUpsDoubleJump = 0;
    int powerUpsBasketball = 0;
};

static XmlCounts CountXmlTagsFromFile(const std::wstring& filename)
{
    XmlCounts c;
    wxXmlDocument doc;
    if (!doc.Load(filename)) {
        return c;
    }
    auto root = doc.GetRoot();
    if (!root) {
        return c;
    }
    auto declarationsNode = root->GetChildren();
    if (!declarationsNode) {
        return c;
    }
    auto itemsNode = declarationsNode->GetNext();
    if (!itemsNode) {
        return c;
    }
    auto itemNode = itemsNode->GetChildren();
    while (itemNode) {
        wxString name = itemNode->GetName();
        if (name == L"background") c.backgrounds++;
        else if (name == L"platform") c.platforms++;
        else if (name == L"platform-breakable") c.platformBreakables++;
        else if (name == L"coin") c.coins++;
        else if (name == L"enemy") c.enemies++;
        else if (name == L"enemy-chaser") c.enemyChasers++;
        else if (name == L"enemy-stompable") c.enemyStompables++;
        else if (name == L"wall") c.walls++;
        else if (name == L"goalpost") c.goalposts++;
        else if (name == L"power-up") c.powerUps++;
        else if (name == L"power-up-double-jump") c.powerUpsDoubleJump++;
        else if (name == L"power-up-basketball") c.powerUpsBasketball++;
        itemNode = itemNode->GetNext();
    }
    return c;
}

TEST_F(LevelTest, LoadLevel0ParsesXMLTags) {
    Load(L"levels/level0.xml");
    
    // Level 0 XML has: 1 background, 1 platform, 0 of everything else
    ASSERT_EQ(backgroundCount, 1) << L"Level 0 XML has 1 background tag";
    ASSERT_EQ(platformCount, 1) << L"Level 0 XML has 1 platform tag";
    ASSERT_EQ(coinCount, 0) << L"Level 0 XML has 0 coin tags";
    ASSERT_EQ(enemyCount, 0) << L"Level 0 XML has 0 enemy tags";
    ASSERT_EQ(wallCount, 0) << L"Level 0 XML has 0 wall tags";
    ASSERT_EQ(powerUpCount, 0) << L"Level 0 XML has 0 power-up tags";
    ASSERT_EQ(goalpostCount, 0) << L"Level 0 XML has 0 goalpost tags";
}
 
TEST_F(LevelTest, LoadLevel1ParsesXMLTags) {
    Load(L"levels/level1.xml");

    // Level 1 XML counts (corrected based on actual XML content)
    ASSERT_EQ(backgroundCount, 6) << L"Level 1 XML has 6 background tags";
    ASSERT_EQ(platformCount, 23) << L"Level 1 XML has 23 platform tags";
    ASSERT_EQ(wallCount, 10) << L"Level 1 XML has 10 wall tags";
    ASSERT_EQ(coinCount, 44) << L"Level 1 XML has 44 coin tags";
    ASSERT_EQ(enemyCount, 2) << L"Level 1 XML has 2 enemy tags";
    ASSERT_EQ(powerUpCount, 1) << L"Level 1 XML has 1 power-up tag";
    ASSERT_EQ(goalpostCount, 1) << L"Level 1 XML has 1 goalpost tag";
}

/**
 * Verify level 1 items using the visitor pattern over a loaded Level instance.
 */
TEST_F(LevelTest, Level1_VisitorCounts)
{
    // Load level via Level::Load (no LevelView required for counting)
    Level level;
    auto football = level.Load(L"levels/level1.xml", nullptr);
    ASSERT_NE(football, nullptr);

    // Cross-check XML tag counts vs loaded/visited counts
    XmlCounts xml = CountXmlTagsFromFile(L"levels/level1.xml");

    CountingVisitor v;
    level.Accept(&v);

    ASSERT_EQ(v.goalposts, xml.goalposts);
    ASSERT_EQ(v.powerUps, xml.powerUps);
    ASSERT_EQ(v.powerUpsDoubleJump, xml.powerUpsDoubleJump);
    ASSERT_EQ(v.powerUpsBasketball, xml.powerUpsBasketball);
    ASSERT_EQ(v.enemies, xml.enemies);
    ASSERT_EQ(v.enemyChasers, xml.enemyChasers);
    ASSERT_EQ(v.enemyStompables, xml.enemyStompables);
    ASSERT_EQ(v.walls, xml.walls);
    ASSERT_EQ(v.platforms, xml.platforms);
    ASSERT_EQ(v.platformBreakables, xml.platformBreakables);
    ASSERT_EQ(v.coins, xml.coins);
}


TEST_F(LevelTest, LoadLevel3ParsesXMLTags) {
    Load(L"levels/level3.xml");

    // These values have changed, and the tests are subject to more changes
    // since we are working on developing our level 3 xml file.

    // Level 3 XML has: 0 background, 1 platform, 1 goalpost, 0 of everything else
    // ASSERT_EQ(backgroundCount, 0) << L"Level 3 XML has 0 background tags";
    // ASSERT_EQ(platformCount, 1) << L"Level 3 XML has 1 platform tag";
    // ASSERT_EQ(goalpostCount, 1) << L"Level 3 XML has 1 goalpost tag";
    // ASSERT_EQ(coinCount, 0) << L"Level 3 XML has 0 coin tags";
    // ASSERT_EQ(enemyCount, 0) << L"Level 3 XML has 0 enemy tags";
    // ASSERT_EQ(wallCount, 0) << L"Level 3 XML has 0 wall tags";
    // ASSERT_EQ(powerUpCount, 0) << L"Level 3 XML has 0 power-up tags";
}

/**
 * Verify level 3 loads a comprehensive playable set using visitors.
 * We assert minimums and presence (since level 3 is under active iteration).
 */
TEST_F(LevelTest, Level3_VisitorPresence)
{
    Level level;
    auto football = level.Load(L"levels/level3.xml", nullptr);
    ASSERT_NE(football, nullptr);

    XmlCounts xml = CountXmlTagsFromFile(L"levels/level3.xml");

    CountingVisitor v;
    level.Accept(&v);

    // Assert XML vs visitor counts exactly; this ensures loader matches level design
    ASSERT_EQ(v.goalposts, xml.goalposts);
    ASSERT_EQ(v.powerUps, xml.powerUps);
    ASSERT_EQ(v.powerUpsDoubleJump, xml.powerUpsDoubleJump);
    ASSERT_EQ(v.powerUpsBasketball, xml.powerUpsBasketball);
    ASSERT_EQ(v.enemies, xml.enemies);
    ASSERT_EQ(v.enemyChasers, xml.enemyChasers);
    ASSERT_EQ(v.enemyStompables, xml.enemyStompables);
    ASSERT_EQ(v.walls, xml.walls);
    ASSERT_EQ(v.platforms, xml.platforms);
    ASSERT_EQ(v.platformBreakables, xml.platformBreakables);
    ASSERT_EQ(v.coins, xml.coins);
}