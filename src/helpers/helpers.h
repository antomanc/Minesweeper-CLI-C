#ifndef HELPERS_H
#define HELPERS_H

int isNumber(char *input);
char *getInput(char message[], char errorMessage[], char defaultValue[], int (*validator)(char *));
void clearTerminal();
char **generateMap(int sideLenght, int numberOfMines);
void renderMap(char **hiddenMap, char **visibleMap, int sideLenght);
int checkUncovered(char **hiddenMap, char **visibleMap, int x, int y);
void makeFirstMove(char **hiddenMap, int x, int y, int sideLenght);
char **revealAround(char **hiddenMap, char **visibleMap, int x, int y, int sideLenght);
void calculateNumbers(char **map, int sideLenght);

#endif