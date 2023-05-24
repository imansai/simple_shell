#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"

/**
 * trim - remove whitespace from str
 * @str: str to trim
 * Return: void;
 */

char *trim(char *str)
{
	char *ptr = str;

	while (*ptr == ' ' || *ptr == '\n')
	{
		ptr++;
	}
	str = ptr;
	while (*ptr != '\n')
	{
		ptr++;
	}
	*ptr = '\0';

	ptr--;
	while (*ptr == ' ')
	{
		*ptr = '\0';
		ptr--;
	}
	return (str);
}
