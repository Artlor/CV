#   This folder contains following programs:

### Beam_Fight
- This game is a result of trying to make the most addictive and fun game with the simplest set of rules possible. It’s a console game for 2 players written in C++. 
The game’s rules can be summarized as X < Y < Z. Players need to shoot correct beam to destroy enemy's beam. X beam is weaker than Y. Y beam is weaker than Z.
Z beam is weaker than X. Have fun! :) 

Player controls:  
Player 1: QWE  
Player 2: P[]  

**IMPORTANT: The settings.txt file allows user to change starting HP of players and bullet speed. The game looks for this file in current working directory, so that's
where you should put it.**

### Grrnd
- A fun game written in C++ for two players with simple but engaging rules. Players work together, in order to win they have to catch all the dots that keep reappearing in random places.

Player controls:  
Player 1: WASD  
Player 2: Up/Down/Left/Right Arrows

### Guitar_Note_Helper
- A gamified application written in C++ which makes learning names of notes across entire guitar’s fretboard easy and fun. It contains a neck of the guitar made of ASCII signs that helps learner to visualize the instrument and the position of a particular note user is asked about.

### Run_Build_Fight
- A console game written in C++ in which player can move, build walls and shoot enemies.

Player controls:  
Moving: WASD  
Shooting: Spacebar  
Build wall: Left Shift + Up/Down/Left/Right Arrows  
Change facing direction: Left Control + Up/Down/Left/Right Arrows

## How to build projects on Windows OS
- After cloning repository do the following in console:

```
cd CV/coding_projects
mkdir build
cd build
cmake ../
cmake --build .
```
