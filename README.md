
# Spartan Touchdown
*See the "Playthroughs" section at the bottom of this file for examples of gameplay.*

Developers:  
* ***Beckham Lee***  
* ***Matthew Lopez***  
* ***Nishit Nagpal***  
* ***Hamin Paik***  
* ***Eliott Wurst***

#

![level3](https://github.com/user-attachments/assets/0584469c-11e0-4cbd-afc7-0d5b61a961d3)

**Spartan Touchdown** is a 2D Michigan State University (MSU) themed scroller game. It was completed using Object-oriented Design principles, the C++ programming language, the wxWidgets libraries for GUI interactivity, CMake for Windows and macOS executable building, and a GitLab repository shared among our team members.

The project was developed for MSU's Object-oriented Software Design (CSE335) class, and was completed over a 5-week period using a method like scrum to keep our team on track. We had twice weekly sprint meetings to explore design ideas, implement mechanics, assign coding tasks, and assess risks and shortcomings.

The final product was a fun game with interesting challenges, unique power-ups, and an entertaining boss-fight that won our team 3rd place out of the class's roughly 50 teams. 

--------------------

### Levels
There are 4 distinct levels, each with increasing difficulty and unique style. Each level has a scorecard in the top right corner that increases as the player collects coins, but decreases with the passage of time. Each level also has a stopwatch, in the top left corner, that indicates how long the player has been in the level for. 

The game is played using the left and right arrow keys and the space bar to perform a jump. To beat a level, the player must make the scroller collide with the level's goalpost at the end.

Levels can be automatically traversed if the player starts at level 1 and reaches the goalpost in each level, or manually selected using the "Levels" tab in the toolbar.

--------------------

## Enemies

There are various enemies that can cause the player to lose and reset a level:

<img width="109" height="93" alt="leprechaun" src="https://github.com/user-attachments/assets/8dc7e072-5c61-487d-b218-9d433dde0481" />
<img width="87" height="87" alt="wolverine" src="https://github.com/user-attachments/assets/6329be77-9ddf-499b-9ed1-efe8b15c0d02" />  
<img width="108" height="105" alt="gog" src="https://github.com/user-attachments/assets/fc52c563-d0c7-4e7d-9fbc-9024a6557207" />
<img width="97" height="221" alt="cactus" src="https://github.com/user-attachments/assets/59cc2bbf-0715-409d-9b32-260b5bf558f6" />
<img width="94" height="148" alt="boss" src="https://github.com/user-attachments/assets/9427d6f8-c529-4f04-990e-cfc5af0e7637" />  

* **Green Leprechaun** and **Yellow Wolverine** enemies:
   * Patrols a zone
   * Travels only horizontally or vertically
   * Resets the level upon any collision with the scroller
* **Gog** (green alien dog):
   * Patrols a zone
   * Travels horizontally
   * Becomes inactive if the player lands on top of it
   * Resets the level if the scroller collides with its sides or bottom
* **Cactus**:
   * Initially patrols a zone
   * Increases speed in the direction of the player when the player enters its range
   * Decreases speed and returns to its initial patrol zone when the player exits its range
   * Collides with walls and platforms
   * Resets the level upon any collision with the scroller
* **Cat Boss**:
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

#### *Enemy Demos:*

https://github.com/user-attachments/assets/fd0f0306-4565-4999-8b23-c7758db62256
 
https://github.com/user-attachments/assets/96480dfd-77b9-451d-86fd-b747f6f7defa

https://github.com/user-attachments/assets/3856973d-e0fd-4b4a-91a0-655b3c1a376c

--------------------

***See level 4 of the "Playthroughs" section for the Cat Boss demo.***

--------------------

### Powerups
There are two powerup types that the player can activate by colliding the scroller with a powerup sprite.
* **Spartan Points Doubler**:
   * All coin values are doubled
   * Active for the remainder of the level after activation
* **Double Jump**:
   * The player can jump one extra time while suspended in air
   * Active for 15 seconds
 

<img width="83" height="136" alt="points_doubler" src="https://github.com/user-attachments/assets/c9656a5b-5396-41f8-ab08-6e36315dcc51" />
<img width="102" height="122" alt="double_jump" src="https://github.com/user-attachments/assets/f0a9e7dd-ecd5-4732-aa5d-1b6c077c3012" />

--------------------

# Playthroughs

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
