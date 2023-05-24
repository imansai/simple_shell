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
	char **arr = strtokarray(path);

	while (arr[i] != NULL)
	{
		if (strcmp(arr[i++], str) == 0)
		{
			printf("found %s\n", str);
			return;
		}
	}
	printf("couldnt find %s\n", str);
}
