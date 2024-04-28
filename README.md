# 2048
```
 .----------------.  .----------------.  .----------------.  .----------------. 
| .--------------. || .--------------. || .--------------. || .--------------. |
| |    _____     | || |     ____     | || |   _    _     | || |     ____     | |
| |   / ___ `.   | || |   .'    '.   | || |  | |  | |    | || |   .' __ '.   | |
| |  |_/___) |   | || |  |  .--.  |  | || |  | |__| |_   | || |   | (__) |   | |
| |   .'____.'   | || |  | |    | |  | || |  |____   _|  | || |   .`____'.   | |
| |  / /____     | || |  |  `--'  |  | || |      _| |_   | || |  | (____) |  | |
| |  |_______|   | || |   '.____.'   | || |     |_____|  | || |  `.______.'  | |
| |              | || |              | || |              | || |              | |
| '--------------' || '--------------' || '--------------' || '--------------' |
 '----------------'  '----------------'  '----------------'  '----------------' 
```

## Introduction
This project is a simple implementation of the popular game 2048 in C language. The game is a single-player sliding block puzzle where you combine tiles by sliding them in one of four directions (up, down, left, right). Each move adds a new tile randomly on the board, making the game progressively more challenging.

## Requirements
To compile and run this implementation of 2048, you will need:
- GCC (GNU Compiler Collection)

## Building the Game
To compile the game, use the provided Makefile with the following command:
```
make build
```
This command will compile the source files and generate an executable suitable for running the game.

## Running the Game
To start playing the game, run the following command:
```
make run
```
This will launch the game in your terminal.

## How to Play

### Objective
The goal of 2048 is to slide numbered tiles on a grid to combine them and create a tile with the number 2048.

### Controls
- Use the arrow keys to move the tiles:
  - **Up Arrow**: Moves the tiles upward.
  - **Down Arrow**: Moves the tiles downward.
  - **Left Arrow**: Moves the tiles to the left.
  - **Right Arrow**: Moves the tiles to the right.

### Rules
- On every turn, a new tile (with a number 2 or 4) randomly appears in an empty spot on the board.
- Tiles slide as far as possible in the chosen direction until they are stopped by either another tile or the edge of the grid.
- If two tiles of the same number collide while moving, they will merge into one tile with the total value of the two tiles that collided.
- The game ends when the board fills up and no more moves are possible.

### Winning the Game
To win 2048, create a tile with the number 2048. However, you can continue to play beyond this point to achieve higher scores.

### Tips
- Plan your moves ahead. Try to anticipate where new tiles might appear and how you can keep your largest tiles positioned to maximize your chances of combining them.
- Keep your highest number tile in a corner and work the rest of the tiles around it. This strategy helps to avoid unnecessary tile mixing and maintains control over the game flow.

Enjoy playing 2048, and aim for the highest score!

## License
Specify your license here if applicable, or state that it is unlicensed.
