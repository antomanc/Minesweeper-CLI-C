#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helpers/helpers.h"

#define DEFAULT_SIZE "15"
#define DEFAULT_DIFFICULTY "2"
#define MAX_BOARD_SIZE 100
#define INVALID_INPUT_MESSAGE_BOARD_SIZE "Invalid input. Please enter a number.\n"
#define INVALID_INPUT_MESSAGE_DIFFICULTY "Invalid input. Please enter 1, 2, or 3.\n"
#define ENTER_BOARD_SIZE_MESSAGE "Please enter the length of the sides of the board (default 15): "
#define ENTER_DIFFICULTY_MESSAGE "Please enter the difficulty, easy: 1, medium: 2 (default), hard: 3: "
#define WELCOME_MESSAGE "Welcome to Minesweeper CLI!\n"

void welcome();
char *getBoardSize();
char *getDifficulty();
int validateBoardSize(char *input);
int validateDifficulty(char *input);
int calculateNumberOfMines(int totalCells, int difficulty);

void main()
{
    clearTerminal();
    welcome();
    char *boardSize = getBoardSize();
    int boardSizeInt = atoi(boardSize);
    clearTerminal();
    printf("Board size: %s\n", boardSize);
    char *difficulty = getDifficulty();
    clearTerminal();
    int numberOfMines = 0;
    int totalCells = boardSizeInt * boardSizeInt;
    numberOfMines = calculateNumberOfMines(totalCells, atoi(difficulty));
    char **map = generateMap(atoi(boardSize), numberOfMines);
}

void welcome()
{
    printf(WELCOME_MESSAGE);
    return;
}

int calculateNumberOfMines(int totalCells, int difficulty)
{
    switch (difficulty)
    {
    case 1:
        return totalCells * 0.1;
    case 2:
        return totalCells * 0.2;
    case 3:
        return totalCells * 0.3;
    }
}

char *getBoardSize()
{
    return getInput(ENTER_BOARD_SIZE_MESSAGE, INVALID_INPUT_MESSAGE_BOARD_SIZE, DEFAULT_SIZE, validateBoardSize);
}

char *getDifficulty()
{
    return getInput(ENTER_DIFFICULTY_MESSAGE, INVALID_INPUT_MESSAGE_DIFFICULTY, DEFAULT_DIFFICULTY, validateDifficulty);
}

int validateBoardSize(char *input)
{
    return isNumber(input) && atoi(input) <= MAX_BOARD_SIZE;
}

int validateDifficulty(char *input)
{
    return isNumber(input) && (atoi(input) == 1 || atoi(input) == 2 || atoi(input) == 3);
}
