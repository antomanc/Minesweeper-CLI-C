# Minesweeper CLI C
![image](https://github.com/user-attachments/assets/20277573-dd86-4e4e-8303-d4fe6c62e044)

This is a command line version of the famous game Minesweeper. The game is written in C and uses the ncurses library for input/output.
It supports fast WASD movements and J-K keys for toggling a flag and revealing the cell.

## Build Instructions

To build the project, you will need a C compiler such as gcc.

After installing gcc, navigate with the terminal inside the main folder of the project, then you can compile the project with the following command:

```bash
gcc src/main.c src/helpers/isNumber.c src/helpers/inputManager.c src/helpers/mapManager.c -lncurses -o build/minesweeper
```

This command compiles all the needed files and generates an executable called `minesweeper` in the build directory.

## How to Run the Game

After compiling the project, you can run the game with the following command:

```bash
./build/minesweeper
```

## How to Play

Upon starting the game, you will be asked to enter the grid size and difficulty. You can enter these values or press enter to use the default values.

During the game, you will have the following options:

- `W` to move the cursor up
- `A` to move the cursor left
- `S` to move the cursor down
- `D` to move the cursor right
- `J` to toggle a flag on the current cell
- `K` to reveal the current cell
- `Q` to quit the game
