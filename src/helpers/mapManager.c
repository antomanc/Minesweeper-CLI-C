#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helpers.h"

char **generateMap(int sideLenght, int numberOfMines)
{
    // the map is a square, 2D array of chars
    // we do not check for invalid input here, we assume the input is valid
    char **map = (char **)malloc(sizeof(char *) * sideLenght);

    // we initialize the map with empty cells
    // TODO
}