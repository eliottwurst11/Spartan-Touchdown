project(GameLib)

set(SOURCE_FILES
        pch.h
        MainFrame.cpp
        MainFrame.h
        LevelView.cpp
        LevelView.h
        Item.cpp
        Item.h
        Level.cpp
        Level.h
        Football.cpp
        Football.h
        Wall.cpp
        Wall.h
        Coin.cpp
        Coin.h
        PowerUp.cpp
        PowerUp.h
        Enemy.cpp
        Enemy.h
        Goalpost.cpp
        Goalpost.h
        Scorecard.cpp
        Scorecard.h
        ItemVisitor.cpp
        ItemVisitor.h
        CoinVisitor.cpp
        CoinVisitor.h
        Declaration.cpp
        Declaration.h
        CoinDeclaration.cpp
        CoinDeclaration.h
        Picture.cpp
        Picture.h
        Background.cpp
        Background.h
        PlatformDeclaration.cpp
        PlatformDeclaration.h
        Platform.cpp
        Platform.h
        ids.h
        PowerUpDoubleJump.cpp
        PowerUpDoubleJump.h
        PowerUpBasketball.cpp
        PowerUpBasketball.h
        PowerUpPoints.cpp
        PowerUpPoints.h
        PlatformBreakable.cpp
        PlatformBreakable.h
        EnemyVisitor.cpp
        EnemyVisitor.h
        GoalpostVisitor.cpp
        GoalpostVisitor.h
        PowerUpVisitor.cpp
        PowerUpVisitor.h
        CollisionVisitor.cpp
        CollisionVisitor.h
        PlatformBreakableDeclaration.cpp
        PlatformBreakableDeclaration.h
        PowerUpPointsVisitor.cpp
        PowerUpPointsVisitor.h
        CoinIncrementVisitor.cpp
        CoinIncrementVisitor.h
        EnemyChaser.cpp
        EnemyChaser.h
        EnemyChaserVisitor.cpp
        EnemyChaserVisitor.h
        WallVisitor.cpp
        WallVisitor.h
        PlatformVisitor.cpp
        PlatformVisitor.h
        FloatingText.cpp
        FloatingText.h
        EnemyStompable.cpp
        EnemyStompable.h
        EnemyStompableVisitor.cpp
        EnemyStompableVisitor.h
        EnemyBoss.cpp
        EnemyBoss.h
        PowerUpDoubleJumpVisitor.cpp
        PowerUpDoubleJumpVisitor.h
        PowerUpBasketballVisitor.cpp
        PowerUpBasketballVisitor.h
)

set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC .)

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)