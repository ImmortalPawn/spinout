# RG084-spinout

 ## Author 
Mladjan Gadzic
 
 ## Description
 Collect as many coins as possible while avoiding crash. 
 <br>
 Speed is not on your side.
 
 ## Dependencies
 Built using OpenGL API with GLU/GLUT Libs.
 <br>
 ```
 freeglut-dev3
 ```

 ## Installation and running the program
 Install dependencies.
 <br>
 Download the repository and run: 
 ```
 $ make
 $ ./spinout.out [gameDifficulty] [playerName]
 ```
 gameDifficulty: [emhi] (easy, medium, hard, insane). If gameDifficulty is ommited, the game is set to default (easy) mode.
 <br>
 playerName: Player's choice. If playerName is ommited, player is given default ('Unnamed') name.
 <br>
 If there are more then 3 arguments of command line, they are ignored and default values are set. Only 2 or 3 command line arguments are accepted.
 
 ## Controls 
 | **Key** | **Description** |
 | :---  | :--- |
 | ENTER | start the game |
 | 'p' or 'P' | pause the game |
 | ESC | exit the game |
 | 'a' or 'A' | move player car one line to the left |
 | 'd' or 'D' | move player car one line to the left |
 
 ## Upcoming features
 * Invulerability
 * Ammo boxes
 * Highscore leaderboard
