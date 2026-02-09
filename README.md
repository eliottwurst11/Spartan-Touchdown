
# Spartan Touchdown
*See the "Playthroughs" section at the bottom of this file for examples of gameplay.*

Developers:  
* ***Beckham Lee***  
* ***Matthew Lopez***  
* ***Nishit Nagpal***  
* ***Hamin Paik***  
* ***Eliott Wurst***

Spartan Touchdown is a 2D Michigan State University (MSU) themed scroller and platformer video game developed for MSU's Object-oriented Software Design CSE 335 class. The project was completed over about a 4 to 5-week period using a method like scrum to keep our team on track. We used twice per week sprint meetings to explore design ideas, our
implementation, planning, and assignment of coding tasks, which kept our team on track. The final product was a fun game with interesting challenges and power-ups that won our team 3rd place out of the class's roughly 50 teams.

--------------------

### Gameplay
The game is played using the left and right arrow keys to move the scroller left and right, and the space bar to perform a jump. The scroller collides with all platforms and walls it touches. By collecting coins in a level, the player can increase their score. The player loses and the level is reset if the player falls out of the level or is defeated by an enemy. The player wins and moves to the next level if the player collides with the level's goalpost.

PUT DEMO/VIDS/IMAGES HERE

--------------------

### Levels
There are 4 distinct levels, each with increasing difficulty. Each level has a unique style, with the first level
being snowy, the second in a forest, the third in the mountains, and the fourth in space. Each level has a scorecard, which increases when a coin is collected, but decreases with the passage of time. Each level also has a stopwatch indicatinghow long the player has been in the level for. To beat a level, the player must make the scroller collide with the level's goalpost, which is at the end of the level.

Levels can be automatically traversed by starting at level 1 and reaching the goalpost in each level. They can also be manually 
selected using the "Levels" tab in the toolbar.

![level3](https://github.com/user-attachments/assets/0584469c-11e0-4cbd-afc7-0d5b61a961d3)

--------------------

### Enemies
There are various enemies that can cause the player to lose and reset a level.
* Green Leprechaun and Yellow Wolverine enemies:
   * Patrols a zone
   * Travels only horizontally or vertically
   * Resets the level upon any collision with the scroller

https://github.com/user-attachments/assets/fd0f0306-4565-4999-8b23-c7758db62256

 
* Gog (green alien dog):
   * Patrols a zone
   * Travels horizontally
   * Becomes inactive if the player lands on top of it
   * Resets the level if the scroller collides with its sides or bottom
* Cactus:
   * Initially patrols a zone
   * Increases speed in the direction of the player when the player enters its range
   * Decreases speed and returns to its initial patrol zone when the player exits its range
   * Collides with walls and platforms
   * Resets the level upon any collision with the scroller
* Cat Boss:
  * Periodically switches between patrolling, jumping, and dashing, unless it was recently stomped
  * Switches to a limited time invulnerable sped up state after being stomped
  * Invulnerable while it is preparing to switch states
  * Three successful stomps by the player deactivates the boss
  * Vulnerable state: Takes damage and switches to invulnerable state if the scroller lands on top of it, but resets level if player collides with sides or bottom
    * Active when the boss is patrolling
    * Active when the boss is airborne
  * Invulnerable state: any collision with the scroller resets the level
    * Active when the boss is preparing to dash or jump
    * Active when the boss is dashing  

**See level 4 of the "Playthroughs" section for the Cat Boss.**
  
PUT ENEMY IMAGES HERE

--------------------

### Powerups
There are two powerups that the player can earn, which are activated by direct collision between the scroller and powerup sprite.
* Spartan Points Doubler:
   * All coin values are doubled
   * Active for the remainder of the level after activation
* Double Jump:
   * The player can jump one extra time while suspended in air
   * Active for 15 seconds

PUT POWERUP IMAGES HERE

--------------------

### Level Traversal
To travel through the level, the player must jump between platforms and walls. Most platforms and walls can be stood on
or rammed into. There is one special type of platform, the breakable platform, which is deleted after its timer runs
out (2 seconds). The timer starts once the player has landed on the breakable platform.

BREAKABLE PLATFORM IMAGE

--------------------

### Playthroughs 

LEVEL 1 PLAYTHROUGH

LEVEL 2 PLAYTHROUGH

LEVEL 3 PLAYTHROUGH

LEVEL 4 PLAYTHROUGH





[//]: # (## Team Bridgeforth's special features)

[//]: # ()
[//]: # (--------------------)

[//]: # ()
[//]: # (1. New stompable enemy)

[//]: # (    * Added new green dog enemy that patrols back and forth. )

[//]: # (    * Upon stomp, the enemy dies.)

[//]: # ()
[//]: # (--------------------)

[//]: # ()
[//]: # (2. New chaser enemy )

[//]: # (    * Added new cactus enemy that turns hostile once the player enters its range.)

[//]: # (    * The cactus turns red indicating it is hostile. Once the player is far enough, the cactus stops chasing.)

[//]: # ()
[//]: # (--------------------)

[//]: # ()
[//]: # (3. New boss enemy)

[//]: # (    * Added new boss enemy for level 4. The boss has three patterns.)

[//]: # (    * Every couple second the boss will go into "preparation" state for a few seconds before performing one of the following actions:)

[//]: # (      * A high jump in the direction of the player)

[//]: # (      * A dash toward the player)

[//]: # (    * The boss is invulnerable while it is in the "preparation" state.)

[//]: # (    * It takes three stomps for the boss to die.)

[//]: # (    * The boss alternates dashes and jumps.)

[//]: # (    * When the player stomps on the boss, it enters an enraged mode, and is temporarily invulnerable.)

[//]: # ()
[//]: # (--------------------)

[//]: # ()
[//]: # (4. New level 4)

[//]: # (    * Added new hidden level 4, reachable when the player collides with the door sprite in level 3.)

[//]: # (    * Boss fight level, where the player must fight the boss in order to complete the game.)

[//]: # (    * Once the boss is defeated, the goal post will spawn in allowing the player to enter and end the game.)

[//]: # (    * Level 4 is an optional level. Player does not have to go through level 4 in order to beat level 3.)

[//]: # (   )
[//]: # (--------------------)

[//]: # ()
[//]: # (5. New double jump power up)

[//]: # (    * Added new double jump power up. )

[//]: # (    * Collecting the power up will grant the player the ability to double jump for a limited time &#40;15 seconds&#41;.)

[//]: # (   )
[//]: # (--------------------)

[//]: # ()
[//]: # (6. New breakable platform)

[//]: # (    * Added new breakable platform.)

[//]: # (    * When the player steps on the breakable platform, it will start the "breaking" sequence.)

[//]: # (    * The platform disappears after a set time period.)

[//]: # (   )
[//]: # (--------------------)

[//]: # ()
[//]: # (7. New player sprite)

[//]: # (    * Added new basketball sprite for the player.)

[//]: # (    * When the player enters the hidden level, the player sprite &#40;the football&#41; will turn into a basketball sprite.)
