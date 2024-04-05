#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include "helpers.h"

char *getInput(char message[], char errorMessage[], char defaultValue[], int (*validator)(char *), int getOneChar)
{
    char input[15];
    printw("%s", message);
    if (getOneChar)
    {
        input[0] = getch();
        input[1] = '\0';
    }
    else
    {
        getstr(input);
        printw("%s", input);
        if (input[0] == '\0')
        {
            return defaultValue;
        }
        input[strcspn(input, "\n")] = 0;

        if (!validator(input))
        {
            printw("%s", errorMessage);
            return getInput(message, errorMessage, defaultValue, validator, getOneChar);
        }

        char *result = malloc(sizeof(char) * (strlen(input) + 1));
        strcpy(result, input);
        return result;
    }

    if (!validator(input))
    {
        printw("%s", errorMessage);
        return getInput(message, errorMessage, defaultValue, validator, getOneChar);
    }

    char *result = malloc(sizeof(char) * (strlen(input) + 1));
    strcpy(result, input);
    return result;
}

void clearTerminal()
{
    clear();
}