#ifndef HELPERS_H
#define HELPERS_H

int isNumber(char *input);
char *getInput(char message[], char errorMessage[], char defaultValue[], int (*validator)(char *));
void clearTerminal();
char **generateMap(int sideLenght, int numberOfMines);

#endif