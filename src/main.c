#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helpers/helpers.h"

#define DEFAULT_SIZE 15
#define DEFAULT_DIFFICULTY 2
#define INVALID_INPUT_MESSAGE_BOARD_SIZE "Invalid input. Please enter a number.\n"
#define INVALID_INPUT_MESSAGE_DIFFICULTY "Invalid input. Please enter 1, 2, or 3.\n"
#define ENTER_BOARD_SIZE_MESSAGE "Please enter the length of the sides of the board (default: 15): "
#define ENTER_DIFFICULTY_MESSAGE "Please enter the difficulty, easy: 1, medium: 2 (default), hard: 3: "
#define WELCOME_MESSAGE "Welcome to Minesweeper CLI!\n"

void welcome();
int getInput(char *message, char *errorMessage, int defaultValue, int (*validator)(int));
int getBoardSize();
int getDifficulty();
int validateBoardSize(int size);
int validateDifficulty(int difficulty);
int isNumber(char *input);

int main()
{
    welcome();
    int boardSize = getBoardSize();
    printf("Board size: %d\n", boardSize);
    int difficulty = getDifficulty();
    printf("Difficulty: %s\n", difficulty == 1 ? "easy" : (difficulty == 2 ? "medium" : "hard"));
    return 0;
}

void welcome()
{
    printf(WELCOME_MESSAGE);
    return;
}

int getInput(char *message, char *errorMessage, int defaultValue, int (*validator)(int))
{
    char input[10];
    int isInputNumber;
    printf(message);
    fgets(input, sizeof(input), stdin);
    if (input[0] == '\n')
    {
        return defaultValue;
    }
    input[strcspn(input, "\n")] = 0;
    isInputNumber = isNumber(input);
    if (isInputNumber == 0)
    {
        printf(errorMessage);
        return getInput(message, errorMessage, defaultValue, validator);
    }
    int value = atoi(input);
    if (!validator(value))
    {
        printf(errorMessage);
        return getInput(message, errorMessage, defaultValue, validator);
    }
    return value;
}

int getBoardSize()
{
    return getInput(ENTER_BOARD_SIZE_MESSAGE, INVALID_INPUT_MESSAGE_BOARD_SIZE, DEFAULT_SIZE, validateBoardSize);
}

int getDifficulty()
{
    return getInput(ENTER_DIFFICULTY_MESSAGE, INVALID_INPUT_MESSAGE_DIFFICULTY, DEFAULT_DIFFICULTY, validateDifficulty);
}

int validateBoardSize(int size)
{
    return size > 0;
}

int validateDifficulty(int difficulty)
{
    return difficulty >= 1 && difficulty <= 3;
}
