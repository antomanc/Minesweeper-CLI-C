#include "helpers.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int isNumber(char *input)
{
    int length = strlen(input);
    for (int i = 0; i < length; i++)
    {
        if (!isdigit(input[i]))
        {
            return 0;
        }
    }
    return 1;
}