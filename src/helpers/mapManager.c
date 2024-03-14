#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "time.h"
#include "helpers.h"

// this function is used to get the number of mines around a cell with coordinates x,y in a map
int getNumberOfMines(char **map, int x, int y, int sideLenght)
{
    int numberOfMines = 0;
    if (x - 1 >= 0 && y - 1 >= 0 && map[x - 1][y - 1] == 'M')
    {
        numberOfMines++;
    }
    if (x - 1 >= 0 && map[x - 1][y] == 'M')
    {
        numberOfMines++;
    }
    if (x - 1 >= 0 && y + 1 < sideLenght && map[x - 1][y + 1] == 'M')
    {
        numberOfMines++;
    }
    if (y - 1 >= 0 && map[x][y - 1] == 'M')
    {
        numberOfMines++;
    }
    if (y + 1 < sideLenght && map[x][y + 1] == 'M')
    {
        numberOfMines++;
    }
    if (x + 1 < sideLenght && y - 1 >= 0 && map[x + 1][y - 1] == 'M')
    {
        numberOfMines++;
    }
    if (x + 1 < sideLenght && map[x + 1][y] == 'M')
    {
        numberOfMines++;
    }
    if (x + 1 < sideLenght && y + 1 < sideLenght && map[x + 1][y + 1] == 'M')
    {
        numberOfMines++;
    }
    return numberOfMines;
}

// this function is used to calculate the numbers from a map made of Ms and 0s
void calculateNumbers(char **map, int sideLenght)
{
    for (int i = 0; i < sideLenght; i++)
    {
        for (int j = 0; j < sideLenght; j++)
        {
            if (map[i][j] != 'M')
            {
                int numberOfMines = getNumberOfMines(map, i, j, sideLenght);
                map[i][j] = numberOfMines + '0';
            }
        }
    }
    return;
}

void makeFirstMove(char **hiddenMap, int x, int y, int sideLenght)
{
    // this function is used to make the first move of the player
    // if the player hits a mine or a number different than 0, we need to edit the map
}

// this function uncover all cells around 0s of a map
// it is used when the player does the first move
char **revealAround(char **hiddenMap, char **visibleMap, int x, int y, int sideLenght)
{
}

// this function uses ASCII characters and carefull formatting to render the map
void renderMap(char **hiddenMap, char **visibleMap, int sideLenght)
{
    printf("   ");
    for (int i = 0; i < sideLenght; i++)
    {
        if (i < 9)
        {
            printf("  %d ", i);
        }
        else if (i == 9)
        {
            printf("  %d ", i);
        }
        else
        {
            printf("  %d", i);
        }
    }
    printf("\n   ");
    for (int j = 0; j < sideLenght; j++)
    {
        printf("+---");
    }
    printf("+\n");
    for (int i = 0; i < sideLenght; i++)
    {
        printf("%2d ", i);
        for (int j = 0; j < sideLenght; j++)
        {
            if (visibleMap[i][j] == '0')
            {
                printf("| ? ");
            }
            else if (visibleMap[i][j] == ' ')
            {
                printf("| %c ", hiddenMap[i][j]);
            }
            else
            {
                printf("| %c ", visibleMap[i][j]);
            }
        }
        printf("|\n");
        printf("   ");
        for (int j = 0; j < sideLenght; j++)
        {
            printf("+---");
        }
        printf("+\n");
    }
}

int checkUncovered(char **hiddenMap, char **visibleMap, int x, int y)
{
    if (hiddenMap[x][y] == 'M')
    {
        return 1;
    }
    return 0;
}

char **generateMap(int sideLenght, int numberOfMines)
{
    // the map is a square, 2D array of chars
    // we do not check for invalid input here, we assume the input is valid

    // we allocate memory for the each row
    char **map = (char **)malloc(sizeof(char *) * sideLenght);

    // we allocate memory for each cell
    for (int i = 0; i < sideLenght; i++)
    {
        map[i] = (char *)malloc(sizeof(char) * sideLenght);
    }

    // we initialize the map with 0

    for (int i = 0; i < sideLenght; i++)
    {
        for (int j = 0; j < sideLenght; j++)
        {
            map[i][j] = '0';
        }
    }

    // if there are no mines, we return the map
    // this is useful for the visible map
    if (numberOfMines == 0)
    {
        return map;
    }

    // we use the current time as a seed for the random number generator
    srand(time(NULL));

    // we place the mines
    for (int i = 0; i < numberOfMines; i++)
    {
        int x = rand() % sideLenght;
        int y = rand() % sideLenght;
        map[x][y] = 'M';
    }

    calculateNumbers(map, sideLenght);

    return map;
}
