# Minesweeper CLI C
This is a command line version of the famous game Minesweeper. The game is written in C and uses the standard C library for input/output.

## Build Instructions

To build the project, you will need a C compiler such as gcc.

After installing gcc, navigate with the terminal inside the main folder of the project, then you can compile the project with the following command:

```bash
gcc src/main.c src/helpers/isNumber.c src/helpers/inputManager.c src/helpers/mapManager.c -o build/minesweeper
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

- `f x y`: Place a flag on the cell at coordinates (x, y).
- `u x y`: Remove a flag from the cell at coordinates (x, y).
- `r x y`: Reveal the cell at coordinates (x, y).
- `q`: Quit the game.
