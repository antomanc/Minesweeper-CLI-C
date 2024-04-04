#ifndef HELPERS_H
#define HELPERS_H

int isNumber(char *input);
char *getInput(char message[], char errorMessage[], char defaultValue[], int (*validator)(char *));
char *getInputV2(char message[], char errorMessage[], char defaultValue[], int (*validator)(char *), int streamOneChar);
void clearTerminal();
char **generateMap(int sideLenght);
void renderMap(char **hiddenMap, char **visibleMap, int sideLenght, int cursorX, int cursorY);
int checkUncovered(char **hiddenMap, char **visibleMap, int x, int y);
void populateMapWithMinesAndNumbers(char **hiddenMap, int x, int y, int sideLenght, int numberOfMines);
void revealZerosAround(char **hiddenMap, char **visibleMap, int x, int y, int sideLenght);
void calculateNumbers(char **map, int sideLenght);
int checkWin(char **hiddenMap, char **visibleMap, int sideLenght, int numberOfMines);

#endif