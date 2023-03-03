# DragonShouryo Engine

| Platform | Build Status |
| ----------- | ----------- |
| Windows | ![windows-status](https://github.com/LovelyA72/DragonShouryoXT/actions/workflows/msbuild.yml/badge.svg)  | 

DragonShouryo is a Dragonfly-like SFML game engine for **Microsoft Windows**.

**IMGD3000: Do not copy this code for your Project 2! This engine is structurally different from Dragonfly(Dragonfly games will not run). Second, you might get into trouble from Claypool if you copy my code!**

**IMGD3000学生请注意，请不要将本引擎的源代码用于你的Project 2**

<p align="center">
  <img width="460" src="./logo.jpg">
</p>

## License
DragonShouryo is **not** free software! Please read and agree the `LICENSE` file before continue. However, as long as you are using it personally and not in any Professor Claypool's class you are more than welcome to use DragonShouryo. You may read and analyse the source code of this engine. You may not copy or modify any code for this engine.

Kashouryo is a copyrighted character of TEAM A72. You are not allowed to use this character as your origional work.

## Test
The SampleGame is an arcade shooter and karaoke type software that tests the functionality of DragonShouryo by running different trigger objects in the game loop. Trigger objects receive step events with frame number and triggers predefined events at certain frames. It also tests input and other functionalities.

The cursor can shoot saucer when left clicked. When a saucer makes impact with any objects with `L7` or `L6` as sprite they will both get distroyed and the player will gain 1 point. In this version, player's cursor and space ship are image sprites while saucers stays at classic Dragonfly-style sprite.

<p align="center">
  <img height="100" src="./tips.jpg">
</p>

Controls:
* Use `F` key to toggle FPS display
* Use `C` key to toggle collision box display 
* Use `Q` key to exit
* Use left click to shoot saucer
* use `WASD` to move camera

Interesting frames that worth pointing out:
* Before `GM.run()`: The game creates a MusicTrigger and TestTrigger.
* Frame 1: TestTrigger spawns 200 star objects. It should looks just like Draonfly's Saucer Shooter.
* Frame 5: MusicTrigger says "Welcome to Dragonfly." with SynthManager.
* Frame 20: TestTrigger makes a delay to intentionally trigger the "can't keep up" warning.
* Frame 50: MusicTrigger plays music with SynthManager.

## Compile
To compile the project, open up the solution file and click the run button.


## File Structure

### **DragonShouryo**
The game engine code that can be compiled as a static library.

It contains the following important directories.

* **include** header files of the engine
* **src** C++ code implementation for the engine resides here

### **SampleGame**
A sample game that tests the functionality of the engine.

It contains the following important files
* SampleGame.cpp: Main game file
* MusicTrigger.h/cpp: Trigger object for playing music
* Shouryo.h/cpp: A dummy game object for testing WorldManager's object list and Vector2D location functionality. It's also a `HARD` object.
* TestTrigger.h: Trigger object for terminating the game and testing frame time counter
* Star.h: Star objects to recreate the background effect of Dragonfly Saucer Shooter
* Bullet.h: Bullet object for the player to shoot
* ScoreEvent.h: Custom event to notify TestTrigger that the player is scored (no longer used as the engine now uses `Hud`(ViewModel))

### **SFML**
The SFML library that's also used by the standard Dragonfly Engine

### **SoLoud**
Speech synthsizer and audio playback library.

### **x64**
Compiled game and libraries(such as SFML/OpenMPT dynamic libraries) needed for game function.

## Notes
* Engine's audio system uses `SoLoud` audio library. Which means no SFML audio component is needed. You can safely remove `openal32.dll` and SFML audio dll.
* Instead of using namespace `df`, DragonShouryo uses the namespace `dsr`.
