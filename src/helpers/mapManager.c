#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include "time.h"
#include "helpers.h"

// this just check if all the cells that are not mines are uncovered
int checkWin(char **hiddenMap, char **visibleMap, int sideLenght, int numberOfMines)
{
    int numberOfUncovered = 0;
    for (int i = 0; i < sideLenght; i++)
    {
        for (int j = 0; j < sideLenght; j++)
        {
            if (visibleMap[i][j] != '0' && visibleMap[i][j] != 'F')
            {
                numberOfUncovered++;
            }
        }
    }
    if (numberOfUncovered == sideLenght * sideLenght - numberOfMines)
    {
        return 1;
    }
    return 0;
}

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

// this function populate the map with mines and numbers
// x and y are the coordinates of the first move
// we need to be sure no mines are around and on the first move
void populateMapWithMinesAndNumbers(char **hiddenMap, int x, int y, int sideLenght, int numberOfMines)
{
    // we use the time to generate a random seed
    srand(time(NULL));

    for (int i = 0; i < numberOfMines; i++)
    {
        int randomX = rand() % sideLenght;
        int randomY = rand() % sideLenght;

        // this is very brute force, but it is the easiest way to do it
        while (hiddenMap[randomX][randomY] == 'M' || (randomX == x && randomY == y) ||
               (randomX == x - 1 && randomY == y) || (randomX == x + 1 && randomY == y) ||
               (randomX == x && randomY == y - 1) || (randomX == x && randomY == y + 1) ||
               (randomX == x - 1 && randomY == y - 1) || (randomX == x + 1 && randomY == y + 1) ||
               (randomX == x - 1 && randomY == y + 1) || (randomX == x + 1 && randomY == y - 1))
        {
            randomX = rand() % sideLenght;
            randomY = rand() % sideLenght;
        }

        hiddenMap[randomX][randomY] = 'M';
    }

    calculateNumbers(hiddenMap, sideLenght);

    return;
}

// this function uncover all cells around a 0
// it uncovers all the cells around a 0, and if there are other 0s around, it uncovers them too
// it is used when the player does the first move
void revealZerosAround(char **hiddenMap, char **visibleMap, int x, int y, int sideLenght)
{
    // we suppose the x and y are valid coordinates and the cell is a 0
    for (int i = x - 1; i <= x + 1; i++)
    {
        for (int j = y - 1; j <= y + 1; j++)
        {
            if (i >= 0 && i < sideLenght && j >= 0 && j < sideLenght && hiddenMap[i][j] == '0' && visibleMap[i][j] == '0')
            {
                visibleMap[i][j] = ' ';
                revealZerosAround(hiddenMap, visibleMap, i, j, sideLenght);
            }
            else if (i >= 0 && i < sideLenght && j >= 0 && j < sideLenght && hiddenMap[i][j] != 'M')
            {
                visibleMap[i][j] = ' ';
            }
        }
    }
}

// this function uses ASCII characters and carefull formatting to render the map
void renderMap(char **hiddenMap, char **visibleMap, int sideLenght, int cursorX, int cursorY)
{
    // for (int j = 0; j < sideLenght; j++)
    // {
    //     printf("+---");
    // }
    // printf("+\n");
    // for (int i = 0; i < sideLenght; i++)
    // {
    //     printf("%2d ", i);
    //     for (int j = 0; j < sideLenght; j++)
    //     {
    //         if (visibleMap[i][j] == '0')
    //         {
    //             printf("|   ");
    //         }
    //         else if (i == cursorX && j == cursorY)
    //         {
    //             printf("| \033[1;31m%c\033[0m ", visibleMap[i][j]);
    //         }
    //         else if (visibleMap[i][j] == ' ')
    //         {
    //             printf("| %c ", hiddenMap[i][j]);
    //         }
    //         else
    //         {
    //             printf("| %c ", visibleMap[i][j]);
    //         }
    //     }
    //     printf("|\n");
    //     printf("   ");
    //     for (int j = 0; j < sideLenght; j++)
    //     {
    //         printf("+---");
    //     }
    //     printf("+\n");
    // }

    // we use ncurses to render the map
    for (int i = 0; i < sideLenght; i++)
    {
        for (int j = 0; j < sideLenght; j++)
        {
            if (visibleMap[i][j] == '0')
            {
                mvprintw(i, j * 4, "   ");
            }
            else if (i == cursorX && j == cursorY)
            {
                attron(A_BOLD);
                mvprintw(i, j * 4, " %c ", visibleMap[i][j]);
                attroff(A_BOLD);
            }
            else if (visibleMap[i][j] == ' ')
            {
                mvprintw(i, j * 4, " %c ", hiddenMap[i][j]);
            }
            else
            {
                mvprintw(i, j * 4, " %c ", visibleMap[i][j]);
            }
        }
    }
    mvprintw(sideLenght, 0, "Use WASD or HJKL to move the cursor, R to reveal, F to toggle the flag, Q to quit");
    refresh();
}

int checkUncovered(char **hiddenMap, char **visibleMap, int x, int y)
{
    if (hiddenMap[x][y] == 'M')
    {
        return 1;
    }
    return 0;
}

// this function generate a map of sideLenght x sideLenght
// without adding the mines yet, it just initializes the map with 0s
char **generateMap(int sideLenght)
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

    return map;
}
