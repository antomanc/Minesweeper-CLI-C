#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include "helpers.h"

char *getInput(char message[], char errorMessage[], char defaultValue[], int (*validator)(char *))
{
    char input[15]; // 15 is a good max length for all inputs in this program
    printf("%s", message);
    fgets(input, sizeof(input), stdin);
    if (input[0] == '\n')
    {
        return defaultValue;
    }
    input[strcspn(input, "\n")] = 0;
    if (!validator(input))
    {
        printf("%s", errorMessage);
        return getInput(message, errorMessage, defaultValue, validator);
    }
    char *result = malloc(sizeof(char) * (strlen(input) + 1));
    strcpy(result, input);
    return result;
}

char *getInputV2(char message[], char errorMessage[], char defaultValue[], int (*validator)(char *), int streamOneChar)
{
    // porting the getInput function to use ncurses, with the addition of the isOneChar parameter
    char input[15];
    printw("%s", message);
    if (streamOneChar)
    {
        input[0] = getch();
        input[1] = '\0';
    }
    else
    {
        getstr(input);

        if (input[0] == '\n')
        {
            return defaultValue;
        }
        input[strcspn(input, "\n")] = 0;

        if (!validator(input))
        {
            printw("%s", errorMessage);
            return getInputV2(message, errorMessage, defaultValue, validator, streamOneChar);
        }

        char *result = malloc(sizeof(char) * (strlen(input) + 1));
        strcpy(result, input);
        return result;
    }

    if (!validator(input))
    {
        printw("%s", errorMessage);
        return getInputV2(message, errorMessage, defaultValue, validator, streamOneChar);
    }

    char *result = malloc(sizeof(char) * (strlen(input) + 1));
    strcpy(result, input);
    return result;
}

void clearTerminal()
{
    clear();
}