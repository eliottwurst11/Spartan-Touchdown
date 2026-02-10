
# Spartan Touchdown
*See the "Playthroughs" section at the bottom of this file for examples of gameplay.*

Developers:  
* ***Beckham Lee***  
* ***Matthew Lopez***  
* ***Nishit Nagpal***  
* ***Hamin Paik***  
* ***Eliott Wurst***

![level3](https://github.com/user-attachments/assets/0584469c-11e0-4cbd-afc7-0d5b61a961d3)

Spartan Touchdown is a 2D Michigan State University (MSU) themed scroller and platformer video game developed for MSU's Object-oriented Software Design CSE 335 class. The project was completed over about a 4 to 5-week period using a method like scrum to keep our team on track. We used twice per week sprint meetings to explore design ideas, our implementation, planning, and assignment of coding tasks, which kept our team on track. The final product was a fun game with interesting challenges and power-ups that won our team 3rd place out of the class's roughly 50 teams.

Our most important tools included the C++ programming for implementation the wxWidgets libraries for GUI interactivity, and CMake for building the executable for Windows and macOS. We used a shared GitLab repository for edits throughout the project. We also used the MSU CSE335 course webpage, lectures, and style guidelines for help, especially with regards to the principles of good Object-oriented design that was the groundwork of the project.

--------------------

### Gameplay
The game is played using the left and right arrow keys to move the scroller left and right, and the space bar to perform a jump. The scroller collides with all platforms and walls it touches. By collecting coins in a level, the player can increase their score. The player loses and the level is reset if the player falls out of the level or is defeated by an enemy. The player wins and moves to the next level if the player collides with the level's goalpost.

To travel through the level, the player must jump between platforms and walls. Most platforms and walls can be stood on
or rammed into. There is one special type of platform, the breakable platform, which is deleted after its timer runs
out (2 seconds). The timer starts once the player has landed on the breakable platform.

--------------------

### Levels
There are 4 distinct levels, each with increasing difficulty. Each level has a unique style, with the first level
being snowy, the second in a forest, the third in the mountains, and the fourth in space. Each level has a scorecard, which increases when a coin is collected, but decreases with the passage of time. Each level also has a stopwatch indicatinghow long the player has been in the level for. To beat a level, the player must make the scroller collide with the level's goalpost, which is at the end of the level.

Levels can be automatically traversed by starting at level 1 and reaching the goalpost in each level. They can also be manually 
selected using the "Levels" tab in the toolbar.

--------------------

## Enemies

There are various enemies that can cause the player to lose and reset a level:

<img width="109" height="93" alt="leprechaun" src="https://github.com/user-attachments/assets/8dc7e072-5c61-487d-b218-9d433dde0481" />
<img width="87" height="87" alt="wolverine" src="https://github.com/user-attachments/assets/6329be77-9ddf-499b-9ed1-efe8b15c0d02" />  
<img width="108" height="105" alt="gog" src="https://github.com/user-attachments/assets/fc52c563-d0c7-4e7d-9fbc-9024a6557207" />
<img width="97" height="221" alt="cactus" src="https://github.com/user-attachments/assets/59cc2bbf-0715-409d-9b32-260b5bf558f6" />
<img width="94" height="148" alt="boss" src="https://github.com/user-attachments/assets/9427d6f8-c529-4f04-990e-cfc5af0e7637" />

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
 

<img width="83" height="136" alt="points_doubler" src="https://github.com/user-attachments/assets/c9656a5b-5396-41f8-ab08-6e36315dcc51" />
<img width="102" height="122" alt="double_jump" src="https://github.com/user-attachments/assets/f0a9e7dd-ecd5-4732-aa5d-1b6c077c3012" />

--------------------

# *Playthroughs*

### Level 1:

https://github.com/user-attachments/assets/5c715c3e-c94e-40e9-8411-b21d29e42998

### Level 2:

https://github.com/user-attachments/assets/d212c556-9c7f-4402-9c9b-87effa549f86

### Level 3:

https://github.com/user-attachments/assets/329153f3-6e76-498b-98df-7a10acc81b61

### Level 4 (Boss Fight):

https://github.com/user-attachments/assets/7d611c95-b432-48d9-999c-4c31e92126a9


--------------------
## *Attribution*

The project was developed by Eliott Wurst, Beckham Lee, Matthew Lopez, Nishit Nagpal, and Hamin Paik. We used the C++ programming language, the C++ wxWidgets GUI libraries, and CMake for building. We also used a GitLab repository shared between us for development. For assistance regarding good Object-oriented Design principles, coding style choices, and documentation style, we consulted the MSU CSE335 webpage that was available to students in the course.
