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

char getInputV2()
{
    return getch();
}

void clearTerminal()
{
    system("clear");
}