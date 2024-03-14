#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helpers/helpers.h"

#define DEFAULT_SIZE "15"
#define DEFAULT_DIFFICULTY "2"
#define DEFAULT_ACTION "f 0 0"
#define MAX_BOARD_SIZE 99
#define INVALID_INPUT_MESSAGE_BOARD_SIZE "Invalid input. Please enter a number.\n"
#define INVALID_INPUT_MESSAGE_DIFFICULTY "Invalid input. Please enter 1, 2, or 3.\n"
#define ENTER_BOARD_SIZE_MESSAGE "Please enter the length of the sides of the board (default 15): "
#define ENTER_DIFFICULTY_MESSAGE "Please enter the difficulty, easy: 1, medium: 2 (default), hard: 3: "
#define WELCOME_MESSAGE "Welcome to Minesweeper CLI!\n"
#define ENTER_ACTION_MESSAGE "Please enter f: Flag, u: Unflag, r: Reveal, q: Quit (e.g. f 1 2): "
#define INVALID_INPUT_MESSAGE_ACTION "Invalid input. Please enter f, u, r, or q followed by two numbers (e.g. f 1 2).\n"

void welcome();
char *getBoardSize();
char *getDifficulty();
char *getAction();
int validateBoardSize(char *input);
int validateDifficulty(char *input);
int validateAction(char *input);
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

    // the hidden map is the real map that the player can't see
    // with the mines and the numbers
    char **hiddenMap = generateMap(boardSizeInt, numberOfMines);
    char **visibleMap = generateMap(boardSizeInt, 0);

    renderMap(hiddenMap, visibleMap, boardSizeInt);

    int isFirstReveal = 1;
    while (1)
    {
        char *action = getAction();
        if (action[0] == 'q')
        {
            break;
        }
        int x = atoi(&action[2]);
        int y = atoi(&action[4]);
        if (isFirstReveal && action[0] == 'r')
        {
            makeFirstMove(hiddenMap, x, y, boardSizeInt);
            revealAround(hiddenMap, visibleMap, x, y, boardSizeInt);
        }
        else if (action[0] == 'f')
        {
            visibleMap[x][y] = 'F';
        }
        else if (action[0] == 'u')
        {
            visibleMap[x][y] = '?';
        }
        else if (action[0] == 'r')
        {
            int isThereMine = checkUncovered(hiddenMap, visibleMap, x, y);
            if (isThereMine)
            {
                printf("Game over! You hit a mine.\n");
                break;
            }
            else
                visibleMap[x][y] = ' ';
        }
        clearTerminal();
        renderMap(hiddenMap, visibleMap, boardSizeInt);
        if (isFirstReveal && action[0] == 'r')
        {
            isFirstReveal = 0;
        }
        for (int i = 0; i < boardSizeInt; i++)
        {
            for (int j = 0; j < boardSizeInt; j++)
            {
                printf("%c ", hiddenMap[i][j]);
            }
            printf("\n");
        }
    }
    printf("Goodbye!\n");
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

char *getAction()
{
    return getInput(ENTER_ACTION_MESSAGE, INVALID_INPUT_MESSAGE_ACTION, DEFAULT_ACTION, validateAction);
}

char *getBoardSize()
{
    return getInput(ENTER_BOARD_SIZE_MESSAGE, INVALID_INPUT_MESSAGE_BOARD_SIZE, DEFAULT_SIZE, validateBoardSize);
}

char *getDifficulty()
{
    return getInput(ENTER_DIFFICULTY_MESSAGE, INVALID_INPUT_MESSAGE_DIFFICULTY, DEFAULT_DIFFICULTY, validateDifficulty);
}

int validateAction(char *input)
{
    return 1;
    return (input[0] == 'f' || input[0] == 'u' || input[0] == 'r') && (input[1] == ' ' && isNumber(&input[2]) && input[3] == ' ' && isNumber(&input[4]) || input[0] == 'q');
}

int validateBoardSize(char *input)
{
    return isNumber(input) && atoi(input) <= MAX_BOARD_SIZE;
}

int validateDifficulty(char *input)
{
    return isNumber(input) && (atoi(input) == 1 || atoi(input) == 2 || atoi(input) == 3);
}
