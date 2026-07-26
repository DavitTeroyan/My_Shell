#include <string.h>
#include "parser.h"

void parse(char *line, char **argv)
{
    int i = 0;

    char *token = strtok(line, " \n");

    while (token != NULL)
    {
        argv[i++] = token;
        token = strtok(NULL, " \n");
    }

    argv[i] = NULL;
}
