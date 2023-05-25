#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"

/**
 * _which - finds file in path
 * @str: path to find
 * Return: void;
 */

void _which(char *str)
{
	char *path = getenv("PATH");
	int i = 0;
	char **arr = strtokarray(path, ":");

	printf("%s\n", str);
	while (arr[i] != NULL)
	{
		printf("%s\n", arr[i]);
		i++;
	}
}
