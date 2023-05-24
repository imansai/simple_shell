#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"

/**
 * strtokarray - converts string into array of strings delimited by ":"
 * @str: str to cut with delim ":"
 * Return: void;
 */

char **strtokarray(char *str)
{
	char **arr = malloc(sizeof(char *));
	char *token;
	int i = 0;

	if (str == NULL)
		return (NULL);
	token = strtok(str, " ");

	while (token != NULL)
	{
		arr = realloc(arr, (i + 1) * sizeof(char *));
		arr[i] = malloc((strlen(token) + 1) * sizeof(char));
		arr[i] = token;

		token = strtok(NULL, " ");

		i++;
	}
	arr[i] = NULL;
	return (arr);
}
