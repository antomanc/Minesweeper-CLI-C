#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include "helpers/helpers.h"

#define DEFAULT_SIZE "15"
#define DEFAULT_DIFFICULTY "2"
#define DEFAULT_ACTION "f 0 0"
#define MAX_BOARD_SIZE 99
#define MIN_BOARD_SIZE 4
#define INVALID_INPUT_MESSAGE_BOARD_SIZE "Invalid input. Please enter a number between 4 and 99.\n"
#define INVALID_INPUT_MESSAGE_DIFFICULTY "Invalid input. Please enter 1, 2, or 3.\n"
#define INVALID_INPUT_MESSAGE_ACTION "Invalid input. Please enter f, u, r, or q followed by two numbers (e.g. f 1 2).\n"
#define ENTER_BOARD_SIZE_MESSAGE "Please enter the length of the sides of the board (default 15): "
#define ENTER_DIFFICULTY_MESSAGE "Please enter the difficulty, easy: 1, medium: 2 (default), hard: 3: "
#define ENTER_ACTION_MESSAGE "Please enter f: Flag, u: Unflag, r: Reveal, q: Quit (e.g. f 1 2): "
#define WELCOME_MESSAGE "Welcome to Minesweeper CLI!\n"
#define GAME_OVER_MESSAGE "Game over! You hit a mine.\n"
#define CONGRATULATIONS_MESSAGE "Congratulations! You won!\n"
#define GOODBYE_MESSAGE "Goodbye!\n"

char *getBoardSize();
char *getDifficulty();
int validateBoardSize(char *input);
int validateDifficulty(char *input);
int validateAction(char *input);
int calculateNumberOfMines(int totalCells, int difficulty);

void main()
{

    initscr();
    cbreak();

    char *boardSize = getBoardSize();
    int boardSizeInt = atoi(boardSize);
    mvprintw(0, 0, "Board size: %s\n", boardSize);
    char *difficulty = getDifficulty();

    clearTerminal();
    noecho();
  
    int numberOfMines;

    int totalCells = boardSizeInt * boardSizeInt;
    numberOfMines = calculateNumberOfMines(totalCells, atoi(difficulty));

    // the hidden map is the real map that the player can't see
    // with the mines and the numbers
    char **hiddenMap = generateMap(boardSizeInt);
    char **visibleMap = generateMap(boardSizeInt);

    free(boardSize);
    free(difficulty);

    int isFirstReveal = 1;
    int isGameWon = 0;

    // we initialize the the current position, x and y, of the cursor
    int cursorX = 0;
    int cursorY = 0;

    curs_set(0);
    renderMap(hiddenMap, visibleMap, boardSizeInt, cursorX, cursorY, "");

    while (1)
    {
        char *actionPointer = getInput(
            "", "", DEFAULT_ACTION, validateAction, 1);
        char action = actionPointer[0];
        if (action == 'q')
        {
            mvprintw(boardSizeInt * 2 + 2, 0, GOODBYE_MESSAGE);
            refresh();
            break;
        }
        else if (action == 'j')
        {
            if (visibleMap[cursorX][cursorY] == '0')
            {
                visibleMap[cursorX][cursorY] = 'F';
            }
            else if (visibleMap[cursorX][cursorY] == 'F')
            {
                visibleMap[cursorX][cursorY] = '0';
            }
        }
        else if (action == 'k')
        {
            if (isFirstReveal)
            {
                populateMapWithMinesAndNumbers(hiddenMap, cursorX, cursorY, boardSizeInt, numberOfMines);
                revealZerosAround(hiddenMap, visibleMap, cursorX, cursorY, boardSizeInt);
                isFirstReveal = 0;
            }
            else
            {
                int isThereMine = checkUncovered(hiddenMap, visibleMap, cursorX, cursorY);
                if (isThereMine)
                {
                    // we reveal all the mines
                    for (int i = 0; i < boardSizeInt; i++)
                    {
                        for (int j = 0; j < boardSizeInt; j++)
                        {
                            if (hiddenMap[i][j] == 'M')
                            {
                                visibleMap[i][j] = 'M';
                            }
                        }
                    }
                    renderMap(hiddenMap, visibleMap, boardSizeInt, cursorX, cursorY, GAME_OVER_MESSAGE);
                    break;
                }
                else
                    visibleMap[cursorX][cursorY] = ' ';
            }
        }
        else if (action == 'w')
        {
            if (cursorX > 0)
            {
                cursorX--;
            }
        }
        else if (action == 'a')
        {
            if (cursorY > 0)
            {
                cursorY--;
            }
        }
        else if (action == 's')
        {
            if (cursorX < boardSizeInt - 1)
            {
                cursorX++;
            }
        }
        else if (action == 'd')
        {
            if (cursorY < boardSizeInt - 1)
            {
                cursorY++;
            }
        }

        isGameWon = checkWin(hiddenMap, visibleMap, boardSizeInt, numberOfMines);
        if (isGameWon)
        {
            renderMap(hiddenMap, visibleMap, boardSizeInt, cursorX, cursorY, CONGRATULATIONS_MESSAGE);
            break;
        }
      
        free(action);
        renderMap(hiddenMap, visibleMap, boardSizeInt, cursorX, cursorY, "");
    }
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
    return getInput(ENTER_BOARD_SIZE_MESSAGE, INVALID_INPUT_MESSAGE_BOARD_SIZE, DEFAULT_SIZE, validateBoardSize, 0);
}

char *getDifficulty()
{
    return getInput(ENTER_DIFFICULTY_MESSAGE, INVALID_INPUT_MESSAGE_DIFFICULTY, DEFAULT_DIFFICULTY, validateDifficulty, 0);
}

int validateBoardSize(char *input)
{
    return isNumber(input) && atoi(input) <= MAX_BOARD_SIZE && atoi(input) >= MIN_BOARD_SIZE;
}

int validateDifficulty(char *input)
{
    return isNumber(input) && (atoi(input) == 1 || atoi(input) == 2 || atoi(input) == 3);
}

int validateAction(char *input)
{
    return 1;
}
