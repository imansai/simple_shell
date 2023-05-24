#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"

/**
 * printenv - prints env
 * @env: env to print
 * Return: void;
 */

void printenv(char **env)
{
    int i = 0;
    while (env[i] != NULL)
        printf("%s\n", env[i++]);
}
