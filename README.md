
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
 
https://github.com/user-attachments/assets/96480dfd-77b9-451d-86fd-b747f6f7defa

* Cactus:
   * Initially patrols a zone
   * Increases speed in the direction of the player when the player enters its range
   * Decreases speed and returns to its initial patrol zone when the player exits its range
   * Collides with walls and platforms
   * Resets the level upon any collision with the scroller

https://github.com/user-attachments/assets/4bc09dba-4dd5-4f47-92a9-afb362005e02

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

**See level 4 of the "Playthroughs" section for the Cat Boss demo.**

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

## Playthroughs 

### Level 1


### Level 2 

### Level 3

### Level 4 (Boss Fight)

https://github.com/user-attachments/assets/7d611c95-b432-48d9-999c-4c31e92126a9


