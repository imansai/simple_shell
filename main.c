#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * shell_interactive - starts shell
 *
 * Return: void;
 */
void shell_interactive()
{
	char *line = NULL;
	size_t size = 0;

	printf("($) ");
	getline(&line, &size, stdin);

	printf("%s", line);
	free(line);
}

char **strtokarray(char *str)
{
	char **arr = malloc(sizeof(char *));
	char *token;
	int i = 0;

	if (str == NULL)
		return (NULL);
	token = strtok(str, ":");
	while (token != NULL)
	{
		arr = realloc(arr, (i + 1) * sizeof(char *));
		arr[i] = malloc((strlen(token) + 1) * sizeof(char));
		token = strtok(NULL, ":");
		arr[i++] = token;
	}
	return (arr);
}

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

int main(int ac, char **av)
{
	shell_interactive();
	return (0);
}
