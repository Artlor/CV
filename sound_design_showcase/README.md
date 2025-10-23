<h1 align="center";>GAME SOUND DESIGN SHOWCASE</h2>

*<p align="center">All sounds created from scratch by Paweł Biernacki</p>*
## Link to Sound Design Showcase Playlist

**Sound Design Showcase Playlist:** https://www.youtube.com/playlist?list=PLvpdlLqA7GcO6Ll8M5C_s50nYjSAZ8B6e

## Links to Individual Sound Design Showcases
**1. Sci-Fi Space Shooter Sound Design Showcase on YouTube:** https://youtu.be/_EdfwHmRIZ0?si=PF_fdKPd2Zo-9imN

**Game download on Windows:** https://clippinpaul.itch.io/under-stars

**2. Hack 'n' Slash RPG Sound Design Showcase on YouTube:** https://youtu.be/F85gFpdsko8?si=gsNrqsPtyCfqK9bU

## Sci-Fi Space Shooter Description

A space shooter game where your task is to fly around in a spaceship and destroy asteroids. Implemented a variety of sounds, both 2D and 3D, ranging from short one shots to long looped sounds with multiple fade in and fade outs. Parameter automation used to enhance the player's immersion by changing intensity of the ship's engine sound. Carefully implemented randomization formula for playback of background asteroid spawning sounds helps to create a cohesive ambient experience.

<h2 align="center">
  &#8595; SOUND LIST &#8595;
</h2>

**Extra sound 1: Laser Overload**

- You can activate the "Laser Overload" by shooting more than two laser beams in a row. Once you do this, the overload sound starts loading up until its maximum state. When player stops shooting, overload fades out.

**Extra sound 2: Asteroid Spawn Ambience**

- I thought it could be an interesting idea if game's ambience was made of distant, long, low pitched cracking sounds reminiscing of space debris hitting each other far away from spaceship. That's why I prepared 12 unique sounds which are randomly triggered every once in a while as well when asteroids spawn (10% chance), filling the game's soundscape.  

### List of all sounds (over 70 in total):

**Ship:**

- 'Ship engine sound' (dynamic) that is on all the time and changes its intensity based on the ship's speed. 'Ship Speed' parameter controls automation of pitch (up to +1 octave), EQ (high shelf boost) and gain (up to +5dB  

- 'Regular fire exhaust' sound which starts playing once spacebar is pressed (loop + 3 fade in + 3 fade out sounds)  

- 'Boosted fire exhaust' sound which starts playing once shift is pressed (loop + 3 fade in + 3 fade out sounds)  

- 4 high pitched + 5 low pitched 'changing direction' sounds triggered randomly when WASD keys are pressed, giving 20 sound combinations in total.  

- 16 'ship damaged' sounds split into 3 groups (strong, medium, weak) triggered based on how hard ship hits the asteroid

**Shooting:**

- 5 'Shooting laser' sounds triggered randomly when LMB is pressed

- 'Overload' which starts loading when more than 2 laser beams are shot in a row

**Asteroids:**

- 7 'Asteroid damaged' 3D sounds triggered randomly each time asteroid is hit with laser beam

- 9 'Asteroid destroyed' 3D sounds triggered randomly when asteroid is destroyed

- 12 Asteroid spawned' background sounds that are randomly triggered all the time in the background as well as when asteroids spawn (10% chance)
