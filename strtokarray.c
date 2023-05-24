#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"

/**
 * strtokarray - converts string into array of strings delimited by ":"
 * @str: str to cut with delim ":"
 * @delim : delimiter
 * Return: void;
 */

char **strtokarray(char *str, char *delim)
{
	char **arr = malloc(100 * sizeof(char *));
	char *token;
	int i = 0;

	if (str == NULL)
		return (NULL);
	token = strtok(str, delim);

	while (token != NULL)
	{
		arr[i] = malloc((strlen(token) + 1) * sizeof(char));
		strcpy(arr[i], token);
		token = strtok(NULL, delim);
		i++;
	}

	arr[i] = NULL;
	return (arr);
}
