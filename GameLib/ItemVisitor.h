/**
 * @file ItemVisitor.h
 * @author Eliott Wurst
 *
 * Basic visitor class for Item objects
 */

#ifndef GAME_ITEMVISITOR_H
#define GAME_ITEMVISITOR_H


/// Forward reference to each child of Item class
class Coin;
class Enemy;
class Football;
class Goalpost;
class Platform;
class PowerUp;
class Wall;
class PowerUpPoints;
class PlatformBreakable;
class EnemyChaser;
class EnemyStompable;
class PowerUpDoubleJump;
class PowerUpBasketball;

/**
 * Definition of a basic visitor class for Item objects
 */
class ItemVisitor {
private:
protected:
    /**
     * Protected constructor; can be used in upcalls
     */
    ItemVisitor() {}

public:
    /**
     * virtual destructor
     */
    virtual ~ItemVisitor() {}

    /**
     * Visit a Coin object
     * @param coin Coin to visit
     */
    virtual void VisitCoin(Coin* coin) {}

    /**
     * Visit an Enemy object
     * @param enemy Enemy to visit
     */
    virtual void VisitEnemy(Enemy* enemy) {}

    /**
     * Visit a Football object
     * @param football Football to visit
     */
    virtual void VisitFootball(Football* football) {}

    /**
     * Visit a Goalpost object
     * @param goalpost Goalpost to visit
     */
    virtual void VisitGoalpost(Goalpost* goalpost) {}

    /**
     * Visit a Platform object
     * @param platform Platform to visit
     */
    virtual void VisitPlatform(Platform* platform) {}

    /**
     * Visit a PowerUp object
     * @param powerUp PowerUp to visit
     */
    virtual void VisitPowerUp(PowerUp* powerUp) {}

    /**
     * Visit a Wall object
     * @param wall Wall to visit
     */
    virtual void VisitWall(Wall* wall) {}

    /**
     * Visit a points power up
     * @param powerUpPoints Points power up to be visited
     */
    virtual void VisitPowerUpPoints(PowerUpPoints* powerUpPoints) {}

    /**
     * Visit a PlatformBreakable object
     * @param platform PlatformBreakable object to visit
     */
    virtual void VisitPlatformBreakable(PlatformBreakable* platform) {}

    /**
     * Visit an EnemyChaser object
     * @param enemyChaser EnemyChaser object to visit
     */
    virtual void VisitEnemyChaser(EnemyChaser* enemyChaser) {}

    /**
     * Visit an EnemyStompable object
     * @param enemyStompable object to visit
     */
    virtual void VisitEnemyStompable(EnemyStompable* enemyStompable) {}

    /**
     * Visit a double jump powerup
     * @param powerUpDoubleJump
     */
    virtual void VisitPowerUpDoubleJump(PowerUpDoubleJump* powerUpDoubleJump) {}

    /**
     * Visit a basketball powerup
     * @param powerUpBasketball
     */
    virtual void VisitPowerUpBasketball(PowerUpBasketball* powerUpBasketball) {}
};


#endif //GAME_ITEMVISITOR_H