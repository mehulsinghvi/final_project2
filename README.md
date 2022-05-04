# Arcade Pong(1972) reimagined
This is a game of simple pong where the objective is to defend your wall and score points
by hitting the opposition's wall. The game was made written in C++ and used Cinder extensively

---
## Dependencies

Cinder was used in development of this game. Follow the steps below: (taken from course website)

1. Download Cinder (v0.9.2) for your platform. Create a folder named Cinder and extract the downloaded item into it.

    https://libcinder.org/download

2. Open the ~/Cinder folder in CLion and click the green build button. This will build libcinder. You only need to do this once per machine. This build might take a while.

3. Open ~/Cinder/samples/BasicApp in a NEW PROJECT WINDOW in CLion and click the run button.

4. Now that you have cinder working, you can run this code by adding it to the directory
5. you can use execute the CMake target and run the game!

---
## Game controls
Game dynamics are pretty similar to Atari's 1972 game. The goal is to defend your wall by preventing the ball 
to hit your side, while trying to force your opponent to make a mistake and win points. The scoreboard keeps updating
as the game progresses. Once the game touches your side wall, the opponent wins a point and the ball starts hovering in the center
of the board.

### Controls
The left player controls the paddle using the up/down arrow, while the right side player controls using the mouse scrolling wheel.
New ball is introduced only when both player consent by clicking the left mouse and caps lock respectively.
Game can be restarted by right-clicking the "restart" button or using the space keys.

#### Keys

| Key                                          | Action                                                      |
|----------------------------------------------|-------------------------------------------------------------|
| `UP`                                         | Left player moves up                                        |
| `Down`                                       | Left player moves down                                      |
| `SPACE`/ right clicking <br/>"restart" button | Restart                                                     |
| `Caps` & `left click`                        | Add new ball                                                |
| `mouse wheel`                                | Right player moves up and down                              |
| `1`                                          | Start Game                                                  |

---

