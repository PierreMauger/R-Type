# <p align="center">🗺️ Map loader</p>

## 🔎 Description

The map loader is a feature that allows the server host to manage the layout of the incoming in-game enemies with a simple text file.
This file has to be located in R-Type/Assets/Levels and has to have the proper syntax:
- `# charPerScreen:x`
The number of characters that split the game window horizontally
- `-`
A limit of the game window (not necessary as they will be ignored but can help you visualize the limits, shouldn't be anything else)
- `E`
A normal enemy (has 2 hp and 2 levels of oscillation or shoots if it doesn't)
- `B`
A normal boss (has 10 hp and shoots while circling around after the appearance animation from the top of the screen)
- `C`
Terraria's Cthulu (has 10 hp and, after its appearance animation from the top of the screen, follows/dashes on you or shoots and has a 2nd phase where he dashes 5 times to you if you damage him enough)
- `D`
Terraria's Devourer of gods (has 10 hp for each parts of the body and rushes you while weaving)
- `O`
An obstacle (indestructible)

Note that:
- The layout that you represent is actually the layout of enemies that will appear on the right of the playable zone
- You can design the incoming waves of enemies that will appear every 10seconds from the start by putting enemies farther than the charPerScreen width
- Enemies with an appearance animation (like a Boss or Cthulu) will still appear to the spot you've put but from the top
- The height of the layout map lets you split vertically the screen into how many zones you want (as the game is a sidescroller, the waves size is decided horizontally and not vertically)
- You can layout your levels in multiple separate files (they get loaded alphabetically)

## 📍 Example

Here the enemies map/game window is split into 5 horizontal zones (per wave) and 4 vertical zones.
```
# charPerScreen:5
-----------------
-    E     E    -
-  E     E   C  -
-  C      E     -
-E   E     E    -
-----------------
```
So at the start of the game those enemies that are in the 5 characters will spawn on the right of the playable zone of the same size:
```
playable zone that you can't leave
   v
-------------
-     -    E-
-     -  E  -
-     -  C  -
-     -E   E-
-------------
         ^
5 chars wide wave of enemies that will come from the right (or from the top if boss)
```
After 10 seconds (doesnt matter if you killed all the enemies or not) the other wave (5 chars after) is summoned/comes:
```
-------------
-     -     -
-     -   E -
-     -    E-
-     -     -
-------------
```
Et cetera (until there's no more enemy waves laid out in the file)